TOOLS := ffun ffcompress ffindex
BIN_DIR := bin

GOCMD=go
GOFLAGS=-trimpath -ldflags="-s -w"

# Windows64
WIN_GOOS=windows
WIN_GOARCH=amd64


.PHONY: all  clean $(TOOLS)

all: ffun

$(TOOLS):
	$(GOCMD) build -o $(BIN_DIR)/$@ $(GOFLAGS) ./cmd/$@

deps:
	go mod tidy

clean:
	rm -rf $(BIN_DIR)

generate:
	go generate ./...

genclean:
	go run ./tools/cleangen
