FROM ps2dev/ps2dev:latest

RUN apk add --no-cache git make wine xvfb

RUN git clone https://github.com/ps2dev/ps2sdk.git /tmp/ps2sdk && \
    cd /tmp/ps2sdk && \
    make -C tools && \
    make -C tools install && \
    rm -rf /tmp/ps2sdk
