#define osGbpakInit func_8003D6B0
#define __osGbpakTimer D_800956B0
#define __osGbpakTimerQ D_800956D0
#define __osGbpakTimerMsg D_800956E8
#include "libultra/sdk_names.h"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/controller_gbpak.h"

/* .bss 800956B0..800956F0 */
OSTimer __osGbpakTimer;
OSMesgQueue __osGbpakTimerQ ALIGNED(0x8);
OSMesg __osGbpakTimerMsg;

s32 osGbpakInit(OSMesgQueue* mq, OSPfs* pfs, int channel) {
    int i;
    s32 ret;
    u8 temp[BLOCKSIZE];

    pfs->status = 0;

    // Turn off the transfer pak
    for (i = 0; i < BLOCKSIZE; temp[i++] = GB_POWER_OFF) {
        ;
    }

    ret = __osContRamWrite(mq, channel, CONT_BLOCK_GB_POWER, temp, FALSE);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = __osContRamWrite(mq, channel, CONT_BLOCK_GB_POWER, temp, FALSE);
    }

    if (ret != 0) {
        return ret;
    }

    ret = __osContRamRead(mq, channel, CONT_BLOCK_GB_POWER, temp);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    if (ret != 0) {
        return ret;
    } else {
        // Check if the power is still off as set earlier
        if (temp[BLOCKSIZE - 1] == GB_POWER_OFF) {
            return PFS_ERR_DEVICE;
        }
    }

    // Turn on the transfer pak
    for (i = 0; i < BLOCKSIZE; temp[i++] = GB_POWER_ON) {
        ;
    }

    ret = __osContRamWrite(mq, channel, CONT_BLOCK_GB_POWER, temp, FALSE);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    if (ret != 0) {
        return ret;
    }

    ret = __osContRamRead(mq, channel, CONT_BLOCK_GB_POWER, temp);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    if (ret != 0) {
        return ret;
    } else {
        // Check if the power is still on as set earlier
        if (temp[BLOCKSIZE - 1] != GB_POWER_ON) {
            return PFS_ERR_DEVICE;
        }
    }

    /* this version has no __osPfsGetStatus check here */
    osCreateMesgQueue(&__osGbpakTimerQ, &__osGbpakTimerMsg, 1);
    osSetTimer(&__osGbpakTimer, 9000000 /* OS_USEC_TO_CYCLES(192000) with the fixed 46.875MHz count rate */, 0, &__osGbpakTimerQ, &__osGbpakTimerMsg);
    osRecvMesg(&__osGbpakTimerQ, NULL, OS_MESG_BLOCK);
    pfs->queue = mq;
    pfs->status = PFS_GBPAK_INITIALIZED;
    pfs->channel = channel;
    pfs->activebank = 0x84;
    pfs->banks = 0xFF;
    pfs->version = 0xFF;
    pfs->dir_size = 0xFF;

    return 0;
}
