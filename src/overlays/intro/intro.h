#ifndef OVERLAYS_INTRO_INTRO_H
#define OVERLAYS_INTRO_INTRO_H

#include "common.h"
#include "overlays/intro/intro_data.h"

typedef struct IntroSpriteFlags {
    /* 0x00 */ s32 active : 1;
    /* 0x00 */ u32 flags : 31;
} IntroSpriteFlags; /* 0x4 bytes */

typedef union IntroSpriteFlagWord {
    /* 0x00 */ IntroSpriteFlags b;
    /* 0x00 */ s32 w;
} IntroSpriteFlagWord; /* 0x4 bytes */

typedef struct IntroSprite {
    /* 0x00 */ IntroSpriteFlagWord unk0;
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
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C;
    /* 0x4E */ s16 unk4E;
} IntroSprite; /* size = 0x50 */





typedef struct IntroRect {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} IntroRect; /* size = 0x38 */

extern s32 intro_phase_timer;
extern s32 intro_clip_left;
extern s32 intro_clip_top;
extern s32 intro_clip_width;
extern s32 intro_clip_height;
extern s32 intro_elapsed_frames;
extern s32 intro_sprite_spawn_count;
extern s32 intro_scene_initialized;
extern s32 intro_cue_entry_index;
extern s32 intro_previous_cue_index;
extern s32 intro_cue_frame;
extern s32 intro_cue_group_index;
extern s32 intro_wait_for_sprites;
extern IntroSprite intro_sprite_slots[150];
extern Gfx intro_display_list_buffers[2][0xBB8];
extern Gfx *intro_saved_display_ptr;
extern s32 D_80276F44_ovl_intro;
extern u8 D_80276F48_ovl_intro[0x12C];
extern s32 intro_fade_alpha;
extern u8 intro_skip_requested;

void Intro_Init(void);
s32 Intro_Update(void);
s32 Intro_RunSpriteScript(void);
s32 Intro_FindSpriteScriptEntry(s32 id, u32 *outIdx);
void Intro_ClearAllSprites(void);
void Intro_ClearSprite(s32 idx);
s32 Intro_CountFreeSprites(s32 n);
#ifdef NON_MATCHING
/* The draft call has no argument; the callee overwrites n before reading it. H2 fixes the call. */
s32 Intro_CountActiveSprites();
#else
s32 Intro_CountActiveSprites(s32 n);
#endif
s16 Intro_FindFreeSprite(void);
s32 Intro_StepClipGrow(s32 arg0, s32 arg1, IntroRect* arg2);
s32 Intro_StepClipShrink(s32 idx, s32 flags, IntroRect *r);
void Intro_SetClipAnchor(s32 idx);
s32 Intro_StepAlphaFade(s32 idx, s32 arg1);
s32 Intro_StepBrightnessFade(s32 idx, s32 arg1);
s32 Intro_StepMoveXY(s32 idx, s32 flags);
void Intro_SetMoveTarget(s32 idx, s32 arg1, s32 arg2);
s32 Intro_StepMoveX(s32 idx, s32 flags);
s32 Intro_StepMoveY(s32 idx, s32 flags);
s32 Intro_StepWait(s32 idx);
void Intro_ResetWait(s32 idx);
void Intro_UpdateAndDrawSprites(s32 arg0);
void Intro_SpawnSprite(s16 idx, s32 flags, s16 x, s16 y, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13);

#endif
