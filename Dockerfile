FROM ps2dev/ps2dev:latest

RUN apk add --no-cache git make wine xvfb

RUN git clone https://github.com/ps2dev/ps2stuff.git /tmp/ps2stuff && \
    cd /tmp/ps2stuff/tools/bin2s && \
    make && \
    make install && \
    rm -rf /tmp/ps2stuff

ENV PATH="/usr/local/ps2dev/bin:${PATH}"
