FROM ps2dev/ps2dev:latest

RUN apk add --no-cache \
    make \
    gcc \
    libc-dev \
    zlib-dev \
    bash

COPY tools/ps2-packer /tmp/ps2-packer
RUN make -C /tmp/ps2-packer ps2-packer-lite && \
    cp /tmp/ps2-packer/ps2-packer-lite /usr/local/bin/ps2-packer && \
    rm -rf /tmp/ps2-packer

