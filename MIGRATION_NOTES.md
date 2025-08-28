# OpenTuna Modernization Migration Notes

This document outlines the changes made to the OpenTuna repository to modernize its build system and ensure it compiles cleanly with a modern ps2dev toolchain.

## Summary of Changes

1.  **Unified Toolchain Makefile**:
    - A new file, `mk/toolchain.mk`, was created to centralize the build settings for all PS2 ELF binaries.
    - This file includes the standard `Makefile.pref` and `Makefile.eeglobal` from the ps2sdk, ensuring compatibility with modern toolchain layouts.
    - All PS2-side Makefiles (`launcher-boot`, `launcher-keys`, `exploit`) were updated to include this new file, replacing the old, deprecated `include` paths.

2.  **Compiler Flags**:
    - The `toolchain.mk` sets strict warning flags: `-Wall -Wextra -Werror`.
    - The `-Wpedantic` flag, which was present in the original Makefiles, has been **removed**. This was necessary because it caused build failures in the official ps2sdk headers (specifically, in `sifdma.h`), which use enum values that are out of range for a signed `int` according to the ISO C standard. Since modifying the SDK headers is not feasible, this warning was disabled to allow the project to compile.

3.  **Compatibility Layer**:
    - A compatibility layer consisting of `compat/compat.h` and `compat/compat.c` has been added.
    - Currently, this layer is empty, as no immediate need for shims was identified after fixing the build system. It exists as a centralized place to add any compatibility code that may be needed in the future.
    - The `launcher-boot` and `launcher-keys` Makefiles have been updated to compile and link this compatibility layer.

4.  **Continuous Integration (CI)**:
    - The original `.github/workflows/ci.yml` was replaced with a new workflow.
    - A new build and test script, `scripts/ci-smoke.sh`, was created to handle the entire build and test process. This script builds all components and performs basic smoke tests to ensure that the expected binaries are created and are not empty.
    - The new CI workflow uses the `ps2dev/ps2dev:v1.3.0` Docker container. The `latest` tag was found to have an incomplete ps2sdk installation, so the older, more stable version is used instead.
    - On a successful build, the workflow uploads all the important binaries as build artifacts.

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
docker run --rm -v $(pwd):/src -w /src ps2dev/ps2dev:latest ./scripts/ci-smoke.sh
```
