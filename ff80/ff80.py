#ad-hoc command line wrapper around experimental ff80 functions
import usb1
import argparse

import sys

import ff80_cmd

import fftlib
import ffjlib

VENDOR_ID = 0x04cb
PRODUCT_ID = 0xff80

trace = 0

def cmd_parser():

    def Int(x):
        #double try to make python int() accept leading zeroes
        try: return int(x, base=0)
        except ValueError:
            try: return int(x, base=10)
            except: raise

    parser = argparse.ArgumentParser(description='Process jig commands.')
    commands = parser.add_subparsers(dest='command', required=True)

    #command bootrom
    cmd = commands.add_parser('bootrom', help='Check bootrom presense at known location and optionall save it to a file')
    cmd.add_argument('-o', '--output', metavar='filename', nargs = '?', help = 'Output file name')
    cmd.add_argument('-s', '--size', metavar='size', nargs = '?', help = 'size of data to read', const = 0x4000)

    #command syslog
    cmd = commands.add_parser('syslog', help = 'Save debug syslog content')
    cmd.add_argument('-o', '--output', nargs = '?',  help = 'Output file name')

    #command cfgdata
    cmd = commands.add_parser('cfgdata', help='Read/write/save/load config data')
    actions = cmd.add_subparsers(dest='action', required=True)

    #action cfgdata.read
    action = actions.add_parser('read', help='Read config data')
    action.add_argument('address', metavar='address', help = 'start address to read from', type = Int)
    action.add_argument('-o', '--output', metavar='filename', nargs = '?', help = 'save data to file')
    action.add_argument('-s', '--size', metavar='size', nargs = '?', help = 'size of data to read or 1 byte by default', default = 1, const = 1, type=Int)
    action.add_argument('--dontuse', help=argparse.SUPPRESS, action='store_true')

    #action cfgdata.write
    action = actions.add_parser('write', help='Write config data')
    action.add_argument('address', metavar='address', help = 'starting address of data', type = Int)
    action.add_argument('data', metavar='data', help='hex string of data to write')

    #actions cfgdata.load and cfgdata.save with no options
    actions.add_parser('load', help='load config data from nvram to ram')
    actions.add_parser('save', help='save config data from ram to nvram')

    #action cfgdata.dump
    action = actions.add_parser('dump', help='Dump all cfg data to file')
    action.add_argument('-o', '--output', metavar='filename', help = 'output file name', required=True)

    #command ram
    cmd = commands.add_parser('ram', help='Read/Write/Dump RAM')
    actions = cmd.add_subparsers(dest='action', required=True)

    #action ram.read
    action = actions.add_parser('read', help='Read RAM')
    action.add_argument('address', metavar='address', help = 'memory address', type=Int)
    action.add_argument('-s', '--size', metavar='size', nargs='?', help = 'size of data to read, default 4 bytes', default=4, const=4, type=Int)
    action.add_argument('-o', '--output', metavar='filename', nargs = '?', help = 'output file name')

    #action ram.write
    action = actions.add_parser('write', help='Write RAM')
    action.add_argument('address', metavar='address', help = 'memory address', type=Int)
    action.add_argument('data', metavar='data', help='bcd hex string of data to write')
    action.add_argument('-i', '--input', metavar='filename', nargs = '?', help = 'input file name')

    #action ram.dump
    action = actions.add_parser('dump', help='Dump RAM to file')
    action.add_argument('address', metavar='address', help = 'starting RAM address', type=Int)
    action.add_argument('-s', '--size', metavar='size', nargs='?', help = 'size of data to dump, default is as much as possible', default=0, const=0, type=Int)
    action.add_argument('-o', '--output', metavar='filename', help = 'output file name', required=True)

    #command xe2 -- experimenatl
    cmd = commands.add_parser('xe2', help='xe2 specifics, do not use!')
    actions = cmd.add_subparsers(dest='action')

    #action xe2.readtime
    action = actions.add_parser('readtime', help='Check real time location')
    action = actions.add_parser('deae', help='Check deae location and optionaly save deae to a file')
    action.add_argument('-o', '--output', metavar='filename', help = 'output file name', required=False)
    action = actions.add_parser('load', help='Load factory config data from EEP')
    action = actions.add_parser('save', help='Save config data to EEP')
    action = actions.add_parser('jig', help='Enable/disable jig mode')
    action.add_argument('op', choices=['status', 'on', 'off'], metavar='op', help = 'on/off')
    action = actions.add_parser('key', help='Send key events')
    action.add_argument('name',  metavar='name',  help = 'key name')
    action.add_argument('value', metavar='value', help = 'on/off')
    action = actions.add_parser('cmdline', help='interactive shell')
    action.add_argument('-o', '--output', metavar='filename',  help = 'saved session trace file name')
    action = actions.add_parser('media', help='get media info')
    action = actions.add_parser('playback', help='playback')
    action.add_argument('op',   choices = ['start', 'stop', 'next', 'prev'],  metavar='op',  help = 'start/stop playback')
    action.add_argument('dst',  choices = ['lcd', 'evf'],  metavar='dst',  help = 'playback type')
    action = actions.add_parser('beep', help='beep')
    action.add_argument('sound', metavar='sound',  help = '17-22 beeps, 23-31 shutter clicks', type=Int)
    action.add_argument('volume', metavar='volume',  help = 'volume 0-2', type=Int)
    action = actions.add_parser('firmware', help='upload firmware')
    action.add_argument('-i', '--input', metavar='filename', help = 'input file name', required=True)
    action = actions.add_parser('cmd07', help='cmd07')
    action.add_argument('port', choices=[0, 1, 2, 3, 4, 5, 6, 7, 8], metavar='port',  help = 'port', type=Int)
    action.add_argument('address', metavar='address',  help = 'address', type=Int)
    action.add_argument('data', metavar='data',  help = 'data', type=Int)
    action = actions.add_parser('cmd11', help='cmd11')
    action.add_argument('op', choices=[0, 1, 2], metavar='op',  help = 'op', type=Int)
    action.add_argument('-d', '--data', metavar='data', help = 'hex data', required=False)
    action = actions.add_parser('cmd12', help='cmd12')
    action = actions.add_parser('cmd00', help='cmd00')
    action.add_argument('port', choices=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ,13 ,14, 15], metavar='port',  help = 'GPIO output port', type=Int)
    action.add_argument('data', metavar='data',  help = 'hex 4 bytes')
    action = actions.add_parser('cmd01', help='cmd01')
    action.add_argument('port', choices=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ,13 ,14, 15], metavar='port',  help = 'GPIO input port', type=Int)
    action = actions.add_parser('cmd02', help='cmd02')
    action.add_argument('sensor', choices=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11], metavar='sensor',  help = 'Analog sensor', type=Int)

    action_hack = actions.add_parser('hack', help='dynamic code')
    actions = action_hack.add_subparsers(dest='op')

    action = actions.add_parser('load', help='load function code (max 64K)')
    action.add_argument('-i', '--input', metavar='filename', help = 'input binary pic file name', required=True)
    action = actions.add_parser('exec', help='call function')
    action.add_argument('-d', '--data', metavar='data', help = 'probe func argument (bcd hex)', required=False)
    action = actions.add_parser('demo', help='load and execute demo')

    #commands with no actions/options
    commands.add_parser('info',  help='Show camera info')
    commands.add_parser('ping',  help='Ping camera')
    commands.add_parser('dummy', help='Read 64K of dummy data generated by camera to test connectivity')
    commands.add_parser('echo',  help='Send/receive/validate dummy data to test connectivity before firmware update')

    return parser

