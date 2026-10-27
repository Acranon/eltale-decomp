#include "overlays/ending/ending.h"
#include "game/audio/audio.h"
#include "game/core/main.h"
#include "overlays/ending/ending_data.h"

/*
 * Ending overlay: entry and per-frame update, the same scripted sprite engine as the intro,
 * and the scrolling, cross-fading backdrop.
 * Original file: ovl_ending/E22690.c (ROM 0xE22690).
 */



typedef struct {
    u32 key;
    u16 idx;
} UnkSortEntry_8020D98C;





/* ovl_ending .bss 8022BB10..80238660: all of it is this file's (source order). */
s32 ending_clip_left; /* sprite clip left, screen pixels */
s32 ending_clip_top;
s32 ending_clip_width;
s32 ending_clip_height;
u32 ending_elapsed_frames;
s32 ending_sprite_spawn_count;
s32 ending_scene_initialized;
u32 ending_cue_entry_index;
u32 ending_previous_cue_index;
s32 ending_cue_frame; /* current sprite-script frame */
EndingSprite ending_sprite_slots[150];
Gfx ending_display_list_buffers[2][2500];
Gfx* ending_saved_display_ptr;
/* 8023865C..80238660: func_8020C254's static */

/* ovl_ending .data 8020F690..8020F6C0 (8020F6C0.. is E25C80.c's). */
u32 ending_cue_group_index = 0;
s32 ending_wait_for_sprites = 0;
s32 ending_display_buffer_index = 0;


#ifdef NON_MATCHING
/* gSPTextureRectangle with the RDPHALF_2 step word built as ((dsdx & 0xFFFF) << 13) << 3
   (func_8020D98C's flipped texrects) */
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

/* func_8020E9C8's picture table (E25C80.c's D_80210800, 16-byte entries) */
typedef struct {
    void* img;
    void* tlut;
    u32 width;
    s32 unkC;
} UnkPic_80210800;

#endif


void Ending_Init(void) {
    Ending_ClearAllSprites();
    ending_clip_left = 0xA;
    ending_clip_top = 1;
    ending_clip_width = 0x12C;
    ending_clip_height = 0xDF;
    ending_cue_entry_index = 0;
    ending_previous_cue_index = 0;
    ending_elapsed_frames = 0;
    ending_sprite_spawn_count = 0;
    ending_cue_frame = 0;
    ending_cue_group_index = 0;
    ending_wait_for_sprites = 0;
    ending_scene_initialized = 0;
}

s32 Ending_Update(void) {
    s32 idx;
    s32 ret;

    idx = (ending_display_buffer_index + 1) & 1;
    ending_saved_display_ptr = gfx_dl_head;
    gfx_dl_head = ending_display_list_buffers[idx];
    gSPDisplayList(gfx_dl_head++, ending_sprite_setup_dl);
    // D_8020F698 is a function static in the original: IDO does not keep its address
    // in a register. Until D2 moves the data into C, write it through the neighbouring
    // symbol so this extern's address is not CSE'd either.
    (&ending_wait_for_sprites)[1] = idx;
    ret = Ending_RunSpriteScript();
    idx = ending_display_buffer_index;
    gSPEndDisplayList(gfx_dl_head++);
    gfx_dl_head = ending_saved_display_ptr;
    gSPDisplayList(gfx_dl_head++, ending_display_list_buffers[idx]);
    return ret;
}


