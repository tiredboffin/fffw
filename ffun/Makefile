TOOLS := ffun ffcompress ffindex
PY_TOOLS := ffundat
BIN_DIR := bin

GOCMD=go
GOFLAGS=-trimpath -ldflags="-s -w"

PYTHON=python3
PY_SRC_ROOT=py
PYZ_OUTPUT_DIR=internal/cli/_assets

# Windows64
WIN_GOOS=windows
WIN_GOARCH=amd64


.PHONY: all  clean $(TOOLS)

all: ffun

ffun.exe:
	GOOS=$(WIN_GOOS) GOARCH=$(WIN_GOARCH) $(GOCMD) build -o $(BIN_DIR)/$@ $(GOFLAGS) ./cmd/ffun

$(TOOLS): pyz
	$(GOCMD) build -o $(BIN_DIR)/$@ $(GOFLAGS) ./cmd/$@

pyz: $(PY_TOOLS:%=$(PYZ_OUTPUT_DIR)/%.pyz)

$(PYZ_OUTPUT_DIR)/%.pyz: $(PY_SRC_ROOT)/%
	@echo "[*] Building $@ from $<..."
	@mkdir -p $(PYZ_OUTPUT_DIR)
	$(PYTHON) -m zipapp $< -o $@ --compress
	@echo "[✓] Done: $@"

tests:
	go test -v ffun/internal/cli/ffcompress

deps:
	go mod tidy

pyzclean:
	rm -f $(PYZ_OUTPUT_DIR)/*.pyz

clean:
	rm -rf $(BIN_DIR)

generate:
	go generate ./...

genclean:
	go run ./tools/cleangen

distclean: clean pyzclean genclean
