# fffw

fffw is a set of research tools for Fujifilm firmware.

Quick usage: python ff80 -h

## Functions

- ff80 - jig mode.
  - tool to research native interface provided by the firmware for adjustments and debugging.
  - can be used to copy (dump) RAM content, for code injections and to selectively enable native debug logging susbsytem(s). 
  - can read, modify and save adjustment and calibration data. 
    
- ffun (unpublished yet) - tool to manipulate firmware image DAT files. 
  - split DAT files (camers, lenses etc) into pieces, decompress compressed 'segments' and construct a new valid DAT files out of the modified pieces. 
  - convert the decompressed DAT into ELF container for furher analysis in Ghidra. Supports most models starting from EXR processor (for e.g XF1) and up to "X Processor 4" cameras (X-T4).
  - Note: Only ARM portions of the image are included into ELF, RX/RL78 code is not supported. The "X Processor 5" images are not supported yet. (work in progress).

- ffui (todo)
  - extract and convert UI localized text resources (menu, help etc) into an editable format (work in porgress)
  - compile the resources back into camera format (work in porgress)
   
- ffre (unpublished) - bricked camera recovery (work in progress)
  - runs firmware updater from SD card. Partially tested only on XE2. Can be made to work on other cameras with EXR-II SoC (XA2, XM1 etc). Porting to other SoC-s depends on bootrom availabilty.
    
- ffem (unpublished) - research emulator (work in porgress)
  - code to emulate (select) functions. At this stage can be used to 
    - demangle the event driven parts of the code
    - research SD and NAND controllers that are used by ffre


## Instructions

To put the camera into service ("ff80") mode 
  - Power off the camera
  - Connect USB cable to PC
  - Power on the camera holding the Shutter and Up buttons

Then test connectivity with
```
python ff80 info
```

### Windows

Additional step is required to install WinUSB driver for 04CB:FF80 :

![image](https://github.com/user-attachments/assets/d4283128-ad91-4102-8ba1-ee36715b9ffb)


## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).
