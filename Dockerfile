FROM ps2dev/ps2dev:latest

RUN apk add --no-cache git wine lib32gcc lib32stdc++

RUN git clone https://github.com/ps2dev/ps2sdk.git /tmp/ps2sdk

RUN cat /tmp/ps2sdk/Makefile.eeglobal
