FROM ps2dev/ps2dev:latest

RUN apk add --no-cache make wine xvfb gcc libc-dev xvfb-run vulkan-loader-dev libgcc libstdc++ zlib-dev ncurses-libs
