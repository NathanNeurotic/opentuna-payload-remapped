# Migration Notes

## Overview
This project historically depended on an early ps2sdk distribution (~2008).
It has been migrated to build against the actively maintained
[ps2dev/ps2sdk](https://github.com/ps2dev/ps2sdk) toolchain and gsKit.
All build files now assume the standard environment variables provided by the
ps2dev toolchain.

## Toolchain
- **Docker image**: `ps2dev/ps2dev:v1.3.0`
- **Environment variables**:
  - `PS2DEV=/usr/local/ps2dev`
  - `PS2SDK=$PS2DEV/ps2sdk`
  - `GSKIT=$PS2DEV/gsKit`
  - `PATH=$PATH:$PS2DEV/bin`

## Source changes
- Added strict warning flags (`-Wall -Wextra -Werror -Wpedantic`) to all
  Makefiles.
- Replaced legacy `u8` usage with standard `<stdint.h>` types and removed
  non‑standard `inline` entry point in `exploit/main.c`.
- Annotated unused parameters in launcher payloads to allow clean compilation
  with `-Werror`.
- Modernised `ps2-packer` sources to use `size_t` for file operations and to
  safely obtain function pointers from `dlsym`/`get_symbol`.
- Added `smoke_test.sh` to verify that expected build artefacts exist.

## Build system
- New GitHub Actions workflow `.github/workflows/ci.yml` builds all
  components inside the pinned ps2dev container and runs the smoke test.
- Workflow caches the `ps2-packer` binary to speed up subsequent builds.

## Compiler errors encountered
Initial builds of the EE components failed with:
```
Makefile:31: /samples/Makefile.eeglobal: No such file or directory
```
indicating that the `PS2SDK` environment was not configured. Using the
ps2dev toolchain resolves this by providing `samples/Makefile.eeglobal`.

## Risk & mitigation
- **Dependency availability**: build relies on the ps2dev Docker image.
  Pinned version mitigates unexpected changes.
- **Function pointer casts**: resolved with `memcpy` copies to satisfy
  ISO C rules under `-Wpedantic`.

## Test strategy
- CI builds `ps2-packer`, `exploit`, `launcher-boot` and `launcher-keys`.
- `smoke_test.sh` verifies the resulting binaries are non‑empty.

## Revisions
None.
