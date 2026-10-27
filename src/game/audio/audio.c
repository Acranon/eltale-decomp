#include "game/audio/audio.h"

/*
 * Audio driver: synthesizer init and sample DMA cache, the audio thread (nnSc client),
 * two compact-sequence players with volume fades, and the sound player with its
 * 5-channel sound-effect script interpreter and request queue.
 * Original file: 29150.c (ROM 0x29150).
 */

/* .bss 8008CEC0..8008FAF0 */
OSThread audio_thread;
u64 audio_thread_stack[0x2000 / 8]; /* Audio_ThreadMain's stack (its top is audio_heap) */
ALHeap audio_heap;
Acmd* audio_cmd_lists[2];
void* D_8008F088[2];
s16* audio_output_buffers[3];
OSMesgQueue audio_dma_queue;
OSMesgQueue audio_rom_read_queue;
OSMesg audio_dma_mesg;
OSMesg audio_rom_read_mesg;
OSIoMesg audio_dma_io_mesgs[32];
ALGlobals audio_globals;
ALSynConfig audio_syn_config;
ALSndPlayer audio_sound_player;
ALSndpConfig audio_sound_player_config;
ALInstrument* audio_sound_inst;
ALBank* audio_sound_bank;
s16* audio_sound_ids;
s32 D_8008F4C0;
AMDMAState audio_dma_state;
AMDMABuffer audio_dma_buffers[32];
s32 D_8008F758;
s32* sfx_script_pos;
s32* sfx_script_loop_pos;
s32 sfx_cur_channel;
u32 sfx_channel_volume_word[5];
s32* sfx_ch0_script_pos;
s32* sfx_ch1_script_pos;
s32* sfx_ch2_script_pos;
s32* sfx_ch3_script_pos;
s32* sfx_ch4_script_pos;
s32* sfx_ch0_loop_pos;
s32* sfx_ch1_loop_pos;
s32* sfx_ch2_loop_pos;
s32* sfx_ch3_loop_pos;
s32* sfx_ch4_loop_pos;
SeqSlot audio_seq_slots[2];
s32 D_8008FAE0;
s32 D_8008FAE4;

extern u8 D_80332DB0[];
f32 sfx_pitch_table[73] = {
#include "assets/sfx_pitch_table.inc.c"
};
s32 sfx_script_data[0x6084 / 4] = {
#include "assets/sfx_script_data.inc.c"
};
ALBankFile* audio_seq_bank_file = NULL;
ALBankFile* audio_sound_bank_file = NULL;
ALSeqFile* audio_seq_file = NULL;
s32 audio_dma_count = 0;
u32 audio_frame_count = 0;

void alCSeqNew(ALCSeq*, u8*);

extern s32 D_800559E4;
extern s32 D_800559F8;

void alSndpNew(ALSndPlayer*, ALSndpConfig*);

void Audio_DmaReadRom(u32 devAddr, void* vAddr, s32 nbytes) {
    OSIoMesg sp28;

    osInvalDCache(vAddr, nbytes);
    osPiStartDma(&sp28, 0, 0, devAddr, vAddr, nbytes, &audio_rom_read_queue);
    osRecvMesg(&audio_rom_read_queue, NULL, 1);
}


void Audio_Init(void) {
    alHeapInit(&audio_heap, D_80332DB0, 0x68000);
    audio_cmd_lists[0] = alHeapAlloc(&audio_heap, 1, 0x8000);
    audio_cmd_lists[1] = alHeapAlloc(&audio_heap, 1, 0x8000);
    D_8008F088[0] = alHeapAlloc(&audio_heap, 1, 0x40);
    D_8008F088[1] = alHeapAlloc(&audio_heap, 1, 0x40);
    audio_output_buffers[0] = alHeapAlloc(&audio_heap, 1, 0x8000);
    audio_output_buffers[1] = alHeapAlloc(&audio_heap, 1, 0x8000);
    audio_output_buffers[2] = alHeapAlloc(&audio_heap, 1, 0x8000);
    osCreateMesgQueue(&audio_dma_queue, &audio_dma_mesg, 1);
    osCreateMesgQueue(&audio_rom_read_queue, &audio_rom_read_mesg, 1);
    audio_dma_state.initialized = 0;
    audio_syn_config.outputRate = osAiSetFrequency(0x5622);
    audio_syn_config.maxVVoices = 0x10;
    audio_syn_config.maxPVoices = 0x10;
    audio_syn_config.maxUpdates = 0x40;
    audio_syn_config.dmaproc = Audio_DmaNew;
    audio_syn_config.fxType = 1;
    audio_syn_config.heap = &audio_heap;
    audio_syn_config.params = 0;
    alInit(&audio_globals, &audio_syn_config);
}