def main():
    args = cmd_parser().parse_args()

    with usb1.USBContext() as context:
        try:
            usb_h = context.openByVendorIDAndProductID(VENDOR_ID, PRODUCT_ID, skip_on_error=True)

            if usb_h is None:
                print("Error: device %04x:%04x not found." % (VENDOR_ID, PRODUCT_ID))
                sys.exit(2)

            fft = fftlib.ftl(usb_h)
            jig = ffjlib.jig(fft)

            with usb_h.claimInterface(0):
                    fft.open_session()
                    #commands moved to a standalone file
                    fcmd = getattr(ff80_cmd, 'cmd_' + args.command, None)
                    if fcmd is not None:
                        fcmd(jig, args)
                    else:
                        print('command', args.command, 'not implemented')
                    fft.close_session()
        except usb1.USBErrorAccess as e:
            print("USB Insufficient user access rights: %s" % (e))
        except usb1.USBErrorTimeout as e:
            print("USB timeout: %s\nPlease remove the battery, then reinsert it to perform a cold boot." % e)
        except usb1.USBErrorIO as e:
            print('USB:', e)
        except usb1.USBErrorNoDevice as e:
            print('USB:', e)
        except ffjlib.jig_exception as e:
            print('jig error:', e)
            fft.close_session()

if __name__ == '__main__':
    main()
