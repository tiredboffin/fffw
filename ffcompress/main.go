/*
ffcompress packs and unpacks fflz and LZSS, it also repacks original segments as a test

Copyright 2024-2025 tiredboffin@gmail.com

IN and OUT are files or "-" for stdin and stdout, with OUT "-" the messages go to stderr.
Everything is done in memory
*/
package main

import (
	"bytes"
	"encoding/binary"
	"ffcompress/fflz"
	"ffcompress/lzss"
	"flag"
	"fmt"
	"io"
	"os"
	"strconv"
)

// packFFLZ packs data with the header first, dirtyTricks packs unknown stream ends by guess
func packFFLZ(data []byte, dirtyTricks bool) ([]byte, fflz.PackedHeader, error) {
	var body bytes.Buffer
	hdr, err := fflz.PackIO(bytes.NewReader(data), &body, dirtyTricks)
	if err != nil {
		return nil, hdr, err
	}
	var out bytes.Buffer
	binary.Write(&out, binary.LittleEndian, hdr)
	out.Write(body.Bytes())
	return out.Bytes(), hdr, nil
}

// unpackFFLZ unpacks a segment, header first
func unpackFFLZ(packed []byte) ([]byte, fflz.PackedHeader, error) {
	if len(packed) < fflz.HEADER_SIZE {
		return nil, fflz.PackedHeader{}, fmt.Errorf("invalid input file")
	}
	var out bytes.Buffer
	hdr, err := fflz.UnpackIO(bytes.NewReader(packed), &out)
	return out.Bytes(), hdr, err
}

// testFFLZ repacks an original segment, an error unless the result is a prefix of the input
func testFFLZ(in []byte) ([]byte, error) {
	data, _, err := unpackFFLZ(in)
	if err != nil {
		return nil, err
	}
	again, _, err := packFFLZ(data, false)
	if err != nil {
		return nil, err
	}
	if len(in) < len(again) || !bytes.Equal(in[:len(again)], again) {
		return again, fmt.Errorf("%d bytes repacked to %d, first difference at %#x", len(in), len(again), firstDifference(in, again))
	}
	return again, nil
}

// testLzss repacks a Sanyo LZSS stream, an error unless the result equals it
func testLzss(in []byte, p lzss.Profile, size int) ([]byte, error) {
	data, err := lzss.Decode(in, size)
	if err != nil {
		return nil, err
	}
	again := lzss.Encode(data, p)
	if !bytes.Equal(in, again) {
		return again, fmt.Errorf("%d bytes repacked to %d, first difference at %#x", len(in), len(again), firstDifference(in, again))
	}
	return again, nil
}

func firstDifference(a, b []byte) int {
	at := 0
	for at < len(a) && at < len(b) && a[at] == b[at] {
		at++
	}
	return at
}

func usage(w io.Writer) {
	fmt.Fprintln(w, "Usage: ffcompress [-codec fflz|lzss18|lzss10] [-size N] [-fill N] [-dirty-tricks] <c|u|t> <input-file> [<output-file>]")
	fmt.Fprintln(w, "  c - compress")
	fmt.Fprintln(w, "  u - uncompress")
	fmt.Fprintln(w, "  t - test (repack original compressed segment and compare)")
	fmt.Fprintln(w, "  -       as the input or output file: stdin or stdout (the messages then go to stderr)")
	fmt.Fprintln(w, "  -codec  fflz (default), or the Sanyo LZSS lzss18 or lzss10")
	fmt.Fprintln(w, "  -size   the unpacked size (decimal or 0x hex), required by u and t with lzss18/lzss10")
	fmt.Fprintln(w, "  -fill   with lzss18/lzss10: the 0xFF bytes encoded after the data, in place of the profile's")
	fmt.Fprintln(w, "  -dirty-tricks  with c and fflz: pack an unknown stream end by guess with a warning")
}

func main() {
	os.Exit(run(os.Args[1:], os.Stdin, os.Stdout, os.Stderr))
}

