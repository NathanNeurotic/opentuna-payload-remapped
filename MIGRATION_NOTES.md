# OpenTuna Modernization Migration Notes

This document outlines the changes made to the OpenTuna repository to modernize its build system and ensure it compiles cleanly with a modern ps2dev toolchain.

## Summary of Changes

1.  **Unified Makefile Template**:
    - A new file, `mk/Makefile.template`, was created to centralize the build settings for all PS2 ELF binaries. This template is based on the standard Makefiles found in the official ps2sdk samples.
    - All PS2-side Makefiles (`launcher-boot`, `launcher-keys`, `exploit`, `ps2-packer/stub`) were rewritten to be minimal and include this new template. This provides a consistent and modern build process across the entire project.

2.  **Compiler Flags**:
    - The `Makefile.template` sets strict warning flags: `-Wall -Wextra -Werror`. This will help to ensure code quality and catch potential bugs early.

3.  **C Code Fixes**:
    - Several issues in `ps2-packer/stub/main.c` were fixed to make it compatible with a modern, stricter compiler:
        - `DISABLE_PATCHED_FUNCTIONS()` and `DISABLE_EXTRA_TIMERS_FUNCTIONS()` were moved inside the `main()` function to fix a "data definition has no type" error.
        - The loop counter `i` was changed to `u32` to match the type of `numSections`, fixing a signed/unsigned comparison warning.
        - The header `<sbv_patches.h>` was included to provide the declarations for the `DISABLE...` functions, fixing an "implicit declaration" error.

4.  **Continuous Integration (CI)**:
    - The original `.github/workflows/ci.yml` was replaced with a new workflow.
    - A new build and test script, `scripts/ci-smoke.sh`, was created to handle the entire build and test process.
    - The CI workflow has been configured to use the `ps2dev/ps2dev:v1.3.0` Docker image, as this is a known-stable version of the toolchain that is compatible with this project.

## Local Building

To build the project locally, you can use either a native ps2dev toolchain installation or the `ps2dev/ps2dev` Docker container.

### Native Toolchain

```bash
# Ensure PS2DEV, PS2SDK, and GSKIT are set correctly
export PS2DEV=/path/to/your/ps2dev
export PS2SDK=$PS2DEV/ps2sdk
export GSKIT=$PS2DEV/gsKit
export PATH=$PATH:$PS2DEV/bin

# Run the build script
./scripts/ci-smoke.sh
```

### Docker

```bash
# Run the build script inside the ps2dev container
docker run --rm -v $(pwd):/src -w /src ps2dev/ps2dev:v1.3.0 ./scripts/ci-smoke.sh
```
