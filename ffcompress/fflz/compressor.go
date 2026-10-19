//go:build !ffunpack_no_rebuild

package fflz

import (
	"fmt"
	"io"
)

// byteLookupTable keeps the window positions of each byte value in a doubly-linked list, to
// find the longest match closest to the window end, as Fujifilm's greedy packer picks it
type byteLookupTable struct {
	heads [256]int
	prev  [WINDOW_SIZE]int
	next  [WINDOW_SIZE]int
}

func (lut *byteLookupTable) init() {
	for i := range lut.heads {
		lut.heads[i] = NULL
	}
	for i := range lut.next {
		lut.next[i] = NULL
		lut.prev[i] = NULL
	}
}

// indexUpdate puts pos at the head of heads[b], so the search finds the match closest to the
// window end first, as rfind would
func (lut *byteLookupTable) indexUpdate(b byte, pos int) {

	h := lut.heads[b]

	lut.heads[b] = pos
	lut.next[pos] = h
	lut.prev[pos] = NULL
	if h != NULL {
		lut.prev[h] = pos
	}
}

// indexDelete drops tail from heads[b] as it slides out of the window
func (lut *byteLookupTable) indexDelete(b byte, tail int) {
	if lut.heads[b] == tail {
		lut.heads[b] = lut.next[tail] // deleting from the head
		if lut.heads[b] != NULL {
			lut.prev[lut.heads[b]] = NULL
		}
	} else {
		if lut.prev[tail] == NULL {
			return //nothing to delete
		}
		lut.next[lut.prev[tail]] = lut.next[tail]
		if lut.next[tail] != NULL {
			lut.prev[lut.next[tail]] = lut.prev[tail]
		}
	}
}

// lzReader reads the input through a LOOKAHEAD_SIZE lookahead
type lzReader struct {
	buf            [READ_BUF_SIZE]byte
	bufTail        int
	bufHead        int
	lookaheadTail  int
	readBytesCount int
	isEOF          bool

	reader io.Reader
}

func (inp *lzReader) init(rdr io.Reader) {
	inp.reader = rdr
}

// refillLookaheadBuf advances the lookahead by length, refilling buf when fewer than
// LOOKAHEAD_SIZE bytes remain
func (inp *lzReader) refillLookaheadBuf(length int) (err error) {

	newHead := inp.bufHead + length

	spaceLeft := inp.bufTail - newHead
	if spaceLeft < LOOKAHEAD_SIZE && !inp.isEOF {
		for i := range spaceLeft {
			inp.buf[i] = inp.buf[newHead+i]
		}

		var n int
		if n, err = inp.reader.Read(inp.buf[spaceLeft:READ_BUF_SIZE]); err != nil && err != io.EOF {
			return
		}
		inp.readBytesCount += n
		inp.isEOF = err == io.EOF
		newHead = 0
		inp.bufTail = spaceLeft + n

		err = nil //ignore EOF
	}
	inp.bufHead = newHead
	inp.lookaheadTail = min(newHead+LOOKAHEAD_SIZE, inp.bufTail)
	return
}

// lzWriter writes literal and match tokens, keeping the page rules
type lzWriter struct {
	write_buf_total int
	tmp_b           [2]byte
	literal         []byte
	writer          io.Writer
	held            []byte // last token, written when the next comes (see finish)
	heldStart       int    // its packed offset, header included
	heldOut         int    // bytes it unpacks to
}

func (w *lzWriter) init(writer io.Writer) (err error) {
	w.writer = writer
	w.literal = make([]byte, 0, MAX_LITERAL_SIZE+2) //+2 for page alignment logic
	w.held = make([]byte, 0, MAX_LITERAL_SIZE+1)
	return
}

// emit writes the held token and holds this one
func (w *lzWriter) emit(token []byte, out int) (err error) {
	if err = w.writeHeld(); err != nil {
		return
	}
	w.heldStart = w.write_buf_total + HEADER_SIZE
	w.held = append(w.held, token...)
	w.heldOut = out
	w.write_buf_total += len(token)
	return
}

func (w *lzWriter) writeHeld() (err error) {
	if len(w.held) > 0 {
		_, err = w.writer.Write(w.held)
		w.held = w.held[:0]
	}
	return
}

func (w *lzWriter) pageFreeBytes() int {
	return PAGE_SIZE - (w.write_buf_total+HEADER_SIZE)%PAGE_SIZE
}

func (w *lzWriter) writeMatch(pos, len int) (err error) {

	w.tmp_b[0] = byte(0x80 | ((pos >> 4) & 0x7F))
	w.tmp_b[1] = byte(((pos & 0x0F) << 4) | ((len) & 0x0F))
	return w.emit(w.tmp_b[:], len)
}

// writeAndSlideLiteral writes the first length literal bytes, length 0 writes all of it
func (w *lzWriter) writeAndSlideLiteral(length int) (err error) {
	var flash bool
	if length == 0 {
		length = len(w.literal)
		flash = true
	}
	token := append([]byte{byte(length)}, w.literal[:length]...)
	if err = w.emit(token, length); err != nil {
		return
	}
	if flash {
		w.literal = w.literal[:0]
	} else {
		w.literal = w.literal[length:]
	}
	return
}

