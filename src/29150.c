#include "common.h"

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

extern ALHeap D_8008F070;
extern u8 D_80332DB0[];
extern Acmd* D_8008F080[2];
extern void* D_8008F088[2];
extern s16* D_8008F090[3];
extern OSMesgQueue D_8008F0A0;
extern OSMesgQueue D_8008F0B8;
extern OSMesg D_8008F0D0;
extern OSMesg D_8008F0D4;
extern OSIoMesg D_8008F0D8[];
extern ALGlobals D_8008F3D8;
extern ALSynConfig D_8008F428;
extern AMDMAState D_8008F4C8;
extern AMDMABuffer D_8008F4D8[32];
extern s32 D_80055934;
extern u32 D_80055938;
extern ALSeqFile* D_80055930;
extern ALBankFile* D_80055928;
extern OSThread D_8008CEC0;
extern SeqSlot D_8008F7A8[2];

void func_80028AAC(void*);
void alCSeqNew(ALCSeq*, u8*);

extern ALBankFile* D_8005592C;
extern ALSndpConfig D_8008F4A8;
extern ALSndPlayer D_8008F450;
extern ALInstrument* D_8008F4B4;
extern ALBank* D_8008F4B8;
extern s16* D_8008F4BC;
extern s32 D_8008F4C0;
extern s32* D_8008F75C;
extern s32* D_80055A24[];
extern s32 D_800559CC;
extern s32 D_800559D0;
extern u32 D_8005594C[8];
extern s32 D_8005596C[8];
extern s32 D_8005598C[8];
extern s32 D_800559AC;
extern s32 D_800559B0;
extern s32 D_8008FAE0;
extern s32 D_8008FAE4;
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

#pragma GLOBAL_ASM("asm/nonmatchings/29150/func_80028AAC.s")

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
extern s32 D_8008F764;
extern s32* D_8008F760;
extern s32* D_8008F77C;
extern s32* D_8008F780;
extern s32* D_8008F784;
extern s32* D_8008F788;
extern s32* D_8008F78C;
extern s32* D_8008F790;
extern s32* D_8008F794;
extern s32* D_8008F798;
extern s32* D_8008F79C;
extern s32* D_8008F7A0;
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

extern f32 D_8004F780[];
extern u32 D_8008F768[5];

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
