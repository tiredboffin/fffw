package main

import (
	"fmt"
	"os"

	"ffun/internal/cli"
)

func main() {
	args := os.Args
	if len(args) < 2 || args[1] == "--help" || args[1] == "help" {
		fmt.Println("Usage: ffun <command> [args...]\n")
		fmt.Println("Available commands:")
		for help := range cli.HelpText {
			fmt.Println("  ", help)
		}
		os.Exit(0)
	}

	cmd := args[1]
	run, ok := cli.Registry[cmd]
	if !ok {
		fmt.Fprintf(os.Stderr, "Unknown command: %s\n", cmd)
		os.Exit(1)
	}
	run(args[2:], cli.AssetsFS)
}
