#include "../common/loader.h"

int main(int argc, char *argv[])
{
        wipeUserMem();

        InitPS2();

        if (file_exists("mc0:/BOOT/BOOT.ELF"))
                LoadElf("mc0:/BOOT/BOOT.ELF", "mc0:/BOOT/");

        if (file_exists("mc1:/BOOT/BOOT.ELF"))
                LoadElf("mc1:/BOOT/BOOT.ELF", "mc1:/BOOT/");

        __asm__ __volatile__(
                "       li $3, 0x04;"
                "       syscall;"
                "       nop;");

        return 0;
}
