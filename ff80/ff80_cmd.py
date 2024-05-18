import ffjlib

#experimental, press Ctrl-C to interrupt
def dump_syslog(jig, fn, size = 0):
    import time
    read_bytes = 0

    print('syslog: dumping to', fn, '\n', 'Ctrl-C to interrupt.')

    xf7 = jig.set_config_usb_debug(1)
    try:
        with open(fn, 'wb') as log:
            while size == 0 or read_bytes < size:
                r = jig.debug_read_log(0x100)
                if len(r) == 0:
                    time.sleep(0.5)
                else:
                    log.write(r)
                    read_bytes += len(r)
                if size !=0 and read_bytes >= size:
                    break;
    except KeyboardInterrupt:
        pass
    finally:
        jig.set_config_usb_debug(xf7)
    print('syslog: read', read_bytes, 'bytes')

def syslog(jig, fn):
    if fn is not None:
        dump_syslog(jig, fn)
        return
    xf7 = jig.set_config_usb_debug(1)
    print('syslog:', end = '')
    log_size = 0
    while True:
        r = jig.debug_read_log(0x100)
        if len(r) == 0:
            break
        if log_size == 0 and len(r) >= 20 and r[0:6] == b'syslog':
            print(r[0:19].decode('ascii'), end =' ')
        log_size += len(r)
    print(' got', log_size, 'bytes')
    jig.set_config_usb_debug(xf7)

def ping(jig):
    print('ping', jig.ftl.ping().hex())
    print('nop', jig.ftl.nop().hex())

def bootrom(jig, fn = None):
    import hashlib

    n = jig.get_device_info(4)
    if n in ['X-E2', 'X-A2', 'X-T1', 'X-M1', 'X-T10']:
        try:
            xf7 = jig.set_config_usb_debug(1)
            r = jig.debug_read_ram(0x80000000+0x3ff0, size = 0x10)
            if len(r) == 0x10 and r[0:4] == b'JASM':
                r = jig.debug_read_ram(0x80000000, size = 0x4000)
                if hashlib.sha1(r).hexdigest() == 'bed698ed1d91b5c29ce7c5d650156e6100c32cce':
                    print('Found FF4227 bootrom')
                else:
                    print('Found unknown bootrom', len(r), hashlib.sha1(r).hexdigest() )
                if fn is not None:
                    with open(fn, 'wb') as f:
                        l = f.write(r)
                        print('Saved' , l, 'bytes to', fn)
            else:
                print('No bootrom at 0x80000000', r[0:16])
                jig.set_config_usb_debug(xf7)
        except:
            pass
    else:
        print('Model', n, 'is not supported')

def dummy(jig):
    import hashlib
    print('dummy data:', end=' ')
    r = jig.read_data_test('dummy')
    print('got', len(r), 'bytes', end = ' ')
    if hashlib.sha1(r).hexdigest() == 'f04977267a391b2c8f7ad8e070f149bc19b0fc25':
        print('hash check OK')
    else:
        print('hash check Failed')


def echo(jig):
    import hashlib
    from random import randbytes
    print('echo data:', end=' ')

    test_data = randbytes(0x10000)
    r = jig.write_data_test(test_data,'echo')
    print('sent', r, 'bytes', end = ' ')

    jig.ftl.nop() #BUGBUG: NOP or delay is required after write_data() - TBC

    if len(test_data) == r:
        #read test data from the camera
        r = jig.read_data_test('echo')
        if hashlib.sha1(r).hexdigest() == hashlib.sha1(test_data).hexdigest():
            print('hash check OK')
        else:
            print('hash check Failed')
    else:
        print(' Failed:', 'expected', 0x10000, 'bytes')