s32 Ending_RunSpriteScript(void) {
    EndingSpriteCue* entries;
    EndingAnimStep* steps;
    u32 listIdx;
    EndingSprite* obj;
    s32 slot;
    s32 dx;
    s32 dy;
    s32 i;
    u32 j;
    s32 flags;
    static s32 D_8023865C_ovl_ending;

    if (ending_scene_initialized == 0) {
        D_8023865C_ovl_ending = 0;
        ending_elapsed_frames = 0;
        ending_scene_initialized = 1;
    }
    ending_elapsed_frames++;
    D_8023865C_ovl_ending++;
    ending_cue_frame++;
    if ((ending_cue_frame >= ending_cue_groups[ending_cue_group_index].cues[ending_cue_entry_index].start_frame) &&
        (ending_cue_groups[ending_cue_group_index].cues[ending_cue_entry_index].sprite_slot == -1) && (ending_wait_for_sprites == 0)) {
        do {
            slot = Ending_FindFreeSprite();
            if (slot == -1) {
                break;
            }
            entries = ending_cue_groups[ending_cue_group_index].cues;
            entries[ending_cue_entry_index].anim_step_index = 0;
            entries[ending_cue_entry_index].sprite_slot = slot;
            steps = ending_sprite_anim_table[entries[ending_cue_entry_index].anim_index].steps;
            Ending_SpawnSprite(slot, 0x80000000 | entries[ending_cue_entry_index].flags | steps[entries[ending_cue_entry_index].anim_step_index].flags,
                                     entries[ending_cue_entry_index].x, entries[ending_cue_entry_index].y, entries[ending_cue_entry_index].texture_s,
                                     entries[ending_cue_entry_index].texture_t, entries[ending_cue_entry_index].width, entries[ending_cue_entry_index].height,
                                     entries[ending_cue_entry_index].texture_width, entries[ending_cue_entry_index].unk16, entries[ending_cue_entry_index].texture_addr,
                                     entries[ending_cue_entry_index].palette_addr, steps[entries[ending_cue_entry_index].anim_step_index].duration, ending_sprite_spawn_count);
            ending_sprite_spawn_count++;
            if (entries[ending_cue_entry_index].start_frame == 0) {
                entries[ending_cue_entry_index].previous_cue_index = ending_previous_cue_index;
            } else {
                ending_previous_cue_index = ending_cue_entry_index;
            }
            if (steps[entries[ending_cue_entry_index].anim_step_index].flags & 0xC800) {
                if (entries[ending_cue_entry_index].start_frame == 0) {
                    dx = entries[ending_cue_entry_index].x - entries[ending_previous_cue_index].x;
                    dy = entries[ending_cue_entry_index].y - entries[ending_previous_cue_index].y;
                } else {
                    dx = 0;
                    dy = 0;
                }
                Ending_SetMoveTarget(slot, steps[entries[ending_cue_entry_index].anim_step_index].x + dx, steps[entries[ending_cue_entry_index].anim_step_index].y + dy);
            }
            if (steps[entries[ending_cue_entry_index].anim_step_index].flags & 0x1000) {
                Ending_ResetWait(slot);
            }
            if (steps[entries[ending_cue_entry_index].anim_step_index].flags & 0x60000000) {
                Ending_SetClipAnchor(slot);
            }
            ending_cue_entry_index++;
            if (ending_cue_entry_index >= ending_cue_groups[ending_cue_group_index].count) {
                ending_cue_entry_index = 0;
                ending_wait_for_sprites = 1;
                ending_cue_frame = 0;
                break;
            }
            ending_cue_frame = 0;
        } while (entries[ending_cue_entry_index].start_frame == 0);
    }
    Ending_UpdateAndDrawSprites(1);
    if (ending_elapsed_frames >= 0xF78) {
        Ending_UpdateAndDrawScrollingBackdrop(1, 0x4C2);
    }
    Ending_UpdateAndDrawSprites(0);
    for (i = 0, obj = ending_sprite_slots; i < 150; i++, obj++) {
        if (i) {
        }
        if (obj->flags & 0x80000000) {
            j = Ending_FindSpriteScriptEntry(i, &listIdx);
            if (j != -1) {
                flags = obj->flags;
                entries = ending_cue_groups[listIdx].cues;
                steps = ending_sprite_anim_table[entries[j].anim_index].steps;
                if (flags & 0x800000) {
                    flags &= ~0x800000;
                }
                if (!(steps[entries[j].anim_step_index].flags & flags)) {
                    // Fake: an empty use of D_8020F690 here stops IDO keeping its address in a
                    // register for the increment at the end of the function (found by the permuter).
                    if (ending_cue_group_index) {
                    }
                    entries[j].anim_step_index++;
                    if (entries[j].anim_step_index >= ending_sprite_anim_table[entries[j].anim_index].count) {
                        Ending_ClearSprite(i);
                        entries[j].sprite_slot = -1;
                    } else {
                        obj->flags &= ~0x800000;
                        obj->flags |= steps[entries[j].anim_step_index].flags;
                        obj->step_duration = steps[entries[j].anim_step_index].duration;
                        if (steps[entries[j].anim_step_index].flags & 0xC800) {
                            if (entries[j].start_frame == 0) {
                                dx = entries[j].x - entries[(s32)entries[j].previous_cue_index].x;
                                dy = entries[j].y - entries[(s32)entries[j].previous_cue_index].y;
                            } else {
                                dx = 0;
                                dy = 0;
                            }
                            Ending_SetMoveTarget(i, steps[entries[j].anim_step_index].x + dx, steps[entries[j].anim_step_index].y + dy);
                        }
                        if (steps[entries[j].anim_step_index].flags & 0x1000) {
                            Ending_ResetWait(i);
                        }
                        if (steps[entries[j].anim_step_index].flags & 0x60000000) {
                            Ending_SetClipAnchor(i);
                        }
                    }
                }
            }
        }
    }
    if ((Ending_CountActiveSprites() == 0) && (ending_wait_for_sprites != 0)) {
        ending_wait_for_sprites = 0;
        ending_cue_group_index++;
        if (ending_cue_group_index >= ending_cue_group_count) {
            ending_cue_group_index = 0;
            return 0;
        }
    }
    return 1;
}

