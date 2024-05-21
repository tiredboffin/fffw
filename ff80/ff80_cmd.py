#experimental ff80 functions

import ffjlib

def cmd_syslog(jig, args):
    fn = args.output
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

def dump_syslog(jig, fn, size = 0):
    #experimental, press Ctrl-C to interrupt
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

def cmd_info(jig, args):
    tag_names = jig.info_tags()
    for tag in [1,2,4,8,0x10,0x20, 0x40]:
        r = jig.get_device_info(tag)
        if len(r) > 0:
            print('{:02x} {:s}: {:s}'.format(tag, tag_names.get(tag, ''),  r))

def cmd_ping(jig, args):
    print('ping', jig.ftl.ping().hex())
    print('nop', jig.ftl.nop().hex())

def cmd_bootrom(jig, args):
    import hashlib
    fn = args.output
    size = args.size

    n = jig.get_device_info(4)
    if n in ['X-E2', 'X-A2', 'X-T1', 'X-M1', 'X-T10']:
        addr = 0x80000000
        if size is None:
            size = 0x4000
        try:
            xf7 = jig.set_config_usb_debug(1)
            r = jig.debug_read_ram(addr+0x3ff0, size = 0x10)
            if len(r) == 0x10 and r[0:4] == b'JASM':
                r = jig.debug_read_ram(addr, size = size)
                if len(r) == 0x4000:
                    if hashlib.sha1(r).hexdigest() == 'bed698ed1d91b5c29ce7c5d650156e6100c32cce':
                        print('Found FF4227 bootrom at', hex(addr))
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
        print('boorom: model', n, 'is not supported')

def cmd_dummy(jig, args):
    import hashlib
    print('dummy data:', end=' ')
    r = jig.read_data_test('dummy')
    print('got', len(r), 'bytes', end = ' ')
    if hashlib.sha1(r).hexdigest() == 'f04977267a391b2c8f7ad8e070f149bc19b0fc25':
        print('hash check OK')
    else:
        print('hash check Failed')

def cmd_echo(jig, args):
    import hashlib
    from random import randbytes
    print('echo data:', end=' ')

    test_data = randbytes(0x10000)
    r = jig.write_data_test(test_data,'echo')
    print('sent', r, 'random bytes', end = ' ')

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

def cmd_cfgdata(jig, argv):
    if argv.action == 'read':
        return cfgdata_read(jig, argv)
    elif argv.action == 'write':
        return cfgdata_write(jig, argv)
    elif argv.action == 'dump':
        return cfgdata_dump(jig, argv)
    else:
        print(argv.command, 'action', argv.action, 'not implemented')

def cfgdata_write(jig, argv):

    ofs  = argv.address
    try:
        data = bytearray.fromhex(argv.data)
    except ValueError:
        print('wrong data: invalid hex string')
        return

    size = len(data)

    max_size, max_rw_size = jig.get_config_data_size()

    if size + ofs > max_size:
        print('Wrong data: cannot write', size, 'bytes', 'at address', hex(ofs))
        return

    if size > max_rw_size:
        print('Wrong data: cannot write more than', max_rw_size, 'bytes at once')
        return

    if size == 0:
        print('Wrong data: cannot write 0 bytes')

    r = jig.write_config_data(0, ofs, data)

    if len(data) == 1:
        print('cfg [0x{:0x}] <= 0x{:02x}'.format(argv.address, data[0]))
    else:
        print('cfg [0x{:0x}..0x{:0x}] {:d} bytes  <= {:s}'.format(argv.address,
                                                                    argv.address + len(data) + 1,
                                                                    len(data),
                                                                    data.hex().upper()))

def cfgdata_read(jig, argv):
    size = argv.size
    ofs  = argv.address
    fn   = argv.output

    max_size, max_rw_size = jig.get_config_data_size()

    if size == 0:
       size = max_size

    if size + ofs > max_size:
        size = max_size - ofs

    if size > max_rw_size and fn is None:
        print('To read more than ', max_rw_size, 'bytes', 'specify an output file name')
        size = max_rw_size

    data = bytearray(0)
    while size > 0:
        if ofs> 0 and ofs % 0x40000 == 0:
            print('Ofs: {:06x}'.format(ofs))
        r = jig.read_config_data(0, ofs, min(max_rw_size, size))
        if len(r) == 0:
            break
        size -= len(r)
        ofs += len(r)
        data += r
    if len(data) and fn is not None:
        with open(fn, 'wb') as out:
            l = out.write(data)
            print('saved {:d} bytes [0x{:0x}..0x{:0x}] to {:s}'.format(l, ofs, ofs + size, fn))
    else:
        if len(data) == 1:
            print('cfg [0x{:0x}] = 0x{:02x}'.format(argv.address, data[0]))
        else:
            print('cfg [0x{:0x}..0x{:0x}] {:d} bytes  = {:s}'.format(argv.address,
                                                                     argv.address + len(data),
                                                                     len(data),
                                                                     data.hex().upper()))

