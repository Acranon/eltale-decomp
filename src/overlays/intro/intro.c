#include "overlays/intro/intro.h"
#include "game/audio/audio.h"
#include "game/audio/sound.h"
#include "game/core/main.h"
#include "game/event/cutscene.h"
#include "game/input/input.h"
#include "overlays/intro/intro_data.h"
#include "overlays/intro/intro_screens.h"

/*
 * Intro overlay: entry and per-frame update (boot pak check, splashes), and the
 * scripted sprite engine (150 slots with move/clip/fade/wait effects) that plays the intro.
 * Original file: ovl_intro/DC62B0.c (ROM 0xDC62B0).
 */

typedef struct {
    /* 0x00 */ u32 key;
    /* 0x04 */ u16 idx;
} SortEnt; /* size = 0x8 */

#define GFX_WORDS(a, b)                    \
    {                                      \
        Gfx *_g = gfx_dl_head++;            \
        _g->words.w0 = (a);                \
        _g->words.w1 = (b);                \
    }

#ifdef NON_MATCHING
/* gSPTextureRectangle with the RDPHALF_2 step word built as ((dsdx & 0xFFFF) << 13) << 3
   (func_8020E108's flipped texrects) */
#define GFX_TEXRECT_STEPS(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                                       \
    {                                                                                                     \
        Gfx *_g = (Gfx *) (pkt);                                                                          \
                                                                                                          \
        _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(xh, 12, 12) | _SHIFTL(yh, 0, 12));            \
        _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12));                 \
        gImmp1(pkt, G_RDPHALF_1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16)));                               \
        gImmp1(pkt, G_RDPHALF_2,                                                                          \
               (((unsigned int) ((((unsigned int) (dsdx)) & ((0x01 << 16) - 1)) << 13) << 3) |             \
                _SHIFTL(dtdy, 0, 16)));                                                                   \
    }
#endif

/* ovl_intro .data 80212230..80212250 (80212250.. is DC9350.c's): 230, then
   func_8020C16C's statics 234..240. */
s32 intro_phase_timer = 0;

/* ovl_intro .bss 802684B0..80277080 (80277080.. is DC9350.c's). */
s32 intro_clip_left; /* sprite clip left, screen pixels */
s32 intro_clip_top;
s32 intro_clip_width;
s32 intro_clip_height;
s32 intro_elapsed_frames;
s32 intro_sprite_spawn_count;
s32 intro_scene_initialized;
s32 intro_cue_entry_index;
s32 intro_previous_cue_index;
s32 intro_cue_frame; /* current sprite-script frame */
s32 intro_cue_group_index;
s32 intro_wait_for_sprites;
IntroSprite intro_sprite_slots[150];
Gfx intro_display_list_buffers[2][0xBB8];
Gfx *intro_saved_display_ptr;
s32 D_80276F44_ovl_intro;
u8 D_80276F48_ovl_intro[0x12C]; /* not referenced */
s32 intro_fade_alpha;
u8 intro_skip_requested;



typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[0x12];
} Unk80092E48; /* size = 0x14 */


