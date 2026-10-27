#ifndef OVERLAYS_ENDING_ENDING_H
#define OVERLAYS_ENDING_ENDING_H

#include "common.h"
#include "overlays/ending/ending_data.h"

typedef struct EndingSprite {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[2];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C;
    /* 0x4E */ s16 unk4E;
} EndingSprite; /* 0x50 bytes */

typedef struct EndingRect {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 s;
    /* 0x0C */ s32 t;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 sw;
    /* 0x1C */ s32 th;
    /* 0x20 */ s32 dsdx;
    /* 0x24 */ s32 dtdy;
    /* 0x28 */ s32 sfrac;
    /* 0x2C */ s32 tfrac;
    /* 0x30 */ s32 env;
    /* 0x34 */ s32 prim;
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
extern u8 D_8020F6AC_ovl_ending;
extern u8 D_8020F6B0_ovl_ending;
extern u8 D_8020F6B4_ovl_ending;

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
