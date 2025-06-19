package main

import (
	"bufio"
	_ "embed"
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

const modulePath = "ffun"
const manifestPath = ".gengenerated"

//go:embed cmd_template.txt
var cmd_template string

//go:embed reg_template.txt
var reg_template string

func main() {
	cliDir := "internal/cli"
	cmdDir := "cmd"

	var registryImports []string
	var registryEntries []string

	var generated []string

	entries, _ := os.ReadDir(cliDir)
	for _, e := range entries {
		if !e.IsDir() || strings.HasPrefix(e.Name(), "_") {
			continue
		}

		name := e.Name()

		// --- Generate cmd/programX/main.go ---
		mainDir := filepath.Join(cmdDir, name)
		_ = os.MkdirAll(mainDir, 0755)
		mainFile := filepath.Join(mainDir, "main.go")

		if _, err := os.Stat(mainFile); os.IsNotExist(err) {
			mainSrc := fmt.Sprintf(cmd_template, modulePath, name)
			_ = os.WriteFile(mainFile, []byte(mainSrc), 0644)
			generated = append(generated, mainFile)
			fmt.Println("Generated:", mainFile)
		}

		// --- Collect entries for registry ---
		registryImports = append(registryImports,
			fmt.Sprintf("\t%[1]sPkg \"%s/internal/cli/%[1]s\"", name, modulePath))
		registryEntries = append(registryEntries,
			fmt.Sprintf("\t\"%[1]s\": { Run: %[1]sPkg.Run, Help: %[1]sPkg.Help, IsAvailable: %[1]sPkg.Available }, \n", name))
	}

	// --- Generate internal/cli/registry_gen.go ---
	regFile := filepath.Join(cliDir, "registry_gen.go")

	regSrc := fmt.Sprintf(reg_template, strings.Join(registryImports, "\n"), strings.Join(registryEntries, "\n"))

	err := os.WriteFile(regFile, []byte(regSrc), 0644)
	generated = append(generated, regFile)
	if err != nil {
		fmt.Println("Error writing registry_gen.go:", err)
		os.Exit(1)
	}
	// Load existing manifest entries (if any)
	manifestSet := map[string]bool{}
	if f, err := os.Open(manifestPath); err == nil {
		scanner := bufio.NewScanner(f)
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if line != "" {
				manifestSet[line] = true
			}
		}
		f.Close()
	}
	// Add new generated paths
	for _, path := range generated {
		manifestSet[filepath.ToSlash(path)] = true // normalize slashes
	}

	// Write merged manifest
	f, err := os.Create(manifestPath)
	if err != nil {
		panic("failed to write .gengenerated: " + err.Error())
	}
	defer f.Close()

	for path := range manifestSet {
		f.WriteString(path + "\n")
	}
	fmt.Println("Generated:", regFile)
}
