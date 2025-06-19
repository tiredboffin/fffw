package ffindex

//translated from ffindex.py to learn a bit of Go

import (
	"crypto/sha1"
	"embed"
	"encoding/hex"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"gopkg.in/yaml.v3"
)

const indexFile = "ffindex.yaml"
const shortHashLen = 7

type Index map[string]string // filename -> hash

var (
	verboseLevel   int
	lastPrintedLen = 0
)

func println(a ...interface{}) {
	if verboseLevel != 0 {
		fmt.Println(a...)
	}
}

func printf(format string, a ...interface{}) {
	if verboseLevel != 0 {
		fmt.Printf(format, a...)
	}
}

func hashFile(path string) (string, error) {
	f, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer f.Close()

	h := sha1.New()
	info, _ := f.Stat()
	fmt.Fprintf(h, "blob %d\u0000", info.Size())
	if _, err := io.Copy(h, f); err != nil {
		return "", err
	}
	return hex.EncodeToString(h.Sum(nil)), nil
}

func loadIndex() (Index, error) {
	data, err := os.ReadFile(indexFile)
	if err != nil {
		if os.IsNotExist(err) {
			return Index{}, nil
		}
		return nil, err
	}
	var idx Index
	err = yaml.Unmarshal(data, &idx)
	return idx, err
}

func saveIndex(idx Index) error {
	var sb strings.Builder
	keys := make([]string, 0, len(idx))
	for k := range idx {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	for _, k := range keys {
		fmt.Fprintf(&sb, "%s: %s\n", k, idx[k])
	}
	return os.WriteFile(indexFile, []byte(sb.String()), 0644)
}

func findDATFiles() ([]string, error) {
	var files []string
	err := filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
		if err == nil && !info.IsDir() && filepath.Ext(path) == ".DAT" {
			files = append(files, path)
		}
		return nil
	})
	return files, err
}

func buildIndex() error {
	files, err := findDATFiles()
	if err != nil {
		return err
	}
	idx := Index{}
	total := len(files)
	for i, file := range files {
		printProgress("[%d/%d] %s", i+1, total, file)
		hash, err := hashFile(file)
		if err != nil {
			fmt.Fprintf(os.Stderr, "\nwarning: cannot hash %s: %v\n", file, err)
			continue
		}
		idx[file] = hash
	}
	println()
	reportDuplicates(idx, nil)
	return saveIndex(idx)
}

func addToIndex() error {
	idx, err := loadIndex()
	if err != nil {
		return err
	}
	files, err := findDATFiles()
	if err != nil {
		return err
	}
	total := len(files)
	updated := false
	added := []string{}

	for i, file := range files {
		if _, exists := idx[file]; exists {
			continue
		}
		printProgress("[%d/%d] %s", i+1, total, file)
		hash, err := hashFile(file)
		if err != nil {
			fmt.Fprintf(os.Stderr, "\nwarning: cannot hash %s: %v\n", file, err)
			continue
		}
		idx[file] = hash
		added = append(added, file)
		updated = true
	}
	println()
	reportDuplicates(idx, added)
	if updated {
		return saveIndex(idx)
	}
	return nil
}

func printProgress(format string, args ...interface{}) {
	if verboseLevel < 2 {
		return
	}
	msg := fmt.Sprintf(format, args...)
	padding := ""
	if lastPrintedLen > len(msg) {
		padding = strings.Repeat(" ", lastPrintedLen-len(msg))
	}
	fmt.Printf("\r%s%s", msg, padding)
	lastPrintedLen = len(msg)
}

func formatHash(hash string, full bool) string {
	if full {
		return hash
	}
	return hash[:shortHashLen]
}

func reportDuplicates(idx Index, added []string) {
	if verboseLevel < 1 {
		return
	}

	reverse := make(map[string][]string)
	for file, hash := range idx {
		reverse[hash] = append(reverse[hash], file)
	}

	dupes := 0
	addedSet := make(map[string]bool)
	for _, f := range added {
		addedSet[f] = true
	}

	for hash, files := range reverse {
		if len(files) <= 1 {
			continue
		}

		report := false
		if added == nil {
			// reindex mode: report all duplicates
			report = true
		} else {
			// update mode: report dups only if new file involved
			for _, f := range files {
				if addedSet[f] {
					report = true
					break
				}
			}
		}

		if report {
			printf("Duplicate hash %s:\n", hash)
			for _, f := range files {
				printf("  %s\n", f)
			}
			dupes++
		}
	}

	if dupes != 0 {
		printf("%d duplicate hashes found.\n", dupes)
	}
}

func searchByHashPrefix(prefix string, full bool) error {
	idx, err := loadIndex()
	if err != nil {
		return err
	}
	keys := make([]string, 0)
	for file, hash := range idx {
		if strings.HasPrefix(hash, prefix) {
			keys = append(keys, file)
		}
	}
	sort.Strings(keys)
	for _, file := range keys {
		fmt.Printf("%s %s\n", formatHash(idx[file], full), file)
	}
	return nil
}

func searchByNamePrefix(prefix string, full bool) error {
	idx, err := loadIndex()
	if err != nil {
		return err
	}
	results := make([]string, 0)
	for file := range idx {
		if strings.HasPrefix(strings.ToLower(filepath.Base(file)), strings.ToLower(prefix)) {
			results = append(results, file)
		}
	}
	sort.Strings(results)
	for _, file := range results {
		fmt.Printf("%s %s\n", formatHash(idx[file], full), file)
	}
	return nil
}

func Help() string {
	return "[build|add|by-hash <prefix>|by-name <prefix>] [--fullhash]"
}

func Run(args []string, _ embed.FS) {
	fs := flag.NewFlagSet("ffindex", flag.ExitOnError)

	fullHash := fs.Bool("fullhash", false, "print full hash")

	fs.IntVar(&verboseLevel, "v", 2, "verbosity level: 0 = silent, 1 = no progress, 2 = full output (default)")

	fs.Usage = func() {
		fmt.Println("Usage: ffindex", Help())
	}

	fs.Parse(args)

	if len(args) < 1 {
		fs.Usage()
		os.Exit(1)
	}

	switch args[0] {
	case "build":
		if err := buildIndex(); err != nil {
			fmt.Fprintln(os.Stderr, "Error:", err)
		}
	case "add":
		if err := addToIndex(); err != nil {
			fmt.Fprintln(os.Stderr, "Error:", err)
		}
	case "by-hash":
		if len(args) < 2 {
			fmt.Fprintln(os.Stderr, "Missing hash prefix")
			os.Exit(1)
		}
		if err := searchByHashPrefix(args[1], *fullHash); err != nil {
			fmt.Fprintln(os.Stderr, "Error:", err)
		}
	case "by-name":
		if len(args) < 2 {
			fmt.Fprintln(os.Stderr, "Missing name prefix")
			os.Exit(1)
		}
		if err := searchByNamePrefix(args[1], *fullHash); err != nil {
			fmt.Fprintln(os.Stderr, "Error:", err)
		}
	default:
		fmt.Fprintln(os.Stderr, "Unknown command:", args[0])
		fs.Usage()
		os.Exit(1)
	}
}

func Name() string { return "ffindex" }

func Available() bool {
	return true
}
