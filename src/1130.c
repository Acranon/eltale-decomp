#include "common.h"

/*
 * Nintendo's nnSc scheduler sample (retrace/pre-NMI broadcast, audio and graphics task
 * threads), with an added retrace counter.
 * Folder: src/game/core/   (proposed for round 4)
 */

#define NN_SC_SWAPBUFFER 0x0040
#define NN_SC_RETRACE_MSG 1
#define NN_SC_PRE_NMI_MSG 3
#define NN_SC_MAX_MESGS 8
#define NN_SC_PRI 120
#define NN_SC_AUDIO_PRI 110
#define NN_SC_GRAPHICS_PRI 100
#define VIDEO_MSG 666
#define RSP_DONE_MSG 667
#define RDP_DONE_MSG 668
#define PRE_NMI_MSG 669

typedef short NNScMsg;

typedef struct SCClient_s {
    struct SCClient_s *next;
    OSMesgQueue *msgQ;
} NNScClient;

typedef struct SCTask_s {
    struct SCTask_s *next;
    u32 state;
    u32 flags;
    void *framebuffer;
    OSTask list;
    OSMesgQueue *msgQ;
    OSMesg msg;
} NNScTask;

typedef struct {
    NNScMsg retraceMsg;
    NNScMsg prenmiMsg;
    OSMesgQueue audioRequestMQ;
    OSMesg audioRequestBuf[NN_SC_MAX_MESGS];
    OSMesgQueue graphicsRequestMQ;
    OSMesg graphicsRequestBuf[NN_SC_MAX_MESGS];
    OSMesgQueue retraceMQ;
    OSMesg retraceMsgBuf[NN_SC_MAX_MESGS];
    OSMesgQueue rspMQ;
    OSMesg rspMsgBuf[NN_SC_MAX_MESGS];
    OSMesgQueue rdpMQ;
    OSMesg rdpMsgBuf[NN_SC_MAX_MESGS];
    OSMesgQueue waitMQ;
    OSMesg waitMsgBuf[NN_SC_MAX_MESGS];
    OSThread schedulerThread;
    OSThread audioThread;
    OSThread graphicsThread;
    NNScClient *clientList;
    NNScTask *curGraphicsTask;
    NNScTask *curAudioTask;
    NNScTask *graphicsTaskSuspended;
    u32 firstTime;
} NNSched;

void nnScEventHandler(NNSched *sc);
void nnScAddClient(NNSched *sc, NNScClient *c, OSMesgQueue *msgQ);
void nnScRemoveClient(NNSched *sc, NNScClient *c);
void nnScEventBroadcast(NNSched *sc, NNScMsg *msg);
void nnScExecuteAudio(NNSched *sc);
void nnScExecuteGraphics(NNSched *sc);
void nnScWaitTaskReady(NNSched *sc, NNScTask *task);
void osSpTaskLoad(OSTask *task);

/* This file's .bss, 80077160..8007A170: the three thread stacks (each passed
 * by its top, the next object's address) and the retrace counter D_8007A160. */
u64 D_80077160[0x1000 / sizeof(u64)];
u64 D_80078160[0x1000 / sizeof(u64)];
u64 D_80079160[0x1000 / sizeof(u64)];
u16 D_8007A160;

void nnScCreateScheduler(NNSched *sc, u8 numFields) {
    sc->curGraphicsTask = 0;
    sc->curAudioTask = 0;
    sc->graphicsTaskSuspended = 0;
    sc->clientList = 0;
    sc->firstTime = 1;
    sc->retraceMsg = NN_SC_RETRACE_MSG;
    sc->prenmiMsg = NN_SC_PRE_NMI_MSG;

    osCreateMesgQueue(&sc->retraceMQ, sc->retraceMsgBuf, NN_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->rspMQ, sc->rspMsgBuf, NN_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->rdpMQ, sc->rdpMsgBuf, NN_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->graphicsRequestMQ, sc->graphicsRequestBuf, NN_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->audioRequestMQ, sc->audioRequestBuf, NN_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->waitMQ, sc->waitMsgBuf, NN_SC_MAX_MESGS);

    osViSetEvent(&sc->retraceMQ, (OSMesg)VIDEO_MSG, numFields);
    osSetEventMesg(OS_EVENT_SP, &sc->rspMQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->rdpMQ, (OSMesg)RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->retraceMQ, (OSMesg)PRE_NMI_MSG);
}

