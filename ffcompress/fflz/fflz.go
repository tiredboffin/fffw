/*
Package fflz is the Fujifilm firmware image LZ compressor and decompressor

Copyright 2024-2025 tiredboffin@gmail.com

The hardware decompressor works on 16K pages, so no token may cross a page boundary. The packer
tries its best to reproduce the original (unknown) packer bit for bit. See README.md for the
background.

This code was translated from a quick Python proof-of-concept script and then reworked in Go as
an excuse to learn the language. The result still carries a lot of C-style or even F77-style
structure and assumptions, I'd honestly be shocked if it couldn't be improved
*/
package fflz

import (
	"fmt"
	"io"
)

type PackedHeader struct {
	UnpackedSize uint32
	PackedSize   uint32
	NumPages     uint32
	PageSize     uint32
	Alignment    uint32
}

func assert(cond bool, txt string) {
	if !cond {
		panic(txt)
	}
}

const (
	HEADER_SIZE      = 20
	MIN_MATCH_LEN    = 3
	MAX_LITERAL_SIZE = 127
	LOOKAHEAD_SIZE   = 15
	WINDOW_SIZE      = 2048
	WINDOW_MASK      = (WINDOW_SIZE - 1)
	PAGE_SIZE        = 16384
	READ_BUF_SIZE    = WINDOW_SIZE * 16
	NULL             = -1
)

// numPages is the header's page count, ceil(packed size / PAGE_SIZE) with the header included
func numPages(size uint32) uint32 {
	return (size + PAGE_SIZE - 1) / PAGE_SIZE
}

func UnpackIO(reader io.Reader, writer io.Writer) (hdr PackedHeader, err error) {

	unpackBuffer := newDecompressor(reader, writer)

	if err = unpackBuffer.init(); err != nil {
		return
	}

	compressedSize := int(unpackBuffer.hdr.PackedSize)

	var offset, length int

	for unpackBuffer.readCount < compressedSize {
		offset, length, err = unpackBuffer.nextItempPosLen()
		if err != nil {
			return
		}

		err = unpackBuffer.copyItem(offset, length)
		if err != nil {
			return
		}
	}

	short := int(unpackBuffer.hdr.UnpackedSize) - unpackBuffer.writtenCount
	if short > 0 && short <= MAX_LITERAL_SIZE && unpackBuffer.readCount == compressedSize && compressedSize%PAGE_SIZE == 0 {
		// Ends at a page boundary one token short, the original packer dropped a final all-zero
		// token that would have started a new page, so restore the zeros
		if _, err = writer.Write(make([]byte, short)); err != nil {
			return
		}
		unpackBuffer.writtenCount += short
		warnZeroFill(short)
	}

	if unpackBuffer.writtenCount != int(unpackBuffer.hdr.UnpackedSize) {
		err = fmt.Errorf("unpacked file size mismatch: expected %d got %d", unpackBuffer.hdr.UnpackedSize, unpackBuffer.writtenCount)
		return hdr, err
	}
	return unpackBuffer.hdr, nil
}
