package ffcompress

/*
   ffcompress – Example usage of the fflz package and also serves as a test tool.

*/

import (
	"bufio"
	"bytes"
	"crypto/md5"
	"encoding/binary"
	"fmt"
	"io"
	"os"
	"ffun/internal/fflz"
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

func Help () (string) {
	return `<c|u|r> <input-file> <output-file>
       c - compress
       u - uncompress
       t - test (repack orginal compressed segment with md5 sum validation)`
}

func usage() {
	fmt.Println("Usage: ffcompress", Help())
	os.Exit(1)
}

func Run(args []string) {
	if len(args) < 3 {
		usage()
	}

	cmd := args[1]
	inFile := args[2]

	switch cmd {
	case "c":
		if len(args) != 4 {
			usage()
		}
		outFile := args[3]
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
		if len(args) != 4 {
			usage()
		}
		outFile := args[3]
		fmt.Printf("Uncompress: %s -> %s\n", inFile, outFile)
		hdr, err := fflz.Unpack(inFile, outFile)
		if err != nil {
			fmt.Printf("Error: %s\n", err)
			os.Exit(1)
		}
		fmt.Printf("Uncompressed %d bytes from %d\n", hdr.UnpackedSize, hdr.PackedSize)
	case "t":

		var outFile string

		if len(args) == 4 {
			outFile = args[3]
		} else if len(args) != 3 {
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

func Name() string { return "ffcompress" }

