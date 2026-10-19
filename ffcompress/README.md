# ffcompress

A tiny Go packer and unpacker for the compression Fujifilm cameras use in their firmware.

- **fflz** is Fujifilm's LZ of the X-series and friends. See [fflz/README.md](fflz/README.md).
- **lzss18** and **lzss10** are the Okumura-style LZSS of the older Sanyo-built firmware. These
  are the files that start with `LENGTH=`.

Both were reverse-engineered from firmware dumps with no docs and no vendor code. The packer
tries to emit the **exact same bytes** as Fujifilm's own packer, so an unpack and repack of a
real segment is a no-op.

However, that was obviously tested only on the available firmware samples, so there is no 100%
guarantee and more experiments on real hardware are needed.

## Why Go

It started life as pure Python inside [ffun](../ffun). That worked but packing a full firmware
image was slow. Go is about 10x faster. Measured on one main image, its three biggest segments
with 42 MB unpacked:

| packer | speed |
|---|---|
| pure Python | 2 MB/s |
| Go (this) | 21 MB/s |
| C (in ffun) | 22 MB/s |

ffun relied on ffcompress for speed but it doesn't need it any more. An agent ported the Go
code to a C extension that now ships inside the ffun Python package and runs just as fast. The
pure Python codec stays in ffun as the reference and for pure Python wheels. So this Go
implementation lives on for historical reasons only.

## Build

Go 1.23 or newer, no deps.

```sh
make            # ./ffcompress
make windows    # ffcompress.exe
go test ./...
```

## Use

```sh
ffcompress c data.bin packed.bin                    # pack (fflz)
ffcompress u packed.bin data.bin                    # unpack
ffcompress t packed.bin                             # repack an original segment and compare
ffcompress -codec lzss18 -size 0x1234 u in.bin out.bin
```

`-` reads stdin or writes stdout. `ffcompress -h` has the rest.

## Tested

Every compressed segment in the firmware vault was unpacked and repacked bit for bit. The fflz
results and limits are in [fflz/README.md](fflz/README.md).

The LZSS check covered 138 streams from 46 Sanyo firmware files, 137 are identical. For the
remaining one the original encoder was given a few bytes more than the recorded size, see the
code for details.

## Copyright

Copyright 2024-2025 tiredboffin@gmail.com
