package ffcompress

import (
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func TestAllFiles(t *testing.T) {
	testDir := "test-data"
	entries, _ := os.ReadDir(testDir)
        if len(entries) == 0 {
		t.Error("No test data")
        }
	for _, e := range entries {
		if e.IsDir() || strings.HasPrefix(e.Name(), ".") {
			continue
		}
		t.Run(e.Name(), func(t *testing.T) {
			err := TestInMem(filepath.Join(testDir, e.Name()), "")
			if err != nil {
				t.Error(err)
			}
		})
	}
}
