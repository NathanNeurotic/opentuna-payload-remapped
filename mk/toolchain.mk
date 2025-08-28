# Common toolchain settings for PS2 builds
PS2DEV ?= /usr/local/ps2dev
PS2SDK ?= $(PS2DEV)/ps2sdk
GSKIT  ?= $(PS2DEV)/gsKit

COMMON_WARNINGS := -Wall -Wextra -Werror -Wpedantic

CFLAGS   += $(COMMON_WARNINGS)
CXXFLAGS += $(COMMON_WARNINGS)
CPPFLAGS += $(COMMON_WARNINGS)

EE_CFLAGS   += $(COMMON_WARNINGS)
EE_INCS     += -I$(GSKIT)/include -I$(PS2SDK)/ports/include
EE_LDFLAGS  += -L$(GSKIT)/lib

# Allow projects to override or extend these variables after inclusion
