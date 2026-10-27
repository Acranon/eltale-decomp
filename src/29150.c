#include "common.h"

/*
 * Audio driver: synthesizer init and sample DMA cache, the audio thread (nnSc client),
 * two compact-sequence players with volume fades, and the sound player with its
 * 5-channel sound-effect script interpreter and request queue.
 * Folder: src/game/audio/   (proposed for round 4)
 */

typedef struct {
    ALLink node;
    s32 startAddr;
    u32 lastFrame;
    char* ptr;
} AMDMABuffer;

typedef struct {
    u8 initialized;
    AMDMABuffer* firstUsed;
    AMDMABuffer* firstFree;
} AMDMAState;

typedef struct {
    /* 0x000 */ ALSeqpConfig config;
    /* 0x01C */ ALCSPlayer player;
    /* 0x098 */ ALCSeq seq;
    /* 0x190 */ u8* seqData;
    /* 0x194 */ s32 seqNo;
    /* 0x198 */ s32 unk198;
} SeqSlot; /* size = 0x19C */

/* .bss 8008CEC0..8008FAF0 */
OSThread D_8008CEC0;
u64 D_8008D070[0x2000 / 8]; /* func_80028AAC's stack (its top is D_8008F070) */
ALHeap D_8008F070;
Acmd* D_8008F080[2];
void* D_8008F088[2];
s16* D_8008F090[3];
OSMesgQueue D_8008F0A0;
OSMesgQueue D_8008F0B8;
OSMesg D_8008F0D0;
OSMesg D_8008F0D4;
OSIoMesg D_8008F0D8[32];
ALGlobals D_8008F3D8;
ALSynConfig D_8008F428;
ALSndPlayer D_8008F450;
ALSndpConfig D_8008F4A8;
ALInstrument* D_8008F4B4;
ALBank* D_8008F4B8;
s16* D_8008F4BC;
s32 D_8008F4C0;
AMDMAState D_8008F4C8;
AMDMABuffer D_8008F4D8[32];
s32 D_8008F758;
s32* D_8008F75C;
s32* D_8008F760;
s32 D_8008F764;
u32 D_8008F768[5];
s32* D_8008F77C;
s32* D_8008F780;
s32* D_8008F784;
s32* D_8008F788;
s32* D_8008F78C;
s32* D_8008F790;
s32* D_8008F794;
s32* D_8008F798;
s32* D_8008F79C;
s32* D_8008F7A0;
SeqSlot D_8008F7A8[2];
s32 D_8008FAE0;
s32 D_8008FAE4;

extern u8 D_80332DB0[];
f32 D_8004F780[73] = {
#include "assets/D_8004F780.inc.c"
};
s32 D_8004F8A4[0x6084 / 4] = {
#include "assets/D_8004F8A4.inc.c"
};
ALBankFile* D_80055928 = NULL;
ALBankFile* D_8005592C = NULL;
ALSeqFile* D_80055930 = NULL;
s32 D_80055934 = 0;
u32 D_80055938 = 0;

void func_80028AAC(void*);
void alCSeqNew(ALCSeq*, u8*);

extern s32* D_80055A24[];
extern s32 D_800559CC;
extern s32 D_800559D0;
extern u32 D_8005594C[8];
extern s32 D_8005596C[8];
extern s32 D_8005598C[8];
extern s32 D_800559AC;
extern s32 D_800559B0;
extern s32 D_800559B4;
extern s32 D_800559B8;
extern s32 D_800559C4[2];
extern s32 D_800559D4[5];
extern s32 D_800559E4;
extern s32 D_800559E8[5];
extern s32 D_800559F8;

void alSndpNew(ALSndPlayer*, ALSndpConfig*);
void func_80029588(s32 id);
void func_80029880();

void func_80028550(u32 devAddr, void* vAddr, s32 nbytes) {
    OSIoMesg sp28;

    osInvalDCache(vAddr, nbytes);
    osPiStartDma(&sp28, 0, 0, devAddr, vAddr, nbytes, &D_8008F0B8);
    osRecvMesg(&D_8008F0B8, NULL, 1);
}

ALDMAproc func_80028908(AMDMAState** state);

