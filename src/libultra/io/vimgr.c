#include "libultra/sdk_names.h"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"
#include "PRinternal/osint.h"

extern OSDevMgr D_8006DED0;      /* __osViDevMgr */
#define __osViDevMgr D_8006DED0
extern u32 __additional_scanline;
extern OSThread D_80094380;      /* viThread */
#define viThread D_80094380
extern OSMesgQueue D_80095530;   /* viEventQueue (viThreadStack ends here) */
#define viEventQueue D_80095530
extern OSMesg D_80095548[5];     /* viEventBuf */
#define viEventBuf D_80095548
extern OSIoMesg D_80095560;      /* viRetraceMsg */
#define viRetraceMsg D_80095560
extern OSIoMesg D_80095578;      /* viCounterMsg */
#define viCounterMsg D_80095578
extern u16 D_80095590;           /* func_80037CF0's static D_80095590 */

void func_80037CF0(void* arg);
/* func_80037CF0 (viMgrMain) needs its static retrace (D_80095590) defined in
 * this file to match (IDO treats a local static differently from an extern),
 * so it waits for the data step. */
void func_80037B70(OSPri pri) {
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
    osCreateThread(&viThread, 0, func_80037CF0, &__osViDevMgr, (u8*)&D_80094380 + 0x11B0, pri);
    __osViInit();
    osStartThread(&viThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/vimgr/func_80037CF0.s")

