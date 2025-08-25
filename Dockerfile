FROM ps2dev/ps2dev:latest

RUN apk add --no-cache git make wine xvfb

ENV PS2SDKSRC=/tmp/ps2sdk

RUN git clone https://github.com/ps2dev/ps2sdk.git ${PS2SDKSRC} && \
    cd ${PS2SDKSRC} && \
    make -C tools && \
    make -C tools install && \
    rm -rf ${PS2SDKSRC}
