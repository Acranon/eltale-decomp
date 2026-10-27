#ifndef GAME_AUDIO_AUDIO_H
#define GAME_AUDIO_AUDIO_H

#include "common.h"

struct NNSched;

/* Sample DMA cache (the libultra audio sample's DMA buffer list). */
typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ s32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer; /* 0x14 bytes */

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState; /* 0xC bytes */

/* One compact-sequence player with its sequence buffer. */
typedef struct SeqSlot {
    /* 0x000 */ ALSeqpConfig config;
    /* 0x01C */ ALCSPlayer player;
    /* 0x098 */ ALCSeq seq;
    /* 0x190 */ u8* seqData;
    /* 0x194 */ s32 seqNo;
    /* 0x198 */ s32 unk198;
} SeqSlot; /* 0x19C bytes */

/* .bss 8008CEC0..8008FAF0, in address order (the order of these declarations fixes it). */
extern OSThread audio_thread;
extern u64 audio_thread_stack[0x2000 / 8];
extern ALHeap audio_heap;
extern Acmd* audio_cmd_lists[2];
extern void* D_8008F088[2];
extern s16* audio_output_buffers[3];
extern OSMesgQueue audio_dma_queue;
extern OSMesgQueue audio_rom_read_queue;
extern OSMesg audio_dma_mesg;
extern OSMesg audio_rom_read_mesg;
extern OSIoMesg audio_dma_io_mesgs[32];
extern ALGlobals audio_globals;
extern ALSynConfig audio_syn_config;
extern ALSndPlayer audio_sound_player;
extern ALSndpConfig audio_sound_player_config;
extern ALInstrument* audio_sound_inst;
extern ALBank* audio_sound_bank;
extern s16* audio_sound_ids;
extern s32 D_8008F4C0;
extern AMDMAState audio_dma_state;
extern AMDMABuffer audio_dma_buffers[32];
extern s32 D_8008F758;
extern s32* sfx_script_pos;
extern s32* sfx_script_loop_pos;
extern s32 sfx_cur_channel;
extern u32 sfx_channel_volume_word[5];
extern s32* sfx_ch0_script_pos;
extern s32* sfx_ch1_script_pos;
extern s32* sfx_ch2_script_pos;
extern s32* sfx_ch3_script_pos;
extern s32* sfx_ch4_script_pos;
extern s32* sfx_ch0_loop_pos;
extern s32* sfx_ch1_loop_pos;
extern s32* sfx_ch2_loop_pos;
extern s32* sfx_ch3_loop_pos;
extern s32* sfx_ch4_loop_pos;
extern SeqSlot audio_seq_slots[2];
extern s32 D_8008FAE0;
extern s32 D_8008FAE4;

/* .data */
extern f32 sfx_pitch_table[73];
extern s32 sfx_script_data[0x6084 / 4];
extern ALBankFile* audio_seq_bank_file;
extern ALBankFile* audio_sound_bank_file;
extern ALSeqFile* audio_seq_file;
extern s32 audio_dma_count;
extern u32 audio_frame_count;
extern u32 sfx_queue_ids[8];
extern s32 sfx_queue_volumes[8];
extern s32 sfx_queue_pans[8];
extern s32 sfx_queue_read;
extern s32 sfx_queue_write;
extern s32 audio_seq_volume_limit;
extern s32 audio_active_seq_slot;
extern s32 audio_pending_seq_request;
extern s32 audio_loaded_seq;
extern s32 audio_seq_volumes[2];
extern s32 audio_seq_fade_out_step;
extern s32 audio_seq_fade_in_step;
extern s32 sfx_channel_sound[5];
extern s32 sfx_channel_timer[5];
extern s32 sfx_channel_volume_factor[5];
extern s32 sfx_channel_pan[5];
extern s32* sfx_scripts[];

void Audio_DmaReadRom(u32 devAddr, void* vAddr, s32 nbytes);
void Audio_Init(void);
s32 Audio_DmaCallback(s32 addr, s32 len, void* state);
ALDMAproc Audio_DmaNew(AMDMAState** state);
void Audio_FreeOldDmaBuffers(void);
void Audio_ThreadMain(void* arg);
void Audio_LoadSeqFileHeader(u32 devAddr);
void Audio_StartThread(struct NNSched* sc);
void Audio_InitSeqPlayers(u8* bankStart, u8* bankEnd, u8* seqFile, u8* seqFileEnd, u8* table);
void Audio_LoadSeq(s32 slot, s32 seqNo);
s32 Audio_PlaySeq(s32 slot);
void Audio_StopSeq(s32 slot);
s32 Audio_GetSeqState(s32 slot);
void Audio_InitSoundPlayer(u8* start, u8* end, u8* table);
void Audio_PlaySound(s32 id);
void Audio_StopSound(s32 id);
void Audio_GetSoundState(s32 id);
void Audio_UpdateFrame(void);
void Sfx_SelectScript(s32 arg0);
s32 func_80029834(s32 arg0);
void Audio_StartSeqRequest(s32 arg0);
void Sfx_EnqueueDefault(s32 arg0);
void Sfx_Enqueue(s32 arg0, s32 arg1, s32 arg2);
void Sfx_ProcessQueue(void);
void Sfx_StepScript(void);
void Audio_StepSeqFadeOut(void);
void Audio_StepSeqFadeIn(void);
s32 Audio_LoadSeqsOrStop(s32 seqNo);
s32 Audio_StartSeqFadeOut(u32 frames);
void Sfx_StopAllChannels(void);
void Sfx_StopChannel4(void);
s32 Audio_SetSeqVolume(s32 vol);

#endif