void func_800285C4(void) {
    alHeapInit(&D_8008F070, D_80332DB0, 0x68000);
    D_8008F080[0] = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F080[1] = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F088[0] = alHeapAlloc(&D_8008F070, 1, 0x40);
    D_8008F088[1] = alHeapAlloc(&D_8008F070, 1, 0x40);
    D_8008F090[0] = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F090[1] = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F090[2] = alHeapAlloc(&D_8008F070, 1, 0x8000);
    osCreateMesgQueue(&D_8008F0A0, &D_8008F0D0, 1);
    osCreateMesgQueue(&D_8008F0B8, &D_8008F0D4, 1);
    D_8008F4C8.initialized = 0;
    D_8008F428.outputRate = osAiSetFrequency(0x5622);
    D_8008F428.maxVVoices = 0x10;
    D_8008F428.maxPVoices = 0x10;
    D_8008F428.maxUpdates = 0x40;
    D_8008F428.dmaproc = func_80028908;
    D_8008F428.fxType = 1;
    D_8008F428.heap = &D_8008F070;
    D_8008F428.params = 0;
    alInit(&D_8008F3D8, &D_8008F428);
}

s32 func_80028788(s32 addr, s32 len, void* state) {
    void* foundBuffer;
    s32 delta;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = D_8008F4C8.firstUsed;

    while (dmaPtr) {
        s32 buffEnd = dmaPtr->startAddr + 0x500;

        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addr + len <= buffEnd) {
            dmaPtr->lastFrame = D_80055938;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer*) dmaPtr->node.next;
    }

    dmaPtr = D_8008F4C8.firstFree;
    D_8008F4C8.firstFree = (AMDMABuffer*) dmaPtr->node.next;
    alUnlink((ALLink*) dmaPtr);

    if (lastDmaPtr) {
        alLink((ALLink*) dmaPtr, (ALLink*) lastDmaPtr);
    } else if (D_8008F4C8.firstUsed) {
        lastDmaPtr = D_8008F4C8.firstUsed;
        D_8008F4C8.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink*) lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink*) dmaPtr;
    } else {
        D_8008F4C8.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_80055938;
    osPiStartDma(&D_8008F0D8[D_80055934++], 0, 0, addr, foundBuffer, 0x500, &D_8008F0A0);

    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc func_80028908(AMDMAState** state) {
    s32 i;

    if (!D_8008F4C8.initialized) {
        D_8008F4C8.firstFree = &D_8008F4D8[0];
        D_8008F4C8.firstUsed = 0;
        for (i = 0; i < 31; i++) {
            alLink((ALLink*) &D_8008F4D8[i + 1], (ALLink*) &D_8008F4D8[i]);
            D_8008F4D8[i].ptr = alHeapAlloc(&D_8008F070, 1, 0x500);
        }
        D_8008F4C8.initialized = 1;
    }
    *state = &D_8008F4C8;
    return func_80028788;
}

void func_800289DC(void) {
    AMDMABuffer* dmaPtr;
    AMDMABuffer* nextPtr;

    dmaPtr = D_8008F4C8.firstUsed;
    while (dmaPtr) {
        nextPtr = (AMDMABuffer*) dmaPtr->node.next;
        if (dmaPtr->lastFrame + 2 < D_80055938) {
            if (D_8008F4C8.firstUsed == dmaPtr) {
                D_8008F4C8.firstUsed = (AMDMABuffer*) dmaPtr->node.next;
            }
            alUnlink((ALLink*) dmaPtr);
            if (D_8008F4C8.firstFree) {
                alLink((ALLink*) dmaPtr, (ALLink*) D_8008F4C8.firstFree);
            } else {
                D_8008F4C8.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    D_80055934 = 0;
    D_80055938++;
}

typedef short NNScMsg;

typedef struct SCClient_s {
    struct SCClient_s* next;
    OSMesgQueue* msgQ;
} NNScClient;

typedef struct SCTask_s {
    struct SCTask_s* next;
    u32 state;
    u32 flags;
    void* framebuffer;
    OSTask list;
    OSMesgQueue* msgQ;
    OSMesg msg;
} NNScTask;

extern s32 D_8008F758;
extern u8 D_8004B980[];
extern u8 D_8004BA50[];
extern u8 D_8004CE80[];
extern u8 D_80070A60[];
void nnScAddClient(void* sc, NNScClient* c, OSMesgQueue* msgQ);
OSMesgQueue* nnScGetAudioMQ(void* sc);
Acmd* alAudioFrame(Acmd* cmdList, s32* cmdLen, s16* outBuf, s32 outLen);
s16 n_alSeqpGetVol(ALSeqPlayer* seqp);
void func_80029618(void);

void func_80028AAC(void* arg) {
    OSMesgQueue msgQ;
    OSMesg msgBuf[8];
    OSMesgQueue rtnQ;
    OSMesg rtnBuf[8];
    NNScClient client;
    f32 fsize;
    u32 i;
    s32 idx;
    s32 frameSize;
    NNScTask* task;
    u32 samplesLeft = 0;
    s16* phys;
    OSMesgQueue* audioMQ;
    NNScTask tasks[2];
    Acmd* end;
    NNScMsg* msg = NULL;
    u32 state = 0;
    s16 vol0[2];
    s16 vol[2];
    static s32 D_8005593C = 0;
    static s32 D_80055940 = 1;
    static s16 D_80055944[4] = { 0 };

    fsize = (f32) D_8008F428.outputRate * 1 / 60.0f;
    frameSize = (s32) fsize;
    if (frameSize < fsize) {
        frameSize++;
    }
    if (frameSize & 0xF) {
        frameSize = (frameSize & ~0xF) + 0x10;
    }
    osCreateMesgQueue(&msgQ, msgBuf, 8);
    osCreateMesgQueue(&rtnQ, rtnBuf, 8);
    nnScAddClient(arg, &client, &msgQ);
    audioMQ = nnScGetAudioMQ(arg);
    while (TRUE) {
        osRecvMesg(&msgQ, (OSMesg*) &msg, OS_MESG_BLOCK);
        switch (*msg) {
            case 1:
                func_80029618();
                switch (state) {
                    case 1:
                    for (i = 0; i < 2; i++) {
                        vol[i] -= vol0[i] / 28;
                        if (vol[i] < 0) {
                            vol[i] = 0;
                        }
                        alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[i].player, vol[i]);
                    }
                    if (vol[0] == 0 && vol[1] == 0) {
                        state++;
                    }
                    default:
                task = &tasks[D_8005593C];
                end = D_8008F080[D_8005593C];
                idx = D_80055940 % 3;
                func_800289DC();
                phys = (s16*) osVirtualToPhysical(D_8008F090[idx]);
                D_80055944[idx] = (frameSize - samplesLeft + 0x60) & ~0xF;
                if (D_80055944[idx] < frameSize - 16) {
                    D_80055944[idx] = frameSize - 16;
                }
                end = alAudioFrame(end, &D_8008F758, phys, D_80055944[idx]);
                task->next = NULL;
                task->msgQ = &rtnQ;
                task->msg = NULL;
                task->list.t.data_ptr = D_8008F080[D_8005593C];
                task->list.t.data_size = (end - D_8008F080[D_8005593C]) * sizeof(Acmd);
                task->list.t.type = M_AUDTASK;
                task->list.t.flags = 0;
                task->list.t.ucode_boot = (u64*) D_8004B980;
                task->list.t.ucode_boot_size = (u32) D_8004BA50 - (u32) D_8004B980;
                task->list.t.ucode = (u64*) D_8004CE80;
                task->list.t.ucode_data = (u64*) D_80070A60;
                task->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
                task->list.t.dram_stack = NULL;
                task->list.t.dram_stack_size = 0;
                task->list.t.output_buff = NULL;
                task->list.t.output_buff_size = 0;
                task->list.t.yield_data_ptr = NULL;
                task->list.t.yield_data_size = 0;
                osSendMesg(audioMQ, task, OS_MESG_BLOCK);
                samplesLeft = osAiGetLength() >> 2;
                D_8005593C ^= 1;
                D_80055940++;
                osRecvMesg(&rtnQ, NULL, OS_MESG_BLOCK);
                osAiSetNextBuffer(D_8008F090[idx], D_80055944[idx] << 2);
                    break;
                    case 2:
                        break;
                }
                break;
            case 3:
                state++;
                vol0[0] = n_alSeqpGetVol((ALSeqPlayer*) &D_8008F7A8[0].player);
                vol0[1] = vol[1] = n_alSeqpGetVol((ALSeqPlayer*) &D_8008F7A8[1].player);
                vol[0] = vol0[0] & 0xFFFF;
                break;
        }
    }
}



u32 D_8005594C[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_8005596C[8] = { 0 };
s32 D_8005598C[8] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 };
s32 D_800559AC = 0;
s32 D_800559B0 = 0;
s32 D_800559B4 = 0x7FFF;
s32 D_800559B8 = 0;
s32 D_800559BC = 0xFF;
s32 D_800559C0 = 0xFF;
s32 D_800559C4[2] = { 0x7FFF, 0x7FFF };
s32 D_800559CC = 0;
s32 D_800559D0 = 0;
s32 D_800559D4[5] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_800559E8[5] = { 0 };
s32 D_800559FC[5] = { 0 };
s32 D_80055A10[5] = { 0x40, 0x40, 0x40, 0x40, 0x40 };
s32* D_80055A24[] = {
    &D_8004F8A4[0x0000 / 4],
    &D_8004F8A4[0x0058 / 4],
    &D_8004F8A4[0x00C0 / 4],
    &D_8004F8A4[0x0148 / 4],
    &D_8004F8A4[0x0160 / 4],
    &D_8004F8A4[0x0218 / 4],
    &D_8004F8A4[0x0230 / 4],
    &D_8004F8A4[0x0248 / 4],
    &D_8004F8A4[0x0260 / 4],
    &D_8004F8A4[0x0278 / 4],
    &D_8004F8A4[0x0290 / 4],
    &D_8004F8A4[0x02A8 / 4],
    &D_8004F8A4[0x02C0 / 4],
    &D_8004F8A4[0x02D8 / 4],
    &D_8004F8A4[0x02F0 / 4],
    &D_8004F8A4[0x0318 / 4],
    &D_8004F8A4[0x0330 / 4],
    &D_8004F8A4[0x0348 / 4],
    &D_8004F8A4[0x0360 / 4],
    &D_8004F8A4[0x0378 / 4],
    &D_8004F8A4[0x0390 / 4],
    &D_8004F8A4[0x03A8 / 4],
    &D_8004F8A4[0x03C0 / 4],
    &D_8004F8A4[0x03D8 / 4],
    &D_8004F8A4[0x03F0 / 4],
    &D_8004F8A4[0x0408 / 4],
    &D_8004F8A4[0x0798 / 4],
    &D_8004F8A4[0x0960 / 4],
    &D_8004F8A4[0x13C0 / 4],
    &D_8004F8A4[0x2330 / 4],
    &D_8004F8A4[0x25D0 / 4],
    &D_8004F8A4[0x2870 / 4],
    &D_8004F8A4[0x2BD0 / 4],
    &D_8004F8A4[0x2BF0 / 4],
    &D_8004F8A4[0x2C48 / 4],
    &D_8004F8A4[0x2D60 / 4],
    &D_8004F8A4[0x2D78 / 4],
    &D_8004F8A4[0x30E8 / 4],
    &D_8004F8A4[0x3148 / 4],
    &D_8004F8A4[0x31A0 / 4],
    &D_8004F8A4[0x32F8 / 4],
    &D_8004F8A4[0x34F8 / 4],
    &D_8004F8A4[0x3610 / 4],
    &D_8004F8A4[0x3728 / 4],
    &D_8004F8A4[0x3850 / 4],
    &D_8004F8A4[0x3A08 / 4],
    &D_8004F8A4[0x3AA0 / 4],
    &D_8004F8A4[0x3C68 / 4],
    &D_8004F8A4[0x3D10 / 4],
    &D_8004F8A4[0x3F98 / 4],
    &D_8004F8A4[0x4210 / 4],
    &D_8004F8A4[0x4248 / 4],
    &D_8004F8A4[0x4398 / 4],
    &D_8004F8A4[0x4730 / 4],
    &D_8004F8A4[0x4758 / 4],
    &D_8004F8A4[0x48D0 / 4],
    &D_8004F8A4[0x4910 / 4],
    &D_8004F8A4[0x49F8 / 4],
    &D_8004F8A4[0x4AE0 / 4],
    &D_8004F8A4[0x4E48 / 4],
    &D_8004F8A4[0x5010 / 4],
    &D_8004F8A4[0x5478 / 4],
    &D_8004F8A4[0x56E0 / 4],
    &D_8004F8A4[0x5988 / 4],
    &D_8004F8A4[0x5FF0 / 4],
    &D_8004F8A4[0x6008 / 4],
    &D_8004F8A4[0x6020 / 4],
    &D_8004F8A4[0x6038 / 4],
    &D_8004F8A4[0x6050 / 4],
    &D_8004F8A4[0x6068 / 4],
};

void func_80028F00(u32 devAddr) {
    s32 size;

    D_80055930 = alHeapAlloc(&D_8008F070, 1, 4);
    func_80028550(devAddr, D_80055930, 4);
    size = D_80055930->seqCount * 8 + 4;
    D_80055930 = alHeapAlloc(&D_8008F070, 1, size);
    func_80028550(devAddr, D_80055930, size);
}

void func_80028FA8(void* arg) {
    osCreateThread(&D_8008CEC0, 5, func_80028AAC, arg, &D_8008F070, 0x32);
    osStartThread(&D_8008CEC0);
}

void func_80028FFC(u32 bankStart, u32 bankEnd, u32 seqFile, s32 arg3, u8* table) {
    s32 size;
    ALBank* bank;

    D_8008F7A8[0].seqData = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F7A8[1].seqData = alHeapAlloc(&D_8008F070, 1, 0x8000);
    D_8008F7A8[0].config.maxVoices = 0x40;
    D_8008F7A8[0].config.maxEvents = 0x40;
    D_8008F7A8[0].config.maxChannels = 0x10;
    D_8008F7A8[0].config.heap = &D_8008F070;
    D_8008F7A8[0].config.initOsc = 0;
    D_8008F7A8[0].config.updateOsc = 0;
    D_8008F7A8[0].config.stopOsc = 0;
    D_8008F7A8[0].config.debugFlags = 0;
    alCSPNew(&D_8008F7A8[0].player, &D_8008F7A8[0].config);
    D_8008F7A8[1].config.maxVoices = 0x40;
    D_8008F7A8[1].config.maxEvents = 0x40;
    D_8008F7A8[1].config.maxChannels = 0x10;
    D_8008F7A8[1].config.heap = &D_8008F070;
    D_8008F7A8[1].config.initOsc = 0;
    D_8008F7A8[1].config.updateOsc = 0;
    D_8008F7A8[1].config.stopOsc = 0;
    D_8008F7A8[1].config.debugFlags = 0;
    alCSPNew(&D_8008F7A8[1].player, &D_8008F7A8[1].config);
    func_80028F00(seqFile);
    alSeqFileNew(D_80055930, (u8*) seqFile);
    size = bankEnd - bankStart;
    D_80055928 = alHeapAlloc(&D_8008F070, 1, size);
    func_80028550(bankStart, D_80055928, size);
    alBnkfNew(D_80055928, table);
    bank = D_80055928->bankArray[0];
    alSeqpSetBank((ALSeqPlayer*) &D_8008F7A8[0].player, bank);
    alSeqpSetBank((ALSeqPlayer*) &D_8008F7A8[1].player, bank);
}

void func_80029198(s32 slot, s32 seqNo) {
    u8* offset;
    s32 len;

    offset = D_80055930->seqArray[seqNo].offset;
    len = D_80055930->seqArray[seqNo].len;
    if (len & 1) {
        len++;
    }
    func_80028550((u32) offset, D_8008F7A8[slot].seqData, len);
    D_8008F7A8[slot].seqNo = seqNo;
}

s32 func_80029224(s32 slot) {
    SeqSlot* s = &D_8008F7A8[slot];
    ALCSeq* seq = &s->seq;
    ALCSPlayer* player;
    s32 i;

    if (s->player.state != 0) {
        return 0;
    }
    alCSeqNew(seq, s->seqData);
    player = &s->player;
    alCSPSetSeq(player, seq);
    alSeqpPlay((ALSeqPlayer*) player);
    for (i = 0; i < 16; i++) {
        alSeqpSetChlFXMix(player, i, 0x18);
    }
    return 1;
}

void func_800292DC(s32 slot) {
    alSeqpStop((ALSeqPlayer*) &D_8008F7A8[slot].player);
}

s32 func_80029328(s32 slot) {
    return alSeqpGetState((ALSeqPlayer*) &D_8008F7A8[slot].player);
}

void func_80029374(u32 start, u32 end, u8* table) {
    s32 size;
    u32 i;

    size = end - start;
    D_8005592C = alHeapAlloc(&D_8008F070, 1, size);
    func_80028550(start, D_8005592C, size);
    D_8008F4A8.maxSounds = 0x50;
    D_8008F4A8.maxEvents = 0x20;
    D_8008F4A8.heap = &D_8008F070;
    alSndpNew(&D_8008F450, &D_8008F4A8);
    alBnkfNew(D_8005592C, table);
    D_8008F4B8 = D_8005592C->bankArray[0];
    D_8008F4B4 = D_8008F4B8->instArray[0];
    D_8008F4BC = alHeapAlloc(&D_8008F070, 1, D_8008F4B4->soundCount * 2);
    D_8008F4C0 = 0;
    for (i = 0; i < D_8008F4B4->soundCount; i++) {
        D_8008F4BC[i] = alSndpAllocate(&D_8008F450, D_8008F4B4->soundArray[i]);
        if (D_8008F4BC[i] != -1) {
            D_8008F4C0++;
        }
    }
}

void func_80029520(s32 id) {
    alSndpSetSound(&D_8008F450, D_8008F4BC[id]);
    if (alSndpGetState(&D_8008F450) == 0) {
        alSndpPlay(&D_8008F450);
        alSndpSetFXMix(&D_8008F450, 0x10);
    }
}

void func_80029588(s32 id) {
    alSndpSetSound(&D_8008F450, D_8008F4BC[id]);
    alSndpStop(&D_8008F450);
}

void func_800295D0(s32 id) {
    alSndpSetSound(&D_8008F450, D_8008F4BC[id]);
    alSndpGetState(&D_8008F450);
}

extern s32 D_800559BC;
void func_80029AD4(void);
void func_80029D10(void);
void func_8002A118(void);
void func_8002A1F8(void);

void func_80029618(void) {
    for (D_8008F764 = 0; D_8008F764 < 5; D_8008F764++) {
        if (D_800559E8[D_8008F764] != 0) {
            switch (D_8008F764) {
                case 0:
                    D_8008F75C = D_8008F77C;
                    D_8008F760 = D_8008F790;
                    break;
                case 1:
                    D_8008F75C = D_8008F780;
                    D_8008F760 = D_8008F794;
                    break;
                case 2:
                    D_8008F75C = D_8008F784;
                    D_8008F760 = D_8008F798;
                    break;
                case 3:
                    D_8008F75C = D_8008F788;
                    D_8008F760 = D_8008F79C;
                    break;
                case 4:
                    D_8008F75C = D_8008F78C;
                    D_8008F760 = D_8008F7A0;
                    break;
            }
            if (--D_800559E8[D_8008F764] == 0) {
                func_80029D10();
            }
        }
    }
    if (D_800559BC != 0xFF) {
        func_80029880(D_800559BC);
    }
    if (D_800559CC != 0) {
        func_8002A118();
    }
    if (D_800559D0 != 0) {
        func_8002A1F8();
    }
    func_80029AD4();
}

void func_800297F4(s32 arg0) {
    if (arg0 >= 0 && arg0 < 0x47) {
        D_8008F75C = D_80055A24[arg0];
        return;
    }
    D_8008F75C = D_80055A24[0];
}

s32 func_80029834(void) {
    if (D_800559CC != 0 || D_800559D0 != 0) {
        return 1;
    }
    func_80029880();
    return 0;
}

extern s32 D_800559BC;
extern s32 D_800559C0;
s32 func_8002A2AC(s32 seqNo);

void func_80029880(s32 arg0) {
    s32 seq;

    D_800559BC = arg0;
    if (arg0 == 1) {
        if (D_800559C0 == 0xFF) {
            if (func_8002A2AC(0) != 0) {
                return;
            }
        } else if (D_8008F7A8[0].player.state != 0) {
            alSeqpStop((ALSeqPlayer*) &D_8008F7A8[0].player);
            return;
        }
        D_800559B8 = 1;
        alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[1].player, 0x7FFF);
        D_800559C4[1] = 0x7FFF;
        func_80029224(1);
        D_800559BC = 0xFF;
        return;
    }
    D_800559B8 = 0;
    alSeqpStop((ALSeqPlayer*) &D_8008F7A8[1].player);
    if (arg0 >= 0x50) {
        seq = arg0 - 0x50;
        if (D_800559C0 == seq || func_8002A2AC(seq) == 0) {
            func_80029224(0);
            alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[0].player, 0);
            D_800559C4[0] = 0;
            D_800559D0 = 0x100;
            D_800559C0 = seq;
            D_800559BC = 0xFF;
        }
    } else if (arg0 == D_800559C0 || func_8002A2AC(arg0) == 0) {
        func_80029224(0);
        alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[0].player, 0x7FFF);
        D_800559C4[0] = 0x7FFF;
        D_800559C0 = arg0;
        D_800559BC = 0xFF;
    }
}

