LOADADDR  = 0x90000
STACKADDR = 0xA8000
STACKSIZE = 0x04000


EE_TARGET=payload
EE_BIN = $(EE_TARGET).elf
EE_BIN_STRIPPED = $(EE_TARGET)-stripped.elf
EE_BIN_PACKED= $(EE_TARGET)-packed.elf
EE_SRCS = main.c pad.c
EE_LDFLAGS += -Wl,-Ttext=$(LOADADDR),--defsym,_stack_size=$(STACKSIZE),--defsym,_stack=$(STACKADDR),--gc-sections
EE_LIBS = -lc -lpatches -lpad 
EE_CFLAGS += -Os



all:
	$(MAKE) $(EE_BIN_PACKED) 
	

clean:
	rm -f *.elf   *.o *.s *.bin
	
			

$(EE_BIN_STRIPPED): $(EE_BIN)
	$(EE_STRIP) -s -R .comment -R .gnu.version --strip-unneeded -o $@ $<
	

	
$(EE_BIN_PACKED): $(EE_BIN_STRIPPED)
	ps2-packer -v $< $@
	



	
include $(PS2SDK)/Defs.make
EE_CFLAGS += -I$(PS2SDK)/ports/include
include $(PS2SDK)/Rules.make