s32 func_8003D554(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D6B0(OSMesgQueue *, OSPfs *, s32);
void func_8003D8EC(char *, ...);

void Intro_Init(void) {
    Intro_ClearAllSprites();
    intro_clip_left = 10;
    intro_clip_top = 1;
    intro_clip_width = 300;
    intro_clip_height = 223;
    intro_cue_entry_index = 0;
    intro_previous_cue_index = 0;
    intro_elapsed_frames = 0;
    intro_sprite_spawn_count = 0;
    intro_cue_frame = 0;
    intro_cue_group_index = 0;
    intro_wait_for_sprites = 0;
    intro_phase_timer = 0;
    intro_splash_fade_alpha = 0;
    intro_scene_initialized = 0;
}

s32 Intro_Update(void) {
    s32 ret;
    s32 err;
    static s32 intro_display_buffer_index = 0;
    static u8 D_80212238_ovl_intro = 0;
    static u8 D_8021223C_ovl_intro = 0;
    static s32 D_80212240_ovl_intro = 1;

    if (input_primary_port == -1) {
        Intro_DrawNoControllerMessage();
        return 2;
    }
    if (intro_pak_check_done == 0) {
        switch (D_80212238_ovl_intro) {
            case 0:
                err = Pak_ClassifyError(Pak_ScanGameFiles(input_primary_port));
                func_8003D8EC("pack_status = %d\n", err);
                if (err != -1 && err != -2 && err != -3) {
                    if (pak_game_file_scans[input_primary_port].flags & 0x2000) {
                        D_80212238_ovl_intro = 1;
                        return 2;
                    }
                    intro_pak_check_done = 1;
                    return 2;
                }
                if (err != -3) {
                    if (func_8003D554(&input_si_queue, &pak_port_states[input_primary_port], input_primary_port) == 0) {
                        D_80212238_ovl_intro = 3;
                        return 2;
                    }
                    if (func_8003D6B0(&input_si_queue, &pak_port_states[input_primary_port], input_primary_port) == 0) {
                        D_80212238_ovl_intro = 3;
                        return 2;
                    }
                    D_80212238_ovl_intro = 2;
                    return 2;
                }
                D_80212238_ovl_intro = 3;
                return 2;
            case 1:
                if (Intro_RunPakFullScreen() != 0) {
                    intro_pak_check_done = 1;
                    return 2;
                }
                break;
            case 2:
                if (Intro_RunNoPakScreen() != 0) {
                    intro_pak_check_done = 1;
                    return 2;
                }
                break;
            case 3:
                if (Intro_RunPakErrorScreen() != 0) {
                    intro_pak_check_done = 1;
                }
                break;
        }
        return 2;
    }
    ret = 2;
    if (intro_first_frame_skipped == 0) {
        intro_first_frame_skipped++;
    } else {
        switch (D_80212240_ovl_intro) {
            case 0:
                Intro_RunSplash1();
                if (intro_phase_timer == 0) {
                    intro_phase_timer = 150;
                    intro_splash_fade_alpha = 0;
                    intro_splash_phase = 0;
                    D_80212240_ovl_intro++;
                }
                break;
            case 1:
                Intro_RunSplash2();
                if (input_pressed_buttons & 0x1000) {
                    Sfx_Enqueue(1, 0xFF, 0x40);
                    intro_phase_timer = 0;
                    D_8021223C_ovl_intro = 1;
                }
                if (intro_phase_timer == 0) {
                    intro_splash_fade_alpha = 0;
                    if (D_8021223C_ovl_intro != 0) {
                        intro_phase_timer = 10;
                        ret = 1;
                    } else {
                        intro_phase_timer = 150;
                        D_80212240_ovl_intro++;
                    }
                    D_8021223C_ovl_intro = 0;
                }
                break;
            case 2:
                Intro_RunSplash3();
                if (input_pressed_buttons & 0x1000) {
                    Sfx_Enqueue(1, 0xFF, 0x40);
                    intro_phase_timer = 0;
                    D_8021223C_ovl_intro = 1;
                }
                if (intro_phase_timer == 0) {
                    intro_splash_fade_alpha = 0;
                    if (D_8021223C_ovl_intro != 0) {
                        intro_phase_timer = 10;
                        ret = 1;
                    } else {
                        intro_phase_timer = 45;
                        D_80212240_ovl_intro++;
                    }
                    D_8021223C_ovl_intro = 0;
                }
                break;
            case 3:
                if (--intro_phase_timer == 0) {
                    D_80212240_ovl_intro++;
                    Bgm_Play(0x1B);
                }
                break;
            case 4:
                D_8006CC74 = 0xFF;
                intro_display_buffer_index = (intro_display_buffer_index + 1) & 1;
                intro_saved_display_ptr = gfx_dl_head;
                gfx_dl_head = intro_display_list_buffers[intro_display_buffer_index];
                gSPDisplayList(gfx_dl_head++, intro_render_setup_dl);
                ret = Intro_RunSpriteScript();
                gSPEndDisplayList(gfx_dl_head);
                gfx_dl_head = intro_saved_display_ptr;
                gSPDisplayList(gfx_dl_head++, intro_display_list_buffers[intro_display_buffer_index]);
                break;
        }
    }
    return ret;
}

#ifdef NON_MATCHING
/* D_80276F44 is the module's global (the original's function static), so its address is kept in a register; v1 spill at sp+0x74 vs 0x70; code is equivalent */
s32 Intro_RunSpriteScript(void) {
    IntroSpriteCue* entries;
    IntroAnimStep* steps;
    u32 listIdx;
    IntroSprite* obj;
    s32 slot;
    s32 dx;
    s32 dy;
    IntroSpriteCue *new_var;
    s32 i;
    s32 j;
    s32 flags;
    Gfx *g;
    if (intro_fade_alpha) {}

    if (intro_scene_initialized == 0) {
        D_80276F44_ovl_intro = 0;
        intro_elapsed_frames = 0;
        intro_skip_requested = 0;
        intro_fade_alpha = 0;
        intro_scene_initialized = 1;
    }
    intro_elapsed_frames++;
    D_80276F44_ovl_intro++;
    intro_cue_frame++;
    if ((intro_cue_frame >= intro_cue_groups[intro_cue_group_index].cues[intro_cue_entry_index].start_frame) &&
        (intro_cue_groups[intro_cue_group_index].cues[intro_cue_entry_index].sprite_slot == -1) && (intro_wait_for_sprites == 0)) {
        do {
            slot = Intro_FindFreeSprite();
            if (slot != -1) {
            entries = intro_cue_groups[intro_cue_group_index].cues;
            entries[intro_cue_entry_index].anim_step_index = 0;
            entries[intro_cue_entry_index].sprite_slot = slot;
            steps = intro_sprite_anim_table[entries[intro_cue_entry_index].anim_index].steps;
            Intro_SpawnSprite(slot, 0x80000000 | entries[intro_cue_entry_index].flags | steps[entries[intro_cue_entry_index].anim_step_index].flags,
                                     entries[intro_cue_entry_index].x, entries[intro_cue_entry_index].y, entries[intro_cue_entry_index].texture_s,
                                     entries[intro_cue_entry_index].texture_t, entries[intro_cue_entry_index].width, entries[intro_cue_entry_index].height,
                                     entries[intro_cue_entry_index].texture_width, entries[intro_cue_entry_index].unk16, entries[intro_cue_entry_index].texture_addr,
                                     entries[intro_cue_entry_index].palette_addr, steps[entries[intro_cue_entry_index].anim_step_index].duration, intro_sprite_spawn_count);
            intro_sprite_spawn_count++;
            if (entries[intro_cue_entry_index].start_frame == 0) {
                entries[intro_cue_entry_index].previous_cue_index = intro_previous_cue_index;
            } else {
                intro_previous_cue_index = intro_cue_entry_index;
            }
            if (steps[entries[intro_cue_entry_index].anim_step_index].flags & 0xC800) {
                if (entries[intro_cue_entry_index].start_frame == 0) {
                    dx = entries[intro_cue_entry_index].x - entries[intro_previous_cue_index].x;
                    dy = entries[intro_cue_entry_index].y - entries[intro_previous_cue_index].y;
                } else {
                    dx = 0;
                    dy = 0;
                }
                Intro_SetMoveTarget(slot, steps[entries[intro_cue_entry_index].anim_step_index].x + dx, steps[entries[intro_cue_entry_index].anim_step_index].y + dy);
            }
            if (steps[entries[intro_cue_entry_index].anim_step_index].flags & 0x1000) {
                Intro_ResetWait(slot);
            }
            if (steps[entries[intro_cue_entry_index].anim_step_index].flags & 0x60000000) {
                Intro_SetClipAnchor(slot);
            }
            intro_cue_entry_index++;
            if (intro_cue_entry_index >= intro_cue_groups[intro_cue_group_index].count) {
                intro_cue_entry_index = 0;
                intro_wait_for_sprites = 1;
                intro_cue_frame = 0;
                break;
            }
            intro_cue_frame = 0;
            } else {
                break;
            }
        } while (entries[intro_cue_entry_index].start_frame == 0);
    }
    if (intro_elapsed_frames == 0x1E00) {
        Audio_StartSeqFadeOut(0x5A);
    }
    Intro_UpdateAndDrawSprites(1);
    Intro_UpdateAndDrawSprites(0);
    for (i = 0, obj = intro_sprite_slots; i < 150; i++, obj++) {
        if (i) {
        }
        if (obj->flags.w & 0x80000000) {
            j = Intro_FindSpriteScriptEntry(i, &listIdx);
            if (j != -1) {
                flags = obj->flags.w;
                entries = intro_cue_groups[listIdx].cues;
                steps = intro_sprite_anim_table[entries[j].anim_index].steps;
                if (flags & 0x800000) {
                    flags &= ~0x800000;
                }
                if (!(steps[entries[j].anim_step_index].flags & flags)) {
                    if (intro_cue_group_index) {
                    }
                    new_var = entries;
                    entries[j].anim_step_index++;
                    if (new_var[j].anim_step_index >= intro_sprite_anim_table[new_var[j].anim_index].count) {
                        Intro_ClearSprite(i);
                        entries[j].sprite_slot = -1;
                    } else {
                        obj->flags.w &= ~0x800000;
                        obj->flags.w |= steps[new_var[j].anim_step_index].flags;
                        obj->step_duration = steps[new_var[j].anim_step_index].duration;
                        if (steps[new_var[j].anim_step_index].flags & 0xC800) {
                            if (new_var[j].start_frame == 0) {
                                dx = new_var[j].x - new_var[new_var[j].previous_cue_index].x;
                                dy = new_var[j].y - new_var[new_var[j].previous_cue_index].y;
                            } else {
                                dx = 0;
                                dy = 0;
                            }
                            Intro_SetMoveTarget(i, steps[new_var[j].anim_step_index].x + dx, steps[new_var[j].anim_step_index].y + dy);
                        }
                        if (steps[new_var[j].anim_step_index].flags & 0x1000) {
                            Intro_ResetWait(i);
                        }
                        if (steps[new_var[j].anim_step_index].flags & 0x60000000) {
                            Intro_SetClipAnchor(i);
                        }
                    }
                }
            }
        }
    }
    if (input_pressed_buttons & 0x1000) {
        intro_skip_requested = 1;
    }
    if (intro_skip_requested != 0) {
        intro_fade_alpha += 10;
        if (intro_fade_alpha >= 0x100) {
            intro_fade_alpha = 0xFF;
        }
        g = gfx_dl_head++; g->words.w0 = _SHIFTL(G_RDPPIPESYNC, 24, 8); g->words.w1 = 0;
        g = gfx_dl_head++; g->words.w0 = (_SHIFTL(G_DL, 24, 8) | _SHIFTL(G_DL_PUSH, 16, 8)); g->words.w1 = (u32)D_802122E0_ovl_intro;
        g = gfx_dl_head++; g->words.w0 = (_SHIFTL(G_SETOTHERMODE_H,24,8) | _SHIFTL(G_MDSFT_TEXTLUT,8,8) | _SHIFTL(2,0,8)); g->words.w1 = G_TT_RGBA16;
        gDPSetRenderMode(gfx_dl_head++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, intro_fade_alpha);
        gDPLoadTLUT_pal256(gfx_dl_head++, D_80217A80_ovl_intro);
        for (i = 0; i < 40; i++) {
            gDPLoadTextureTile(gfx_dl_head++, D_80217C80_ovl_intro, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 6, 0, 0, 319, 5, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, 0, (i * 6) << 2, 320 << 2, (i * 6 + 6) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        if (intro_fade_alpha >= 0xFF) {
            return 1;
        }
    }
    /* Retail sets up no a0 for this call (nop in the delay slot); the callee zeroes n first. */
    if ((Intro_CountActiveSprites(0) == 0) && (intro_wait_for_sprites != 0)) {
        intro_wait_for_sprites = 0;
        intro_cue_group_index++;
        if (intro_cue_group_index >= intro_cue_group_count) {
            intro_cue_group_index = 0;
            return 0;
        }
    }
    return 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/overlays/intro/intro/Intro_RunSpriteScript.s")
#endif

s32 Intro_FindSpriteScriptEntry(s32 id, u32 *outIdx) {
    u32 i;
    u32 j;

    for (i = 0; i < intro_cue_group_count; i++) {
        for (j = 0; j < intro_cue_groups[i].count; j++) {
            if (id == intro_cue_groups[i].cues[j].sprite_slot) {
                *outIdx = i;
                return j;
            }
        }
    }
    return -1;
}

void Intro_SpawnSprite(s16 idx, s32 flags, s16 x, s16 y, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8,
                             s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13) {
    IntroSprite *p = &intro_sprite_slots[idx];

    p->flags.w = flags;
    p->x = x;
    p->y = y;
    p->texture_s = arg4;
    p->texture_t = arg5;
    p->width = arg6;
    p->height = arg7;
    if ((flags & 0x4000000) == 0x4000000) {
        p->texture_width = (arg8 + 15) & 0xFFF0;
    } else {
        p->texture_width = arg8;
    }
    p->unk12 = arg9;
    p->palette_addr = arg11;
    p->texture_addr = arg10;
    p->clip_frame = 0;
    p->fade_value = 0xFF;
    p->fade_frame = 0;
    p->move_frame = 0;
    p->wait_frame = 0;
    p->clip_frac_x = 0.0f;
    p->clip_frac_y = 0.0f;
    p->fade_progress = 0.0f;
    p->move_frac_x = 0.0f;
    p->move_frac_y = 0.0f;
    p->step_duration = arg12;
    p->draw_order = arg13;
    p->clip_anchor_x = p->clip_anchor_y = 0;
}

void Intro_ClearAllSprites(void) {
    s32 i;
    IntroSprite *p = intro_sprite_slots;

    for (i = 0; i < 150; i++, p++) {
        p->flags.w = 0;
        p->x = 0;
        p->y = 0;
        p->texture_s = 0;
        p->texture_t = 0;
        p->width = 0;
        p->height = 0;
        p->texture_width = 0;
        p->unk12 = 0;
        p->palette_addr = 0;
        p->texture_addr = 0;
        p->fade_progress = 0.0f;
        p->fade_value = 0xFF;
        p->fade_frame = 0;
        p->move_frac_x = 0.0f;
        p->move_frac_y = 0.0f;
        p->move_frame = 0;
        p->move_target_x = 0;
        p->move_target_y = 0;
        p->move_start_x = 0;
        p->move_start_y = 0;
        p->clip_anchor_x = p->clip_anchor_y = 0;
        p->wait_frame = 0;
        p->clip_frac_x = 0.0f;
        p->clip_frac_y = 1.0f;
        p->clip_frame = 0;
        p->step_duration = 0;
        p->draw_order = 0;
    }
}

void Intro_ClearSprite(s32 idx) {
    IntroSprite *p = &intro_sprite_slots[idx];

    p->flags.w = 0;
    p->x = 0;
    p->y = 0;
    p->texture_s = 0;
    p->texture_t = 0;
    p->width = 0;
    p->height = 0;
    p->texture_width = 0;
    p->unk12 = 0;
    p->palette_addr = 0;
    p->texture_addr = 0;
    p->fade_progress = 0.0f;
    p->fade_value = 0xFF;
    p->fade_frame = 0;
    p->move_frac_x = 0.0f;
    p->move_frac_y = 0.0f;
    p->move_frame = 0;
    p->move_target_x = 0;
    p->move_target_y = 0;
    p->move_start_x = 0;
    p->move_start_y = 0;
    p->wait_frame = 0;
    p->clip_frac_x = 0.0f;
    p->clip_frac_y = 1.0f;
    p->clip_frame = 0;
    p->step_duration = 0;
    p->draw_order = 0;
    p->clip_anchor_x = p->clip_anchor_y = 0;
}

s32 Intro_CountFreeSprites(s32 n) {
    s32 i;
    IntroSprite *p = intro_sprite_slots;

    n = 0;
    for (i = 0; i < 150; i++, p++) {
        if (!(p->flags.w & 0x80000000)) {
            n++;
        }
    }
    return n;
}

s32 Intro_CountActiveSprites(s32 n) {
    s32 i;
    IntroSprite *p = intro_sprite_slots;

    n = 0;
    for (i = 0; i < 150; i++, p++) {
        if (p->flags.w & 0x80000000) {
            n++;
        }
    }
    return n;
}

s16 Intro_FindFreeSprite(void) {
    s32 i;
    IntroSprite *p = intro_sprite_slots;

    for (i = 0; i < 150; i++, p++) {
        if (!(p->flags.w & 0x80000000)) {
            return i;
        }
    }
    return -1;
}

s32 Intro_StepClipGrow(s32 arg0, s32 arg1, IntroRect* arg2) {
    IntroSprite* temp_v1;
    s32 v = 0;
    s32 x;
    s32 y;
    s32 flag;

    temp_v1 = &intro_sprite_slots[arg0];
    if (!(temp_v1->flags.w & 0x80000000)) {
        return 0xFF;
    }
    x = temp_v1->width;
    y = temp_v1->height;
    flag = arg1 & 0x100;
    temp_v1->clip_frame++;
    if (flag) {
        arg1 = temp_v1->step_duration;
        temp_v1->clip_frac_x += (f32) x / (f32) arg1;
        v = temp_v1->clip_frac_x;
        if ((v >= x) || (temp_v1->clip_frame >= arg1)) {
            v = x;
        }
        arg2->x = temp_v1->clip_anchor_x - v;
        arg2->width = v;
    }
    if (!flag) {
        arg1 = temp_v1->step_duration;
        temp_v1->clip_frac_y += (f32) y / (f32) arg1;
        v = temp_v1->clip_frac_y;
        if ((v >= y) || (temp_v1->clip_frame >= arg1)) {
            v = y;
        }
        arg2->y = temp_v1->clip_anchor_y - v;
        arg2->height = v;
    }
    if (temp_v1->clip_frame >= temp_v1->step_duration) {
        temp_v1->clip_frame = 0;
        temp_v1->clip_anchor_x = 0;
        temp_v1->clip_anchor_y = 0;
        temp_v1->clip_frac_x = 0.0f;
        temp_v1->clip_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 Intro_StepClipShrink(s32 idx, s32 flags, IntroRect *r) {
    IntroSprite *s = &intro_sprite_slots[idx];
    IntroSprite *p;
    s32 v;

    if (!(s->flags.w & 0x80000000)) {
        return 0xFF;
    }
    p = s;
    idx = flags & 0x400;
    p->clip_frame++;
    if (idx) {
        flags = p->width;
        p->clip_frac_x += (f32) flags / p->step_duration;
        v = flags - (s32) p->clip_frac_x;
        if (v <= 0 || p->clip_frame >= p->step_duration) {
            v = 0;
        }
        r->x = p->clip_anchor_x - v;
        r->width = v;
    }
    if (!idx) {
        idx = p->height;
        p->clip_frac_y += (f32) idx / p->step_duration;
        v = idx - (s32) p->clip_frac_y;
        if (v <= 0 || p->clip_frame >= p->step_duration) {
            v = 0;
        }
        r->y = p->clip_anchor_y - v;
        r->height = v;
    }
    if (p->clip_frame >= p->step_duration) {
        p->clip_frame = 0;
        p->clip_anchor_x = 0;
        p->clip_anchor_y = 0;
        p->clip_frac_x = 0.0f;
        p->clip_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

void Intro_SetClipAnchor(s32 idx) {
    IntroSprite *p = &intro_sprite_slots[idx];

    p->clip_anchor_x = p->x + p->width;
    p->clip_anchor_y = p->y + p->height;
}

s32 Intro_StepAlphaFade(s32 idx, s32 arg1) {
    IntroSprite *p = &intro_sprite_slots[idx];
    f32 step;

    if (!(p->flags.w & 0x80000000)) {
        return 0;
    }
    p->fade_frame++;
    step = 255.0f / p->step_duration;
    p->fade_progress += step;
    if (p->fade_progress >= 255.0f || p->fade_frame >= p->step_duration) {
        p->fade_progress = 255.0f;
    }
    if (arg1 == 0) {
        p->fade_value = p->fade_progress;
    } else {
        p->fade_value = 255.0f - p->fade_progress;
    }
    if (p->fade_frame >= p->step_duration) {
        p->fade_frame = 0;
        p->fade_progress = 0.0f;
        if (arg1 == 0) {
            p->fade_value = 0xFF;
        } else {
            p->fade_value = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 Intro_StepBrightnessFade(s32 idx, s32 arg1) {
    IntroSprite *p = &intro_sprite_slots[idx];
    f32 step;

    if (!(p->flags.w & 0x80000000)) {
        return 0;
    }
    p->fade_frame++;
    step = 255.0f / p->step_duration;
    p->fade_progress += step;
    if (p->fade_progress >= 255.0f || p->fade_frame >= p->step_duration) {
        p->fade_progress = 255.0f;
    }
    if (arg1 == 0) {
        p->fade_value = p->fade_progress;
    } else {
        p->fade_value = 255.0f - p->fade_progress;
    }
    if (p->fade_frame >= p->step_duration) {
        p->fade_frame = 0;
        p->fade_progress = 0.0f;
        if (arg1 == 0) {
            p->fade_value = 0xFF;
        } else {
            p->fade_value = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 Intro_StepMoveXY(s32 idx, s32 flags) {
    IntroSprite *p = &intro_sprite_slots[idx];
    f32 step;
    s32 tx;
    s32 ty;
    s32 dx;
    s32 dy;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0;
    }
    p->move_frame++;
    step = ((f32) p->move_target_x - (f32) p->move_start_x) / p->step_duration;
    if (step < 0) {
        step = -step;
    }
    p->move_frac_x += step;
    dir = 2;
    tx = p->move_frac_x;
    step = ((f32) p->move_target_y - (f32) p->move_start_y) / p->step_duration;
    dx = tx;
    if (step < 0) {
        step = -step;
    }
    p->move_frac_y += step;
    ty = p->move_frac_y;
    dy = ty;
    if (p->x < p->move_target_x) {
        dir = 1;
    } else {
        dx = -tx;
    }
    if (p->y < p->move_target_y) {
        dir |= 4;
    } else {
        dy = -ty;
        dir |= 8;
    }
    p->x += dx;
    p->y += dy;
    if (p->move_frac_x >= 1.0f) {
        p->move_frac_x -= tx;
    }
    if (p->move_frac_y >= 1.0f) {
        p->move_frac_y -= ty;
    }
    if (p->move_frame >= p->step_duration) {
        p->x = p->move_target_x;
        p->y = p->move_target_y;
    }
    if (dir & 1) {
        if (p->x >= p->move_target_x) {
            p->x = p->move_target_x;
        }
    } else if (dir & 2) {
        if (p->x <= p->move_target_x) {
            p->x = p->move_target_x;
        }
    }
    if (dir & 4) {
        if (p->y >= p->move_target_y) {
            p->y = p->move_target_y;
        }
    } else if (dir & 8) {
        if (p->y <= p->move_target_y) {
            p->y = p->move_target_y;
        }
    }
    if (p->move_frame >= p->step_duration) {
        p->move_frame = 0;
        p->move_frac_x = 0.0f;
        p->move_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

void Intro_SetMoveTarget(s32 idx, s32 arg1, s32 arg2) {
    IntroSprite *p = &intro_sprite_slots[idx];

    p->move_target_x = arg1;
    p->move_target_y = arg2;
    p->move_start_x = p->x;
    p->move_start_y = p->y;
}

s32 Intro_StepMoveX(s32 idx, s32 flags) {
    IntroSprite *p = &intro_sprite_slots[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->move_frame++;
    step = ((f32) p->move_target_x - (f32) p->move_start_x) / p->step_duration;
    if (step < 0) {
        step = -step;
    }
    p->move_frac_x += step;
    dir = 2;
    t = p->move_frac_x;
    d = t;
    if (p->x < p->move_target_x) {
        dir = 1;
    } else {
        dir = 2;
        d = -t;
    }
    p->x += d;
    if (p->move_frac_x >= 1.0f) {
        p->move_frac_x -= t;
    }
    if (p->move_frame >= p->step_duration) {
        p->x = p->move_target_x;
    }
    if (dir & 1) {
        if (p->x >= p->move_target_x) {
            p->x = p->move_target_x;
        }
    } else if (dir & 2) {
        if (p->x <= p->move_target_x) {
            p->x = p->move_target_x;
        }
    }
    if (p->move_frame >= p->step_duration) {
        p->move_frame = 0;
        p->move_frac_x = 0.0f;
        p->move_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 Intro_StepMoveY(s32 idx, s32 flags) {
    IntroSprite *p = &intro_sprite_slots[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->move_frame++;
    step = ((f32) p->move_target_y - (f32) p->move_start_y) / p->step_duration;
    if (step < 0) {
        step = -step;
    }
    p->move_frac_y += step;
    dir = 8;
    t = p->move_frac_y;
    d = t;
    if (p->y < p->move_target_y) {
        dir = 4;
    } else {
        dir = 8;
        d = -t;
    }
    p->y += d;
    if (p->move_frac_y >= 1.0f) {
        p->move_frac_y -= t;
    }
    if (p->move_frame >= p->step_duration) {
        p->y = p->move_target_y;
    }
    if (dir & 4) {
        if (p->y >= p->move_target_y) {
            p->y = p->move_target_y;
        }
    } else if (dir & 8) {
        if (p->y <= p->move_target_y) {
            p->y = p->move_target_y;
        }
    }
    if (p->move_frame >= p->step_duration) {
        p->move_frame = 0;
        p->move_frac_x = 0.0f;
        p->move_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 Intro_StepWait(s32 idx) {
    IntroSprite *p = &intro_sprite_slots[idx];

    p->wait_frame++;
    if (p->wait_frame >= p->step_duration) {
        return 0xFF;
    }
    return 0;
}

void Intro_ResetWait(s32 idx) {
    intro_sprite_slots[idx].wait_frame = 0;
}

#ifdef NON_MATCHING
/* 23 words: t3/t4 swapped in the flipped texrect block (allocation only); code is equivalent */
void Intro_UpdateAndDrawSprites(s32 arg0) {
    s32 i;
    IntroRect r;
    s32 k;
    IntroSprite *p;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 changed;
    s32 j;
    s32 unused1;
    s32 unused2;
    SortEnt ents[150];
    SortEnt tmp;

    for (i = 0, p = intro_sprite_slots; i < 150; i++, p++) {
        ents[i].idx = i;
        ents[i].key = p->draw_order;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (ents[j + 1].key < ents[j].key) {
                tmp = ents[j];
                ents[j] = ents[j + 1];
                ents[j + 1] = tmp;
            }
        }
    }
    gDPPipeSync(gfx_dl_head++);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPSetTextureFilter(gfx_dl_head++, G_TF_POINT);
    for (k = 0; k < 150; k++) {
        idx = ents[k].idx;
        p = &intro_sprite_slots[idx];
        changed = 0;
        fade = 0;
        if (p->flags.w & 0x80000000) {
        if (arg0 == 1) {
            if (!(p->flags.w & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0 && (p->flags.w & 0x800000)) {
            continue;
        }
        flags = p->flags.w;
        if ((flags & 0x800) && Intro_StepMoveXY(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && Intro_StepMoveX(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && Intro_StepMoveY(idx, flags)) {
            flags &= ~0x8000;
        }
        r.x = p->x;
        r.y = p->y;
        r.s = p->texture_s;
        r.t = p->texture_t;
        r.width = p->width;
        r.height = p->height;
        r.texture_width = p->width;
        r.texture_height = p->height;
        r.dsdx = 0x400;
        r.dtdy = 0x400;
        r.sfrac = r.s << 5;
        r.tfrac = r.t << 5;
        if ((flags & 0x20000000) && Intro_StepClipGrow(idx, flags, &r)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && Intro_StepClipShrink(idx, flags, &r)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade |= 0x10;
            if (Intro_StepAlphaFade(idx, 0)) {
                flags &= ~0x10;
                changed = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (Intro_StepAlphaFade(idx, 1)) {
                flags &= ~0x20;
                changed = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (Intro_StepBrightnessFade(idx, 0)) {
                flags &= ~0x40;
                changed = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (Intro_StepBrightnessFade(idx, 1)) {
                flags &= ~0x80;
                changed = 1;
            }
        }
        if ((flags & 0x1000) && Intro_StepWait(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (Intro_StepWait(idx)) {
                flags &= ~0x10000000;
            }
            p->flags.w = flags;
            continue;
        }
        if (r.x < intro_clip_left && r.y < intro_clip_top && intro_clip_left + intro_clip_width < r.x + r.width &&
            intro_clip_top + intro_clip_height < r.y + r.height) {
            p->flags.w = flags;
            continue;
        }
        if (r.x + r.width < intro_clip_left || r.y + r.height < intro_clip_top) {
            p->flags.w = flags;
            continue;
        }
        if (intro_clip_left + intro_clip_width < r.x || intro_clip_top + intro_clip_height < r.y) {
            p->flags.w = flags;
            continue;
        }
        {
            if (intro_clip_left + intro_clip_width < r.x + r.width) {
                r.width = intro_clip_left + intro_clip_width - r.x;
            }
            if (intro_clip_top + intro_clip_height < r.y + r.height) {
                r.height = intro_clip_top + intro_clip_height - r.y;
            }
            if (r.x < intro_clip_left) {
                r.width = r.width + r.x - intro_clip_left;
                r.s = p->texture_s;
                r.sfrac = ((intro_clip_left - r.x) << 5) + r.sfrac;
                r.x = intro_clip_left;
            }
            if (p->y < intro_clip_top) {
                r.height = r.height + r.y - intro_clip_top;
                r.t = p->texture_t;
                r.tfrac = ((intro_clip_top - r.y) << 5) + r.tfrac;
                r.y = intro_clip_top;
            }
            if (fade == 0) {
                r.prim = 0xFF;
                r.env = 0xFF;
            } else if (fade & 0x30) {
                r.prim = 0xFF;
                r.env = p->fade_value;
            } else if (fade & 0xC0) {
                r.prim = p->fade_value;
                r.env = 0xFF;
            }
            gDPPipeSync(gfx_dl_head++);
            if ((flags & 0xF0) || changed) {
                gSPDisplayList(gfx_dl_head++, D_802122E0_ovl_intro);
                gDPSetEnvColor(gfx_dl_head++, r.prim, r.prim, r.prim, r.env);
            } else {
                gSPDisplayList(gfx_dl_head++, D_802122C8_ovl_intro);
            }
            gDPPipeSync(gfx_dl_head++);
            if (p->flags.w & 0x0C000000) {
                gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
                if (p->flags.w & 0x08000000) {
                    gDPLoadTLUT_pal256(gfx_dl_head++, p->palette_addr);
                    gDPLoadTextureTile(gfx_dl_head++, p->texture_addr, G_IM_FMT_CI, G_IM_SIZ_8b, p->texture_width, 0, r.s, r.t,
                                       r.s + r.texture_width - 1, r.t + r.texture_height - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (p->flags.w & 0x04000000) {
                    gDPLoadTLUT_pal16(gfx_dl_head++, 0, p->palette_addr);
                    gDPLoadTextureTile_4b(gfx_dl_head++, p->texture_addr, G_IM_FMT_CI, p->texture_width, 0, r.s, r.t,
                                          r.s + r.texture_width - 1, r.t + r.texture_height - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
                gDPLoadTextureTile(gfx_dl_head++, p->texture_addr, G_IM_FMT_RGBA, G_IM_SIZ_16b, p->texture_width, 0, r.s, r.t,
                                   r.s + r.texture_width - 1, r.t + r.texture_height - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (p->flags.w & 0x60000) {
                if (p->flags.w & 0x20000) {
                    r.dsdx = -0x400;
                    GFX_TEXRECT_STEPS(gfx_dl_head++, r.x << 2, r.y << 2, (r.x + r.width) << 2,
                                        (r.y + r.height) << 2, G_TX_RENDERTILE, (r.s + r.texture_width - 1) << 5, r.tfrac,
                                        r.dsdx, r.dtdy);
                }
                if (p->flags.w & 0x40000) {
                    r.dtdy = -0x400;
                    GFX_TEXRECT_STEPS(gfx_dl_head++, r.x << 2, r.y << 2, (r.x + r.width) << 2,
                                        (r.y + r.height) << 2, G_TX_RENDERTILE, r.sfrac, (r.t + r.texture_height - 1) << 5,
                                        r.dsdx, r.dtdy);
                }
            } else {
                gSPTextureRectangle(gfx_dl_head++, r.x << 2, r.y << 2, (r.x + r.width) << 2,
                                    (r.y + r.height) << 2, G_TX_RENDERTILE, r.sfrac, r.tfrac, r.dsdx, r.dtdy);
            }
            if (changed) {
                p->fade_value = 0xFF;
            }
        }
        p->flags.w = flags;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/overlays/intro/intro/Intro_UpdateAndDrawSprites.s")
#endif

