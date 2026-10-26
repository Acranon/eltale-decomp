#include "libultra/sdk_names.h"
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

/* .data 8006E750..8006E770, as in ultralib */
struct __osThreadTail __osThreadTail = { NULL, -1 };
OSThread* __osRunQueue = (OSThread*)&__osThreadTail;
OSThread* __osActiveQueue = (OSThread*)&__osThreadTail;
OSThread* __osRunningThread = NULL;
OSThread* __osFaultedThread = NULL;


void __osDequeueThread(register OSThread** queue, register OSThread* t) {
    register OSThread* pred;
    register OSThread* succ;

    pred = (OSThread*)queue;
    succ = pred->next;

    while (succ != NULL) {
        if (succ == t) {
            pred->next = t->next;
#ifdef _DEBUG
            t->next = NULL;
#endif
            return;
        }
        pred = succ;
        succ = pred->next;
    }
}
