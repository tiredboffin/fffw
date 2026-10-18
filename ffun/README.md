# ffun – Fujifilm Firmware Utilities

`ffun` is a collection of CLI tools for working with Fujifilm firmware files. The project started in Python and I later began translating it to Go in preparation for publication. 
In hindsight, that was a mistake for this project, so I abandoned the migration and returned to Python :) 

The optional Go `ffcompress` utility remains for faster compression and decompression.

The tools are still a work in progress. Recent improvements include byte-identical DAT reconstruction for many pre-EXR cameras (Nortic RTOS) and
 intial support for even older cameras (based on EEPROM dumps as DAT flles are often not availbale)

Preparing files for reverse engineering remains the main focus; final ELF generation is still supported but it is limited to ARM-based cameras so the tool is 
slowly migating to custom Ghidra loader scripts to add suppport V850E, MIPS and M32R.

## Design Overview

The approach splits the tools into two parts:

### 1. Analysis Stage

This stage analyzes the firmware and extracts as much metadata as possible -- sometimes heuristically, sometimes manually (e.g., using Ghidra). As more is learned, hints in `ffmap.yaml` can be refined and 
the analysis run again.

The results are collected in a **firmware manifest**, `manifest.yaml`, which describes the extracted pieces, their memory mappings and how the information was found. 
The findings can be exported as sperate chunks of firmware in different formats

### 2. Export Stage

This stage uses the manifest.yaml and firmware file (DAT. .S3 or raw dump) to export artifcats for further analysis in RE tools (like Ghidra) or in emulator.

The main target is now Ghidra loader script but a synthetic ELF can still be produced. 

### 3. Firmware patching

The tool can be used to build the DAT file from patched chunks and it was tested to rebuilt byte-identical DAT files.

## Firmware Files

Firmware files should be downloaded from the official [Fujifilm website](https://fujifilm.com) or from third-party firmware archives for older versions.

**This repository does not distribute firmware files.**

## Install

Python 3.12+. From the repository root:

```
make dev        # editable install into the active venv: "ffun" runs this checkout
make cext       # the C LZ module in place, for python -m ffun
make wheel      # dist/: a pure wheel, and one with the C LZ module (Python 3.12+, abi3)
make nuitka     # dist/ffun.dist/ffun.bin, a standalone build for this machine only (pip install nuitka patchelf)
```

Without installing, `python -m ffun ...` from the repository root works the same, with the
`dependencies` of `pyproject.toml` installed.

**LZ code.** ffun picks the first of:
1. an `ffcompress` given by hand (`--ffcompress`, `$FFCOMPRESS`, the `ffcompress` setting);
2. the C module (the wheel with it, or `make cext`);
3. an `ffcompress` found: the checkout's `ffcompress/ffcompress` (`make -C ffcompress`), or one on `PATH`;
4. the Python code, with a warning. It is about 65× slower to unpack and 9× slower to pack.

The C module and ffcompress give the same bytes. ffcompress isn't in the wheels; it stays
the Go cross-check.

`ffun doctor` shows which external tools ffun finds (ffcompress, the C module, `go`, `make`,
the ARM toolchains, `git`) and what fails without each.

## Quick start

TODO 

## ffun --help

ffun — unpack and repack Fujifilm firmware
Version: develop-462c87f

Usage: ffun COMMAND [OPTIONS]

Commands:
  analyze    analyze firmware and create a manifest.yaml
  export     export to different targets (--list-targets)
  build      rebuild firmware from modified chunks
  vault      manage your firmware collection
  doctor     check which external tools are there (ffcompress, go, toolchains)
  set        show or save settings

Run 'ffun COMMAND --help' for arguments and options, or --help --json to use with agents

Developer tools:
  inspect    examine firmware structures and resources
  lz         compress or decompress Fujifilm data
  guess      run individual firmware guessers
  selftest   test ffun against firmware files

Examples:
  ffun analyze FWUPDATE.DAT -o fw.yaml
  ffun analyze FWUPDATE.DAT --split -o fw/fw.yaml    # also the pieces, in fw/
  ffun export fw.yaml --target elf
  ffun analyze XE2-0411 --update-vault

Run 'ffun --help-long' for the commands' options and the details.

