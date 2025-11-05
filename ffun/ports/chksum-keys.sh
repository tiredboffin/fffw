#!/bin/sh
#find . -type f -name pubkey.der -exec md5sum {} +
if [ "$(find . -type f -name "pubkey.der" -exec md5sum {} + | awk '{print $1}' | sort | uniq -d | wc -l)" -gt 0 ]; then
  echo "matches found?!"
  exit 0
else
  echo "OK"
  exit 1
fi
