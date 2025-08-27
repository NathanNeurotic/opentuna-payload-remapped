# Release Notes

## Unreleased
- Switched build system to pinned `ps2dev/ps2dev:v1.3.0` toolchain and added
  continuous integration workflow `ci.yml`.
- Added strict compiler warnings across the project and updated sources to
  compile cleanly.
- Introduced `smoke_test.sh` and run it in CI to verify generated `.elf`
  binaries.
- Updated documentation for modern ps2dev setup and renamed workflow file.
