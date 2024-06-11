# fffw

fffw is a set of research tools for Fujifilm firmware.

Usage: python ff80 -h

- ff80 - jig mode.
  - research native interface provided by the firmware for adjustments and debugging.

- ffun - dat file.
  - split DAT files into pieces, decompress compressed 'segments' and construct a new valid DAT files out of the modified pieces.
 
- ffre - bricked camera recover (work in progress)

- ffem - research emulator (work in porgress)
  - code to emulate (select) functions. At this tsage can be used to 
    - demangle the event driven parts of the code
    - research SD, SDIO and NAND controllers

## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).