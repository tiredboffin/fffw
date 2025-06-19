/* TBP. So far just wraps python script... */

package ffundat

import (
	"embed"
	"os"
	"os/exec"
)

func Help() string {
	return "todo"
}

func Run(args []string, fs embed.FS) {
	prog1Zip, err := fs.ReadFile("assets/ffundat.pyz")
	if err != nil {
		panic(err)
	}

	tmpFile, err := os.CreateTemp("", "ffundat-*.pyz")
	if err != nil {
		panic(err)
	}
	defer os.Remove(tmpFile.Name())

	tmpFile.Write(prog1Zip)
	tmpFile.Close()
	cmdargs := append([]string{tmpFile.Name()}, args...)
	cmd := exec.Command("python3", cmdargs...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err = cmd.Run()
	if err != nil {
		os.Exit(cmd.ProcessState.ExitCode())
	}
}

func Name() string { return "ffundat" }
