package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	manifest := ".gengenerated"
	file, err := os.Open(manifest)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Warning: %v\n", err)
		os.Exit(0)
	}
	defer file.Close()

	deletedDirs := map[string]bool{}
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		path := scanner.Text()
		path = filepath.Clean(path)
		if path == "" {
			continue
		}

		err := os.Remove(path)
		if err == nil {
			fmt.Println("Deleted file:", path)
			deletedDirs[filepath.Dir(path)] = true
		} else if !os.IsNotExist(err) {
			fmt.Fprintf(os.Stderr, "Failed to delete %s: %v\n", path, err)
		}
	}

	// Now remove empty dirs
	for dir := range deletedDirs {
		entries, err := os.ReadDir(dir)
		if err != nil {
			continue
		}
		if len(entries) == 0 {
			err := os.Remove(dir)
			if err == nil {
				fmt.Println("Removed empty dir:", dir)
			}
		}
	}

	// Delete manifest itself
	_ = os.Remove(manifest)
}
