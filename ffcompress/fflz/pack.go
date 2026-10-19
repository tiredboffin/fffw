//go:build !ffunpack_no_rebuild

package fflz

import (
	"fmt"
	"io"
)

// PackIO writes reader's data as tokens to writer and returns the header. By default an unknown
// stream end is an error, with dirtyTricks it is packed by guess with a warning
func PackIO(reader io.Reader, writer io.Writer, dirtyTricks bool) (hdr PackedHeader, err error) {
	c := newCompressor(reader, writer)
	if c == nil {
		panic(nil)
	}
	c.init(reader, writer)
	c.dirtyTricks = dirtyTricks
	var matchLen, matchPos int
	for {
		if err = c.slideWindow(matchLen); err != nil {
			return
		}
		if c.lookaheadTail == c.bufHead {
			break
		}
		b := c.buf[c.bufHead]
		matchLen, matchPos = c.searchLookaheadBuf()
		if matchLen < MIN_MATCH_LEN {
			c.literal = append(c.literal, b)
			if len(c.literal) == MAX_LITERAL_SIZE {
				if _, err = c.flashLiteral(); err != nil {
					return
				}
			}
			matchLen = 1
		} else {
			// a pending literal takes this byte, the match waits
			var literalPending bool
			literalPending, err = c.flashLiteral()
			if err != nil {
				return
			}
			if literalPending {
				c.literal = append(c.literal, b)
				matchLen = 1
			} else {
				err = c.outputMatch(matchPos, matchLen)
				if err != nil {
					return
				}
			}
		}
	}
	if len(c.literal) > 0 {
		// A final literal that would cross a page or leave 1 byte on it is an unknown end. By guess
		// the first is split at the boundary as mid-stream and the second is written whole
		n, free := len(c.literal), c.pageFreeBytes()
		switch {
		case free < n+1:
			err = c.unknownEnd(fmt.Sprintf("a literal of %d bytes at %#x that would cross a page boundary", n, c.readBytesCount-n))
		case free == n+2:
			err = c.unknownEnd(fmt.Sprintf("a literal of %d bytes at %#x that would leave 1 byte on its page", n, c.readBytesCount-n))
		}
		if err != nil {
			return
		}
		var pending bool
		if pending, err = c.flashLiteral(); err != nil {
			return
		}
		if pending {
			// no byte follows at EOF, write the deferred literal
			if err = c.writeAndSlideLiteral(0); err != nil {
				return
			}
		}
	}
	if err = c.finish(); err != nil {
		return
	}
	sizePacked := c.write_buf_total + HEADER_SIZE
	hdr = PackedHeader{
		UnpackedSize: uint32(c.readBytesCount), PackedSize: uint32(sizePacked),
		NumPages: numPages(uint32(sizePacked)), PageSize: PAGE_SIZE, Alignment: 0x04,
	}
	return
}