void func_80029A38(s32 arg0) {
    s32 i = D_800559B0;

    D_8005594C[i] = arg0;
    D_8005596C[i] = 0;
    D_8005598C[i++] = 0x40;
    D_800559B0 = i & 7;
    // FAKE: under -g3 IDO never fills the delay slot of the final epilogue jr;
    // the label plus a loop-wrapped return give the retail block layout.
end:
    while (TRUE) {
        D_8008FAE0 = i;
        return;
    }
}

void func_80029A88(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_800559B0;

    D_8005594C[i] = arg0;
    D_8005596C[i] = arg1;
    D_8005598C[i++] = arg2;
    D_800559B0 = i & 7;
    // FAKE: same block layout trick as func_80029A38.
end:
    while (TRUE) {
        D_8008FAE4 = i;
        return;
    }
}

extern s32 D_800559FC[5];
extern s32 D_80055A10[5];

void func_80029AD4(void) {
    s32 i;
    s32 idx = D_800559AC;
    s32 id;
    s32 prev;

    if (D_8005594C[idx] != 0xFF) {
        id = D_8005594C[idx];
        D_8005594C[idx] = 0xFF;
        D_800559AC = (idx + 1) & 7;
        D_8008F764 = D_800559AC & 3;
        func_800297F4(id);
        if (*D_8008F75C != 0) {
            D_8008F764 = 4;
            D_800559FC[D_8008F764] = D_8005596C[idx];
            D_80055A10[D_8008F764] = D_8005598C[idx];
            prev = D_800559D4[4];
            if (id != D_800559D4[4] && D_800559D4[4] != 0xFF) {
                func_80029588(D_800559D4[4]);
                D_800559D4[4] = id;
                func_80029520(id);
            }
            if (D_800559D4[4] == 0xFF) {
                D_800559D4[4] = id;
                func_80029520(id);
            }
        } else {
            D_800559FC[D_8008F764] = D_8005596C[idx];
            D_80055A10[D_8008F764] = D_8005598C[idx];
            prev = -1;
            if (D_800559E8[D_8008F764] != 0 && id != D_800559D4[D_8008F764]) {
                func_80029588(D_800559D4[D_8008F764]);
            }
            for (i = 0; i < 4; i++) {
                if (id == D_800559D4[i]) {
                    D_800559E8[i] = 0;
                    D_800559D4[i] = 0xFF;
                }
            }
            D_800559D4[D_8008F764] = id;
            func_80029520(id);
        }
        if (prev != id) {
            D_8008F75C++;
            func_80029D10();
        }
    } else {
        D_800559AC = D_800559B0;
    }
}


