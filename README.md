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
builds a Docker image and runs the build inside a container:

```yaml
- name: Build the Docker image
  run: docker build . --tag opentuna-build:latest
- name: Run the build in the container
  run: |
    docker run --rm --user $(id -u):$(id -g) -v "${{ github.workspace }}":/app -w /app \
    -e HOME=/app -e WINEPREFIX=/app/.wine \
    opentuna-build:latest \
    bash -lc "mkdir -p $WINEPREFIX && make -C exploit"
```

The compiled payload files (such as `payload.bin`) are written to the `exploit/` directory
and are available for download from the workflow run's artifact section.