s32 Ending_FindSpriteScriptEntry(s32 arg0, u32* arg1) {
    u32 i, j;

    for (i = 0; i < ending_cue_group_count; i++) {
        for (j = 0; j < ending_cue_groups[i].count; j++) {
            if (arg0 == ending_cue_groups[i].cues[j].sprite_slot) {
                *arg1 = i;
                return j;
            }
        }
    }

    return -1;
}

void Ending_SpawnSprite(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD) {
    EndingSprite* temp_v0;

    temp_v0 = &ending_sprite_slots[arg0];
    temp_v0->flags = arg1;
    temp_v0->x = arg2;
    temp_v0->y = arg3;
    temp_v0->texture_s = arg4;
    temp_v0->texture_t = arg5;
    temp_v0->width = arg6;
    temp_v0->height = arg7;
    if ((arg1 & 0x04000000) == 0x04000000) {
        temp_v0->texture_width = (arg8 + 0xF) & 0xFFF0;
    } else {
        temp_v0->texture_width = arg8;
    }
    temp_v0->unk12 = arg9;
    temp_v0->palette_addr = argB;
    temp_v0->texture_addr = argA;
    temp_v0->clip_frame = 0;
    temp_v0->fade_value = 0xFF;
    temp_v0->fade_frame = 0;
    temp_v0->move_frame = 0;
    temp_v0->wait_frame = 0;
    temp_v0->clip_frac_x = 0.0f;
    temp_v0->clip_frac_y = 0.0f;
    temp_v0->fade_progress = 0.0f;
    temp_v0->move_frac_x = 0.0f;
    temp_v0->move_frac_y = 0.0f;
    temp_v0->step_duration = argC;
    temp_v0->draw_order = argD;
    temp_v0->clip_anchor_x = temp_v0->clip_anchor_y = 0;
}

void Ending_ClearAllSprites(void) {
    s32 i;
    EndingSprite* temp_v0 = ending_sprite_slots;

    for (i = 0; i < 150; i++, temp_v0++) {
        temp_v0->flags = 0;
        temp_v0->x = 0;
        temp_v0->y = 0;
        temp_v0->texture_s = 0;
        temp_v0->texture_t = 0;
        temp_v0->width = 0;
        temp_v0->height = 0;
        temp_v0->texture_width = 0;
        temp_v0->unk12 = 0;
        temp_v0->palette_addr = 0;
        temp_v0->texture_addr = 0;
        temp_v0->fade_progress = 0.0f;
        temp_v0->fade_value = 0xFF;
        temp_v0->fade_frame = 0;
        temp_v0->move_frac_x = 0.0f;
        temp_v0->move_frac_y = 0.0f;
        temp_v0->move_frame = 0;
        temp_v0->move_target_x = 0;
        temp_v0->move_target_y = 0;
        temp_v0->move_start_x = 0;
        temp_v0->move_start_y = 0;
        temp_v0->wait_frame = 0;
        temp_v0->clip_frac_x = 0.0f;
        temp_v0->clip_frac_y = 1.0f;
        temp_v0->clip_frame = 0;
        temp_v0->step_duration = 0;
        temp_v0->draw_order = 0;
        temp_v0->clip_anchor_x = temp_v0->clip_anchor_y = 0;
    }
}

void Ending_ClearSprite(s32 arg0) {
    EndingSprite* temp_v0;

    temp_v0 = &ending_sprite_slots[arg0];
    temp_v0->flags = 0;
    temp_v0->x = 0;
    temp_v0->y = 0;
    temp_v0->texture_s = 0;
    temp_v0->texture_t = 0;
    temp_v0->width = 0;
    temp_v0->height = 0;
    temp_v0->texture_width = 0;
    temp_v0->unk12 = 0;
    temp_v0->palette_addr = 0;
    temp_v0->texture_addr = 0;
    temp_v0->fade_value = 0xFF;
    temp_v0->fade_frame = 0;
    temp_v0->move_frame = 0;
    temp_v0->move_target_x = 0;
    temp_v0->move_target_y = 0;
    temp_v0->move_start_x = 0;
    temp_v0->move_start_y = 0;
    temp_v0->wait_frame = 0;
    temp_v0->clip_frame = 0;
    temp_v0->step_duration = 0;
    temp_v0->draw_order = 0;
    temp_v0->fade_progress = 0.0f;
    temp_v0->move_frac_x = 0.0f;
    temp_v0->move_frac_y = 0.0f;
    temp_v0->clip_frac_x = 0.0f;
    temp_v0->clip_frac_y = 1.0f;
    temp_v0->clip_anchor_x = temp_v0->clip_anchor_y = 0;
}

