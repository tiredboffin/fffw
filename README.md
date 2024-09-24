# fffw

fffw is a set of research tools for Fujifilm firmware.

Usage: python ff80 -h

- ff80 - jig mode.
  - tool to research native interface provided by the firmware for adjustments and debugging.
  - can be used to copy (dump) RAM content, for code injections and to selectively enable native debug logging susbsytem(s). 
  - can read, modify and save adjustemt and calibration data. 
    
- ffun (unpublished yet) - dat file 
  - split DAT files (camers, lenses etc) into pieces, decompress compressed 'segments' and construct a new valid DAT files out of the modified pieces. 
  - convert the decompressed DAT into ELF container for furher analysis in Ghidra. Supports models from EXR processor (for e.g XF1) and up to "X Processor 4" cameras (X-T4). Only for ARM portions of the image are included into ELF, RX/RL78 is not supprted. (work in progress).

- ffui (todo)
  - extract and convert UI localized text resources (menu, help etc) into an editable format (work in porgress)
  - compile the resources back into camera format (work in porgress)
   
- ffre (unpublished) - bricked camera recovery (work in progress)
  - runs firmware updater from SD card. Partially tested only on XE2. Can be made to work on other cameras with EXR-II SoC (XA2, XM1 etc). Porting to other SoC-s depends on bootrom availabilty.
    
- ffem (unpublished) - research emulator (work in porgress)
  - code to emulate (select) functions. At this stage can be used to 
    - demangle the event driven parts of the code
    - research SD and NAND controllers that are used by ffre

## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).
