#include "libultra/sdk_names.h"
#undef BUILD_VERSION
#define BUILD_VERSION VERSION_I
#include "PR/os_version.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/piint.h"

/* osInitialize, between ultralib I and J: J's speed-param call and AI writes,
 * I's clock read from the ROM header, no RCP-interrupt wait. */

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble[];

/* This file's data, as in ultralib's initialize.c: .data 8006CD00..8006CD14
 * (padded to 8006CD20) and .bss __osFinalrom at 80092FF0. osClockRate must be
 * defined here for func_80036AC0 to match (same-object 64-bit access). */
OSTime osClockRate = 62500000LL;   /* OS_CLOCK_RATE */
s32 osViClock = 48681812;       /* VI_NTSC_CLOCK */
u32 D_8006CD0C = 0;            /* __osShutdown (used by exceptasm) */
u32 __OSGlobalIntMask = OS_IM_ALL;
u32 __osFinalrom;
extern s32 D_8000030C;       /* osResetType */
extern u8 D_8000031C[];      /* osAppNMIBuffer */

void osUnmapTLBAll(void);
void __createSpeedParam(void);

void func_80036AC0(void) {
    u32 pifdata;
    u32 clock = 0;

    __osFinalrom = TRUE;

    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector*)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)E_VEC = *__osExceptionPreamble;
    osWritebackDCache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osUnmapTLBAll();
    __createSpeedParam();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock != 0) {
        osClockRate = clock;
    }
    osClockRate = osClockRate * 3 / 4;

    if (D_8000030C == 0) {
        bzero(D_8000031C, OS_APP_NMI_BUFSIZE);
    }

    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }

    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    IO_WRITE(AI_DACRATE_REG, AI_MAX_DAC_RATE - 1);
    IO_WRITE(AI_BITRATE_REG, AI_MAX_BIT_RATE - 1);
}
