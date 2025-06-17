GOCMD=go
TINYGO= tinygo
BINARY=ffcompress
WASM_BINARY=fflz.wasm
TINYGO_WASM_BINARY=fflz-tiny.wasm
WIN_BINARY=ffcompress.exe
GOFLAGS=-trimpath -ldflags="-s -w"

# Windows64
WIN_GOOS=windows
WIN_GOARCH=amd64

# WASM settings
WASM_GOOS=js
WASM_GOARCH=wasm

.PHONY: all native wasm windows clean

all: native wasm

native:
	$(GOCMD) build $(GOFLAGS) 

wasm:
	GOOS=$(WASM_GOOS) GOARCH=$(WASM_GOARCH) $(GOCMD) build $(GOFLAGS) -o $(WASM_BINARY) fflz_wasm.go

tinywasm:
	$(TINYGO) build -target=wasi -o $(TINYGO_WASM_BINARY) 

windows:
	GOOS=$(WIN_GOOS) GOARCH=$(WIN_GOARCH) $(GOCMD) build $(GOFLAGS) -o $(WIN_BINARY)

clean:
	rm -f $(BINARY) $(WASM_BINARY)
