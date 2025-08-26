FROM ps2dev/ps2dev:latest

RUN apk add --no-cache \
    git \
    build-base \
    zlib-dev \
    bash

RUN git clone --depth=1 https://github.com/ps2dev/ps2sdk.git /tmp/ps2sdk \
    && cd /tmp/ps2sdk && make install \
    && rm -rf /tmp/ps2sdk

COPY tools/ps2-packer /tmp/ps2-packer
RUN make -C /tmp/ps2-packer ps2-packer-lite && \
    cp /tmp/ps2-packer/ps2-packer-lite /usr/local/bin/ps2-packer && \
    rm -rf /tmp/ps2-packer

