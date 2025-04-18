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
  - convert the decompressed DAT into ELF container for furher analysis in Ghidra. Supports most models starting from EXR processor (for e.g XF1) and up to "X Processor 5" cameras (X-T5, X100VI).
  - generate .h files with enums and structures for use in Ghidra scripts to load the image, and to name and identify specific code sections, functions, and constants (e.g., task IDs).
  - Note: Only the ARM portions of the image are included in the ELF. IBIS RX/RL78, video codecs, DSP, and AI chip code are not supported.
  - Note: The Linux subsystem can be extracted and later analyzed using various standard tools.

- ffbt (unpublished): A CLI tool for researching Bluetooth functions.
  - ffbt app: emulate BLE functions of XApp and Camera Remote applications. This tool currently supports the following actions:
    - sending "Take", "Get", "Firmware Update" commands to the camera, which makes the camera to start the Wi-Fi access point.
    - trigger shutter
    - update (sync) geolocation and/or time
    - backup/restore user settings data (xapp)
    - enable/disable and collect activity logs (xapp)
    - collect camera vital JSON data (xapp, newer cameras)
  - ffbt bt1tg: emulate BT1-TG remote control buttons
    - supports pairing, shutter release, record movie and zoom buttons
    - lock button is not supported yet
  - ffbt camera: emulate BLE functions of camera. 
    - supports pairing and handing over to Wi-Fi (i.e. accepts "Take" and "Get" commands from XApp). Can be useful to trick XApp/CameraRemote into connecting to any arbitrary Wi-Fi access point.
    - send and receive backup data (xapp)
    - send activity logs (xapp)
    - send camera vital data (xapp on newer cameras)
    - supports "connect when power off" mode (xapp)

- ffbak (unpublished): backup file parser
    - extract and manipulate C1-C7 profiles: the structure is more or less stable across camera models
    - extract "global" camera settings: work in progress, only X-T4 is supported at the moment

- ffraf (unpublished): RAF 
   - decompress RAF file to produce an uncompressed version for analyzing the impact of lossy compression on image quality
   - compress RAF file (work in progress)
   - parse and extract data from proprietary sections of RAF file (work in porgress)

- ffem (unpublished) - research emulator (work in porgress)
  - tool to analyse (select) functions of firmware by executing them in unicorn ARM/ARM64 emulator. At this stage can be used to 
    - demangle the event driven parts of the code - finate state machines
    - research SD and NAND controllers that are used by ffre

- ffui (unpublished, abandoned)
  - extract and convert UI localized text resources (menu, help etc) into an editable format (complete for XE2)
  - compile the resources back into camera format

- ffre (unpublished, abandoned) - bricked camera recovery (put on hold)
  - runs firmware updater from SD card. Partially tested only on XE2. Can be made to work on other cameras with EXR, EXR Pro and EXR-II SoC (XPro1, XE1, XE2, XA1, XA2, XM1 etc).

## Instructions ff80

To put the camera into service ("ff80") mode 
  - Power off the camera
  - Connect USB cable to PC
  - Power on the camera holding the Shutter and Up buttons to put into service ("jig" or "ff80") mode
  - Run

      ```lsusb -d 04cb:ff80```

    It should return

      ```ID 04cb:ff80 Fuji Photo Film Co., Ltd```
   

Then test connectivity with
```
python ff80 info
```

### Linux

To run the script as a non-admin user put the ff80/60-fjig.rules file to the udev rules directory (typically /etc/udev/rules.d) and reload the rules with
```
sudo udevadm control --reload-rules
```

Then add your username to usbdev group

```sudo usermod -a -G usbdev <username>```

### Windows

Additional step is required to install WinUSB driver for 04CB:FF80 :

![image](https://github.com/user-attachments/assets/d4283128-ad91-4102-8ba1-ee36715b9ffb)


## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).
