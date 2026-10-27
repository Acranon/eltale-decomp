#ifndef OVERLAYS_ENDING_ENDING_DATA_H
#define OVERLAYS_ENDING_ENDING_DATA_H

#include "common.h"

typedef struct EndingAnimStep {
    /* 0x00 */ u32 flags;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s32 duration;
} EndingAnimStep; /* 0xC bytes */

typedef struct EndingAnim {
    /* 0x00 */ EndingAnimStep* steps;
    /* 0x04 */ u32 count;
} EndingAnim; /* 0x8 bytes */

typedef struct EndingSpriteCue {
    /* 0x00 */ u16 anim_index;
    /* 0x02 */ s16 start_frame;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ s16 width;
    /* 0x0E */ s16 height;
    /* 0x10 */ s16 texture_s;
    /* 0x12 */ s16 texture_t;
    /* 0x14 */ s16 texture_width;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 texture_addr;
    /* 0x1C */ s32 palette_addr;
    /* 0x20 */ s16 anim_step_index;
    /* 0x22 */ s16 sprite_slot;
    /* 0x24 */ u16 previous_cue_index;
    /* 0x26 */ char unk26[2];
} EndingSpriteCue; /* 0x28 bytes */

typedef struct EndingCueGroup {
    /* 0x00 */ EndingSpriteCue* cues;
    /* 0x04 */ u32 count;
} EndingCueGroup; /* 0x8 bytes */

extern Gfx ending_sprite_setup_dl[11];
extern Gfx ending_sprite_default_combine_dl[3];
extern Gfx ending_scroll_backdrop_combine_dl[3];
extern Gfx ending_sprite_fade_combine_dl[3];
extern EndingAnimStep ending_sprite_anim_steps_0[3];
extern EndingAnimStep ending_sprite_anim_steps_1[3];
extern EndingAnimStep ending_sprite_anim_steps_2[4];
extern EndingAnimStep ending_sprite_anim_steps_3[3];
extern EndingAnimStep ending_sprite_anim_steps_4[3];
extern EndingAnimStep ending_sprite_anim_steps_5[3];
extern EndingAnimStep ending_sprite_anim_steps_6[3];
extern EndingAnimStep ending_sprite_anim_steps_7[2];
extern EndingAnim ending_sprite_anim_table[8];
extern EndingSpriteCue ending_sprite_cues[97];
extern Gfx D_802107E8_ovl_ending[1];
extern EndingCueGroup ending_cue_groups[1];
extern u32 ending_cue_group_count;
extern u32 D_802107FC_ovl_ending[1];
extern u32 ending_picture_defs[4];
extern u16 ending_scroll_backdrop_first_tlut[0x100];
extern u8 ending_scroll_backdrop_tex[0x10A00];
extern u16 ending_scroll_backdrop_second_tlut[0x100];
extern Gfx D_80221610_ovl_ending[1];
extern u8 D_80221618_ovl_ending[0xA4B0];
extern Gfx D_8022BAC8_ovl_ending[1];
extern u16 D_8022BAD0_ovl_ending[0x10];
extern f32 D_8022BAF0_ovl_ending;
extern f64 D_8022BAF8_ovl_ending;

#endif
