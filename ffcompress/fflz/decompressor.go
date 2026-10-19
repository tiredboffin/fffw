package fflz

import (
	"encoding/binary"
	"fmt"
	"io"
)

type decompressor struct {
	hdr          PackedHeader
	r            io.Reader
	w            io.Writer
	buf          []byte
	epos         int
	tmp_b        []byte
	readCount    int
	writtenCount int
}

func validateHeader(hdr *PackedHeader) bool {
	usize := hdr.UnpackedSize
	csize := hdr.PackedSize
	return (csize != 0 && usize != 0 && csize < usize && hdr.PageSize == PAGE_SIZE && numPages(csize) == hdr.NumPages && hdr.Alignment == 4)
}

func newDecompressor(r io.Reader, w io.Writer) *decompressor {
	return &decompressor{
		r:     r,
		w:     w,
		buf:   make([]byte, READ_BUF_SIZE),
		tmp_b: make([]byte, 1),
	}
}

func (hw *decompressor) init() (err error) {

	if err = binary.Read(hw.r, binary.LittleEndian, &hw.hdr); err != nil {
		err = fmt.Errorf("error reading header %s", err)
		return
	}
	hw.readCount += HEADER_SIZE
	if !validateHeader(&hw.hdr) {
		err = fmt.Errorf("invalid file header")
	}
	return
}

// nextItempPosLen reads a token, offset is 0 for a literal and the distance for a match
func (hw *decompressor) nextItempPosLen() (offset int, length int, err error) {

	if _, err = hw.r.Read(hw.tmp_b); err != nil {
		return
	}
	hw.readCount++
	b0 := hw.tmp_b[0]
	if b0&0x80 == 0 {
		length = int(b0)
		offset = 0
	} else {
		if _, err = hw.r.Read(hw.tmp_b); err != nil {
			return
		}
		hw.readCount++
		b1 := hw.tmp_b[0]
		length = int(b1 & 0x0f)
		offset = (int(b0&0x7f)<<4 | int(b1>>4)) & WINDOW_MASK
		assert(length <= offset && length != 0, "len == 0 or len > offset")
	}
	return
}

// copyItem writes length bytes, a literal from the input or with offset > 0 a match from the
// output
func (hw *decompressor) copyItem(offset int, length int) (err error) {
	if hw.epos > READ_BUF_SIZE-length {
		copy(hw.buf[:], hw.buf[hw.epos-WINDOW_SIZE:hw.epos])
		hw.epos = WINDOW_SIZE
	}
	if offset > 0 {
		copy(hw.buf[hw.epos:hw.epos+length], hw.buf[hw.epos-offset:hw.epos-offset+length])
	} else {
		var bytesRead int
		if bytesRead, err = io.ReadFull(hw.r, hw.buf[hw.epos:hw.epos+length]); err != nil {
			return
		}
		hw.readCount += bytesRead
	}
	n, err := hw.w.Write(hw.buf[hw.epos : hw.epos+length])
	hw.writtenCount += n
	hw.epos += length
	return
}
