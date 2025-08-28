# OpenTuna unified toolchain makefile

# Default C flags.
# - The project's original flags were: -Os -Wall -Wextra -Werror -Wpedantic
# - We are removing -Os from the global flags so it can be set per-project.
# - We are removing -Wpedantic because it causes build failures in the ps2sdk headers.
EE_CFLAGS += -Wall -Wextra -Werror

# Default include paths.
EE_INCS += -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I.

# Default library paths
EE_LDFLAGS += -L$(PS2SDK)/ee/lib
EE_LIBS += -lpatches

# Include the main ps2sdk makefiles.
include $(PS2SDK)/Makefile.pref
include $(PS2SDK)/Makefile.eeglobal
