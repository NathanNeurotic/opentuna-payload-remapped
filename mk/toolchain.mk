# OpenTuna unified toolchain makefile

# This file is based on the standard practices for ps2sdk projects.
# It includes the main Defs.make from the installed ps2sdk, and then
# provides the necessary rules for compiling EE binaries.

# Common compiler flags.
EE_CFLAGS += -Wall -Wextra -Werror

# Common include paths.
EE_INCS += -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I.

# Common library paths
EE_LDFLAGS += -L$(PS2SDK)/ee/lib

# Include the main ps2sdk makefiles.
# The v1.3.0 toolchain uses these paths.
include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.eeglobal