s32 Audio_DmaCallback(s32 addr, s32 len, void* state) {
    void* foundBuffer;
    s32 delta;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = audio_dma_state.firstUsed;

    while (dmaPtr) {
        s32 buffEnd = dmaPtr->startAddr + 0x500;

        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addr + len <= buffEnd) {
            dmaPtr->lastFrame = audio_frame_count;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer*) dmaPtr->node.next;
    }

    dmaPtr = audio_dma_state.firstFree;
    audio_dma_state.firstFree = (AMDMABuffer*) dmaPtr->node.next;
    alUnlink((ALLink*) dmaPtr);

    if (lastDmaPtr) {
        alLink((ALLink*) dmaPtr, (ALLink*) lastDmaPtr);
    } else if (audio_dma_state.firstUsed) {
        lastDmaPtr = audio_dma_state.firstUsed;
        audio_dma_state.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink*) lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink*) dmaPtr;
    } else {
        audio_dma_state.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audio_frame_count;
    osPiStartDma(&audio_dma_io_mesgs[audio_dma_count++], 0, 0, addr, foundBuffer, 0x500, &audio_dma_queue);

    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc Audio_DmaNew(AMDMAState** state) {
    s32 i;

    if (!audio_dma_state.initialized) {
        audio_dma_state.firstFree = &audio_dma_buffers[0];
        audio_dma_state.firstUsed = 0;
        for (i = 0; i < 31; i++) {
            alLink((ALLink*) &audio_dma_buffers[i + 1], (ALLink*) &audio_dma_buffers[i]);
            audio_dma_buffers[i].ptr = alHeapAlloc(&audio_heap, 1, 0x500);
        }
        audio_dma_state.initialized = 1;
    }
    *state = &audio_dma_state;
    return Audio_DmaCallback;
}

void Audio_FreeOldDmaBuffers(void) {
    AMDMABuffer* dmaPtr;
    AMDMABuffer* nextPtr;

    dmaPtr = audio_dma_state.firstUsed;
    while (dmaPtr) {
        nextPtr = (AMDMABuffer*) dmaPtr->node.next;
        if (dmaPtr->lastFrame + 2 < audio_frame_count) {
            if (audio_dma_state.firstUsed == dmaPtr) {
                audio_dma_state.firstUsed = (AMDMABuffer*) dmaPtr->node.next;
            }
            alUnlink((ALLink*) dmaPtr);
            if (audio_dma_state.firstFree) {
                alLink((ALLink*) dmaPtr, (ALLink*) audio_dma_state.firstFree);
            } else {
                audio_dma_state.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    audio_dma_count = 0;
    audio_frame_count++;
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

extern u8 D_8004B980[];
extern u8 D_8004BA50[];
extern u8 D_8004CE80[];
extern u8 D_80070A60[];
void nnScAddClient(void* sc, NNScClient* c, OSMesgQueue* msgQ);
OSMesgQueue* nnScGetAudioMQ(void* sc);
Acmd* alAudioFrame(Acmd* cmdList, s32* cmdLen, s16* outBuf, s32 outLen);
s16 n_alSeqpGetVol(ALSeqPlayer* seqp);

void Audio_ThreadMain(void* arg) {
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

    fsize = (f32) audio_syn_config.outputRate * 1 / 60.0f;
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
                Audio_UpdateFrame();
                switch (state) {
                    case 1:
                    for (i = 0; i < 2; i++) {
                        vol[i] -= vol0[i] / 28;
                        if (vol[i] < 0) {
                            vol[i] = 0;
                        }
                        alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[i].player, vol[i]);
                    }
                    if (vol[0] == 0 && vol[1] == 0) {
                        state++;
                    }
                    default:
                task = &tasks[D_8005593C];
                end = audio_cmd_lists[D_8005593C];
                idx = D_80055940 % 3;
                Audio_FreeOldDmaBuffers();
                phys = (s16*) osVirtualToPhysical(audio_output_buffers[idx]);
                D_80055944[idx] = (frameSize - samplesLeft + 0x60) & ~0xF;
                if (D_80055944[idx] < frameSize - 16) {
                    D_80055944[idx] = frameSize - 16;
                }
                end = alAudioFrame(end, &D_8008F758, phys, D_80055944[idx]);
                task->next = NULL;
                task->msgQ = &rtnQ;
                task->msg = NULL;
                task->list.t.data_ptr = audio_cmd_lists[D_8005593C];
                task->list.t.data_size = (end - audio_cmd_lists[D_8005593C]) * sizeof(Acmd);
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
                osAiSetNextBuffer(audio_output_buffers[idx], D_80055944[idx] << 2);
                    break;
                    case 2:
                        break;
                }
                break;
            case 3:
                state++;
                vol0[0] = n_alSeqpGetVol((ALSeqPlayer*) &audio_seq_slots[0].player);
                vol0[1] = vol[1] = n_alSeqpGetVol((ALSeqPlayer*) &audio_seq_slots[1].player);
                vol[0] = vol0[0] & 0xFFFF;
                break;
        }
    }
}



u32 sfx_queue_ids[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
s32 sfx_queue_volumes[8] = { 0 };
s32 sfx_queue_pans[8] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 };
s32 sfx_queue_read = 0;
s32 sfx_queue_write = 0;
s32 audio_seq_volume_limit = 0x7FFF;
s32 audio_active_seq_slot = 0;
s32 audio_pending_seq_request = 0xFF;
s32 audio_loaded_seq = 0xFF;
s32 audio_seq_volumes[2] = { 0x7FFF, 0x7FFF };
s32 audio_seq_fade_out_step = 0;
s32 audio_seq_fade_in_step = 0;
s32 sfx_channel_sound[5] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
s32 sfx_channel_timer[5] = { 0 };
s32 sfx_channel_volume_factor[5] = { 0 };
s32 sfx_channel_pan[5] = { 0x40, 0x40, 0x40, 0x40, 0x40 };
s32* sfx_scripts[] = {
    &sfx_script_data[0x0000 / 4],
    &sfx_script_data[0x0058 / 4],
    &sfx_script_data[0x00C0 / 4],
    &sfx_script_data[0x0148 / 4],
    &sfx_script_data[0x0160 / 4],
    &sfx_script_data[0x0218 / 4],
    &sfx_script_data[0x0230 / 4],
    &sfx_script_data[0x0248 / 4],
    &sfx_script_data[0x0260 / 4],
    &sfx_script_data[0x0278 / 4],
    &sfx_script_data[0x0290 / 4],
    &sfx_script_data[0x02A8 / 4],
    &sfx_script_data[0x02C0 / 4],
    &sfx_script_data[0x02D8 / 4],
    &sfx_script_data[0x02F0 / 4],
    &sfx_script_data[0x0318 / 4],
    &sfx_script_data[0x0330 / 4],
    &sfx_script_data[0x0348 / 4],
    &sfx_script_data[0x0360 / 4],
    &sfx_script_data[0x0378 / 4],
    &sfx_script_data[0x0390 / 4],
    &sfx_script_data[0x03A8 / 4],
    &sfx_script_data[0x03C0 / 4],
    &sfx_script_data[0x03D8 / 4],
    &sfx_script_data[0x03F0 / 4],
    &sfx_script_data[0x0408 / 4],
    &sfx_script_data[0x0798 / 4],
    &sfx_script_data[0x0960 / 4],
    &sfx_script_data[0x13C0 / 4],
    &sfx_script_data[0x2330 / 4],
    &sfx_script_data[0x25D0 / 4],
    &sfx_script_data[0x2870 / 4],
    &sfx_script_data[0x2BD0 / 4],
    &sfx_script_data[0x2BF0 / 4],
    &sfx_script_data[0x2C48 / 4],
    &sfx_script_data[0x2D60 / 4],
    &sfx_script_data[0x2D78 / 4],
    &sfx_script_data[0x30E8 / 4],
    &sfx_script_data[0x3148 / 4],
    &sfx_script_data[0x31A0 / 4],
    &sfx_script_data[0x32F8 / 4],
    &sfx_script_data[0x34F8 / 4],
    &sfx_script_data[0x3610 / 4],
    &sfx_script_data[0x3728 / 4],
    &sfx_script_data[0x3850 / 4],
    &sfx_script_data[0x3A08 / 4],
    &sfx_script_data[0x3AA0 / 4],
    &sfx_script_data[0x3C68 / 4],
    &sfx_script_data[0x3D10 / 4],
    &sfx_script_data[0x3F98 / 4],
    &sfx_script_data[0x4210 / 4],
    &sfx_script_data[0x4248 / 4],
    &sfx_script_data[0x4398 / 4],
    &sfx_script_data[0x4730 / 4],
    &sfx_script_data[0x4758 / 4],
    &sfx_script_data[0x48D0 / 4],
    &sfx_script_data[0x4910 / 4],
    &sfx_script_data[0x49F8 / 4],
    &sfx_script_data[0x4AE0 / 4],
    &sfx_script_data[0x4E48 / 4],
    &sfx_script_data[0x5010 / 4],
    &sfx_script_data[0x5478 / 4],
    &sfx_script_data[0x56E0 / 4],
    &sfx_script_data[0x5988 / 4],
    &sfx_script_data[0x5FF0 / 4],
    &sfx_script_data[0x6008 / 4],
    &sfx_script_data[0x6020 / 4],
    &sfx_script_data[0x6038 / 4],
    &sfx_script_data[0x6050 / 4],
    &sfx_script_data[0x6068 / 4],
};

void Audio_LoadSeqFileHeader(u32 devAddr) {
    s32 size;

    audio_seq_file = alHeapAlloc(&audio_heap, 1, 4);
    Audio_DmaReadRom(devAddr, audio_seq_file, 4);
    size = audio_seq_file->seqCount * 8 + 4;
    audio_seq_file = alHeapAlloc(&audio_heap, 1, size);
    Audio_DmaReadRom(devAddr, audio_seq_file, size);
}

void Audio_StartThread(void* arg) {
    osCreateThread(&audio_thread, 5, Audio_ThreadMain, arg, &audio_heap, 0x32);
    osStartThread(&audio_thread);
}

void Audio_InitSeqPlayers(u32 bankStart, u32 bankEnd, u32 seqFile, s32 arg3, u8* table) {
    s32 size;
    ALBank* bank;

    audio_seq_slots[0].seqData = alHeapAlloc(&audio_heap, 1, 0x8000);
    audio_seq_slots[1].seqData = alHeapAlloc(&audio_heap, 1, 0x8000);
    audio_seq_slots[0].config.maxVoices = 0x40;
    audio_seq_slots[0].config.maxEvents = 0x40;
    audio_seq_slots[0].config.maxChannels = 0x10;
    audio_seq_slots[0].config.heap = &audio_heap;
    audio_seq_slots[0].config.initOsc = 0;
    audio_seq_slots[0].config.updateOsc = 0;
    audio_seq_slots[0].config.stopOsc = 0;
    audio_seq_slots[0].config.debugFlags = 0;
    alCSPNew(&audio_seq_slots[0].player, &audio_seq_slots[0].config);
    audio_seq_slots[1].config.maxVoices = 0x40;
    audio_seq_slots[1].config.maxEvents = 0x40;
    audio_seq_slots[1].config.maxChannels = 0x10;
    audio_seq_slots[1].config.heap = &audio_heap;
    audio_seq_slots[1].config.initOsc = 0;
    audio_seq_slots[1].config.updateOsc = 0;
    audio_seq_slots[1].config.stopOsc = 0;
    audio_seq_slots[1].config.debugFlags = 0;
    alCSPNew(&audio_seq_slots[1].player, &audio_seq_slots[1].config);
    Audio_LoadSeqFileHeader(seqFile);
    alSeqFileNew(audio_seq_file, (u8*) seqFile);
    size = bankEnd - bankStart;
    audio_seq_bank_file = alHeapAlloc(&audio_heap, 1, size);
    Audio_DmaReadRom(bankStart, audio_seq_bank_file, size);
    alBnkfNew(audio_seq_bank_file, table);
    bank = audio_seq_bank_file->bankArray[0];
    alSeqpSetBank((ALSeqPlayer*) &audio_seq_slots[0].player, bank);
    alSeqpSetBank((ALSeqPlayer*) &audio_seq_slots[1].player, bank);
}

void Audio_LoadSeq(s32 slot, s32 seqNo) {
    u8* offset;
    s32 len;

    offset = audio_seq_file->seqArray[seqNo].offset;
    len = audio_seq_file->seqArray[seqNo].len;
    if (len & 1) {
        len++;
    }
    Audio_DmaReadRom((u32) offset, audio_seq_slots[slot].seqData, len);
    audio_seq_slots[slot].seqNo = seqNo;
}

s32 Audio_PlaySeq(s32 slot) {
    SeqSlot* s = &audio_seq_slots[slot];
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

void Audio_StopSeq(s32 slot) {
    alSeqpStop((ALSeqPlayer*) &audio_seq_slots[slot].player);
}

s32 Audio_GetSeqState(s32 slot) {
    return alSeqpGetState((ALSeqPlayer*) &audio_seq_slots[slot].player);
}

void Audio_InitSoundPlayer(u32 start, u32 end, u8* table) {
    s32 size;
    u32 i;

    size = end - start;
    audio_sound_bank_file = alHeapAlloc(&audio_heap, 1, size);
    Audio_DmaReadRom(start, audio_sound_bank_file, size);
    audio_sound_player_config.maxSounds = 0x50;
    audio_sound_player_config.maxEvents = 0x20;
    audio_sound_player_config.heap = &audio_heap;
    alSndpNew(&audio_sound_player, &audio_sound_player_config);
    alBnkfNew(audio_sound_bank_file, table);
    audio_sound_bank = audio_sound_bank_file->bankArray[0];
    audio_sound_inst = audio_sound_bank->instArray[0];
    audio_sound_ids = alHeapAlloc(&audio_heap, 1, audio_sound_inst->soundCount * 2);
    D_8008F4C0 = 0;
    for (i = 0; i < audio_sound_inst->soundCount; i++) {
        audio_sound_ids[i] = alSndpAllocate(&audio_sound_player, audio_sound_inst->soundArray[i]);
        if (audio_sound_ids[i] != -1) {
            D_8008F4C0++;
        }
    }
}

void Audio_PlaySound(s32 id) {
    alSndpSetSound(&audio_sound_player, audio_sound_ids[id]);
    if (alSndpGetState(&audio_sound_player) == 0) {
        alSndpPlay(&audio_sound_player);
        alSndpSetFXMix(&audio_sound_player, 0x10);
    }
}

void Audio_StopSound(s32 id) {
    alSndpSetSound(&audio_sound_player, audio_sound_ids[id]);
    alSndpStop(&audio_sound_player);
}

void Audio_GetSoundState(s32 id) {
    alSndpSetSound(&audio_sound_player, audio_sound_ids[id]);
    alSndpGetState(&audio_sound_player);
}


void Audio_UpdateFrame(void) {
    for (sfx_cur_channel = 0; sfx_cur_channel < 5; sfx_cur_channel++) {
        if (sfx_channel_timer[sfx_cur_channel] != 0) {
            switch (sfx_cur_channel) {
                case 0:
                    sfx_script_pos = sfx_ch0_script_pos;
                    sfx_script_loop_pos = sfx_ch0_loop_pos;
                    break;
                case 1:
                    sfx_script_pos = sfx_ch1_script_pos;
                    sfx_script_loop_pos = sfx_ch1_loop_pos;
                    break;
                case 2:
                    sfx_script_pos = sfx_ch2_script_pos;
                    sfx_script_loop_pos = sfx_ch2_loop_pos;
                    break;
                case 3:
                    sfx_script_pos = sfx_ch3_script_pos;
                    sfx_script_loop_pos = sfx_ch3_loop_pos;
                    break;
                case 4:
                    sfx_script_pos = sfx_ch4_script_pos;
                    sfx_script_loop_pos = sfx_ch4_loop_pos;
                    break;
            }
            if (--sfx_channel_timer[sfx_cur_channel] == 0) {
                Sfx_StepScript();
            }
        }
    }
    if (audio_pending_seq_request != 0xFF) {
        Audio_StartSeqRequest(audio_pending_seq_request);
    }
    if (audio_seq_fade_out_step != 0) {
        Audio_StepSeqFadeOut();
    }
    if (audio_seq_fade_in_step != 0) {
        Audio_StepSeqFadeIn();
    }
    Sfx_ProcessQueue();
}

void Sfx_SelectScript(s32 arg0) {
    if (arg0 >= 0 && arg0 < 0x47) {
        sfx_script_pos = sfx_scripts[arg0];
        return;
    }
    sfx_script_pos = sfx_scripts[0];
}

/* Takes the request argument: the code leaves a0 untouched for Audio_StartSeqRequest (H1;
 * it was written with no parameter and a no-argument call). */
s32 func_80029834(s32 arg0) {
    if (audio_seq_fade_out_step != 0 || audio_seq_fade_in_step != 0) {
        return 1;
    }
    Audio_StartSeqRequest(arg0);
    return 0;
}


void Audio_StartSeqRequest(s32 arg0) {
    s32 seq;

    audio_pending_seq_request = arg0;
    if (arg0 == 1) {
        if (audio_loaded_seq == 0xFF) {
            if (Audio_LoadSeqsOrStop(0) != 0) {
                return;
            }
        } else if (audio_seq_slots[0].player.state != 0) {
            alSeqpStop((ALSeqPlayer*) &audio_seq_slots[0].player);
            return;
        }
        audio_active_seq_slot = 1;
        alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[1].player, 0x7FFF);
        audio_seq_volumes[1] = 0x7FFF;
        Audio_PlaySeq(1);
        audio_pending_seq_request = 0xFF;
        return;
    }
    audio_active_seq_slot = 0;
    alSeqpStop((ALSeqPlayer*) &audio_seq_slots[1].player);
    if (arg0 >= 0x50) {
        seq = arg0 - 0x50;
        if (audio_loaded_seq == seq || Audio_LoadSeqsOrStop(seq) == 0) {
            Audio_PlaySeq(0);
            alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[0].player, 0);
            audio_seq_volumes[0] = 0;
            audio_seq_fade_in_step = 0x100;
            audio_loaded_seq = seq;
            audio_pending_seq_request = 0xFF;
        }
    } else if (arg0 == audio_loaded_seq || Audio_LoadSeqsOrStop(arg0) == 0) {
        Audio_PlaySeq(0);
        alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[0].player, 0x7FFF);
        audio_seq_volumes[0] = 0x7FFF;
        audio_loaded_seq = arg0;
        audio_pending_seq_request = 0xFF;
    }
}

