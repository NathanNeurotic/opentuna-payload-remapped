FROM ps2dev/ps2dev:latest

RUN apk add --no-cache make wine xvfb gcc libc-dev xvfb-run vulkan-dev lib32gcc lib32stdc++ lib32zlib lib32ncurses
