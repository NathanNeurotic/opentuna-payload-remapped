## Source code for OpenTuna exploit and payloads.

### Toolchain setup
The project is built with the [ps2dev toolchain](https://github.com/ps2dev/ps2dev). A typical installation flow is:

```bash
git clone https://github.com/ps2dev/ps2dev
cd ps2dev
./toolchain.sh
```

After installation, set up the required environment variables (these are normally added to your shell profile):

```bash
export PS2DEV=/usr/local/ps2dev
export PS2SDK="$PS2DEV/ps2sdk"
export GSKIT="$PS2DEV/gsKit"
export PATH="$PATH:$PS2DEV/bin"
```

`PS2DEV` points to the root of the installed toolchain, `PS2SDK` to the SDK, and `GSKIT` to the graphics library used by the payloads.

### Building
Each component of the project has its own `Makefile`. Build them individually from the repository root:

```bash
make -C launcher-boot
make -C launcher-keys
make -C exploit            # builds using PAYLOAD=launcher-keys by default
```

The exploit embeds one of the launcher payloads. Override the payload by passing the `PAYLOAD` variable, for example:

```bash
make -C exploit PAYLOAD=launcher-boot
```

### Continuous Integration
This repository uses a GitHub Actions workflow defined in `.github/workflows/build.yml` to build the project inside the
`ps2dev/ps2dev` Docker image.
The workflow installs `ps2-packer` when needed, runs `make` in the `exploit`, `launcher-boot`, and `launcher-keys` directories, and uploads the resulting `.elf` binaries as artifacts for every push and pull request.