void Sfx_EnqueueDefault(s32 arg0) {
    s32 i = sfx_queue_write;

    sfx_queue_ids[i] = arg0;
    sfx_queue_volumes[i] = 0;
    sfx_queue_pans[i++] = 0x40;
    sfx_queue_write = i & 7;
    // FAKE: under -g3 IDO never fills the delay slot of the final epilogue jr;
    // the label plus a loop-wrapped return give the retail block layout.
end:
    while (TRUE) {
        D_8008FAE0 = i;
        return;
    }
}

void Sfx_Enqueue(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = sfx_queue_write;

    sfx_queue_ids[i] = arg0;
    sfx_queue_volumes[i] = arg1;
    sfx_queue_pans[i++] = arg2;
    sfx_queue_write = i & 7;
    // FAKE: same block layout trick as Sfx_EnqueueDefault.
end:
    while (TRUE) {
        D_8008FAE4 = i;
        return;
    }
}


void Sfx_ProcessQueue(void) {
    s32 i;
    s32 idx = sfx_queue_read;
    s32 id;
    s32 prev;

    if (sfx_queue_ids[idx] != 0xFF) {
        id = sfx_queue_ids[idx];
        sfx_queue_ids[idx] = 0xFF;
        sfx_queue_read = (idx + 1) & 7;
        sfx_cur_channel = sfx_queue_read & 3;
        Sfx_SelectScript(id);
        if (*sfx_script_pos != 0) {
            sfx_cur_channel = 4;
            sfx_channel_volume_factor[sfx_cur_channel] = sfx_queue_volumes[idx];
            sfx_channel_pan[sfx_cur_channel] = sfx_queue_pans[idx];
            prev = sfx_channel_sound[4];
            if (id != sfx_channel_sound[4] && sfx_channel_sound[4] != 0xFF) {
                Audio_StopSound(sfx_channel_sound[4]);
                sfx_channel_sound[4] = id;
                Audio_PlaySound(id);
            }
            if (sfx_channel_sound[4] == 0xFF) {
                sfx_channel_sound[4] = id;
                Audio_PlaySound(id);
            }
        } else {
            sfx_channel_volume_factor[sfx_cur_channel] = sfx_queue_volumes[idx];
            sfx_channel_pan[sfx_cur_channel] = sfx_queue_pans[idx];
            prev = -1;
            if (sfx_channel_timer[sfx_cur_channel] != 0 && id != sfx_channel_sound[sfx_cur_channel]) {
                Audio_StopSound(sfx_channel_sound[sfx_cur_channel]);
            }
            for (i = 0; i < 4; i++) {
                if (id == sfx_channel_sound[i]) {
                    sfx_channel_timer[i] = 0;
                    sfx_channel_sound[i] = 0xFF;
                }
            }
            sfx_channel_sound[sfx_cur_channel] = id;
            Audio_PlaySound(id);
        }
        if (prev != id) {
            sfx_script_pos++;
            Sfx_StepScript();
        }
    } else {
        sfx_queue_read = sfx_queue_write;
    }
}


