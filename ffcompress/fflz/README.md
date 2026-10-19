fflz is the Fujifilm firmware image LZ compressor and decompressor.

Copyright 2024-2025 tiredboffin@gmail.com

Fujifilm implements firmware decompression in hardware. So this software implementation is
based entirely on educated guesses from analyzing compressed original data.

The closest matching algorithm I found in the literature is Algorithm A1, described in E. Fiala
and D. Greene, "Data Compression with Finite Windows". It is a variant of LZ77.

The actual hardware implementation in the SoC is undocumented. Based on analysis of numerous
firmware samples it appears that the hardware decompressor processes input in 16K pages. Most
likely it uses DMA to load each page and triggers an interrupt when a new one is needed. So the
compressor must ensure that no LZ77 token crosses a 16K page boundary.

A naive approach would be to pad pages with 0-length literals when nearing the boundary. But
Fujifilm's implementation never uses such tokens. Instead it splits literal or copy tokens at
page boundaries so the remaining part starts cleanly on the next page.

There are many ways to do this and the rules for where and how to split tokens on the page
boundary are inherently ambiguous.

This implementation is based on reverse-engineering hundreds of compressed firmware images and
reproduces them bit for bit. Whether this exact behavior is required by the hardware
decompressor is still unclear. It may be more flexible than assumed, further research is
needed.

## Tested

1259 unique segments from 484 firmware files of 70+ camera models were unpacked and repacked
bit for bit.

## Limits

- Bit-exact only for what real firmware shows. Unknown stream ends are refused.
  `PackIO(r, w, true)` (`-dirty-tricks`) packs them by guess with a warning.
- Only one sample of 1259 tested compressed chunks ends exactly on a page boundary with its
  last zeros dropped. Both sides handle that but with low confidence. Hence a warning.
- Knowing the hardware decompressor logic with 100% confidence takes experiments on real
  hardware. For practical purposes this code is enough. Those experiments run as part of ffun
  and new findings are kept only there.

Warnings go through the `Warn` hook, stderr by default. `-tags=ffunpack_release` compiles them
out.