s32 Ending_CountFreeSprites(void) {
    s32 count;
    EndingSprite* ptr = ending_sprite_slots;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if ((ptr->flags & 0x80000000) == 0) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

s32 Ending_CountActiveSprites(void) {
    s32 count;
    EndingSprite* ptr = ending_sprite_slots;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if (ptr->flags & 0x80000000) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

s16 Ending_FindFreeSprite(void) {
    EndingSprite* ptr = ending_sprite_slots;
    s32 i = 0;

    while (i < 150) {
        if ((ptr->flags & 0x80000000) == 0) {
            return i;
        }
        i++;
        ptr++;
    }
    return -1;
}

s32 Ending_StepClipGrow(s32 arg0, s32 arg1, EndingRect* arg2) {
    EndingSprite* temp_v1;
    s32 v;
    s32 x;
    s32 y;
    s32 flag;

    temp_v1 = &ending_sprite_slots[arg0];
    // Fake (permuter): a dead read of x here gives v the register retail uses.
    v = x;
    if (!(temp_v1->flags & 0x80000000)) {
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
            // Fake (permuter): a dead read of x here gives v the register retail uses.
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

s32 Ending_StepClipShrink(s32 arg0, s32 arg1, EndingRect* arg2) {
    EndingSprite* temp_v1;
    s32 v;
    s16 x;
    s16 y;
    s32 flag;

    temp_v1 = &ending_sprite_slots[arg0];
    if (!(temp_v1->flags & 0x80000000)) {
        return 0xFF;
    }
    v = arg1 & 0x400;
    flag = v;
    temp_v1->clip_frame++;
    if (flag) {
        x = temp_v1->width;
        temp_v1->clip_frac_x += (f32) x / (f32) temp_v1->step_duration;
        v = x - (s32) temp_v1->clip_frac_x;
        if ((v <= 0) || (temp_v1->clip_frame >= temp_v1->step_duration)) {
            v = 0;
        }
        arg2->x = temp_v1->clip_anchor_x - v;
        arg2->width = v;
    }
    if (!flag) {
        y = temp_v1->height;
        temp_v1->clip_frac_y += (f32) y / (f32) temp_v1->step_duration;
        v = y - (s32) temp_v1->clip_frac_y;
        if ((v <= 0) || (temp_v1->clip_frame >= temp_v1->step_duration)) {
            v = 0;
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

void Ending_SetClipAnchor(s32 arg0) {
    EndingSprite* temp_v0;

    temp_v0 = &ending_sprite_slots[arg0];
    temp_v0->clip_anchor_x = temp_v0->x + temp_v0->width;
    temp_v0->clip_anchor_y = temp_v0->y + temp_v0->height;
}

s32 Ending_StepAlphaFade(s32 arg0, s32 arg1) {
    EndingSprite* temp_v0;
    f32 step;

    temp_v0 = &ending_sprite_slots[arg0];
    if (!(temp_v0->flags & 0x80000000)) {
        return 0;
    }
    temp_v0->fade_frame++;
    step = 255.0f / temp_v0->step_duration;
    temp_v0->fade_progress += step;
    if ((temp_v0->fade_progress >= 255.0f) || (temp_v0->fade_frame >= temp_v0->step_duration)) {
        temp_v0->fade_progress = 255.0f;
    }
    if (arg1 == 0) {
        temp_v0->fade_value = temp_v0->fade_progress;
    } else {
        temp_v0->fade_value = 255.0f - temp_v0->fade_progress;
    }
    if (temp_v0->fade_frame >= temp_v0->step_duration) {
        temp_v0->fade_frame = 0;
        temp_v0->fade_progress = 0.0f;
        if (arg1 == 0) {
            temp_v0->fade_value = 0xFF;
        } else {
            temp_v0->fade_value = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 Ending_StepBrightnessFade(s32 arg0, s32 arg1) {
    EndingSprite* temp_v0;
    f32 step;

    temp_v0 = &ending_sprite_slots[arg0];
    if (!(temp_v0->flags & 0x80000000)) {
        return 0;
    }
    temp_v0->fade_frame++;
    step = 255.0f / temp_v0->step_duration;
    temp_v0->fade_progress += step;
    if ((temp_v0->fade_progress >= 255.0f) || (temp_v0->fade_frame >= temp_v0->step_duration)) {
        temp_v0->fade_progress = 255.0f;
    }
    if (arg1 == 0) {
        temp_v0->fade_value = temp_v0->fade_progress;
    } else {
        temp_v0->fade_value = 255.0f - temp_v0->fade_progress;
    }
    if (temp_v0->fade_frame >= temp_v0->step_duration) {
        temp_v0->fade_frame = 0;
        temp_v0->fade_progress = 0.0f;
        if (arg1 == 0) {
            temp_v0->fade_value = 0xFF;
        } else {
            temp_v0->fade_value = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 Ending_StepMoveXY(s32 arg0, s32 arg1) {
    EndingSprite* temp_v1;
    f32 step;
    s32 dir;
    s32 dx;
    s32 dy;
    s32 deltaX;
    s32 deltaY;

    temp_v1 = &ending_sprite_slots[arg0];
    if (!(arg1 & 0x80000000)) {
        return 0;
    }
    temp_v1->move_frame++;
    step = ((f32) temp_v1->move_target_x - (f32) temp_v1->move_start_x) / (f32) temp_v1->step_duration;
    if (step < 0) {
        step = -step;
    }
    dir = 2;
    temp_v1->move_frac_x += step;
    dx = temp_v1->move_frac_x;
    step = ((f32) temp_v1->move_target_y - (f32) temp_v1->move_start_y) / (f32) temp_v1->step_duration;
    deltaX = dx;
    if (step < 0) {
        step = -step;
    }
    temp_v1->move_frac_y += step;
    dy = temp_v1->move_frac_y;
    deltaY = dy;
    if (temp_v1->x < temp_v1->move_target_x) {
        dir = 1;
    } else {
        deltaX = -dx;
    }
    if (temp_v1->y < temp_v1->move_target_y) {
        dir |= 4;
    } else {
        deltaY = -dy;
        dir |= 8;
    }
    temp_v1->x += deltaX;
    temp_v1->y += deltaY;
    if (temp_v1->move_frac_x >= 1.0f) {
        temp_v1->move_frac_x -= dx;
    }
    if (temp_v1->move_frac_y >= 1.0f) {
        temp_v1->move_frac_y -= dy;
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->x = temp_v1->move_target_x;
        temp_v1->y = temp_v1->move_target_y;
    }
    if (dir & 1) {
        if (temp_v1->x >= temp_v1->move_target_x) {
            temp_v1->x = temp_v1->move_target_x;
        }
    } else if (dir & 2) {
        if (temp_v1->x <= temp_v1->move_target_x) {
            temp_v1->x = temp_v1->move_target_x;
        }
    }
    if (dir & 4) {
        if (temp_v1->y >= temp_v1->move_target_y) {
            temp_v1->y = temp_v1->move_target_y;
        }
    } else if (dir & 8) {
        if (temp_v1->y <= temp_v1->move_target_y) {
            temp_v1->y = temp_v1->move_target_y;
        }
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->move_frame = 0;
        temp_v1->move_frac_x = 0.0f;
        temp_v1->move_frac_y = 0.0f;
        return 0xFF;
    }
    return 0;
}

void Ending_SetMoveTarget(s32 arg0, s32 arg1, s32 arg2) {
    EndingSprite* temp_v0;

    temp_v0 = &ending_sprite_slots[arg0];
    temp_v0->move_target_x = (s16) arg1;
    temp_v0->move_target_y = (s16) arg2;
    temp_v0->move_start_x = temp_v0->x;
    temp_v0->move_start_y = temp_v0->y;
}

s32 Ending_StepMoveX(s32 arg0, s32 arg1) {
    EndingSprite* temp_v1;
    f32 step;
    s32 dir;
    s32 d;
    s32 delta;

    if (!(arg1 & 0x80000000)) {
        return 0xFF;
    }
    temp_v1 = &ending_sprite_slots[arg0];
    temp_v1->move_frame++;
    step = ((f32) temp_v1->move_target_x - (f32) temp_v1->move_start_x) / (f32) temp_v1->step_duration;
    if (step < 0) {
        step = -step;
    }
    temp_v1->move_frac_x += step;
    d = temp_v1->move_frac_x;
    delta = d;
    if (temp_v1->x < temp_v1->move_target_x) {
        dir = 1;
    } else {
        dir = 2;
        delta = -d;
    }
    temp_v1->x += delta;
    if (temp_v1->move_frac_x >= 1.0f) {
        temp_v1->move_frac_x -= d;
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->x = temp_v1->move_target_x;
    }
    if (dir & 1) {
        if (temp_v1->x >= temp_v1->move_target_x) {
            temp_v1->x = temp_v1->move_target_x;
        }
    } else if (dir & 2) {
        if (temp_v1->x <= temp_v1->move_target_x) {
            temp_v1->x = temp_v1->move_target_x;
        }
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->move_frame = 0;
        temp_v1->move_frac_x = 0.0f;
        temp_v1->move_frac_y = 0.0f;
        return 0xFF;
    }
    if (!temp_v1) {
    }
    return 0;
}

s32 Ending_StepMoveY(s32 arg0, s32 arg1) {
    EndingSprite* temp_v1;
    f32 step;
    s32 dir;
    s32 d;
    s32 delta;

    if (!(arg1 & 0x80000000)) {
        return 0xFF;
    }
    temp_v1 = &ending_sprite_slots[arg0];
    temp_v1->move_frame++;
    step = ((f32) temp_v1->move_target_y - (f32) temp_v1->move_start_y) / (f32) temp_v1->step_duration;
    if (step < 0) {
        step = -step;
    }
    temp_v1->move_frac_y += step;
    d = temp_v1->move_frac_y;
    delta = d;
    if (temp_v1->y < temp_v1->move_target_y) {
        dir = 4;
    } else {
        dir = 8;
        delta = -d;
    }
    temp_v1->y += delta;
    if (temp_v1->move_frac_y >= 1.0f) {
        temp_v1->move_frac_y -= d;
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->y = temp_v1->move_target_y;
    }
    if (dir & 4) {
        if (temp_v1->y >= temp_v1->move_target_y) {
            temp_v1->y = temp_v1->move_target_y;
        }
    } else if (dir & 8) {
        if (temp_v1->y <= temp_v1->move_target_y) {
            temp_v1->y = temp_v1->move_target_y;
        }
    }
    if (temp_v1->move_frame >= temp_v1->step_duration) {
        temp_v1->move_frame = 0;
        temp_v1->move_frac_x = 0.0f;
        temp_v1->move_frac_y = 0.0f;
        return 0xFF;
    }
    if (!temp_v1) {
    }
    return 0;
}

s32 Ending_StepWait(s32 arg0) {
    EndingSprite* temp_v0;

    temp_v0 = &ending_sprite_slots[arg0];
    temp_v0->wait_frame += 1;
    if (temp_v0->wait_frame >= temp_v0->step_duration) {
        return 0xFF;
    }
    return 0;
}

void Ending_ResetWait(s32 arg0) {
    ending_sprite_slots[arg0].wait_frame = 0;
}


#ifdef NON_MATCHING
/* 25 words: t4/t9 and t3/t5 swapped in the flipped texrect block (allocation only); code is equivalent */
void Ending_UpdateAndDrawSprites(s32 arg0) {
    s32 i;
    EndingRect rect;
    UnkSortEntry_8020D98C* entry;
    EndingSprite* obj;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 fadeDone;
    s32 j;
    s32 unused1;
    s32 unused2;
    UnkSortEntry_8020D98C list[150];
    UnkSortEntry_8020D98C tmp;
    s32 unused3;
    s32 unused4;

    for (i = 0; i < 150; i++) {
        list[i].idx = i;
        list[i].key = ending_sprite_slots[i].draw_order;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (list[j + 1].key < list[j].key) {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
    gDPSetRenderMode(gfx_dl_head++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(gfx_dl_head++, G_TF_POINT);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    for (entry = list; entry != &list[150]; entry++) {
        idx = entry->idx;
        obj = &ending_sprite_slots[idx];
        fadeDone = 0;
        fade = 0;
        if (!(obj->flags & 0x80000000)) {
            continue;
        }
        if (arg0 == 1) {
            if (!(obj->flags & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0) {
            if (obj->flags & 0x800000) {
                continue;
            }
        }
        flags = obj->flags;
        if ((flags & 0x800) && Ending_StepMoveXY(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && Ending_StepMoveX(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && Ending_StepMoveY(idx, flags)) {
            flags &= ~0x8000;
        }
        rect.x = obj->x;
        rect.y = obj->y;
        rect.s = obj->texture_s;
        rect.t = obj->texture_t;
        rect.width = obj->width;
        rect.height = obj->height;
        rect.sw = obj->width;
        rect.th = obj->height;
        rect.dsdx = 0x400;
        rect.dtdy = 0x400;
        rect.sfrac = rect.s << 5;
        rect.tfrac = rect.t << 5;
        if ((flags & 0x20000000) && Ending_StepClipGrow(idx, flags, &rect)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && Ending_StepClipShrink(idx, flags, &rect)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade = 0x10;
            if (Ending_StepAlphaFade(idx, 0)) {
                flags &= ~0x10;
                fadeDone = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (Ending_StepAlphaFade(idx, 1)) {
                flags &= ~0x20;
                fadeDone = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (Ending_StepBrightnessFade(idx, 0)) {
                flags &= ~0x40;
                fadeDone = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (Ending_StepBrightnessFade(idx, 1)) {
                flags &= ~0x80;
                fadeDone = 1;
            }
        }
        if ((flags & 0x1000) && Ending_StepWait(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (Ending_StepWait(idx)) {
                flags &= ~0x10000000;
            }
            obj->flags = flags;
            continue;
        }
        if ((rect.x < ending_clip_left) && (rect.y < ending_clip_top) && (ending_clip_left + ending_clip_width < rect.x + rect.width) &&
            (ending_clip_top + ending_clip_height < rect.y + rect.height)) {
            obj->flags = flags;
            continue;
        }
        if ((rect.x + rect.width < ending_clip_left) || (rect.y + rect.height < ending_clip_top)) {
            obj->flags = flags;
            continue;
        }
        if ((ending_clip_left + ending_clip_width < rect.x) || (ending_clip_top + ending_clip_height < rect.y)) {
            obj->flags = flags;
            continue;
        }
        {
            if (ending_clip_left + ending_clip_width < rect.x + rect.width) {
                rect.width = ending_clip_left + ending_clip_width - rect.x;
            }
            if (ending_clip_top + ending_clip_height < rect.y + rect.height) {
                rect.height = ending_clip_top + ending_clip_height - rect.y;
            }
            if (rect.x < ending_clip_left) {
                rect.width = rect.width + rect.x - ending_clip_left;
                rect.s = obj->texture_s;
                rect.sfrac = ((ending_clip_left - rect.x) << 5) + rect.sfrac;
                rect.x = ending_clip_left;
            }
            if (obj->y < ending_clip_top) {
                rect.height = rect.height + rect.y - ending_clip_top;
                rect.t = obj->texture_t;
                rect.tfrac = ((ending_clip_top - rect.y) << 5) + rect.tfrac;
                rect.y = ending_clip_top;
            }
            if (fade == 0) {
                rect.prim = 0xFF;
                rect.env = 0xFF;
            } else if (fade & 0x30) {
                rect.prim = 0xFF;
                rect.env = obj->fade_value;
            } else if (fade & 0xC0) {
                rect.prim = obj->fade_value;
                rect.env = 0xFF;
            }
            gDPPipeSync(gfx_dl_head++);
            if ((flags & 0xF0) || fadeDone) {
                gSPDisplayList(gfx_dl_head++, D_8020F748_ovl_ending);
                gDPSetEnvColor(gfx_dl_head++, rect.prim, rect.prim, rect.prim, rect.env);
            } else {
                gSPDisplayList(gfx_dl_head++, D_8020F718_ovl_ending);
            }
            gDPPipeSync(gfx_dl_head++);
            if (obj->flags & 0x0C000000) {
                if (obj->flags & 0x08000000) {
                    gDPLoadTLUT_pal256(gfx_dl_head++, obj->palette_addr);
                    gDPLoadTextureTile(gfx_dl_head++, obj->texture_addr, G_IM_FMT_CI, G_IM_SIZ_8b, obj->texture_width, 0, rect.s, rect.t,
                                       rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (obj->flags & 0x04000000) {
                    gDPLoadTLUT_pal16(gfx_dl_head++, 0, obj->palette_addr);
                    gDPLoadTextureTile_4b(gfx_dl_head++, obj->texture_addr, G_IM_FMT_CI, obj->texture_width, 0, rect.s, rect.t,
                                          rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
                gDPLoadTextureTile(gfx_dl_head++, obj->texture_addr, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->texture_width, 0, rect.s, rect.t,
                                   rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (obj->flags & 0x60000) {
                if (obj->flags & 0x20000) {
                    rect.dsdx = -0x400;
                    GFX_TEXRECT_STEPS(gfx_dl_head++, rect.x << 2, rect.y << 2, (rect.x + rect.width) << 2,
                                        (rect.y + rect.height) << 2, G_TX_RENDERTILE, (rect.s + rect.sw - 1) << 5,
                                        rect.tfrac, rect.dsdx, rect.dtdy);
                } else {
                    rect.dtdy = -0x400;
                    GFX_TEXRECT_STEPS(gfx_dl_head++, rect.x << 2, rect.y << 2, (rect.x + rect.width) << 2,
                                        (rect.y + rect.height) << 2, G_TX_RENDERTILE, rect.sfrac,
                                        (rect.t + rect.th - 1) << 5, rect.dsdx, rect.dtdy);
                }
            } else {
                gSPTextureRectangle(gfx_dl_head++, rect.x << 2, rect.y << 2, (rect.x + rect.width) << 2,
                                    (rect.y + rect.height) << 2, G_TX_RENDERTILE, rect.sfrac, rect.tfrac, rect.dsdx,
                                    rect.dtdy);
            }
            if (fadeDone) {
                obj->fade_value = 0xFF;
            }
        }
        obj->flags = flags;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawSprites.s")
#endif

/* func_8020E9C8's function statics; globals here while it is asm. */
f32 ending_scroll_offset = 32767.0f;
s32 ending_backdrop_frame = 0;
f32 ending_first_fade_alpha = 0.0f;
f32 ending_second_fade_alpha = 0.0f;
u8 D_8020F6AC_ovl_ending = 1;
u8 D_8020F6B0_ovl_ending = 0;
u8 D_8020F6B4_ovl_ending = 0;

#ifdef NON_MATCHING
/* code 0xC70 vs 0xCBC, frame 0x198 vs 0x1A8: arg0/width homes, the B3/B4 hoists and allocation differ; the statics are the module's globals; code is equivalent */
s32 Ending_UpdateAndDrawScrollingBackdrop(s32 arg0, s32 arg1) {
    u32 width;
    f32 alpha;
    f32 delta;
    s32 x;
    s32 y;
    UnkPic_80210800* pic;
    void* img;
    f32 scroll;
    s32 frame;

    if (arg0 == 0) {
        ending_scroll_offset = D_8022BAF0_ovl_ending;
        D_8020F6B4_ovl_ending = 0;
        return 0;
    }
    if (D_8020F6B4_ovl_ending == 2) {
        return 1;
    }
    gDPPipeSync(gfx_dl_head++);
    gDPSetRenderMode(gfx_dl_head++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gfx_dl_head++, D_8020F730_ovl_ending);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    if (ending_backdrop_frame == 0x26AC) {
        D_8020F6AC_ovl_ending = 2;
        D_8020F6B0_ovl_ending = 1;
    } else if (ending_backdrop_frame == D_8022BAF8_ovl_ending) {
        D_8020F6B0_ovl_ending = 2;
        Audio_StartSeqFadeOut(0x1E0);
    }

    switch (D_8020F6AC_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 1.0666667f;
            break;
        case 2:
            delta = -0.7111111f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = ending_first_fade_alpha + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6AC_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6AC_ovl_ending = 0;
    }
    ending_first_fade_alpha = alpha;
    if (ending_backdrop_frame < 0x2814) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &((UnkPic_80210800 *)ending_picture_defs)[arg0];
        width = pic->width;
        img = pic->img;
        gDPLoadTLUT_pal256(gfx_dl_head++, pic->tlut);
        ending_first_fade_alpha = alpha;
        x = (s32) ending_scroll_offset % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(gfx_dl_head++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(gfx_dl_head++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }

    scroll = ending_scroll_offset;
    switch (D_8020F6B0_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 0.7111111f;
            break;
        case 2:
            delta = -0.42666668f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = ending_second_fade_alpha + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6B0_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6B0_ovl_ending = 0;
        if (D_8020F6B4_ovl_ending == 1) {
            D_8020F6B4_ovl_ending = 2;
        }
    }
    ending_second_fade_alpha = alpha;
    if (ending_backdrop_frame >= 0x26AC) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &((UnkPic_80210800 *)ending_picture_defs)[arg0 + 1];
        width = pic->width;
        img = pic->img;
        gDPLoadTLUT_pal256(gfx_dl_head++, pic->tlut);
        ending_second_fade_alpha = alpha;
        x = (s32) scroll % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(gfx_dl_head++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(gfx_dl_head++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }
    frame = ending_backdrop_frame + 1;
    ending_backdrop_frame = frame;
    if ((frame >= 240.0) && (frame < 0x26E8)) {
        ending_scroll_offset = scroll - (f32) width / (f32) arg1;
        return 0;
    }
    if (ending_backdrop_frame == 0x26E8) {
        D_8020F6B4_ovl_ending = 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawScrollingBackdrop.s")
#endif
