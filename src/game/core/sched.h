#ifndef GAME_CORE_SCHED_H
#define GAME_CORE_SCHED_H

#include "common.h"

/*
 * Nintendo's nnSc scheduler sample (nnsched.h). libultra's PR/sched.h is the other
 * scheduler (OSSched/osSc*), not this one. The struct tags are the typedef names, not the
 * sample's SCClient_s/SCTask_s, which PR/sched.h also uses.
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

typedef struct NNScClient {
    /* 0x00 */ struct NNScClient *next;
    /* 0x04 */ OSMesgQueue *msgQ;
} NNScClient; /* 0x8 bytes */

typedef struct NNScTask {
    /* 0x00 */ struct NNScTask *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask list;
    /* 0x50 */ OSMesgQueue *msgQ;
    /* 0x54 */ OSMesg msg;
} NNScTask; /* 0x58 bytes */

typedef struct NNSched {
    /* 0x000 */ NNScMsg retraceMsg;
    /* 0x002 */ NNScMsg prenmiMsg;
    /* 0x004 */ OSMesgQueue audioRequestMQ;
    /* 0x01C */ OSMesg audioRequestBuf[NN_SC_MAX_MESGS];
    /* 0x03C */ OSMesgQueue graphicsRequestMQ;
    /* 0x054 */ OSMesg graphicsRequestBuf[NN_SC_MAX_MESGS];
    /* 0x074 */ OSMesgQueue retraceMQ;
    /* 0x08C */ OSMesg retraceMsgBuf[NN_SC_MAX_MESGS];
    /* 0x0AC */ OSMesgQueue rspMQ;
    /* 0x0C4 */ OSMesg rspMsgBuf[NN_SC_MAX_MESGS];
    /* 0x0E4 */ OSMesgQueue rdpMQ;
    /* 0x0FC */ OSMesg rdpMsgBuf[NN_SC_MAX_MESGS];
    /* 0x11C */ OSMesgQueue waitMQ;
    /* 0x134 */ OSMesg waitMsgBuf[NN_SC_MAX_MESGS];
    /* 0x158 */ OSThread schedulerThread;
    /* 0x308 */ OSThread audioThread;
    /* 0x4B8 */ OSThread graphicsThread;
    /* 0x668 */ NNScClient *clientList;
    /* 0x66C */ NNScTask *curGraphicsTask;
    /* 0x670 */ NNScTask *curAudioTask;
    /* 0x674 */ NNScTask *graphicsTaskSuspended;
    /* 0x678 */ u32 firstTime;
} NNSched; /* 0x680 bytes (OSThread makes it 8-aligned: 4 bytes tail padding) */

extern u64 nnsc_stack[0x1000 / sizeof(u64)];
extern u64 nnsc_audio_stack[0x1000 / sizeof(u64)];
extern u64 nnsc_graphics_stack[0x1000 / sizeof(u64)];
extern u16 nnsc_retrace_count;

void nnScCreateScheduler(NNSched *sc, u8 numFields);
void nnScStartScheduler(NNSched *sc);
OSMesgQueue *nnScGetAudioMQ(NNSched *sc);
OSMesgQueue *nnScGetGfxMQ(NNSched *sc);
void nnScEventHandler(NNSched *sc);
void nnScAddClient(NNSched *sc, NNScClient *c, OSMesgQueue *msgQ);
void nnScRemoveClient(NNSched *sc, NNScClient *c);
void nnScEventBroadcast(NNSched *sc, NNScMsg *msg);
void nnScExecuteAudio(NNSched *sc);
void nnScExecuteGraphics(NNSched *sc);
void nnScWaitTaskReady(NNSched *sc, NNScTask *task);

#endif
