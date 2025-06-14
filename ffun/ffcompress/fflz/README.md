fflz – Basic implementation of the Fujifilm LZ compression algorithm, part of the ffun toolkit.

Implementation notes:

- The actual hardware implementation is undocumented.
This reversed algorithm is based purely on analysis of DAT file samples and may not be a 100% accurate reconstruction.

- The software compressor implementation is likely more complex than necessary.

The hardware decompressor processes input in 16K pages — most likely using DMA to load each page and raising an interrupt when a new one is needed.

Based on analysis of numerous firmware samples, it seems the compressor tries its best to ensure that no LZ77 token (either a literal or a copy) crosses a 16K page boundary.
Whether the hardware decompressor is sensitive to the precise padding rules, or is more flexible, is not yet known — confirming this would require testing on real hardware (which can currently be done safely only on the X-E2).

For now, the safe choice has been made to replicate the original output exactly, rather than pursue a simpler design or better compression ratio.

- The software decompressor doesn’t rely on these page-boundary quirks, but it detects them and reports any deviations from the (guessed) padding rules as warnings.

- This code was translated from a quick Python proof-of-concept script and then reworked in Go as an excuse to learn the language.
The result still carries a lot of C-style structure and assumptions. I'd honestly be shocked if it couldn't be improved.