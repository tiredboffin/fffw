#ffj  jig library
#uses fft - transport library to send commands to the camera

import struct

trace = False

class jig_exception(Exception):
    pass

class jig:

    def __init__(self, ftl):
        #transport lib handle
        self.ftl = ftl
        self.trace = trace
        self.TO = {}

    def _mem_op(self, op, f_code, f_param, read_size = 0, data = bytearray()):
        #basic low level request/response op
        ff = self.ftl
        assert len(f_param) == 16
        buf = bytearray(20+len(f_param)+len(data))
        buf[0:4]= op.to_bytes(4, 'little')
        buf[16:20] = f_code.to_bytes(4, 'little')
        buf[20:20+16] = f_param[:]
        if len(data):
            buf[36:36+len(data)] = data[:]
        r = ff.write_cmd(buf)
        r = ff.read_cmd(read_size+20+16)
        u0, errcode1, errcode2, u1, u2 = struct.unpack('<5I', r[0:20])
        if errcode1 != 0:
            raise jig_exception({'_mem' : hex(op), 'err1': hex(errcode1), 'err2': hex(errcode2)})
        assert u0 == op
        assert u1 == 0
        assert u2 == f_code
        return r[20:]

    #experimental, should use _mem_op
    def get_device_info(self, tag):
        #get predefined text info data, for supprted tags see info_tags()
        ff = self.ftl
        cmd = bytearray(32)
        cmd[0:4] = 0x150000.to_bytes(4, 'little')
        cmd[16:20] = tag.to_bytes(4, 'little')
        ff.write_cmd(cmd)
        r = ff.read_cmd(128)
        if self.trace:
            print('get_device_info', r.hex())
        cmd_code, errcode1, errcode2, u1 = struct.unpack('<4I', r[0:16])
        assert cmd_code == 0x150000
        if errcode1 == 0:
            return r[16:].decode('UTF-16').encode('ascii').rstrip(b'\0').decode('ascii')
        elif not (errcode1 == 9 and errcode2 == 3): #not found?
            raise jig_exception({'ged_device_info err1': hex(errcode1), 'err2': hex(errcode2)})
        return ''

    def info_tags(self):
        return {
            0x01:   'Vendor Name',
            0x02:   'Manufacturer',
            0x04:   'Product Name',
            0x08:   'FW Version?',
            0x10:   'Device Type',
            0x20:   'Serial Number',
            0x40:   'Framework',
            0xf0001:'FW Download Status?',      #result of memop x660002: 'NORMAL', WRITING' or 'FAILED'
            0xf0002:'FW Reset Download Status?',#set result of xx660002 to 'NORMAL' and return it
        }

    def get_config_data_size(self, mb = 1):
        #return config data size and max read chunk/page size (?)
        params = bytearray(16)
        mb = mb != 0
        params[0:4] = mb.to_bytes(4, 'little')
        r = self._mem_op(0x1a0002, 1, params, 12)
        if self.trace:
            print('get_config_data_size', r.hex())
        if len(r) > 0:
            u0, u1, mem_size, max_read = struct.unpack('<4I', r[0:16])
            assert u0 == mb
            assert u1 == 0
            assert max_read == 0x100
            return mem_size, max_read
        return 0, 0

    def read_config_data(self, page_no, ofs, size, mb = 1):
        #read config data
        params = bytearray(16)
        mb = mb != 0
        params[0:4] = mb.to_bytes(4, 'little')
        params[4:8] = page_no.to_bytes(4, 'little')
        params[8:12] = ofs.to_bytes(4, 'little')
        params[12:16] = size.to_bytes(4, 'little')
        r = self._mem_op(0x1a0002, 2, params, size)
        if self.trace:
            print('read_config_data', r.hex())
        if len(r) == 0:
            return r
        assert r[0:16] == params[0:16]
        return r[16:]

    def get_config_data_byte(self, tag, mb = 1):
        r = self.read_config_data(0, tag, 1, mb = mb)
        return struct.unpack('B', r)[0]

    def get_config_data_word(self, tag, mb = 1):
        r = self.read_config_data(0, tag, 2,  mb = mb)
        return struct.unpack('<H', r)[0]

    def known_config_params(self):
        #some known/guessed config parameters
        return [
            [0x0A2,  'B',  '?Mask: enable auto script mode?'],
            [0x0D8,  'B',  '?FW Overwrites to 0x80?'],
            [0x0F7,  'B',  '?Mask: enable USB debug?'],
            [0x100,  '<H',  'USB Device Vendor'],
            [0x102,  '<H',  'USB Default Product Id'],
            [0x106,  '20s', 'USB Camera Name'],
            [0x11b,  '30s', 'USB Serial Number'],
            [0x13a,  '<H',  'USB JIG Product Id ?'],
            [0x13e,  '<H',  'USB PTP Product Id ?'],
            [0x146,  '5s',  'Default Directory Name'],
            [0x14B,  '4s',  'Default File Name Prefix'],
            [0x15c,  '19s', 'Exif Camera Name'],
            [0x16f,  '12s', 'Exit Manufacturer Name?'],
            [0x1e8,  'BB',  'EEP Version?'],
            [0x1ea,  'BB',  'EEP Month/Day?', '{:02d}/{:02d}'],
            [0x204,  'BB',  '?FW Ovewrites, Version?'],
            [0x266,  'B',   '?Mask: Save post mortem log?'],
        ]

    def write_config_data(self, page_no, ofs, data, mb = 1):
        #write data to RAM, debug must be enabled
        mb = mb != 0
        params = bytearray(16)
        params[0:4] = mb.to_bytes(4, 'little')
        params[4:8] = page_no.to_bytes(4, 'little')
        params[8:12] = ofs.to_bytes(4, 'little')
        params[12:16] = len(data).to_bytes(4, 'little')
        r = self._mem_op(0x1a0002, 3, params, data = data)
        if self.trace:
            print('write_config_data', r.hex())
        if len(r) == 0:
            return r
        assert r[0:16] == params[0:16]
        return r[16:]

    def set_config_data_byte(self, tag, v):
        self.write_config_data(0, tag, bytearray([v]))

    def set_config_data_word(self, tag, v):
        self.write_config_data(0, tag, struct.pack('<H', v))

    def app80_request(self, cmd, params = bytearray(0)):
        assert len(params) <= 32
        buf = bytearray(33)
        buf[0] = cmd
        buf[1:len(params)] = params[:]
        self.write_config_data(0, 0x80, buf)

    def app80_response(self):
        r = self.read_config_data(0, 0x80, 33)
        return r

    def set_config_usb_debug(self, v = 1):
        old_v = self.get_config_data_byte(0xf7)
        self.set_config_data_byte(0xf7, v)
        return old_v

    def get_config_usb_debug(self):
        old_v = self.get_config_data_byte(0xf7)
        return old_v

    def debug_read_log(self, size = 0x100):
        #read debug log, the log must be enabled otherwise return empty data
        params = bytearray(16)
        params[0:4] = size.to_bytes(4, 'little')
        r = self._mem_op(0x200001, 1, params, size)
        if self.trace:
            print('debug_read_log', r.hex())
        u0, u1 = struct.unpack('<2I', r[0:8])
        if u0:
           raise jig_exception({'debug_read_log err1': hex(u0), 'err2': hex(u1)})
        return r[8:8+u1]

    def debug_read_ram(self, mem_addr, size = None):
        #read RAM, debug must be enabled
        if size is None:
            size = self.ftl.max_pkt_size
        params = bytearray(16)
        data = bytearray(0)
        while size > 0:
            params[8:12] = mem_addr.to_bytes(4, 'little')
            params[12:16] = min(size, self.ftl.max_pkt_size).to_bytes(4, 'little')
            r = self._mem_op(0x200001, 2, params, size)
            if self.trace:
                print('debug_read_ram', r.hex())
            assert r[0:16] == params[0:16]
            mem_addr += len(r[16:])
            size -= len(r[16:])
            data += r[16:]
        return data

    def debug_read_ram_b(self,tag):
        r = self.debug_read_ram(tag, 1)
        return struct.unpack('B', r)[0]

    def debug_read_ram_w(self,tag):
        r = self.debug_read_ram(tag, 2)
        return struct.unpack('<H', r)[0]

    def debug_read_ram_dw(self,tag):
        r = self.debug_read_ram(tag, 4)
        return struct.unpack('<I', r)[0]

    def debug_write_ram(self, mem_addr, data):
        #write RAM, debug must be enabled
        params = bytearray(16)
        params[8:12] = mem_addr.to_bytes(4, 'little')
        params[12:16] = len(data).to_bytes(4, 'little')
        r = self._mem_op(0x200001, 3, params, data = data)
        if self.trace:
            print('debug_write_ram', r.hex())
        assert r[0:16] == params[0:16]
        return r[16:]

    def debug_send_key(self, key, state):
        #Send a key or change mode, debug must be enabled
        data = (key + ' ' + state + '\n').encode('ascii')
        params = bytearray(16)
        params[12:16] = len(data).to_bytes(4, 'little')
        r = self._mem_op(0x200001, 5, params, data = data)
        if self.trace:
            print('debug_send_key', r.hex())
        assert r[0:16] == params[0:16]
        return r[16:]

    #experimental
    def debug_cmdline_req(self, str):
        #TODO
        ff = self.ftl
        data = str.encode('ascii')
        buf = bytearray(24+len(data)+4)
        buf[0:4]     = 0x200001.to_bytes(4, 'little')
        buf[16:20]   = 0x6.to_bytes(4, 'little')
        buf[20:20+4] = len(data).to_bytes(4, 'little')
        if len(data):
            buf[24:24+len(data)] = data[:]
        r = ff.write_cmd(buf)
        r = ff.read_cmd(0x32)
        if self.trace:
            print('debug_cmdline_req', r.hex())
        assert r[0:24] == buf[0:24]
        return r[24:]

    def debug_cmd_line_rsp(self, rsize = 0x100):
        ff = self.ftl
        buf = bytearray(32)
        buf[0:4]= 0x200001.to_bytes(4, 'little')
        buf[16:20] = 0x7.to_bytes(4, 'little')
        buf[20:20+4] = rsize.to_bytes(4, 'little')
        r = ff.write_cmd(buf)
        r = ff.read_cmd(rsize+32)
        if self.trace:
            print('debug_cmdline_rsp', r.hex())
        u0, u1, u2, u3, u4 = struct.unpack('<5I', r[0:20])
        assert r[0:20] == buf[0:20]
        u0, u1, u2 = struct.unpack('<3I', r[20:32])
        return u0, u1, r[32:32+u2].decode('ascii') if u2 > 0 else ''

    #experimental
    def get_timeouts(self):
        #TBC: get timeouts in ms for long data operations
        ff = self.ftl
        params = bytearray(16)
        params[0:4] = 0x100.to_bytes(4, 'little')
        r = self._mem_op(0x580000, 0, params)
        if self.trace:
            print('get_timeouts', r.hex())
        assert len(r) == 12
        size, u1, u2 = struct.unpack('<3I', r[0:12])
        if size > 0 and u1 == 0 and u2 == 0:
            r = ff.read_data(size)
            if self.trace:
                print('get_timeouts', r.hex())
            n, _, _, _ = struct.unpack_from('<4I', r)
            assert n > 0
            ofs  = 16
            while n > 0:
                op, to = struct.unpack_from('<2I', r, ofs)
                ofs += 8
                n -= 1
                self.TO.update({op: to})
            return r
        else:
            raise jig_exception({'err1': hex(u1), 'err2': hex(u2)})

    def unk_1a0001(self):
        #TBC: return d55.104.high_bit && d54.9c.bit14
        params = bytearray(16)
        r = self._mem_op(0x1a0001, 0, params)
        if self.trace:
            print('unk_1a0001', r.hex())
        return r

    ###Experimental staff
    def read_data_test(self, op):
        #op = 0     return 64k of bytes 0..ff
        #op = 0x100 echo bytes back

        if op == 'echo':
            op = 0x100
        else:
            op = 0x0

        ff = self.ftl
        cmd = bytearray(32)
        cmd[0:4] = 0x550001.to_bytes(4, 'little')
        cmd[16:20] = op.to_bytes(4, 'little')
        ff.write_cmd(cmd)
        r = ff.read_cmd(0x20)
        if self.trace:
            print('read_data_test ..', r[0:min(0x40, len(r))].hex())
        cmd_code, errcode1, errcode2, u1, u2, size, u3, u4  = struct.unpack('<8I', r[0:0x20])
        assert cmd_code == 0x550001
        if errcode1 == 0:
            if op == 0 and size == 0x10000:
                r = ff.read_data(size)
            elif op == 0x100 and size > 0:
                r = ff.read_data(size)
            elif op == 0x100 and size == 0:
                r = bytearray(0)
            else:
                raise jig_exception({'read data test unexpected result size': size})
        else:
            raise jig_exception({'read_data_test' : hex(op), 'err1': hex(errcode1), 'err2': hex(errcode2)})
        return r

    def write_data_test(self, data, op):
        #op = 0     return 64k of bytes 0..ff
        #some size? = 0x100
        if op == 'echo':
            op = 0x100
        else:
            op = 0

        ff = self.ftl
        cmd = bytearray(32)
        cmd[0:4] = 0x760001.to_bytes(4, 'little')
        cmd[20:24] = len(data).to_bytes(4, 'little')
        cmd[24:28] = op.to_bytes(4, 'little')
        ff.write_cmd(cmd)
        r = ff.read_cmd(0x20)
        if self.trace:
            print('write_data_test', r.hex())
        cmd_code, errcode1, errcode2, u1, u2, size, u3, u4  = struct.unpack('<8I', r[0:0x20])
        assert cmd_code == 0x760001
        if errcode1 == 0:
            r = ff.write_data(data)
            if trace:
                print('write data write_data:', hex(r))
        else:
            raise jig_exception({'write_data_test' : hex(op), 'err1': hex(errcode1), 'err2': hex(errcode2)})
        return r

    ####
    #TODO: examples do not belong here
    def print_known_config_params(self, mb = 1):
        config_params = self.known_config_params()
        print('===Known config params:', 'RAM' if mb else 'ROM')
        for p in config_params:
            if len(p) == 4:
                pfmt = p.pop()
            else:
                pfmt = None

            tag, fmt, desc = p

            size = struct.calcsize(fmt)
            r = self.read_config_data(0, tag, size, mb = mb)
            v = struct.unpack(fmt, r)

            if size > 2:
                print('{:03X} {:s}: {:s}'.format(tag, desc, v[0].decode('ascii')))
            else:
                if pfmt is None:
                    if len(v) == 1:
                        pfmt = '{:04X}'
                    else:
                        pfmt = '{:02X}.{:02X}'
                pfmt = '{:03X} {:s}: ' + pfmt
                print(pfmt.format(tag, desc, *v))

    def dump_config_data(self, file_name, mb = 1):
        ff = self.ftl
        config_data_size, max_read = self.get_config_data_info(mb)
        print('==Config data size: 0x{:06x}'.format(config_data_size))
        with open(file_name, 'wb') as f:
            ofs = 0
            while config_data_size > 0:
                if ofs % 0x40000 == 0:
                    print('{:06x}'.format(ofs))
                r = self.read_config_data(0, ofs, max_read, mb = mb)
                if len(r) == 0:
                    break
                config_data_size -= len(r)
                ofs += len(r)
                f.write(r)
        print('=== 0x{:06x}'.format(ofs))

    def dump_ram(self, file_prefix, ofs = 0, size = None):
        ff = self.ftl
        print('===Dump RAM')
        with open('{:s}-{:08X}.bin'.format(file_prefix, ofs), 'wb') as out:
            count = 0
            while size is None or size > 0:
                if (count % 0x10000) == 0:
                    print(hex(count//0x10000))
                r = self.debug_read_ram(ofs, 0x100)
                if len(r) == 0:
                    break
                out.write(r)
                ofs += len(r)
                count += len(r)
                if size is not None:
                    size -= len(r)
            print('===Dump RAM:', hex(ofs))
