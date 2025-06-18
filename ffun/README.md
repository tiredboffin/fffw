# ffun 

# ffun – Fujifilm Firmware Utilities

`ffun` is a collection of CLI tools for working with Fujifilm firmware files. The codebase is currently being translated from Python to Go in preparation for publication, but the process is still ongoing — most modules don’t even build yet.

## Design Overview

The current approach splits the tools into two parts:

### 1. Analysis Stage

This stage analyzes the firmware and extracts as much metadata as possible — sometimes heuristically, sometimes manually (e.g., using Ghidra). The process is iterative: as the firmware is analyzed, new structures and details often emerge.

The results of this analysis are then *compiled* into a single **firmware manifest** file, which contains offsets, sizes, and relevant metadata.

Currently, the manifest is "precompiled" using a mix of Python and Bash scripts, with some parts written in Go where Python is too slow.

### 2. Synthesis Stage

This stage uses the firmware manifest and original firmware files to reconstruct (synthesize) useful artifacts — typically synthetic files that didn’t exist as standalone entities in the original firmware.

The most notable output is the main camera code, either in ELF format or as a raw binary plus a loader script for Ghidra. For most users, that’s all that’s needed.

However, newer cameras often package firmware more like a tar archive — which may include a Linux distribution, lens firmware, unrecognized RL78 code, etc depending on the model.

The current focus is on preparing and publishing the stage 2 (Synthesis) tools -- there seems to be more demand for those. Unfortunately, it’s also the most boring part :)


## Firmware Files

Firmware files should be downloaded from the official [Fujifilm website](https://fujifilm.com) or from third-party firmware archive sites if you're looking for older versions.

**This repository does not distribute firmware files.**


-- -

## ffun dat2elf 

Tool to convert Fujifilm .DAT firmware files into synthetic ELF binaries for import into Ghidra or IDA.

---

### Overview

If you're interested in analyzing firmware from various Fujifilm models and versions, `ffun dat2elf` helps convert `.DAT` firmware files into ELF binaries or Ghidra-compatible Python scripts. The generated output includes:

- Memory region mappings
- Basic functions (e.g. `create_thread()`)
- Some global data structures (depending on firmware version)

It’s meant to give you a starting point for reverse engineering in Ghidra or IDA.

`dat2elf` 

For a list of supported cameras, see the manifest/ directory.

---

### Basic Usage

```
ffun dat2elf -s FWUP0001.DAT -m xe1-0101 -o xe1-0101.elf
```

 -  -s — path to the input .DAT firmware file. Must be an original, unmodified DAT file.
 -  -m — name of the manifest file to use, by convention uses camera model name and firmware version (e.g., xe1-0101 for X-E1 v1.01 firmware).
 -  -o — output file. The format of the output file is determined by the extension:
        .elf — ELF binary
        .py — Ghidra loader script (work in progress)
 
If you have the library of pre-compiled manifest librrary cloned you can simply run

```
ffun dat2elf -s FWUPDATE_FILE.DAT -o elf
```

When manifest file is not specified `ffun dat2elf` calculates a hash of the firmware .DAT file to find and use the matching manifest file in the library.

---

## Cross-Version Workflow

If you're working with multiple firmware versions and/or models you might find it easier to specify manifest as input and make `ffdat2elf` match the firmware file, like:

```
ffun dat2elf -m xe1-0101
ffun dat2elf -m xe1-0102
...

```

This assumes a matching .DAT files are available locally and file index.yaml is present in current working directory:


```index.yaml
sha1_hash1: filename1.DAT
sha1_hash2: filename2.DAT
```

To create the index you can use a simple `ffun ffindex` or use `git`:

```
for f in *.DAT; do echo "$(git hash-object -w "$f"): $f"; done > index.yaml
```

For other options run ```ffun dat2elf -h``` 

---

## ffun ffcompress

Unpack packed portions of firmware. Used internally by `dat2elf` and `patch`.

---

## ffun ffindex

Creates or updates the index.yaml file (see above). The main reason is that the manifest needs to refer to the original firmware file name — but Fujifilm firmware filenames are not unique, and users often rename them arbitrarily when storing multiple files. To avoid ambiguity, the tools use Git-like hashes (for historical reasons) to identify the original firmware files instead of relying on filenames.

