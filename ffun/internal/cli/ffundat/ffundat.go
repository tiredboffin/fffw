package ffundat

/* Wraps python script... to be ported */

import (
	"embed"
	"ffun/internal/pycheck"
	"os"
	"os/exec"
)

func Run(args []string, fs embed.FS) {

	if !pycheck.IsAvailable() || pycheck.Cmd() == "" {
		return
	}

	prog1Zip, err := fs.ReadFile("_assets/ffundat.pyz")
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
	cmd := exec.Command(pycheck.Cmd(), cmdargs...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err = cmd.Run()
	if err != nil {
		os.Exit(cmd.ProcessState.ExitCode())
	}
}

func Name() string { return "ffundat" }

func Help() string { return "todo" }

func Available() bool { return pycheck.IsAvailable() }
