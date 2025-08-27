#include "loader.h"
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include <fcntl.h>
#include <unistd.h>

void wipeUserMem(void)
{
        int i;
        for (i = 0x100000; i < GetMemorySize(); i += 64)
        {
                asm volatile(
                        "\tsq $0, 0(%0) \n"
                        "\tsq $0, 16(%0) \n"
                        "\tsq $0, 32(%0) \n"
                        "\tsq $0, 48(%0) \n" :: "r"(i));
        }
}

void ResetIOP(void)
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

void InitPS2(void)
{
        ResetIOP();
        SifInitIopHeap();
        SifLoadFileInit();
        sbv_patch_disable_prefix_check();
        SifLoadModule("rom0:SIO2MAN", 0, NULL);
        SifLoadModule("rom0:MCMAN", 0, NULL);
        SifLoadModule("rom0:MCSERV", 0, NULL);
        SifLoadModule("rom0:FILEXIO", 0, NULL);
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

int file_exists(char filepath[])
{
        int fdn;

        fdn = open(filepath, O_RDONLY);
        if (fdn < 0)
                return 0;
        close(fdn);

        return 1;
}
