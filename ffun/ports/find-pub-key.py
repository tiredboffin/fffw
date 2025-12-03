#!/usr/bin/env python3
import argparse
import mmap
from ecdsa import VerifyingKey, NIST256p
from ecdsa.keys import MalformedPointError

PAT_LEN = 72
TAIL_ZEROS_LEN = 7

def is_valid_p256_point(xy: bytes) -> bool:
    try:
        VerifyingKey.from_string(xy, curve=NIST256p, validate_point=True)
        return True
    except (MalformedPointError, AssertionError, ValueError):
        return False

def find_pubkeys(path: str):
    with open(path, "rb") as f, mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) as m:
        off = m.find(b"\x04", 0)
        while off != -1:
            if off + PAT_LEN <= len(m):
                tail_start = off + 1 + 64
                if m[tail_start: tail_start + TAIL_ZEROS_LEN] == b"\x00" * TAIL_ZEROS_LEN:
                    if is_valid_p256_point(m[off + 1 : off + 65]):
                        yield off, m[off: off + 65]
            off = m.find(b"\x04", off + 1)

def main():
    ap = argparse.ArgumentParser(
        description="Find and validate NIST P-256 uncompressed pubkeys"
    )
    ap.add_argument("file", help="Path to binary file")
    ap.add_argument("--print-offset", action="store_true",
                    help="Print offset of the found key in file and exit")
    args = ap.parse_args()

    hits = list(find_pubkeys(args.file))
    if args.print_offset:
        print("offset\tkey65_hex")
        for off, key65 in hits:
            print(f"0x{off:0x}\t{key65.hex()}")
    else:
        for i, (_, key65) in enumerate(hits):
            print(key65.hex())
            vk = VerifyingKey.from_string(key65[1:], curve=NIST256p, validate_point=True)
            fn = "pubkey" if i == 0 else f"pubkey{i}"
            with open(f"{fn}.pem", "wb") as f:
                f.write(vk.to_pem())
            with open(f"{fn}.der", "wb") as f:
                f.write(vk.to_der())

if __name__ == "__main__":
    main()
