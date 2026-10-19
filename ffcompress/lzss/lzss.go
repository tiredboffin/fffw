/*
Package lzss is the LZSS of Sanyo firmware (LENGTH=, "SANYO burn file"), ported from the
original C code

Copyright 2025 tiredboffin@gmail.com

The stream is described in docs/formats/lzss.md. A flag byte covers the next 8 items, LSB
first, bit 1 is a literal byte and bit 0 a 2-byte match b0 b1 at ring position
b0 | (b1&0xF0)<<4 with length (b1&0x0F)+3. The 4096-byte ring is zero-filled and writing starts
at 4096-18, as in Okumura's LZSS.C but with zeros in place of spaces. There is no header, the
unpacked size comes from the section table or the DFI record.

The encoder tries its best to reproduce the firmware's bytes: greedy longest match, nearest
first and never into the pre-filled ring. PadFF 0xFF bytes are encoded after the data and one
more follows the stream
*/
package lzss

import "fmt"

const (
	ringSize  = 4096
	ringStart = ringSize - 18
	minMatch  = 3
)

// Profile is one encoder's parameters
type Profile struct {
	Name    string
	MaxLen  int // longest match
	MinDist int // nearest match distance
	MaxDist int // farthest match distance
	PadFF   int // 0xFF bytes encoded after the data
	TrailFF int // 0xFF bytes written after the stream
}

var (
	// Lzss18 is for firmware with a linker section table (XA3, XA20, YI-M1)
	Lzss18 = Profile{Name: "lzss18", MaxLen: 18, MinDist: 3, MaxDist: 4077, PadFF: 0, TrailFF: 1}
	// Lzss10 is for the @DFI chunks (XA5, XA7)
	Lzss10 = Profile{Name: "lzss10", MaxLen: 10, MinDist: 11, MaxDist: 4085, PadFF: 8, TrailFF: 1}
)

var Profiles = map[string]Profile{Lzss18.Name: Lzss18, Lzss10.Name: Lzss10}

// Decode returns the first size unpacked bytes, an error if the stream ends before
func Decode(packed []byte, size int) ([]byte, error) {
	var ring [ringSize]byte
	r := ringStart
	out := make([]byte, 0, size+18)
	pos := 0
	for len(out) < size {
		if pos >= len(packed) {
			return nil, fmt.Errorf("stream ends at %#x with %#x of %#x bytes unpacked", pos, len(out), size)
		}
		flags := packed[pos]
		pos++
		for bit := 0; bit < 8 && len(out) < size; bit++ {
			if flags>>bit&1 == 1 {
				if pos >= len(packed) {
					return nil, fmt.Errorf("literal past the end of the stream at %#x", pos)
				}
				c := packed[pos]
				pos++
				ring[r] = c
				r = (r + 1) & (ringSize - 1)
				out = append(out, c)
				continue
			}
			if pos+1 >= len(packed) {
				return nil, fmt.Errorf("match past the end of the stream at %#x", pos)
			}
			j := int(packed[pos]) | int(packed[pos+1]&0xF0)<<4
			n := int(packed[pos+1]&0x0F) + minMatch
			pos += 2
			for k := 0; k < n; k++ {
				c := ring[(j+k)&(ringSize-1)]
				ring[r] = c
				r = (r + 1) & (ringSize - 1)
				out = append(out, c)
			}
		}
	}
	return out[:size], nil
}

const hashBits = 16

func hash3(b []byte) int {
	return (int(b[0])<<8 ^ int(b[1])<<4 ^ int(b[2])) & (1<<hashBits - 1)
}

// Encode packs data as the profile's encoder does
func Encode(data []byte, p Profile) []byte {
	stop := len(data) + p.PadFF
	src := make([]byte, 0, stop+p.MaxLen)
	src = append(src, data...)
	for len(src) < stop+p.MaxLen { // a match may run on past stop into 0xFF
		src = append(src, 0xFF)
	}
	size := len(src)
	head := make([]int32, 1<<hashBits)
	for i := range head {
		head[i] = -1
	}
	prev := make([]int32, size)
	inserted := 0 // positions below this are in the hash chains
	insertUpTo := func(end int) {
		for ; inserted < end; inserted++ {
			if inserted+minMatch <= size {
				h := hash3(src[inserted:])
				prev[inserted] = head[h]
				head[h] = int32(inserted)
			}
		}
	}

	out := make([]byte, 0, size/2+16)
	flagsAt, mask := 0, 0
	for pos := 0; pos < stop; {
		if mask == 0 {
			flagsAt = len(out)
			out = append(out, 0)
			mask = 1
		}
		insertUpTo(pos)
		best, bestDist := 0, 0
		for c := head[hash3(src[pos:])]; c >= 0; c = prev[c] {
			d := pos - int(c)
			if d > p.MaxDist {
				break
			}
			if d < p.MinDist {
				continue
			}
			k := 0
			for k < p.MaxLen && src[pos+k] == src[pos+k-d] {
				k++
			}
			if k >= minMatch && k > best {
				best, bestDist = k, d
				if k == p.MaxLen {
					break
				}
			}
		}
		if best >= minMatch {
			j := (ringStart + pos - bestDist) & (ringSize - 1)
			out = append(out, byte(j), byte(j>>4&0xF0|(best-minMatch)))
			pos += best
		} else {
			out[flagsAt] |= byte(mask)
			out = append(out, src[pos])
			pos++
		}
		mask = mask << 1 & 0xFF
	}
	for ; mask != 0; mask = mask << 1 & 0xFF {
		out[flagsAt] |= byte(mask)
	}
	for i := 0; i < p.TrailFF; i++ {
		out = append(out, 0xFF)
	}
	return out
}
