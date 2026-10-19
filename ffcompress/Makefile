GOCMD=go
BINARY=ffcompress
WIN_BINARY=ffcompress.exe
GOFLAGS=-trimpath -ldflags="-s -w"

# Windows64
WIN_GOOS=windows
WIN_GOARCH=amd64

.PHONY: all native windows clean

all: native

native:
	$(GOCMD) build $(GOFLAGS)

windows:
	GOOS=$(WIN_GOOS) GOARCH=$(WIN_GOARCH) $(GOCMD) build $(GOFLAGS) -o $(WIN_BINARY)

clean:
	rm -f $(BINARY) $(WIN_BINARY)