void Sfx_StepScript(void) {
    s32 snd = sfx_channel_sound[sfx_cur_channel];
    u32 vol;
    s32 cmd;
    s32 end;

    end = 0xFFFF;
    if (*sfx_script_pos == 0xFFFF) {
        Audio_StopSound(snd);
        return;
    }
    if (*sfx_script_pos == 0xFFFD) {
        sfx_script_loop_pos = sfx_script_pos;
        sfx_script_pos++;
    }
    if (*sfx_script_pos == 0xFFFE) {
        sfx_script_pos = sfx_script_loop_pos;
        sfx_script_pos++;
    }
    sfx_channel_timer[sfx_cur_channel] = *sfx_script_pos;
    sfx_script_pos++;
    if (*sfx_script_pos != 0xFFFF) {
        alSndpSetSound(&audio_sound_player, audio_sound_ids[snd]);
        alSndpSetPitch(&audio_sound_player, sfx_pitch_table[*sfx_script_pos]);
    }
    sfx_script_pos++;
    cmd = *sfx_script_pos;
    if (end != cmd) {
        vol = cmd;
        sfx_channel_volume_word[sfx_cur_channel] = cmd;
        if (sfx_channel_volume_factor[sfx_cur_channel] != 0) {
            vol = sfx_channel_volume_factor[sfx_cur_channel] * ((u32) cmd >> 8);
        }
        alSndpSetSound(&audio_sound_player, audio_sound_ids[snd]);
        alSndpSetVol(&audio_sound_player, vol);
    } else if (sfx_channel_volume_factor[sfx_cur_channel] != 0) {
        cmd = sfx_channel_volume_word[sfx_cur_channel] >> 8;
        vol = sfx_channel_volume_factor[sfx_cur_channel] * cmd;
        alSndpSetSound(&audio_sound_player, audio_sound_ids[snd]);
        alSndpSetVol(&audio_sound_player, vol);
    }
    sfx_script_pos++;
    if (*sfx_script_pos != end && sfx_channel_pan[sfx_cur_channel] == 0x40) {
        alSndpSetSound(&audio_sound_player, audio_sound_ids[snd]);
        alSndpSetPan(&audio_sound_player, *sfx_script_pos);
    }
    if (sfx_channel_pan[sfx_cur_channel] != 0x40) {
        alSndpSetSound(&audio_sound_player, audio_sound_ids[snd]);
        alSndpSetPan(&audio_sound_player, sfx_channel_pan[sfx_cur_channel]);
    }
    sfx_script_pos++;
    switch (sfx_cur_channel) {
        case 0:
            sfx_ch0_script_pos = sfx_script_pos;
            sfx_ch0_loop_pos = sfx_script_loop_pos;
            break;
        case 1:
            sfx_ch1_script_pos = sfx_script_pos;
            sfx_ch1_loop_pos = sfx_script_loop_pos;
            break;
        case 2:
            sfx_ch2_script_pos = sfx_script_pos;
            sfx_ch2_loop_pos = sfx_script_loop_pos;
            break;
        case 3:
            sfx_ch3_script_pos = sfx_script_pos;
            sfx_ch3_loop_pos = sfx_script_loop_pos;
            break;
        case 4:
            sfx_ch4_script_pos = sfx_script_pos;
            sfx_ch4_loop_pos = sfx_script_loop_pos;
            break;
    }
}

