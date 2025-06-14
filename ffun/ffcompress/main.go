package main

/*
  ffcompress – Basic implementation of the Fujifilm LZ compression algorithm, part of the ffun toolkit.

  Notes:

  - This reversed algorithm is based solely on analysis of DAT file samples and may not be a fully accurate
    reconstruction of the original hardware implementation. However, it has been tested by decompressing original
    data, then recompressing it across many images, and the output matches the originals bit-for-bit.

  - The packer is probably more complex than necessary. It’s engineered to reproduce the original compressed data
    exactly, even though the hardware decompressor is likely more forgiving.

    For example, the original (unknown) compressor seems to avoid crossing 16K page boundaries.
    Whether this is actually required by hardware is still unverified. For now, the focus is on generating
    byte-for-byte identical output, rather than maximizing compression efficiency or simplifying the code.
    The software decompressor code doesn’t care about these page-boundary quirks.

  - This code was translated from a quick and simple Python script I wrote as a proof of concept,
    then reworked in Go as a way to learn the language. It still carries a lot of C-style structure and
    assumptions. There's definitely room for cleanup and improvement.
*/

import (
	"bufio"
	"bytes"
	"crypto/md5"
	"encoding/binary"
	"ffcompress/fflz"
	"fmt"
	"io"
	"os"
)

// Repack original compressed firmware segment and compare it with the original
func TestInMem(fnIn string, fnOut string) (err error) {
	// Create a temporary file in the default temp directory
	var hdr fflz.PackedHeader

	var unpackedBuf bytes.Buffer
	var packedBuf bytes.Buffer

	inp, err := os.Open(fnIn)
	if err != nil {
		return
	}
	defer inp.Close()
	reader := bufio.NewReader(inp)

	hdr, err = fflz.UnpackIO(reader, &unpackedBuf)

	if err != nil {
		fmt.Printf("Error: %s\n", err)
		os.Exit(1)
	}

	hdr, err = fflz.PackIO(&unpackedBuf, &packedBuf)
	if err != nil {
		fmt.Printf("Error: %s\n", err)
		os.Exit(1)
	}
	hasher := md5.New()
	f, _ := os.Open(fnIn)
	io.Copy(hasher, io.LimitReader(f, int64(hdr.PackedSize)))
	f.Close()
	sumIn := hasher.Sum(nil)

	hasher.Reset()
	binary.Write(hasher, binary.LittleEndian, hdr)
	io.Copy(hasher, &packedBuf)
	sumOut := hasher.Sum(nil)

	if bytes.Equal(sumIn, sumOut) {
	} else {
		err = fmt.Errorf("%x != %x", sumIn, sumOut)
	}
	if fnOut != "" {
		err := os.WriteFile(fnOut, packedBuf.Bytes(), os.FileMode(os.O_CREATE))
		if err != nil {
			fmt.Printf("Error: %s\n", err)
			os.Exit(1)
		}
	}
	return
}

// Repack original compressed firmware segment and compare it with the original
func Test(fnIn string, fnOut string) (err error) {
	// Create a temporary file in the default temp directory
	var hdr fflz.PackedHeader

	tmpFile, err := os.CreateTemp("", "ffr-*.tmp")
	if err != nil {
		fmt.Printf("Error: %s\n", err)
		os.Exit(1)
	}
	defer os.Remove(tmpFile.Name())

	hdr, err = fflz.Unpack(fnIn, tmpFile.Name())
	if err != nil {
		fmt.Printf("Error: %s\n", err)
		os.Exit(1)
	}

	if fnOut == "" {
		tmpFile, err := os.CreateTemp("", "myapp-*.tmp")
		if err != nil {
			fmt.Printf("Error: %s\n", err)
			os.Exit(1)
		}
		defer os.Remove(tmpFile.Name())
		fnOut = tmpFile.Name()
	}
	_, err = fflz.Pack(tmpFile.Name(), fnOut)
	if err != nil {
		fmt.Printf("Error: %s\n", err)
		os.Exit(1)
	}

	hasher := md5.New()
	f, _ := os.Open(fnIn)
	io.Copy(hasher, io.LimitReader(f, int64(hdr.PackedSize)))
	f.Close()
	sumIn := hasher.Sum(nil)

	hasher.Reset()
	f, _ = os.Open(fnOut)
	io.Copy(hasher, f)
	f.Close()
	sumOut := hasher.Sum(nil)

	if bytes.Equal(sumIn, sumOut) {
	} else {
		err = fmt.Errorf("%x != %x", sumIn, sumOut)
	}
	return
}

func usage() {
	fmt.Println("Usage: ffcompress <c|u|r> <input-file> <output-file>")
	fmt.Println("  c - compress")
	fmt.Println("  u - uncompress")
	fmt.Println("  t - test (repack orginal compressed segment with md5 sum validation)")
	os.Exit(1)
}

func main() {
	if len(os.Args) < 3 {
		usage()
	}

	cmd := os.Args[1]
	inFile := os.Args[2]

	switch cmd {
	case "c":
		if len(os.Args) != 4 {
			usage()
		}
		outFile := os.Args[3]
		if inFile == outFile {
			usage()
		}
		fmt.Printf("Compress: %s -> %s\n", inFile, outFile)
		hdr, err := fflz.Pack(inFile, outFile)
		if err != nil {
			fmt.Printf("Error: %s\n", err)
			os.Exit(1)
		}
		fmt.Printf("Compressed %d bytes to %d\n", hdr.UnpackedSize, hdr.PackedSize)
	case "u":
		if len(os.Args) != 4 {
			usage()
		}
		outFile := os.Args[3]
		fmt.Printf("Uncompress: %s -> %s\n", inFile, outFile)
		hdr, err := fflz.Unpack(inFile, outFile)
		if err != nil {
			fmt.Printf("Error: %s\n", err)
			os.Exit(1)
		}
		fmt.Printf("Uncompressed %d bytes from %d\n", hdr.UnpackedSize, hdr.PackedSize)
	case "t":

		var outFile string

		if len(os.Args) == 4 {
			outFile = os.Args[3]
		} else if len(os.Args) != 3 {
			usage()
		}
		err := Test(inFile, outFile)
		if err != nil {
			fmt.Printf("%s TEST FALIED: %s\n", inFile, err)
		} else {
			fmt.Printf("%s TESTOK\n", inFile)
		}

	default:
		usage()
	}
}
