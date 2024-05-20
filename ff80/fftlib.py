#ff transport library
#
#usb control transfer is used to transfer a 12 bytes 'request'
#the request body is sent (or received - for read op) via bulk transfer
#
#identified  'requests':
#   03 -- ?? returns a constant
#   1d -- ?? returns err
#   c0 -- open a 'session'
#   c2 -- ping? or check session is alive - returns 2 bytes 'session id'
#   c4 -- close session
#   d0 -- write_cmd  - send a command request
#   d1 -- read_cmd   - get command result
#   e0 -- write_data - bulk write
#   e1 -- read_data  - bulk read
#   e8 -- nop ?      - returns 4 bytes, zero-es confirm confirmation of long op (?)

import usb1
import struct

trace = False

class ftl:
    def __auto_ep(self, EP_IN, EP_OUT):
        self.EP_IN, self.EP_OUT = EP_IN, EP_OUT
        if self.EP_IN is not None and self.EP_OUT is not None:
            return
        s = next(
            next(
                next(
                    self.usb_h.getDevice().iterConfiguations()
                ).iterInterfaces()
                ).iterSettings()
            )
        assert s.getNumEndpoints() == 3

        for e in s.iterEndpoints():
            if e.getAttributes() == usb1.TRANSFER_TYPE_BULK:
                a = e.getAddress()
                if (a & 0x80) == 0:
                    self.EP_OUT = a
                else:
                    self.EP_IN = a
        assert self.EP_OUT is not None and self.EP_IN is not None

    def __init__(self,usb_h, EP_IN = None, EP_OUT = None):
        self.usb_h = usb_h
        self.ms = 5000
        self.sid = None
        self.trace = trace
        self.__auto_ep(EP_IN, EP_OUT)

    def open_session(self):
        cmd = bytearray([0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00])
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER  , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkRead(self.EP_IN, 8, timeout=self.ms)
        if self.trace:
            print('ftl.open_session br', r.hex())
        self.sid, self.max_pkt_size = struct.unpack('<H', r[0:2])[0], struct.unpack('>I', r[-4:])[0]

    def ping(self):
        cmd = bytearray([0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00])
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkRead(self.EP_IN, 2, timeout=self.ms)
        if self.trace:
            print('ftl.ping  br', r.hex())
        return r

    def close_session(self):
        cmd = bytearray([0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00])
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r =  self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER  , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkRead(self.EP_IN, 2, timeout=self.ms)
        if self.trace:
            print('ftl.close_session br', r.hex())

    def nop(self):
        return self._bread_raw_cmd(0xe8, 32, 32)

    def write_cmd(self, wbuf):
        cmd = bytearray([0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        cmd[6:10] = len(wbuf).to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkWrite(self.EP_OUT, wbuf, timeout=self.ms)
        if self.trace:
            print('ftl.write_cmd bw', hex(r))
        assert r == len(wbuf)

    def read_cmd(self, size = 256):
        cmd = bytearray([0xd1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        cmd[6:10] = size.to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkRead(self.EP_IN, size, timeout=self.ms)
        if self.trace:
            print('ftl.read_cmd br', r.hex())
        return r

    def _bread_raw_cmd(self, cmd_code, cmd_param, size, wbuf = None):
        cmd = bytearray(12)
        cmd[0] = cmd_code & 0xff
        cmd[6:10] = cmd_param.to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        if trace:
            print('ftl.raw_cmd br', hex(r))
        assert r == len(cmd)
        r = self.usb_h.bulkRead(self.EP_IN, size, timeout=self.ms)
        if self.trace:
            print('ftl.bread_raw_cmd br', r.hex())
        return r


    def read_data(self, size = 256):
        cmd = bytearray([0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        cmd[6:10] = size.to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        ofs = 0
        data = bytearray(0)
        cmd[2:6] =  ofs.to_bytes(4, 'big')
        cmd[6:10] = size.to_bytes(4, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        #BUGBUG?
        while size > 0:
            r = self.usb_h.bulkRead(self.EP_IN, size, timeout=self.ms)
            if self.trace:
                print('ftl.read_data br', 'ofs', hex(ofs), 'size', size, '[0..32]:', r[0:min(32, len(r))].hex())
            size -= len(r)
            ofs  += len(r)
            data += r
        return data

    def write_data(self, data):
        cmd = bytearray([0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        cmd[6:10] = len(data).to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkWrite(self.EP_OUT, data, timeout=self.ms)
        if self.trace:
            print('ftl.write_data bw', hex(r))
        return r

    def req03(self, data):
        assert False, 'Not implemented'
        cmd = bytearray([0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        assert len(data) < 0x100
        cmd[6:10] = len(data).to_bytes(4, 'big')
        cmd [10:12] = self.sid.to_bytes(2, 'big')
        r = self.usb_h.controlWrite(usb1.REQUEST_TYPE_VENDOR|usb1.RECIPIENT_OTHER , 0, 0, 0,  cmd, self.ms)
        assert r == len(cmd)
        r = self.usb_h.bulkWrite(self.EP_OUT, data, timeout=self.ms)
        if self.trace:
            print('ftl.req03 br', r.hex())
        return r

        assert False

