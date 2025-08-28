#!/bin/sh
set -e

# Build host tool
make -C ps2-packer ps2-packer

# Build payloads and exploit
make -C launcher-boot
make -C launcher-keys
make -C exploit

# Verify generated binaries
for f in ps2-packer/ps2-packer launcher-boot/payload-packed.elf launcher-keys/payload-packed.elf exploit/payload.elf; do
  if [ ! -s "$f" ]; then
    echo "Missing or empty $f" >&2
    exit 1
  fi
done

echo "CI smoke test passed"
