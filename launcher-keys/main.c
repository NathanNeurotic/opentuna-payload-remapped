#include <tamtypes.h>
#include <loadfile.h>
#include <fileXio_rpc.h>
#include <libpad.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../common/loader.h"

#define NTSC 2
#define PAL 3

#define DELAY 0

int VMode = NTSC;
extern u32 new_pad;

char romver_region_char[1];
char ROMVersionNumStr[5];
u8 romver[16];
u32 bios_version = 0;

int main(int argc, char *argv[])
{
        u32 lastKey = 0;
        int isEarlyJap = 0;

        wipeUserMem();

        InitPS2();

        SifLoadModule("rom0:PADMAN", 0, NULL);
        setupPad();
        waitAnyPadReady();

        int fdnr;
        if ((fdnr = fileXioOpen("rom0:ROMVER", O_RDONLY)) > 0)
        { // Reading ROMVER
                fileXioRead(fdnr, romver, sizeof romver);
                fileXioClose(fdnr);
        }

        // Getting region char
        romver_region_char[0] = (romver[4] == 'E' ? 'E' : (romver[4] == 'J' ? 'I' : (romver[4] == 'H' ? 'A' : (romver[4] == 'U' ? 'A' : romver[4]))));

        strncpy(ROMVersionNumStr, romver, 4);
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
                if (file_exists("mc0:/APPS/ULE.ELF"))
                        LoadElf("mc0:/APPS/ULE.ELF", "mc0:/APPS/");

                if (file_exists("mc1:/APPS/ULE.ELF"))
                        LoadElf("mc1:/APPS/ULE.ELF", "mc1:/APPS/");

                if (file_exists("mc0:/APPS/OPNPS2LD.ELF"))
                        LoadElf("mc0:/APPS/OPNPS2LD.ELF", "mc0:/APPS/");

                if (file_exists("mc1:/APPS/OPNPS2LD.ELF"))
                        LoadElf("mc1:/APPS/OPNPS2LD.ELF", "mc0:/APPS/");
        }
        else
        {
                if (file_exists("mc0:/APPS/OPNPS2LD.ELF"))
                        LoadElf("mc0:/APPS/OPNPS2LD.ELF", "mc0:/APPS/");

                if (file_exists("mc1:/APPS/OPNPS2LD.ELF"))
                        LoadElf("mc1:/APPS/OPNPS2LD.ELF", "mc0:/APPS/");

                if (file_exists("mc0:/APPS/ULE.ELF"))
                        LoadElf("mc0:/APPS/ULE.ELF", "mc0:/APPS/");

                if (file_exists("mc1:/APPS/ULE.ELF"))
                        LoadElf("mc1:/APPS/ULE.ELF", "mc1:/APPS/");
        }

        __asm__ __volatile__(
                "       li $3, 0x04;"
                "       syscall;"
                "       nop;");

        return 0;
}
