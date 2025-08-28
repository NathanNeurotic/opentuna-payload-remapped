# Migration Notes

## Overview
The project has been updated from an early ps2sdk (~2008) to the current
[ps2dev/ps2sdk](https://github.com/ps2dev/ps2sdk) toolchain. Builds now run
with strict warnings and are tested in CI inside the `ps2dev/ps2dev:v1.3.0`
Docker image.

## Inventory
| Legacy item | Modern equivalent | Notes |
|-------------|------------------|-------|
| Custom type `u8` | `uint8_t` | Replaced throughout code.
| `<kernel.h>` pedantic enum warnings | `compat/compat.h` wrapper | Suppresses GCC `-Wpedantic` warning for large enum values in ps2sdk headers.

No other deprecated ps2sdk APIs were detected; existing calls such as
`SifLoadElf` and `sbv_patch_disable_prefix_check` remain valid.

## Toolchain
- **Docker image**: `ps2dev/ps2dev:v1.3.0`
- **Environment variables**:
  - `PS2DEV=/usr/local/ps2dev`
  - `PS2SDK=$PS2DEV/ps2sdk`
  - `GSKIT=$PS2DEV/gsKit`
  - `PATH=$PATH:$PS2DEV/bin`

## Source changes
- Introduced `compat/compat.h` and `compat/compat.c` to centralise
  compatibility shims and to wrap `<kernel.h>` with a pedantic suppression.
- Added `mk/toolchain.mk` used by all Makefiles to enable strict warnings and
  standard include/lib paths.
- Converted build smoke test to `scripts/ci-smoke.sh`.

## Build system
- Makefiles normalised to include `mk/toolchain.mk` and link against
  `ps2sdk`/`gsKit` using environment variables.
- GitHub Actions workflow `.github/workflows/ci.yml` runs
  `scripts/ci-smoke.sh` inside the ps2dev container and uploads the resulting
  `.elf` files.

## Compiler notes
- `<kernel.h>` from ps2sdk defines enumerators outside the range of `int`,
  which triggers `-Wpedantic`; the wrapper in `compat/compat.h` suppresses
  this warning.

## Test strategy
- `scripts/ci-smoke.sh` builds `ps2-packer`, `launcher-boot`,
  `launcher-keys`, and `exploit`, then verifies artefacts are non-empty.
- CI runs this script on every push and pull request.

## Revisions
- none