void nnScStartScheduler(NNSched *sc) {
    osCreateThread(&sc->schedulerThread, 0x13, (void (*)(void *))nnScEventHandler, sc, D_80078160, NN_SC_PRI);
    osStartThread(&sc->schedulerThread);
    osCreateThread(&sc->audioThread, 0x12, (void (*)(void *))nnScExecuteAudio, sc, D_80079160, NN_SC_AUDIO_PRI);
    osStartThread(&sc->audioThread);
    osCreateThread(&sc->graphicsThread, 0x11, (void (*)(void *))nnScExecuteGraphics, sc, &D_8007A160, NN_SC_GRAPHICS_PRI);
    osStartThread(&sc->graphicsThread);
}

OSMesgQueue *nnScGetAudioMQ(NNSched *sc) {
    return &sc->audioRequestMQ;
}

OSMesgQueue *nnScGetGfxMQ(NNSched *sc) {
    return &sc->graphicsRequestMQ;
}

void nnScEventHandler(NNSched *sc) {
    OSMesg msg = (OSMesg)0;

    while (1) {
        osRecvMesg(&sc->retraceMQ, &msg, OS_MESG_BLOCK);
        switch ((int)msg) {
            case VIDEO_MSG:
                D_8007A160++;
                nnScEventBroadcast(sc, &sc->retraceMsg);
                break;
            case PRE_NMI_MSG:
                nnScEventBroadcast(sc, &sc->prenmiMsg);
                osViBlack(TRUE);
                break;
        }
    }
}

void nnScAddClient(NNSched *sc, NNScClient *c, OSMesgQueue *msgQ) {
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;
    osSetIntMask(mask);
}

void nnScRemoveClient(NNSched *sc, NNScClient *c) {
    NNScClient *client = sc->clientList;
    NNScClient *prev = 0;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    while (client != 0) {
        if (client == c) {
            if (prev)
                prev->next = c->next;
            else
                sc->clientList = c->next;
            break;
        }
        prev = client;
        client = client->next;
    }
    osSetIntMask(mask);
}

void nnScEventBroadcast(NNSched *sc, NNScMsg *msg) {
    NNScClient *client;

    for (client = sc->clientList; client != 0; client = client->next) {
        osSendMesg(client->msgQ, (OSMesg *)msg, OS_MESG_NOBLOCK);
    }
}

void nnScExecuteAudio(NNSched *sc) {
    OSMesg msg = (OSMesg)0;
    NNScTask *task = (NNScTask *)0;
    NNScTask *gfxTask = (NNScTask *)0;
    u32 yieldFlag;

    while (1) {
        osRecvMesg(&sc->audioRequestMQ, (OSMesg *)&task, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        yieldFlag = 0;
        gfxTask = sc->curGraphicsTask;
        if (gfxTask) {
            osSpTaskYield();
            osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
            if (osSpTaskYielded(&gfxTask->list)) {
                yieldFlag = 1;
            } else {
                yieldFlag = 2;
            }
        }

        sc->curAudioTask = task;
        osSpTaskLoad(&task->list);
        osSpTaskStartGo(&task->list);
        osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        sc->curAudioTask = (NNScTask *)0;

        if (sc->graphicsTaskSuspended)
            osSendMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
        if (yieldFlag == 1) {
            osSpTaskLoad(&gfxTask->list);
            osSpTaskStartGo(&gfxTask->list);
        } else if (yieldFlag == 2) {
            osSendMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        }
        osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
    }
}

void nnScExecuteGraphics(NNSched *sc) {
    OSMesg msg = (OSMesg)0;
    NNScTask *task;

    while (1) {
        osRecvMesg(&sc->graphicsRequestMQ, (OSMesg *)&task, OS_MESG_BLOCK);
        nnScWaitTaskReady(sc, task);
        if (sc->curAudioTask) {
            sc->graphicsTaskSuspended = task;
            osRecvMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
            sc->graphicsTaskSuspended = (NNScTask *)0;
        }

        sc->curGraphicsTask = task;
        osSpTaskLoad(&task->list);
        osSpTaskStartGo(&task->list);
        osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        sc->curGraphicsTask = (NNScTask *)0;

        osRecvMesg(&sc->rdpMQ, &msg, OS_MESG_BLOCK);

        if (sc->firstTime) {
            osViBlack(FALSE);
            sc->firstTime = 0;
        }
        if (task->flags & NN_SC_SWAPBUFFER) {
            osViSwapBuffer(task->framebuffer);
        }
        osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
    }
}

void nnScWaitTaskReady(NNSched *sc, NNScTask *task) {
    OSMesg msg = (OSMesg)0;
    NNScClient client;
    void *fb = task->framebuffer;

    if (osViGetCurrentFramebuffer() == fb) {
        do {
            nnScAddClient(sc, &client, &sc->waitMQ);
            osRecvMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
            nnScRemoveClient(sc, &client);
        } while (osViGetCurrentFramebuffer() == fb);
    }
}
