/* Wrap ffun commands in a single executable. */

package main

import (
	"ffun/internal/cli"
	"ffun/internal/pycheck"
	"fmt"
	"os"
)

func main() {
	pythonAvailable := pycheck.IsAvailable()
	args := os.Args
	if len(args) < 2 || args[1] == "--help" || args[1] == "help" {
		fmt.Println("Usage: ffun <command> [args...]")
		fmt.Println("Commands:")
		for cmd_name := range cli.Registry {
			fmt.Println("  ", cmd_name)
		}
		if !pythonAvailable {
			fmt.Println("Warning: some commands still rely on python3.")
		}
		os.Exit(0)
	}
	cmd_name := args[1]
	cmd, ok := cli.Registry[cmd_name]
	if !ok {
		fmt.Fprintf(os.Stderr, "Unknown command: %s\n", cmd_name)
		os.Exit(1)
	}
	if !cmd.IsAvailable() {
		fmt.Fprintf(os.Stderr, "Command needs python3: %s\n", cmd_name)
	}
	cmd.Run(args[2:], cli.AssetsFS)
}
