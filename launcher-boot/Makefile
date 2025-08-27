LOADADDR = 0x90000
STACKADDR = 0xA8000
STACKSIZE = 0x04000

EE_BIN = payload.elf
EE_BIN_STRIPPED = payload-stripped.elf
EE_BIN_PACKED = payload-packed.elf
EE_OBJS = main.o
EE_LDFLAGS += -Wl,--gc-sections -Wl,-Ttext -Wl,$(LOADADDR) -Wl,--defsym -Wl,_stack_size=$(STACKSIZE) -Wl,--defsym -Wl,_stack=$(STACKADDR)
EE_LIBS += -lpatches -lfileXio
EE_INCS += -I$(GSKIT)/include -I$(PS2SDK)/ports/include
EE_CFLAGS += -Os

all: $(EE_BIN_PACKED)

clean:
	rm -f *.elf   *.o *.s *.bin

$(EE_BIN_STRIPPED): $(EE_BIN)
	$(EE_STRIP) -s -R .comment -R .gnu.version --strip-unneeded -o $@ $<

PS2_PACKER = ../ps2-packer/ps2-packer

$(EE_BIN_PACKED): $(EE_BIN_STRIPPED) $(PS2_PACKER)
	$(PS2_PACKER) -v $< $@

$(PS2_PACKER):
	$(MAKE) -C $(dir $(PS2_PACKER)) ps2-packer

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.eeglobal
