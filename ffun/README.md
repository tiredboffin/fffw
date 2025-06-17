## ffcompress

Unpack packed portions of firmware. Used internally by `ffdat2elf` and `ffpatch`.

--- 

## ffdat2elf

Tool to convert Fujifilm .DAT firmware files into synthetic ELF binaries for import into Ghidra or IDA.

---

### Overview

If you're interested in analyzing firmware from various Fujifilm models and versions, `ffdat2elf` helps convert `.DAT` firmware files into ELF binaries or Ghidra-compatible Python scripts. The generated output includes:

- Memory region mappings
- Basic functions (e.g. `create_thread()`)
- Data structures (depending on firmware version)

It’s meant to give you a starting point for reverse engineering in Ghidra or IDA.

`ffdat2elf` uses **firmware manifest** files, which contain the offsets, sizes, and metadata needed to generate an ELF. These manifests are "precompiled" using the `ffundat` tool (TBP).

For a list of supported cameras, see the manifest/ directory.

---

### Basic Usage

```
ffdat2elf -s FWUP0001.DAT -m xe1-0101 -o xe1-0101.elf
```

    -s — path to the input .DAT firmware file. Must be an original, unmodified DAT file.
    -m — name of the manifest file to use, by convention uses camere model name and firmware version (e.g., xe1-0101 for X-E1 v1.01 firmware).
    -o — output file. The format of teh ourput file is determined by the extension:
        .elf — ELF binary
        .py — Ghidra loader script (work in progress)
 
If you have the library of pre-compiled manifest librrary cloned you can simply run

```
ffdat2elf -s FWUPDATE_FILE.DAT -o elf
```

When manifest file is not specified `ffdat2elf` calculates a hash of the firmware .DAT file to find and use the matching manifest file in the library.

---

## Cross-Version Workflow

If you're working with multiple firmware versions and/or models you might find it easier to specify manifest as input and make `ffdat2elf` match the firmware file, like:

```
ffdat2elf -m xe1-0101
ffdat2elf -m xe1-0102
...

```

This assumes a matching .DAT files are available locally and file index.yaml is present in current working directory:


```index.yaml
sha1_hash1: filename1.DAT
sha1_hash2: filename2.DAT
```

To create the index you can use a simple `cmd/fwindex` or use `git`:

```
for f in *.DAT; do echo "$(git hash-object -w "$f"): $f"; done > index.yaml
```

For other options run ```ffdat2elf -h``` 


