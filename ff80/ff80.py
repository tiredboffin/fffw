import usb1
import sys
import time
import struct
import hashlib
import argparse, readline

import fftlib
import ffjlib

import ff80_cmd

VENDOR_ID = 0x04cb
PRODUCT_ID = 0xff80

trace = 0

parser = argparse.ArgumentParser(description='Process jig commands.')

subparsers = parser.add_subparsers(dest='command')

parse_bootrom = subparsers.add_parser('bootrom', help='Check bootrom presense at known location and optionally save it to a file')
parse_bootrom.add_argument('file', nargs = '?', help = 'save bootrom to file')

syslog = subparsers.add_parser('syslog', help='Check debug syslog content and optinally save it to a file')
syslog.add_argument('file', nargs = '?', help = 'save bootrom to file')

subparsers.add_parser('info', help='Show camera info')
subparsers.add_parser('ping', help='Ping camera')
subparsers.add_parser('dummy', help='Read 64K of dummy data to test connectivity')
subparsers.add_parser('echo', help='Send/receive/validate data')

args = parser.parse_args()

with usb1.USBContext() as context:
    usb_h = context.openByVendorIDAndProductID(VENDOR_ID, PRODUCT_ID, skip_on_error=False)

    if usb_h is None:
        print("usb open failed")
        sys.exit(2)

    fft = fftlib.ftl(usb_h)
    jig = ffjlib.jig(fft)

    with usb_h.claimInterface(0):
        try:

            fft.open_session()

            if args.command == 'info':
                ff80_cmd.info(jig)
            elif args.command in ['ping', 'nop']:
                ff80_cmd.ping(jig)
            elif args.command  == 'dummy':
                ff80_cmd.dummy(jig)
            elif args.command  == 'echo':
                ff80_cmd.echo(jig)
            elif args.command == 'bootrom':
                ff80_cmd.bootrom(jig, args.file)
            elif args.command == 'syslog':
                ff80_cmd.syslog(jig, args.file)

        except usb1.USBErrorTimeout as err:
            print('timeout:', err.received)
        except ffjlib.jig_exception as err:
            print('jig err:', err)
        finally:
            fft.close_session()


