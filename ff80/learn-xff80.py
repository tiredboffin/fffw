import usb1
import sys
import struct

import fftlib
import ffjlib

VENDOR_ID = 0x04cb
PRODUCT_ID = 0xff80

with usb1.USBContext() as context:
    usb_h = context.openByVendorIDAndProductID(VENDOR_ID,  PRODUCT_ID, skip_on_error=False)
    if usb_h is None:
        print("open failed")
        sys.exit(2)

    fftlib.trace = 0

    fft = fftlib.ftl(usb_h)
    jig = ffjlib.jig(fft)

    with usb_h.claimInterface(0):
        try:

            fft.open_session()

            #TBC: both commands can be used to check camera presense (?)
            print('ping', fft.ping().hex())

            #print simple info
            jig.print_info()

            print('TBC: get timeouts:', end = '')
            r = jig.get_timeouts()
            n, u1, u2, u3 = struct.unpack_from('<4I', r)
            ofs  = 16
            while n > 0:
                op, to = struct.unpack_from('<2I', r, ofs)
                ofs += 8
                n -= 1
                print(' [op:', hex(op), 'to:', to, end = ']')
            print()

            print('TBC: Unknown function:')
            jig.ftl.trace = True
            r = jig.unk_1a0001()
            jig.ftl.trace = False
            print('(#TBC:d55.104.high_bit && d54.9c.bit14) == ', 0 if r[0] == 1 else 1)

        except usb1.USBErrorTimeout as err:
            print('timeout:', err.received)
        except ffjlib.jig_exception as err:
            print('jig err:', err)
        finally:
            fft.close_session()
