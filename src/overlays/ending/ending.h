#ifndef OVERLAYS_ENDING_ENDING_H
#define OVERLAYS_ENDING_ENDING_H

#include "common.h"
#include "overlays/ending/ending_data.h"

typedef struct EndingSprite {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
    /* 0x0C */ s16 texture_s;
    /* 0x0E */ s16 texture_t;
    /* 0x10 */ s16 texture_width;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 palette_addr;
    /* 0x18 */ s32 texture_addr;
    /* 0x1C */ f32 move_frac_x;
    /* 0x20 */ f32 move_frac_y;
    /* 0x24 */ s16 move_frame;
    /* 0x26 */ s16 move_start_x;
    /* 0x28 */ s16 move_start_y;
    /* 0x2A */ s16 move_target_x;
    /* 0x2C */ s16 move_target_y;
    /* 0x2E */ s16 clip_anchor_x;
    /* 0x30 */ s16 clip_anchor_y;
    /* 0x32 */ u16 fade_frame;
    /* 0x34 */ s16 wait_frame;
    /* 0x36 */ char unk36[2];
    /* 0x38 */ s32 step_duration;
    /* 0x3C */ u32 draw_order;
    /* 0x40 */ f32 clip_frac_x;
    /* 0x44 */ f32 clip_frac_y;
    /* 0x48 */ f32 fade_progress;
    /* 0x4C */ u16 clip_frame;
    /* 0x4E */ s16 fade_value;
} EndingSprite; /* 0x50 bytes */

typedef struct EndingRect {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 s;
    /* 0x0C */ s32 t;
    /* 0x10 */ s32 width;
    /* 0x14 */ s32 height;
    /* 0x18 */ s32 sw;
    /* 0x1C */ s32 th;
    /* 0x20 */ s32 dsdx;
    /* 0x24 */ s32 dtdy;
    /* 0x28 */ s32 sfrac;
    /* 0x2C */ s32 tfrac;
    /* 0x30 */ s32 alpha;
    /* 0x34 */ s32 brightness;
} EndingRect; /* 0x38 bytes */

extern s32 ending_clip_left;
extern s32 ending_clip_top;
extern s32 ending_clip_width;
extern s32 ending_clip_height;
extern u32 ending_elapsed_frames;
extern s32 ending_sprite_spawn_count;
extern s32 ending_scene_initialized;
extern u32 ending_cue_entry_index;
extern u32 ending_previous_cue_index;
extern s32 ending_cue_frame;
extern EndingSprite ending_sprite_slots[150];
extern Gfx ending_display_list_buffers[2][2500];
extern Gfx *ending_saved_display_ptr;
extern u32 ending_cue_group_index;
extern s32 ending_wait_for_sprites;
extern s32 ending_display_buffer_index;
extern f32 ending_scroll_offset;
extern s32 ending_backdrop_frame;
extern f32 ending_first_fade_alpha;
extern f32 ending_second_fade_alpha;
extern u8 ending_first_backdrop_fade_mode;
extern u8 ending_second_backdrop_fade_mode;
extern u8 ending_backdrop_completion_state;

void Ending_Init(void);
s32 Ending_Update(void);
s32 Ending_RunSpriteScript(void);
s32 Ending_FindSpriteScriptEntry(s32 arg0, u32* arg1);
void Ending_SpawnSprite(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD);
void Ending_ClearAllSprites(void);
void Ending_ClearSprite(s32 arg0);
s32 Ending_CountFreeSprites(void);
s32 Ending_CountActiveSprites(void);
s16 Ending_FindFreeSprite(void);
s32 Ending_StepClipGrow(s32 arg0, s32 arg1, EndingRect* arg2);
s32 Ending_StepClipShrink(s32 arg0, s32 arg1, EndingRect* arg2);
void Ending_SetClipAnchor(s32 arg0);
s32 Ending_StepAlphaFade(s32 arg0, s32 arg1);
s32 Ending_StepBrightnessFade(s32 arg0, s32 arg1);
s32 Ending_StepMoveXY(s32 arg0, s32 arg1);
void Ending_SetMoveTarget(s32 arg0, s32 arg1, s32 arg2);
s32 Ending_StepMoveX(s32 arg0, s32 arg1);
s32 Ending_StepMoveY(s32 arg0, s32 arg1);
s32 Ending_StepWait(s32 arg0);
void Ending_ResetWait(s32 arg0);
void Ending_UpdateAndDrawSprites(s32 arg0);
s32 Ending_UpdateAndDrawScrollingBackdrop(s32 arg0, s32 arg1);

#endif
