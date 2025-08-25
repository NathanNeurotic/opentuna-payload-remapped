FROM ps2dev/ps2dev:latest
RUN apk add --no-cache git
RUN git clone https://github.com/ps2dev/ps2stuff.git /tmp/ps2stuff
RUN ls -R /tmp/ps2stuff