// flashLiteral writes the literal under the observed page rules, pending means it is deferred
// to take one more byte
func (w *lzWriter) flashLiteral() (pending bool, err error) {

	if len(w.literal) == 0 {
		return
	}

	spaceLeft := w.pageFreeBytes()
	literalLen := len(w.literal)

	if spaceLeft == literalLen+2 {
		// Writing it now would leave 1 byte on the page, defer it to take one more byte ...
		if literalLen == MAX_LITERAL_SIZE {
			// ... unless it is full, then write all but the tail and leave 2 bytes free
			if err = w.writeAndSlideLiteral(spaceLeft - 3); err != nil {
				return
			}
		}
		return true, nil
	}
	if spaceLeft < literalLen+1 {
		// would cross the page, split at the boundary
		if err = w.writeAndSlideLiteral(spaceLeft - 1); err != nil {
			return
		}
		// a full literal keeps its rest pending, as the original packer does
		if literalLen == MAX_LITERAL_SIZE {
			return true, nil
		}
	}
	err = w.writeAndSlideLiteral(0)
	return
}

type compressor struct {
	lzReader
	lzWriter
	byteLookupTable
	ringBuf     [WINDOW_SIZE]byte // the window
	ringTail    int
	dirtyTricks bool // pack unknown stream ends by guess (see unknownEnd)
}

func newCompressor(r io.Reader, w io.Writer) *compressor {
	sw := compressor{}
	sw.init(r, w)
	return &sw
}

func (c *compressor) init(r io.Reader, w io.Writer) {
	c.byteLookupTable.init()
	c.lzReader.init(r)
	c.lzWriter.init(w)
}

// slideWindow moves length bytes from the lookahead into the window
func (c *compressor) slideWindow(length int) (err error) {
	for i := range length {
		tail := c.ringTail
		c.indexDelete(c.ringBuf[tail], tail)
		c.ringBuf[tail] = c.buf[c.bufHead+i]
		c.indexUpdate(c.ringBuf[tail], tail)
		c.ringTail = (c.ringTail + 1) % WINDOW_SIZE
	}
	err = c.refillLookaheadBuf(length)
	return
}

// searchLookaheadBuf returns the longest match of the lookahead in the window, its length and
// its distance from the window end
func (c *compressor) searchLookaheadBuf() (mlen int, matchPos int) {

	node := c.heads[c.buf[c.bufHead]]

	if node == NULL {
		return
	}

	mlen = 1
	mpos := node

	wtail := c.ringTail

	lookahead := c.buf[c.bufHead:c.lookaheadTail]

	for node != NULL && wtail != node {
		l := 1 // lookahead[0] matches by construction
		for l < len(lookahead) {
			m := (node + l) % WINDOW_SIZE
			if m == wtail || lookahead[l] != c.ringBuf[m] {
				break
			}
			l++
		}
		if l > mlen {
			mlen = l
			mpos = node
			if mlen == len(lookahead) {
				break
			}
		}
		node = c.next[node]
	}
	return mlen, (WINDOW_SIZE + wtail - mpos) % WINDOW_SIZE

}

// finish writes the last token, unless it is a 2-byte zero copy alone on a new page: the
// original packer drops that (in one sample only) and hence the unpacker restores the zeros.
// Any other last token alone on a new page is still an unknown end
func (c *compressor) finish() (err error) {
	if len(c.held) > 0 && c.heldStart%PAGE_SIZE == 0 {
		kind := "literal"
		if c.held[0]&0x80 != 0 {
			kind = "copy"
		}
		at := c.readBytesCount - c.heldOut
		if !c.lastBytesZero(c.heldOut) {
			if err = c.unknownEnd(fmt.Sprintf("a %s of %d bytes at %#x alone on a new page", kind, c.heldOut, at)); err != nil {
				return
			}
			return c.writeHeld()
		}
		if kind != "copy" || c.heldOut != 2 {
			if err = c.unknownEnd(fmt.Sprintf("an all-zero %s of %d bytes at %#x alone on a new page", kind, c.heldOut, at)); err != nil {
				return
			}
		}
		c.write_buf_total -= len(c.held)
		c.held = c.held[:0]
		warnDroppedToken(c.heldOut)
		return
	}
	return c.writeHeld()
}

// unknownEnd reports an unknown stream end as an error by default, dirtyTricks can override it
// into a warning and the caller packs the end by guess
func (c *compressor) unknownEnd(what string) error {
	if !c.dirtyTricks {
		return fmt.Errorf("LZ pack: the data ends with %s; no firmware sample shows how the original packer "+
			"ends such a stream (--dirty-tricks packs it by guess, #275)", what)
	}
	warnGuess(what)
	return nil
}

// lastBytesZero tells whether the window's last n bytes are zero
func (c *compressor) lastBytesZero(n int) bool {
	for i := 1; i <= n; i++ {
		if c.ringBuf[(WINDOW_SIZE+c.ringTail-i)%WINDOW_SIZE] != 0 {
			return false
		}
	}
	return true
}

func (c *compressor) outputMatch(matchPos int, matchLen int) (err error) {
	unmatchedBytes := 0
	switch c.pageFreeBytes() {
	case 3:
		unmatchedBytes = 2
	case 4:
		unmatchedBytes = 1
	case 0, 1:
		panic("Logic check: fewer than 2 bytes of free space left on the page")
	}
	if unmatchedBytes != 0 {
		// 3 or 4 bytes left on the page, the match's first bytes go out as a literal
		wpos := (WINDOW_SIZE + c.ringTail - matchPos) % WINDOW_SIZE
		for i := range unmatchedBytes {
			c.literal = append(c.literal, c.ringBuf[(wpos+i)%WINDOW_SIZE])
		}
		_, err = c.flashLiteral()
		if err != nil {
			return
		}
	}
	return c.writeMatch(matchPos, matchLen-unmatchedBytes)
}
