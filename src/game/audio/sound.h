#ifndef GAME_AUDIO_SOUND_H
#define GAME_AUDIO_SOUND_H

#include "common.h"

/* A delayed sound effect (Sfx_Play with a delay): frames_left, sound_id,
 * volume; Bgm_Update enqueues it when the delay runs out. */
typedef struct SfxDelayed {
    /* 0x00 */ u8 frames_left;
    /* 0x01 */ s8 sound_id;
    /* 0x02 */ u8 volume;
} SfxDelayed; /* 0x3 bytes */

/* bgm_map_table: map_id and subarea_id (-1 = any) play sequence_id (-1 = none). */
typedef struct BgmMapEntry {
    /* 0x00 */ s16 map_id;
    /* 0x02 */ s16 subarea_id;
    /* 0x04 */ s8 sequence_id;
} BgmMapEntry; /* 0x6 bytes */

/* .bss 8008FAF0..8008FB30, in address order (the order of these declarations fixes it). */
extern s8 bgm_current;
extern s8 bgm_next;
extern u16 bgm_flags;
extern u8 sfx_master_volume;
extern u16 bgm_change_delay;
extern SfxDelayed sfx_delayed[16];

/* .data */
extern BgmMapEntry bgm_map_table[72];
extern u8 bgm_volume_levels[8];
extern u8 sfx_volumes[72];

void Bgm_Init(void);
void Bgm_Update(void);
void Bgm_Play(s8 bgm);
void Bgm_PlayDelayed(s8 bgm, u16 delay);
void Bgm_PlayForMap(s32 arg0, s32 arg1, u16 delay);
void Sfx_Play(u8 arg0, s8 arg1, u8 arg2);
void Sfx_PlayIfAudible(s8 arg0, u8 arg1);
void Bgm_ApplyVolumeOption(void);

#endif
