#include "libultra/sdk_names.h"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"

#define SI_Q_BUF_LEN 1
extern OSMesg siAccessBuf[SI_Q_BUF_LEN];
extern OSMesgQueue __osSiAccessQueue;
u32 __osSiAccessQueueEnabled = 0;   /* .data 8006EB20 */

void __osSiCreateAccessQueue(void) {
    __osSiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osSiAccessQueue, siAccessBuf, SI_Q_BUF_LEN);
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osSiAccessQueueEnabled) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&__osSiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
