#!/bin/sh
find . -type f -name pubkey.der -exec md5sum {} +
