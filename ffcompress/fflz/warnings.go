//go:build !ffunpack_release

package fflz

import (
	"fmt"
	"os"
)

const warningsEnabled = true

// Warn reports page-boundary corner cases, by default on stderr, callers may replace it
var Warn = func(msg string) { fmt.Fprintf(os.Stderr, "warning: %s\n", msg) }

func warnZeroFill(short int) {
	Warn(fmt.Sprintf("LZ stream ends at a page boundary and is %d bytes short of the unpacked size; zero-filled", short))
}

func warnGuess(what string) {
	Warn(fmt.Sprintf("the data ends with %s: not seen in any firmware, packed by guess (--dirty-tricks, #275)", what))
}

func warnDroppedToken(size int) {
	Warn(fmt.Sprintf("final all-zero token (%d bytes) dropped at a page boundary to match the original packer", size))
}
