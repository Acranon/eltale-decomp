#include "libultra/sdk_names.h"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"
#include "PRinternal/osint.h"

/* This file's data, as in ultralib's vimgr.c: .data 8006DED0..8006DEF0
 * (__osViDevMgr, __additional_scanline) and .bss 80094380..800955A0 (the
 * statics below, then func_80037CF0's static retrace counter at 80095590,
 * which must be a function-scope static for IDO to match). */
OSDevMgr D_8006DED0 = { 0 };     /* __osViDevMgr */
#define __osViDevMgr D_8006DED0
u32 __additional_scanline = 0;
static OSThread D_80094380;      /* viThread */
#define viThread D_80094380
static STACK(D_80094530, OS_VIM_STACKSIZE) ALIGNED(0x10); /* viThreadStack */
static OSMesgQueue D_80095530 ALIGNED(0x8); /* viEventQueue */
#define viEventQueue D_80095530
static OSMesg D_80095548[5] ALIGNED(0x8);   /* viEventBuf */
#define viEventBuf D_80095548
static OSIoMesg D_80095560 ALIGNED(0x8);    /* viRetraceMsg */
#define viRetraceMsg D_80095560
static OSIoMesg D_80095578 ALIGNED(0x8);    /* viCounterMsg */
#define viCounterMsg D_80095578

void func_80037CF0(void* arg);
void osCreateViManager(OSPri pri) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

#ifdef _DEBUG
    if ((pri < OS_PRIORITY_IDLE) || (pri > OS_PRIORITY_MAX)) {
        __osError(ERR_OSCREATEVIMANAGER, 1, pri);
        return;
    }
#endif

    if (__osViDevMgr.active) {
        return;
    }
    __osTimerServicesInit();
#if BUILD_VERSION >= VERSION_J
    __additional_scanline = 0;
#endif
    osCreateMesgQueue(&viEventQueue, viEventBuf, ARRLEN(viEventBuf));
    viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
    viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
    viRetraceMsg.hdr.retQueue = NULL;
    viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
    viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
    viCounterMsg.hdr.retQueue = NULL;
    osSetEventMesg(OS_EVENT_VI, &viEventQueue, &viRetraceMsg);
    osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, &viCounterMsg);
    oldPri = -1;
    myPri = osGetThreadPri(NULL);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }

    savedMask = __osDisableInt();
    __osViDevMgr.active = TRUE;
    __osViDevMgr.thread = &viThread;
    __osViDevMgr.cmdQueue = &viEventQueue;
    __osViDevMgr.evtQueue = &viEventQueue;
    __osViDevMgr.acsQueue = NULL;
    __osViDevMgr.dma = NULL;
    __osViDevMgr.edma = NULL;
    osCreateThread(&viThread, 0, func_80037CF0, &__osViDevMgr, STACK_START(D_80094530), pri);
    __osViInit();
    osStartThread(&viThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

void func_80037CF0(void* arg) {
    __OSViContext* vc;
    OSDevMgr* dm;
    OSIoMesg* mb;
    static u16 D_80095590; /* static retrace */
    s32 first;
    u32 count;

    mb = NULL;
    first = 0;
    vc = __osViGetCurrentContext();
    D_80095590 = vc->retraceCount;
    if (D_80095590 == 0) {
        D_80095590 = 1;
    }
    dm = (OSDevMgr*)arg;

    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                D_80095590--;
                if (D_80095590 == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_80095590 = vc->retraceCount;
                }

                __osViIntrCount++;

                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }

                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
            default:
                break;
        }
    }
}