void func_80029D10(void) {
    s32 snd = D_800559D4[D_8008F764];
    u32 vol;
    s32 cmd;
    s32 end;

    end = 0xFFFF;
    if (*D_8008F75C == 0xFFFF) {
        func_80029588(snd);
        return;
    }
    if (*D_8008F75C == 0xFFFD) {
        D_8008F760 = D_8008F75C;
        D_8008F75C++;
    }
    if (*D_8008F75C == 0xFFFE) {
        D_8008F75C = D_8008F760;
        D_8008F75C++;
    }
    D_800559E8[D_8008F764] = *D_8008F75C;
    D_8008F75C++;
    if (*D_8008F75C != 0xFFFF) {
        alSndpSetSound(&D_8008F450, D_8008F4BC[snd]);
        alSndpSetPitch(&D_8008F450, D_8004F780[*D_8008F75C]);
    }
    D_8008F75C++;
    cmd = *D_8008F75C;
    if (end != cmd) {
        vol = cmd;
        D_8008F768[D_8008F764] = cmd;
        if (D_800559FC[D_8008F764] != 0) {
            vol = D_800559FC[D_8008F764] * ((u32) cmd >> 8);
        }
        alSndpSetSound(&D_8008F450, D_8008F4BC[snd]);
        alSndpSetVol(&D_8008F450, vol);
    } else if (D_800559FC[D_8008F764] != 0) {
        cmd = D_8008F768[D_8008F764] >> 8;
        vol = D_800559FC[D_8008F764] * cmd;
        alSndpSetSound(&D_8008F450, D_8008F4BC[snd]);
        alSndpSetVol(&D_8008F450, vol);
    }
    D_8008F75C++;
    if (*D_8008F75C != end && D_80055A10[D_8008F764] == 0x40) {
        alSndpSetSound(&D_8008F450, D_8008F4BC[snd]);
        alSndpSetPan(&D_8008F450, *D_8008F75C);
    }
    if (D_80055A10[D_8008F764] != 0x40) {
        alSndpSetSound(&D_8008F450, D_8008F4BC[snd]);
        alSndpSetPan(&D_8008F450, D_80055A10[D_8008F764]);
    }
    D_8008F75C++;
    switch (D_8008F764) {
        case 0:
            D_8008F77C = D_8008F75C;
            D_8008F790 = D_8008F760;
            break;
        case 1:
            D_8008F780 = D_8008F75C;
            D_8008F794 = D_8008F760;
            break;
        case 2:
            D_8008F784 = D_8008F75C;
            D_8008F798 = D_8008F760;
            break;
        case 3:
            D_8008F788 = D_8008F75C;
            D_8008F79C = D_8008F760;
            break;
        case 4:
            D_8008F78C = D_8008F75C;
            D_8008F7A0 = D_8008F760;
            break;
    }
}

