
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <libcdvd.h>
#include <fcntl.h>
#include <sbv_patches.h>
#include <libpad.h>
#include <debug.h>
#include <stdlib.h>
#include <stdint.h>

// Forward declarations for pad functions
int  readPad(void);
void waitAnyPadReady(void);
int  setupPad(void);

#define NTSC 2
#define PAL 3

#define DELAY 0

int VMode = NTSC;
extern uint32_t new_pad;

char romver_region_char[1];
char ROMVersionNumStr[5];
uint8_t romver[16];
uint32_t bios_version = 0;

static void wipeUserMem(void)
{
	int i;
	for (i = 0x100000; i < GetMemorySize(); i += 64)
	{
		asm volatile(
			"\tsq $0, 0(%0) \n"
			"\tsq $0, 16(%0) \n"
			"\tsq $0, 32(%0) \n"
			"\tsq $0, 48(%0) \n" ::"r"(i));
	}
}

void ResetIOP()
{
	SifInitRpc(0);
	while (!SifIopReset("", 0))
	{
	};
	while (!SifIopSync())
	{
	};
	SifInitRpc(0);
}

void InitPS2()
{
	//init_scr();
	ResetIOP();
	SifInitIopHeap();
	SifLoadFileInit();
	sbv_patch_disable_prefix_check();
	SifLoadModule("rom0:SIO2MAN", 0, NULL);
	SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
	SifLoadModule("rom0:PADMAN", 0, NULL);

	setupPad();
	waitAnyPadReady();
}

void LoadElf(char *filename, char *party)
{

	char *args[1];
	t_ExecData exec;
	SifLoadElf(filename, &exec);

	if (exec.epc > 0)
	{
		ResetIOP();

		if (party != 0)
		{
			args[0] = party;
			ExecPS2((void *)exec.epc, (void *)exec.gp, 1, args);
		}
		else
		{
			ExecPS2((void *)exec.epc, (void *)exec.gp, 0, NULL);
		}
	}
}

int file_exists(const char *filepath)
{
        int fdn;

	fdn = open(filepath, O_RDONLY);
	if (fdn < 0)
		return 0;
	close(fdn);

	return 1;
}

int main(int argc, char *argv[])
{

        uint32_t lastKey = 0;
	int isEarlyJap = 0;

	wipeUserMem();

	InitPS2();

	int fdnr;
	if ((fdnr = open("rom0:ROMVER", O_RDONLY)) > 0)
	{ // Reading ROMVER
		read(fdnr, romver, sizeof romver);
		close(fdnr);
	}

        // Getting region char
        switch (romver[4])
        {
        case 'E':
                romver_region_char[0] = 'E';
                break;
        case 'J':
                romver_region_char[0] = 'I';
                break;
        case 'H':
        case 'U':
                romver_region_char[0] = 'A';
                break;
        default:
                romver_region_char[0] = romver[4];
                break;
        }

	strncpy(ROMVersionNumStr, (const char*)romver, 4);
	ROMVersionNumStr[4] = '\0';
	bios_version = strtoul(ROMVersionNumStr, NULL, 16);

	if ((romver_region_char[0] == 'J') && (bios_version <= 0x120))
		isEarlyJap = 1;

	//Stores last key during DELAY msec

	//Waits for pad
	waitAnyPadReady();
	//If key was detected
	if (readPad() && new_pad)
		lastKey = new_pad;

	//Deinits pad
	if (!isEarlyJap)
	{
		padPortClose(0, 0);
		padPortClose(1, 0);
		padEnd();
	}

       if (lastKey & PAD_CIRCLE)
       {
              if (file_exists("mc0:/OPENTUNA/BOOT.ELF"))
                      LoadElf("mc0:/OPENTUNA/BOOT.ELF", "mc0:/OPENTUNA/");

              if (file_exists("mc1:/OPENTUNA/BOOT.ELF"))
                      LoadElf("mc1:/OPENTUNA/BOOT.ELF", "mc1:/OPENTUNA/");
       }
       else
       {
              if (file_exists("mc0:/OPENTUNA/BOOT.ELF"))
                      LoadElf("mc0:/OPENTUNA/BOOT.ELF", "mc0:/OPENTUNA/");

              if (file_exists("mc1:/OPENTUNA/BOOT.ELF"))
                      LoadElf("mc1:/OPENTUNA/BOOT.ELF", "mc1:/OPENTUNA/");
       }

	__asm__ __volatile__(
		"	li $3, 0x04;"
		"	syscall;"
		"	nop;");

	return 0;
}