void Audio_StepSeqFadeOut(void) {
    s32 vol;

    vol = audio_seq_volumes[audio_active_seq_slot] -= audio_seq_fade_out_step;
    if (vol < 0 || audio_seq_volume_limit < vol) {
        audio_seq_volumes[audio_active_seq_slot] = audio_seq_volume_limit;
        alSeqpStop((ALSeqPlayer*) &audio_seq_slots[audio_active_seq_slot].player);
        audio_seq_fade_out_step = 0;
    } else {
        alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[audio_active_seq_slot].player, vol);
    }
}

void Audio_StepSeqFadeIn(void) {
    s32 vol;

    vol = audio_seq_volumes[audio_active_seq_slot] += audio_seq_fade_in_step;
    if (vol < 0 || audio_seq_volume_limit < vol) {
        audio_seq_volumes[audio_active_seq_slot] = audio_seq_volume_limit;
        audio_seq_fade_in_step = 0;
    } else {
        alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[audio_active_seq_slot].player, vol);
    }
}

s32 Audio_LoadSeqsOrStop(s32 seqNo) {
    if (audio_seq_slots[audio_active_seq_slot].player.state == 0) {
        Audio_LoadSeq(0, seqNo);
        Audio_LoadSeq(1, 1);
        return 0;
    }
    alSeqpStop((ALSeqPlayer*) &audio_seq_slots[0].player);
    alSeqpStop((ALSeqPlayer*) &audio_seq_slots[1].player);
    return 1;
}

