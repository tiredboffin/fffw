package ffcompress

import (
	"os"
	"path/filepath"
	"testing"
)

func TestAllFiles(t *testing.T) {
	testDir := "test-data"
	entries, _ := os.ReadDir(testDir)
        if len(entries) == 0 {
		t.Error("No test data")
        }
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		t.Run(entry.Name(), func(t *testing.T) {
			err := TestInMem(filepath.Join(testDir, entry.Name()), "")
			if err != nil {
				t.Error(err)
			}
		})
	}
}