void func_8002A118(void) {
    s32 vol;

    vol = D_800559C4[D_800559B8] -= D_800559CC;
    if (vol < 0 || D_800559B4 < vol) {
        D_800559C4[D_800559B8] = D_800559B4;
        alSeqpStop((ALSeqPlayer*) &D_8008F7A8[D_800559B8].player);
        D_800559CC = 0;
    } else {
        alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[D_800559B8].player, vol);
    }
}

void func_8002A1F8(void) {
    s32 vol;

    vol = D_800559C4[D_800559B8] += D_800559D0;
    if (vol < 0 || D_800559B4 < vol) {
        D_800559C4[D_800559B8] = D_800559B4;
        D_800559D0 = 0;
    } else {
        alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[D_800559B8].player, vol);
    }
}

s32 func_8002A2AC(s32 seqNo) {
    if (D_8008F7A8[D_800559B8].player.state == 0) {
        func_80029198(0, seqNo);
        func_80029198(1, 1);
        return 0;
    }
    alSeqpStop((ALSeqPlayer*) &D_8008F7A8[0].player);
    alSeqpStop((ALSeqPlayer*) &D_8008F7A8[1].player);
    return 1;
}

s32 func_8002A338(u32 frames) {
    if (D_800559CC != 0 || D_800559D0 != 0) {
        return 1;
    }
    D_800559CC = 0x8000 / frames;
    return 0;
}

void func_8002A38C(void) {
    s32 i;
    s32 id;

    for (i = 0; i < 5; i++) {
        id = D_800559D4[i];
        if (id != 0xFFU) {
            func_80029588(id);
        }
        D_800559E8[i] = 0;
        D_800559D4[i] = 0xFF;
    }
}

void func_8002A410(void) {
    if (D_800559E4 != 0xFF) {
        func_80029588(D_800559E4);
    }
    D_800559F8 = 0;
    D_800559E4 = 0xFF;
}

s32 func_8002A458(s32 vol) {
    if (D_800559CC != 0 || D_800559D0 != 0) {
        return 1;
    }
    D_800559B4 = (vol << 7) + 0x7F;
    alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[0].player, D_800559B4);
    alSeqpSetVol((ALSeqPlayer*) &D_8008F7A8[1].player, D_800559B4);
    D_800559C4[0] = D_800559B4;
    D_800559C4[1] = D_800559B4;
    return 0;
}
