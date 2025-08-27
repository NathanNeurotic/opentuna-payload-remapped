#!/bin/sh
set -e

test -s ps2-packer/ps2-packer
# payload-packed.elf produced by launcher-boot and launcher-keys
for f in launcher-boot/payload-packed.elf launcher-keys/payload-packed.elf exploit/payload.elf; do
  if [ ! -s "$f" ]; then
    echo "Missing or empty $f" >&2
    exit 1
  fi
done

echo "Smoke test passed"
