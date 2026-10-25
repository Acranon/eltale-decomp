#include "libultra/sdk_names.h"
#undef BUILD_VERSION
#define BUILD_VERSION VERSION_I
#include "PR/os_version.h"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/piint.h"
#undef __osPiRawStartDma
#undef __osEPiRawStartDma

/* Between ultralib I and J: J's __Dom1SpeedParam/__Dom2SpeedParam, read from
 * the PI registers here instead of in osInitialize. */
extern OSThread D_800930F0;          /* piThread */
extern OSMesgQueue D_800942A0;       /* piEventQueue (piThreadStack ends here) */
extern OSMesg D_800942B8[1];         /* piEventBuf */
extern OSPiHandle D_80093000;        /* __Dom1SpeedParam */
extern OSPiHandle D_80093078;        /* __Dom2SpeedParam */
extern OSDevMgr __osPiDevMgr;
extern s32 __osPiRawStartDma(s32, u32, void*, u32);
extern s32 __osEPiRawStartDma(OSPiHandle*, s32, u32, void*, u32);

void createSpeedParam(void);

void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (__osPiDevMgr.active) {
        return;
    }
    createSpeedParam();
    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&D_800942A0, (OSMesg*)D_800942B8, 1);

    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }

    osSetEventMesg(OS_EVENT_PI, &D_800942A0, (OSMesg)0x22222222);
    oldPri = -1;
    myPri = osGetThreadPri(NULL);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }

    savedMask = __osDisableInt();
    __osPiDevMgr.active = 1;
    __osPiDevMgr.thread = &D_800930F0;
    __osPiDevMgr.cmdQueue = cmdQ;
    __osPiDevMgr.evtQueue = &D_800942A0;
    __osPiDevMgr.acsQueue = &__osPiAccessQueue;
    __osPiDevMgr.dma = __osPiRawStartDma;
    __osPiDevMgr.edma = __osEPiRawStartDma;
    osCreateThread(&D_800930F0, 0, __osDevMgrMain, &__osPiDevMgr, &D_800942A0, pri);
    osStartThread(&D_800930F0);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

void createSpeedParam(void) {
    D_80093000.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    D_80093000.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    D_80093000.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    D_80093000.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);
    D_80093000.domain = PI_DOMAIN1;
    D_80093078.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    D_80093078.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    D_80093078.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    D_80093078.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
    D_80093078.domain = PI_DOMAIN2;
}
