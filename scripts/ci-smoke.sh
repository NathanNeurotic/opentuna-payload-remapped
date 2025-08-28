#!/bin/sh
set -e

# This script is intended to be run from the root of the repository.
# It can be run locally or in a CI environment.

# Set up toolchain environment if not already set
export PS2DEV=${PS2DEV:-/usr/local/ps2dev}
export PS2SDK=${PS2SDK:-$PS2DEV/ps2sdk}
export GSKIT=${GSKIT:-$PS2DEV/gsKit}
export PATH=$PATH:$PS2DEV/bin

# --- Build everything ---
echo "Building ps2-packer..."
make -C ps2-packer

echo "Building launcher-boot..."
make -C launcher-boot

echo "Building launcher-keys..."
make -C launcher-keys

echo "Building exploit (default payload: launcher-keys)..."
make -C exploit

echo "Building exploit (payload: launcher-boot)..."
make -C exploit PAYLOAD=launcher-boot clean all

# --- Smoke Test ---
echo "Running smoke tests..."

test -f ps2-packer/ps2-packer && echo "ps2-packer OK"
test -s ps2-packer/ps2-packer && echo "ps2-packer size OK"

test -f launcher-boot/payload.elf && echo "launcher-boot/payload.elf OK"
test -s launcher-boot/payload.elf && echo "launcher-boot/payload.elf size OK"
test -f launcher-boot/payload-packed.elf && echo "launcher-boot/payload-packed.elf OK"
test -s launcher-boot/payload-packed.elf && echo "launcher-boot/payload-packed.elf size OK"

test -f launcher-keys/payload.elf && echo "launcher-keys/payload.elf OK"
test -s launcher-keys/payload.elf && echo "launcher-keys/payload.elf size OK"
test -f launcher-keys/payload-packed.elf && echo "launcher-keys/payload-packed.elf OK"
test -s launcher-keys/payload-packed.elf && echo "launcher-keys/payload-packed.elf size OK"

test -f exploit/payload.bin && echo "exploit/payload.bin OK"
test -s exploit/payload.bin && echo "exploit/payload.bin size OK"

echo "All builds and smoke tests passed!"