def cfgdata_dump(jig,argv):
    import time

    fn = argv.output
    if fn is None:
        print('cfgdata_dump: filename not specified')

    max_size, max_rw_size = jig.get_config_data_size()
    size = max_size
    ofs = 0
    count = 0

    data = bytearray(0)

    start_time = time.time()
    end_time = time.time()
    while size > 0:
        if (ofs % 0x10000) < 0x100:
            elapsed = time.time()-start_time+0.000001
            if time.time() - end_time  > 1.0:
                print('read {:d} bytes in {:.02f} seconds {:.02f} kB/s'.format(ofs, elapsed, ofs/elapsed/1000))
                end_time = time.time()

        r = jig.read_config_data(0, ofs, min(max_rw_size, size))
        if len(r) == 0:
            break
        size -= len(r)
        ofs += len(r)
        data += r
    elapsed = time.time()-start_time+0.000001
    print('read {:d} bytes in {:.02f} seconds {:.01f} kB/s'.format(ofs, elapsed, ofs/elapsed/1000.0))
    if len(data) and fn is not None:
        with open(fn, 'wb') as out:
            l = out.write(data)
            print('saved {:d} bytes [0x{:0x}..0x{:0x}] to {:s}'.format(l, 0, len(data), fn))

def cmd_ram(jig, argv):
    if argv.action == 'read':
        return ramdata_read(jig, argv)
    elif argv.action == 'write':
        return ramdata_write(jig, argv)
    elif argv.action == 'dump':
        return ramdata_dump(jig, argv)
    else:
        print(argv.command, 'action', argv.action, 'not implemented')

def ramdata_read(jig, argv):
    size = argv.size
    ofs  = argv.address
    fn   = argv.output
    if fn is None:
        if size > jig.ftl.max_pkt_size:
            print('To read more than ', jig.ftl.max_pkt_size, 'bytes', 'specify an output file name')
            return
        if size == 0:
            size = jig.ftl.max_pkt_size
        try:
            xf7 = jig.set_config_usb_debug(1)
            data = jig.debug_read_ram(ofs, size)
        finally:
            jig.set_config_usb_debug(xf7)
        print('ram [0x{:0x}..0x{:0x}] {:d} bytes  = {:s}'.format(argv.address,
                                                                argv.address + len(data),
                                                                len(data), data.hex().upper()))
    else:
        with open(fn, 'wb') as out:
            l = 0
            try:
                xf7 = jig.set_config_usb_debug(1)
                while size > 0:
                    if ofs> 0 and ofs % 0x40000 < jig.ftl.max_pkt_size:
                        print('Ofs: {:06x}'.format(ofs))
                    r = jig.debug_read_ram(ofs, size)
                    if len(r) == 0:
                        break
                    size -= len(r)
                    ofs += len(r)
                    l += out.write(r)
            finally:
                jig.set_config_usb_debug(xf7)
            print('saved {:d} bytes [0x{:0x}..0x{:0x}] to {:s}'.format(l, argv.address, argv.address + l, fn))

def ramdata_write(jig, argv):

    ofs  = argv.address

    fn = argv.input

    if fn is None:
        try:
            data = bytearray.fromhex(argv.data)
        except ValueError:
            print('wrong data: invalid hex string')
            return
    else:
        with open (fn, 'rb') as inp:
            data = inp.read()
    size = len(data)

    if size > jig.ftl.max_pkt_size:
        print('Writing of more than ', jig.ftl.max_pkt_size, 'bytes', 'not implemented (yet)')
        return
    try:
        xf7 = jig.set_config_usb_debug(1)
        r = jig.debug_write_ram(ofs, data)
        print('Unk:', r)
    finally:
        jig.set_config_usb_debug(xf7)
        if len(data) == 1:
            print('ram [0x{:0x}] <= 0x{:02x}'.format(argv.address, data[0]))
        else:
            print('ram [0x{:0x}..0x{:0x}] {:d} bytes  <= {:s}'.format(argv.address,
                                                                    argv.address + len(data) + 1,
                                                                    len(data),
                                                                    data.hex().upper()))

def ramdata_dump(jig, argv):
    import time

    fn = argv.output
    ofs = argv.address
    size = argv.size

    if size == 0:
        size = None

    #fn = '{:s}-{:08X}.bin'.format(file_prefix, ofs)

    print('Dump RAM at 0x{:08X} to {:s}'.format(ofs, fn))
    with open(fn, 'wb') as out:
        count = 0
        try:
            xf7 = jig.set_config_usb_debug(1)
            start_time = time.time()
            while size is None or size > 0:
                if (count % 0x10000) < 0x100:
                    elapsed = time.time()-start_time+0.000001
                    if elapsed > 10.0:
                        print('read {:d} bytes in {:.02f} seconds {:.02f} kB/s'.format(count, elapsed, count/elapsed/1000))
                end_time = time.time()
                r = jig.debug_read_ram(ofs)
                end_time = time.time()
                if len(r) == 0:
                    break
                out.write(r)
                ofs += len(r)
                count += len(r)
                if size is not None:
                    size -= len(r)
        finally:
            elapsed = time.time()-start_time+0.000001
            jig.set_config_usb_debug(xf7)
            print('read {:d} bytes in {:.02f} seconds {:.01f} kB/s'.format(count, elapsed, count/elapsed/1000.0))
            print('Dump RAM end address:', hex(ofs).upper())