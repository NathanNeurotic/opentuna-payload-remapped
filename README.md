## Source code for OpenTuna exploit and payloads.

### Continuous Integration
This repository uses a GitHub Actions workflow defined in `.github/workflows/build.yml` to build the project inside the
`ps2dev/ps2dev` Docker image.
The workflow installs `ps2-packer` when needed, runs `make` in the `exploit`, `launcher-boot`, and `launcher-keys` directories, and uploads the resulting `.elf` binaries as artifacts for every push and pull request.
