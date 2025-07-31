#raise ImportError
import time
import struct

from .cmd_data import key2code

model = None

def cmd_xe2(jig, argv):
    global model
    n = jig.get_device_info(4)
    if n not in ['X-E2', 'X-A2', 'X100V', "X-T4", "FinePix HS30EXR", "X-T5"]:
        print('Warning: camera model', n, 'not tested')
    model = n
    if argv.action == None:
        print('Command not specified')
    elif argv.action == 'cmd01':
        return _exp_cmd01(jig, argv)
    elif argv.action == 'cmd02':
        return _exp_cmd02(jig, argv)
    else:
        print(argv.command, 'action', argv.action, 'not implemented')

def gpio_bit_name(p, b16):
    if model not in ["X-E2"]:
        return ''
    key_map = {
        0x00 : ["b0", "b1", "Sh1", "Sh2",
                "Lens", "b5", "b6", "LensP",
                "Eye sensor?", "b9", "Jog Dial", "Fn",
                "b12", "b13", "b14", "b15"],
        0x02 : ["b0", "b1", "b2", "b3",
                "b4", "b5", "b6", "b7",
                "tp b8?", "Fn2/(XA2)Play", "b10", "pb b11?",
                "pb b12?", "b13", "pb b14?", "pb b15?"],
       0x03 : ["b0", "pb b1?", "Flash lock", "pb b3?", #pb = bits relate to playback, perhaps sensor on/off?
                "b4", "b5", "b6", "b7",
                "b8", "b9", "b10", "Lcd0?",
                "Lcd1?", "b13", "b14", "Evf?"],
       0x04 : ["Lens b0?", "b1", "Lens b2?", "b3",
                "b4?", "Q", "b6", "b7", #b4 rel to lcd off evf off?
                "b8", "b9", "pi b10?", "b11", #rel to power off
                "po b12?", "b13", "b14", "b15"],
       0x0C : ["b0", "b1", "b2", "b3",
                "b4", "b5", "SD Sensor0", "SD Sensor1",
                "b8", "b9", "b10", "b11",
                "b12", "b13", "b14", "b15"]
    }
    x = key_map.get(p, None)
    print("b16:", hex(b16))
    if x is None:
       x = ["b0", "b1", "b2", "b3",
                "b4", "b5", "b6", "b7",
                "b8", "b9", "b10", "b11",
                "b12", "b13", "b14", "b15"]
    txt = ''
    for i in range(0,16):
        if b16 & 1:
           txt += x[i] + '- '
        else:
           txt += x[i] + '+ '
        txt += ","
        b16 = (b16 >> 1) & 0xFFFF
    return txt

def _exp_cmd01(jig,argv):
    p = argv.port
    if p < 0 or p > 0x0f:
        print("Note: XE2 invalid GPIO port", p)
    old_value = None
    count = 0
    while True:
        try:
            jig.app80_request(0x01, [p&0xf])
        except Exception as e:
            print(e)
            raise
        time.sleep(0.05)
        r = jig.app80_response()
        h, l = r[2:4]
        new_value = struct.unpack('>H', r[2:4])[0]
        if old_value is None:
            print("GPIO port 0x{:02x}".format(p))
        elif new_value == old_value:
            time.sleep(0.2)
            continue
        old_value = new_value
        keys = ''
        print("{:04d} le value 0x{:02x}{:02x} Lo {:08b}b Hi {:08b}b ".format(count, h, l, l , h))
        count += 1
        keys = gpio_bit_name(p, new_value)
        if keys:
           print(keys)
        time.sleep(0.2)
    return

def _exp_cmd02(jig,argv):
    p = argv.sensor
    if p < 0 or p > 0x0d:
        print("Note: XE2 invalid A/D port", p)
    old_value = None
    count = 0
    while True:
        jig.app80_request(0x02, [p&0xf])
        time.sleep(0.1)
        r = jig.app80_response()
        h, l = r[2:4]
        new_value = struct.unpack('>H', r[2:4])[0]
        if old_value is None:
            print("Analog sensor 0x{:02x}".format(p))
        elif new_value == old_value:
            time.sleep(0.2)
            continue
        old_value = new_value
        keys = ''
        print("{:04d} le value 0x{:02x}{:02x} {:d}".format(count, h, l, new_value))
        count += 1
        time.sleep(0.2)
    return