s32 Audio_StartSeqFadeOut(u32 frames) {
    if (audio_seq_fade_out_step != 0 || audio_seq_fade_in_step != 0) {
        return 1;
    }
    audio_seq_fade_out_step = 0x8000 / frames;
    return 0;
}

void Sfx_StopAllChannels(void) {
    s32 i;
    s32 id;

    for (i = 0; i < 5; i++) {
        id = sfx_channel_sound[i];
        if (id != 0xFFU) {
            Audio_StopSound(id);
        }
        sfx_channel_timer[i] = 0;
        sfx_channel_sound[i] = 0xFF;
    }
}

void Sfx_StopChannel4(void) {
    if (D_800559E4 != 0xFF) {
        Audio_StopSound(D_800559E4);
    }
    D_800559F8 = 0;
    D_800559E4 = 0xFF;
}

s32 Audio_SetSeqVolume(s32 vol) {
    if (audio_seq_fade_out_step != 0 || audio_seq_fade_in_step != 0) {
        return 1;
    }
    audio_seq_volume_limit = (vol << 7) + 0x7F;
    alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[0].player, audio_seq_volume_limit);
    alSeqpSetVol((ALSeqPlayer*) &audio_seq_slots[1].player, audio_seq_volume_limit);
    audio_seq_volumes[0] = audio_seq_volume_limit;
    audio_seq_volumes[1] = audio_seq_volume_limit;
    return 0;
}
