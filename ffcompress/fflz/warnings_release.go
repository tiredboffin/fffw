//go:build ffunpack_release

package fflz

const warningsEnabled = false

// Warn stays assignable for callers but release codecs never invoke it
var Warn = func(string) {}

func warnZeroFill(int)     {}
func warnDroppedToken(int) {}
func warnGuess(string)     {}