// run returns the exit status
func run(argv []string, stdin io.Reader, stdout, stderr io.Writer) int {
	flags := flag.NewFlagSet("ffcompress", flag.ContinueOnError)
	flags.SetOutput(stderr)
	flags.Usage = func() { usage(stdout) }
	codec := flags.String("codec", "fflz", "")
	sizeText := flags.String("size", "", "")
	fill := flags.Int("fill", -1, "")
	dirtyTricks := flags.Bool("dirty-tricks", false, "")
	if flags.Parse(argv) != nil {
		return 1
	}
	args := flags.Args()
	if len(args) < 2 || len(args) > 3 || (len(args) == 2 && args[0] != "t") {
		usage(stdout)
		return 1
	}
	cmd, inFile, outFile := args[0], args[1], ""
	if len(args) == 3 {
		outFile = args[2]
	}
	if outFile == inFile && inFile != "-" {
		usage(stdout)
		return 1
	}
	msg := stdout // stderr when stdout carries the data
	if outFile == "-" {
		msg = stderr
	}

	var p lzss.Profile
	size := 0
	if *codec != "fflz" {
		var ok bool
		if p, ok = lzss.Profiles[*codec]; !ok {
			usage(stdout)
			return 1
		}
		if *fill >= 0 {
			p.PadFF = *fill
		}
		if cmd != "c" {
			n, err := strconv.ParseInt(*sizeText, 0, 64)
			if err != nil || n < 0 {
				fmt.Fprintf(msg, "Error: -size %q: an unpacked size is required\n", *sizeText)
				return 1
			}
			size = int(n)
		}
	}
	if cmd != "c" && cmd != "u" && cmd != "t" {
		usage(stdout)
		return 1
	}

	var in []byte
	var err error
	if inFile == "-" {
		in, err = io.ReadAll(stdin)
	} else {
		in, err = os.ReadFile(inFile)
	}
	if err != nil {
		fmt.Fprintf(msg, "Error: %s\n", err)
		return 1
	}
	write := func(data []byte) error {
		if outFile == "-" {
			_, err := stdout.Write(data)
			return err
		}
		return os.WriteFile(outFile, data, 0o644)
	}

	if cmd == "t" {
		var again []byte
		if *codec == "fflz" {
			again, err = testFFLZ(in)
		} else {
			again, err = testLzss(in, p, size)
		}
		if again != nil && outFile != "" { // also when they differ
			if werr := write(again); werr != nil {
				fmt.Fprintf(msg, "Error: %s\n", werr)
				return 1
			}
		}
		if err != nil {
			fmt.Fprintf(msg, "%s TEST FAILED: %s\n", inFile, err)
			return 1
		}
		fmt.Fprintf(msg, "%s TESTOK\n", inFile)
		return 0
	}

	var out []byte
	switch {
	case cmd == "c" && *codec == "fflz":
		fmt.Fprintf(msg, "Compress: %s -> %s\n", inFile, outFile)
		var hdr fflz.PackedHeader
		if out, hdr, err = packFFLZ(in, *dirtyTricks); err == nil {
			fmt.Fprintf(msg, "Compressed %d bytes to %d\n", hdr.UnpackedSize, hdr.PackedSize)
		}
	case cmd == "u" && *codec == "fflz":
		fmt.Fprintf(msg, "Uncompress: %s -> %s\n", inFile, outFile)
		var hdr fflz.PackedHeader
		if out, hdr, err = unpackFFLZ(in); err == nil {
			fmt.Fprintf(msg, "Uncompressed %d bytes from %d\n", hdr.UnpackedSize, hdr.PackedSize)
		}
	case cmd == "c":
		out = lzss.Encode(in, p)
		fmt.Fprintf(msg, "Compressed %d bytes to %d\n", len(in), len(out))
	default:
		if out, err = lzss.Decode(in, size); err == nil {
			fmt.Fprintf(msg, "Uncompressed %d bytes from %d\n", len(out), len(in))
		}
	}
	if err == nil {
		err = write(out)
	}
	if err != nil {
		fmt.Fprintf(msg, "Error: %s\n", err)
		return 1
	}
	return 0
}
