## Source code for OpenTuna exploit and payloads.

### Requirements
- **Docker** – used to build the project inside an isolated container.
- **PlayStation 2 SDK** – provides the `ee-gcc` toolchain required to compile the exploit.

### Build targets
The exploit is built with Make from the `exploit` directory.

```sh
make -C exploit
```

The default payload is `launcher-keys`. Override `PAYLOAD` to switch payloads:

```sh
make -C exploit PAYLOAD=launcher-boot
```

Run `make -C exploit clean` to remove generated files.

### Continuous integration
A GitHub Actions workflow builds the exploit on each push and pull request. The workflow
builds a Docker image (which compiles a native `ps2-packer` from `tools/ps2-packer`), runs the build inside a container, and uploads the resulting payload as an artifact:

```yaml
- name: Build the Docker image
  run: docker build . --tag opentuna-build:latest
- name: Build exploit in container
  run: |
    docker run --rm \\
      -v "${{ github.workspace }}":/app -w /app \\
      opentuna-build:latest \\
      bash -lc "source /etc/profile && make -C exploit"
- uses: actions/upload-artifact@v4
  with:
    name: opentuna-payload
    path: exploit/payload.bin
```

The build job ships `exploit/payload.bin` on every run. When a tag is pushed, the artifact
is downloaded in a release job and attached to the corresponding GitHub release.
