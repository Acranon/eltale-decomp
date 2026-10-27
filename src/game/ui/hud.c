#include "game/ui/hud.h"
#include "game/camera/camera.h"
#include "game/gfx/effect.h"
#include "game/audio/sound.h"
#include "game/battle/battle.h"
#include "game/core/dma.h"
#include "game/enemy/enemy.h"
#include "game/input/input.h"
#include "game/magic/magic.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/npc/npc.h"
#include "game/player/player.h"
#include "game/ui/menu.h"
#include "game/core/main.h"

/*
 * In-game HUD: meters, compass, spell input, status indicators, and text primitives.
 * Original file: 216E0.c (ROM 0x216E0).
 */






/* This file's .bss, 8008C040..8008C190, in address order (first declaration fixes
 * the order). D_8008C164 is used only by 12610. */
u16 hud_npc_marker_phase;
u16 hud_element_allocation_flags;
s32 hud_clip_left; /* HUD clip bound, screen pixels */
s32 hud_clip_top;
s32 hud_clip_right;
u16 hud_spirit_marker_phase;
s32 hud_clip_bottom;
HudPopup hud_popup_slots[8];
u32 hud_element_gain_flash_timer;
u32 hud_selected_element_index;
Vec3f hud_temp_vec;
u16 hud_chest_text_marker_phases[2];
u16 hud_melee_marker_phase;
u16 hud_panel_transition_frame;
u16 hud_panel_transition_state;
u16 hud_hp_meter_width;
u16 hud_mp_meter_width;
u16 hud_spell_input_anim_timer;
u16 hud_spell_input_anim_flags;
u16 hud_spell_name_timer;
u16 hud_element_input_timer; /* eight-frame element input/fade timer */
u16 hud_enemy_info_timer;
s32 D_8008C164;
s32 D_8008C168;
s32 D_8008C16C;
s32 audio_pending_seq_id;
s32 hud_draw_origin_x;
s32 hud_draw_origin_y;
s32 hud_npc_marker_screen_y;
u16 hud_element_pulse_phase;
extern u8** D_800C03D8[];





extern Gfx D_803AA448[];
extern Gfx D_803AA4C0[];
extern Gfx D_803AA538[];

s16 sins(u16);


extern u8 D_803A4118[];
extern u8 D_803A8728[];
extern u8* D_803A8778[];
extern HudTextureDesc D_803A8748;



typedef struct {
    /* 0x00 */ u16 status_bits;
    /* 0x02 */ char unk2[0x12 - 0x2];
    /* 0x12 */ u8 status_icon_ids[0x10];
    /* 0x22 */ s8 status_icon_timers[0x10];
    /* 0x32 */ s8 status_effect_timers[0x12];
    /* 0x44 */ s32 status_effect_handles[4];
    /* 0x54 */ char unk54[0x94 - 0x54];
    /* 0x94 */ f32 unk94;
} Struct_8002373C_68; /* view of ActorBattle opaque status/icon fields */


typedef struct {
    /* 0x0 */ s16 visual_def_index;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x8 */ f32 scale_x;
    /* 0xC */ f32 scale_y;
} Struct_803AA6C4;

extern MagicVisualDef D_803AA690[];
extern Struct_803AA6C4 D_803AA6C4[];


void Hud_ResetState(void) {
    D_8008C168 = 0;
    D_8008C16C = 0;
    audio_pending_seq_id = -1;
    hud_draw_origin_y = 0;
    hud_draw_origin_x = hud_draw_origin_y;
    hud_clip_top = 0;
    hud_clip_left = hud_clip_top;
    hud_clip_right = 0x140;
    hud_clip_bottom = 0xF0;
    hud_enemy_info_timer = 0;
    hud_spell_name_timer = 0;
    hud_spell_input_anim_flags = 0;
    hud_spell_input_anim_timer = hud_spell_input_anim_flags;
    hud_element_gain_flash_timer = 0;
    hud_element_allocation_flags = 0;
}





extern Gfx D_803A8788[];

struct Struct_80021030;
struct Struct_80021C04;
struct Struct_80022970;

void Hud_Draw(GfxFrameData* buf) {
    s32 n;
    Enemy* e;

    gSPMatrix(gfx_dl_head++, &D_2000000.ortho, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guTranslate(&buf->mtx[gfx_mtx_index], -160.0f, -120.0f, 0.0f);
    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    hud_clip_right = 0x140;
    hud_clip_bottom = 0xF0;
    gSPDisplayList(gfx_dl_head++, D_803A8788);
    if ((core_flags & 2) && hud_panel_transition_state != 1) {
        hud_panel_transition_state = 1;
    } else if (!(core_flags & 2) && hud_panel_transition_state == 1) {
        hud_panel_transition_state = 2;
    }
    if (!(core_flags & 0xC00)) {
        Hud_DrawPlayerMeters((Actor*)&player_state.actor);
        Hud_DrawElementLevels(buf, (s32)player_state.stats);
        if (hud_panel_transition_state == 1) {
            if (++hud_panel_transition_frame >= 13) {
                hud_panel_transition_frame = 12;
            }
        } else if (hud_panel_transition_state == 2) {
            if (--hud_panel_transition_frame == 0) {
                hud_panel_transition_state = 0;
            }
        }
    }
    if ((map_flags & 0xD) && !(battle_flags & 1) && !(map_subarea_def->flags & 8) && !(core_flags & 2)) {
        Hud_DrawCompass(buf);
    }
    if ((battle_flags & 1) && hud_enemy_info_timer) {
        Hud_DrawEnemyInfoPanel();
        hud_enemy_info_timer--;
    }
    hud_draw_origin_x = hud_draw_origin_y = 0;
    if (battle_flags & 1) {
        Hud_DrawPopups();
        if (!(battle_flags & 2) && player_state.melee_target_plus_one && !(player_state.actor.animFlags & 1) && !(magic_cast_state & 1)) {
            Hud_DrawMeleeTargetMarker(player_state.melee_target_plus_one - 1);
        }
        if ((player_state.flags & 0x20) && !(core_flags & 0x800)) {
            Hud_DrawOutOfRangeIcon();
        }
        Hud_UpdateAndDrawActorStatusIndicators((Actor*)&player_state.actor);
        n = enemy_count;
        e = enemy_slots;
        while (n != 0) {
            if (e->actor.animSetIndex != -1) {
                Hud_UpdateAndDrawActorStatusIndicators(&e->actor);
                n--;
            }
            e++;
        }
    } else if (!(core_flags & 0x87) && !(player_state.actor.animFlags & 1)) {
        if (player_talk_npc) {
            Hud_DrawNpcTalkMarker();
        } else if (player_front_spirit && !(core_flags & 8)) {
            Hud_DrawSpiritMarker();
        } else if (player_front_chest) {
            Hud_DrawChestMarker();
        } else if (player_front_text_spot) {
            Hud_DrawTextSpotMarker();
        }
    }
    if (core_flags & 4) {
        Hud_DrawSpellInput(buf, (Player*)&player_state);
    } else if (core_flags & 8) {
        Hud_UpdateElementAllocation(buf, (Player*)&player_state);
    }
    if (hud_spell_name_timer) {
        Hud_DrawSpellName(&player_state);
        hud_spell_name_timer--;
    }
}



extern HudTextureDesc D_803A86F8;

void Hud_DrawPlayerMeters(Actor* arg0) {
    ActorStats* st;
    s32 w;
    s32 d;

    hud_draw_origin_x = 0x1C;
    hud_draw_origin_y = 0x18;
    if (hud_panel_transition_state != 0) {
        w = hud_panel_transition_frame * hud_panel_transition_frame;
        hud_draw_origin_x -= w * 150 / 144;
    }
    st = arg0->stats;
    Hud_DrawTextureTile(&D_803A86F8, 0, 1, 0x3E, 0x11, 0x20, 0x27, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A86F8, 0, 0x12, 0x3E, 0x12, 0x20, 0x38, 0x400, 0x400);
    w = st->hp * 56 / st->max_hp;
    d = w - hud_hp_meter_width;
    if (d >= 2 || d < -1) {
        hud_hp_meter_width += d >> 1;
    } else {
        hud_hp_meter_width = w;
    }
    if (hud_hp_meter_width) {
        Hud_DrawTextureTile(&D_803A86F8, 3, 0xB, hud_hp_meter_width, 5, 0x5E, 0x27, 0x400, 0x400);
    }
    w = st->mp * 56 / st->max_mp;
    d = w - hud_mp_meter_width;
    if (d >= 2 || d < -1) {
        hud_mp_meter_width += d >> 1;
    } else {
        hud_mp_meter_width = w;
    }
    if (hud_mp_meter_width) {
        Hud_DrawTextureTile(&D_803A86F8, 3, 0x15, hud_mp_meter_width, 5, 0x5E, 0x2C, 0x400, 0x400);
    }
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    Hud_DrawNumber(3, 0xC, 0, st->hp);
    Hud_DrawNumber(1, 0x36, 0, st->max_hp);
    Hud_DrawNumber(3, 0xC, 0x1B, st->mp);
    Hud_DrawNumber(1, 0x36, 0x1B, st->max_mp);
    Hud_DrawClippedTextureRect(0x2F, 0, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
    Hud_DrawClippedTextureRect(0x2F, 0x1B, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
}

extern Gfx D_803AA3C8[];
extern Gfx D_803AA2F8[];

void Hud_DrawElementLevels(GfxFrameData* buf, s32 arg1) {
    s32 x;
    f32 fx;
    f32 fy;
    s32 i;
    u8* p;
    u8* col;
    u16 *angle = &hud_element_pulse_phase;

    hud_draw_origin_x = 0x1C;
    hud_draw_origin_y = 0xC6;
    if (hud_panel_transition_state != 0) {
        i = hud_panel_transition_frame * hud_panel_transition_frame;
        hud_draw_origin_x -= i * 200 / 144;
    }
    Hud_DrawTextureTile(&D_803A86F8, 0, 0, 0xC, 0xC, 0x20, 0x10, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A86F8, 0x16, 0, 0xC, 0xC, 0x2C, 0x10, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A86F8, 0x2C, 0, 0xC, 0xC, 0x38, 0x10, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A86F8, 0x42, 0, 0xC, 0xC, 0x44, 0x10, 0x400, 0x400);
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    x = 6;
    for (i = 0, p = (u8*)arg1; i < 4; i++) {
        Hud_DrawNumber(1, x, 6, p[0x24]);
        p++;
        x += 0x16;
    }
    for (i = 0; i < 4; i++) {
        if (player_state.flags & hud_element_max_level_masks[i]) {
            col = &hud_element_colors[0][i];
            fx = i * 22.0f + 5.0 + (f32)hud_draw_origin_x;
            fy = hud_draw_origin_y + 5.0f;
            guTranslate(&buf->mtx[gfx_mtx_index], fx, fy, 0.0f);
            gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gDPPipeSync(gfx_dl_head++);
            gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], (sins(*angle) >> 10) + 0x88);
            gSPDisplayList(gfx_dl_head++, D_803AA3C8);
        }
    }
    *angle += 0x444;
    if (hud_element_gain_flash_timer) {
        col = hud_element_colors[hud_selected_element_index];
        fx = hud_selected_element_index * 22.0f + 5.0 + (f32)hud_draw_origin_x;
            fy = hud_draw_origin_y + 5.0f;
            guTranslate(&buf->mtx[gfx_mtx_index], fx, fy, 0.0f);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(gfx_dl_head++);
        gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], hud_element_gain_flash_timer * 255 / 30);
        gSPDisplayList(gfx_dl_head++, D_803AA2F8);
        hud_element_gain_flash_timer--;
    }
}


extern Gfx D_803AA758[];
extern HudTextureDesc D_803A86F8;
f32 sqrtf(f32);

void Hud_DrawCompass(GfxFrameData* buf) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ang;
    MtxF mf;

    hud_draw_origin_x = 0x104;
    hud_draw_origin_y = 0x18;
    Math_MtxFRotate(&mf, 0.0f, 0.0f, camera_state.yaw);
    mf.mf[3][0] = hud_draw_origin_x + 17;
    mf.mf[3][1] = hud_draw_origin_y + 17;
    mf.mf[3][2] = 0.0f;
    guMtxF2L(mf.mf, &buf->mtx[gfx_mtx_index]);
    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(gfx_dl_head++, D_803AA758);
    Hud_DrawTextureTile(&D_803A86F8, 13, 10, 11, 14, 0x93, 0, 0x400, 0x400);
    if (menu_map_region < 6 && menu_map_spot < 0 && !(core_flags & 0x80)) {
        dx = menu_map_marker_x - player_state.actor.x;
        dz = menu_map_marker_z - player_state.actor.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist > 10.0) {
            ang = Math_Atan2(dx, dz) - camera_state.yaw;
            if (ang < -3.141592653589793) {
                ang += 6.283185307179586;
            } else if (ang > 3.141592653589793) {
                ang -= 6.283185307179586;
            }
            hud_temp_vec.x = 0.0f;
            hud_temp_vec.y = 18.0f;
            /* hud_temp_vec is a Vec3f elsewhere; here its x,y pair is the compass offset. */
            Math_RotateVec2(ang, (Vec2f *)&hud_temp_vec); /* its x/y pair is the compass offset */
            Hud_DrawTextureTile(&D_803A86F8, hud_temp_vec.x + 14.0f, hud_temp_vec.y + 13.0f, 8, 8, 0, 0x32, 0x400, 0x400);
        }
    }
}

extern u8 D_8039EC90[];
extern HudTextureDesc D_803A8718;




extern Gfx D_803AA2F8[];

void Hud_DrawSpellInput(GfxFrameData* buf, Player* arg1) {
    s32 i;
    s32 x1;
    u8* col;
    s32 x2;
    s32 x3;
    s32 x0;
    s32 y0;
    s32 y1;
    s32 y2;
    s32 y3;
    s32 yoff;
    f32* pos;
    f32 fx;
    f32 fy;
    u8 str[0x8];

    hud_draw_origin_x = 0x22;
    hud_draw_origin_y = 0x8C;
    x0 = 0x47;
    y0 = 0;
    x1 = 0;
    y1 = 0x18;
    x2 = 0x47;
    y2 = 0x31;
    x3 = 0x91;
    y3 = 0x18;
    yoff = 0;
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureFilter(gfx_dl_head++, G_TF_POINT);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
    if (hud_spell_input_anim_timer && (hud_spell_input_anim_flags & 2)) {
        i = hud_spell_input_anim_timer * hud_spell_input_anim_timer;
        x0 = 0x47 - i * 20 / 64;
        y0 = -(i * 10 / 64);
        x1 = 0 - i * 10 / 64;
        y1 = i * 20 / 64 + 0x18;
        x2 = i * 20 / 64 + 0x47;
        y2 = i * 10 / 64 + 0x31;
        x3 = i * 10 / 64 + 0x91;
        y3 = 0x18 - i * 20 / 64;
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        /* Keep this block on one line for IDO scheduling. */
        { Gfx* _g = gfx_dl_head++; if (i) {} _g->words.w0 = 0xFCFF9BFF; _g->words.w1 = 0xFF34FE7F; }
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255 - i * 255 / 64);
    }
    if (arg1->spell_input_count < 3) {
        Hud_DrawTextureTile(&D_803A8718, x0, y0, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x1, y1, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x2, y2, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x3, y3, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        for (i = 0; i < arg1->spell_input_count; i++) {
            str[i] = arg1->spell_input_dirs[i];
        }
        str[i] = 0;
        Hud_DrawSpellLabel(x0, y0 + 3, str, i + 1, arg1->stats->mp);
        str[i] = 1;
        Hud_DrawSpellLabel(x1, y1 + 3, str, i + 1, arg1->stats->mp);
        str[i] = 2;
        Hud_DrawSpellLabel(x2, y2 + 3, str, i + 1, arg1->stats->mp);
        str[i] = 3;
        Hud_DrawSpellLabel(x3, y3 + 3, str, i + 1, arg1->stats->mp);
    }
    hud_draw_origin_x = 0x69;
    hud_draw_origin_y = 0x32;
    if (hud_spell_input_anim_timer && (hud_spell_input_anim_flags & 2)) {
        i = hud_spell_input_anim_timer * hud_spell_input_anim_timer;
        yoff = i * 40 / 64;
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        gDPSetCombine(gfx_dl_head++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255 - i * 255 / 64);
    }
    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x6E, 0xE, 0x64, 0xE, 0x400, 0x400);
    x0 = 0x37 - arg1->spell_input_count * 6;
    for (i = 0; i < arg1->spell_input_count; i++) {
        y0 = arg1->spell_input_dirs[i];
        Hud_DrawTextureTile(&D_803A8718, x0, yoff + 0xD, 0xB, 0xB, 0x40, y0 * 0xB + 0x24, 0x400, 0x400);
        x0 += 0xC;
    }
    Hud_DrawSpellLabel(0, yoff + 3, arg1->spell_input_dirs, arg1->spell_input_count, arg1->stats->mp);
    hud_draw_origin_x = 0x22;
    hud_draw_origin_y = 0x8C;
    if (arg1->spell_input_count != 3) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0x0F0A4000, 0);
        gDPSetCombine(gfx_dl_head++, 0xFFFFFF, 0xFFFCF279);
        gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
        Hud_DrawTextureTile(&D_803A8718, 0x6D, 0xD, 0x24, 0x24, 0x40, 0, 0x400, 0x400);
    }
    if (hud_spell_input_anim_timer && (hud_spell_input_anim_flags & 1)) {
        col = hud_element_colors[arg1->spell_input_dirs[arg1->spell_input_count - 1]];
        pos = (f32*)hud_spell_input_icon_positions + arg1->spell_input_dirs[arg1->spell_input_count - 1] * 2;
        fx = pos[0] + 109.0f + hud_draw_origin_x;
        fy = pos[1] + 13.0f + hud_draw_origin_y;
        guTranslate(&buf->mtx[gfx_mtx_index], fx, fy, 0.0f);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(gfx_dl_head++);
        gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], hud_spell_input_anim_timer * 255 / 8);
        gSPDisplayList(gfx_dl_head++, D_803AA2F8);
    }
    if (hud_spell_input_anim_timer) {
        hud_spell_input_anim_timer--;
    }
}



extern u8 D_8039EC90[];
extern HudTextureDesc D_803A8718;

#ifdef NON_MATCHING
/* register-only: (u8)w lands in a2 instead of t9 and w >> 8 misses ra; code is equivalent */
void Hud_DrawSpellName(void* arg0) {
    s32 tmp;
    volatile s32 id;
    s32 t;
    s32 w;
    s32 yoff;
    u8* str;

    hud_draw_origin_x = 0x69;
    hud_draw_origin_y = 0x32;
    w = ((Player *)arg0)->spell_id;
    id = (u8)w;
    str = D_800C03D8[(u8)(w >> 8) & 0xF][(u8)w];
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureFilter(gfx_dl_head++, G_TF_POINT);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
    yoff = 0;
    if (hud_spell_input_anim_timer && (hud_spell_input_anim_flags & 2)) {
        w = hud_spell_input_anim_timer;
        t = w * w;
        yoff = t * 40 / 64;
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        gDPSetCombine(gfx_dl_head++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255 - t * 255 / 64);
        hud_spell_input_anim_timer--;
    }
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x6E, 0xE, 0x64, 0xE, 0x400, 0x400);
    Hud_DrawGlyphString(0x37 - Hud_MeasureGlyphString(str) / 2, yoff + 3, 0, str);
    gDPPipeSync(gfx_dl_head++);
    gDPSetRenderMode(gfx_dl_head++, 0x0F0A4000, 0);
    gDPSetCombine(gfx_dl_head++, 0xFFFFFF, 0xFFFCF279);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/ui/hud/Hud_DrawSpellName.s")
#endif




extern u8 D_8039ADB0[];
extern Gfx D_803AA2F8[];

void Hud_UpdateElementAllocation(GfxFrameData* buf, Player* pl) {
    u16 alpha;
    s32 yoff;
    s32 t;
    f32* pos;
    f32 x;
    u8* col;
    f32 y;

    hud_draw_origin_x = 0x81;
    hud_draw_origin_y = 0x48;
    yoff = 0;
    if (hud_element_input_timer) {
        if (hud_element_allocation_flags & 1) {
            alpha = hud_element_input_timer * 255 / 8;
        } else {
            t = hud_element_input_timer * hud_element_input_timer;
            yoff = t * 20 / 64;
            alpha = 255 - t * 255 / 64;
        }
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        gDPSetCombine(gfx_dl_head++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, alpha);
    }
    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x40, 0x14, 0, 0, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x14, 0x40, 0x14, 0, 0x14, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x28, 0x40, 0x14, 0, 0x28, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x3C, 0x40, 0x14, 0, 0x3C, 0x400, 0x400);
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039ADB0);
    Hud_DrawNumber(5, 0x1C, yoff + 0x24, player_stats.element_levels[0]);
    Hud_DrawNumber(5, 0xA, yoff + 0x34, player_stats.element_levels[1]);
    Hud_DrawNumber(5, 0x1C, yoff + 0x43, player_stats.element_levels[2]);
    Hud_DrawNumber(5, 0x2E, yoff + 0x34, player_stats.element_levels[3]);
    if (hud_element_input_timer && (hud_element_allocation_flags & 1)) {
        col = hud_element_colors[hud_selected_element_index];
        pos = (f32*)hud_element_icon_positions + hud_selected_element_index * 2;
        x = pos[0] + hud_draw_origin_x;
        y = pos[1] + hud_draw_origin_y;
        guTranslate(&buf->mtx[gfx_mtx_index], x, y, 0.0f);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(gfx_dl_head++);
        gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], hud_element_input_timer * 255 / 8);
        gSPDisplayList(gfx_dl_head++, D_803AA2F8);
    }
    if (hud_element_input_timer == 0) {
        if (input_pressed_buttons & 0xF) {
            if (input_pressed_buttons & 8) {
                hud_selected_element_index = 0;
            } else if (input_pressed_buttons & 2) {
                hud_selected_element_index = 1;
            } else if (input_pressed_buttons & 4) {
                hud_selected_element_index = 2;
            } else {
                hud_selected_element_index = 3;
            }
            if (pl->stats->element_levels[hud_selected_element_index] < 50) {
                pl->stats->element_levels[hud_selected_element_index]++;
                if (pl->stats->element_levels[hud_selected_element_index] == 50) {
                    pl->flags |= hud_element_max_level_set_masks[hud_selected_element_index];
                    if ((pl->flags & 0xF000) == 0xF000) {
                        pl->flags |= 0x10000;
                    }
                }
                Sfx_Play(0, 4, 0xFF);
                hud_element_gain_flash_timer = 30;
                hud_element_input_timer = 8;
                hud_element_allocation_flags |= 1;
            }
        }
    } else {
        hud_element_input_timer--;
        if ((hud_element_allocation_flags & 1) && hud_element_input_timer == 0) {
            core_flags &= ~8;
            hud_element_allocation_flags ^= 1;
        }
    }
}




void Hud_DrawNpcTalkMarker(void) {
    s32 sx;
    s32 bob;
    Actor* p;
    u16 *angle = &hud_npc_marker_phase;

    p = &npc_slots[player_talk_npc - 1].actor;
    if (Camera_WorldToScreen(p->x, p->y + 14.0, p->z, &sx, &hud_npc_marker_screen_y)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(gfx_dl_head++, D_803AA448);
        Hud_DrawClippedTextureRect(sx, hud_npc_marker_screen_y - bob - 30, 0x40, 29, 0, 0, 0x400, 0x400);
    } else {
        hud_npc_marker_screen_y = 0xF0;
    }
}

void Hud_DrawSpiritMarker(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &hud_spirit_marker_phase;

    if (Camera_WorldToScreen(player_state.actor.x, player_state.actor.y + 11.0, player_state.actor.z, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(gfx_dl_head++, D_803AA538);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 24, 30, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawChestMarker(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &hud_chest_text_marker_phases[0];

    if (Camera_WorldToScreen(player_state.actor.x, player_state.actor.y + 11.0, player_state.actor.z, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(gfx_dl_head++, D_803AA4C0);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 0x10, 30, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawTextSpotMarker(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &hud_chest_text_marker_phases[1];

    if (Camera_WorldToScreen(player_state.actor.x, player_state.actor.y + 11.0, player_state.actor.z, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(gfx_dl_head++, D_803AA448);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 0x40, 29, 0, 0, 0x400, 0x400);
    }
}


extern Gfx D_803AA5B0[];

void Hud_DrawMeleeTargetMarker(u16 arg0) {
    s32 sx;
    s32 sy;
    s32 bob;
    f32 y;
    Actor* a;
    u16 *angle = &hud_melee_marker_phase;

    a = &enemy_slots[arg0].actor;
    if (a->stats->unk0 == 1) {
        y = a->battle->unk94;
    } else if (a->stats->unk0 == 2) {
        y = a->y + 350.0 * a->scale;
    } else {
        y = a->y + a->stats->body_height * a->scale;
    }
    if (Camera_WorldToScreen(a->x, y, a->z, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(gfx_dl_head++, D_803AA5B0);
        Hud_DrawClippedTextureRect(sx - 4, sy - bob - 42, 24, 42, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawOutOfRangeIcon(void) {
    s32 sx;
    s32 sy;
    f32 y;
    f32 h;

    h = player_state.actor.stats->body_height * player_state.actor.scale;
    y = player_state.actor.y + h;
    if (Camera_WorldToScreen(player_state.actor.x, y, player_state.actor.z, &sx, &sy) != 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, D_803A4118);
        Hud_DrawTextureTile(D_803A8728, sx - 0x17, sy - 0xF, 0x2E, 0xF, 0x51, 0x31, 0x400, 0x400);
    }
}

void Hud_StartActorStatusIndicator(Actor* arg0, u16 mask, u16 idx, s16 val) {
    Struct_8002373C_68* s = (Struct_8002373C_68*)arg0->battle;
    u32 i;
    Struct_803AA6C4* e;
    f32 y;
    MagicVisualDef* fx;

    for (i = 0; i < 7; i++) {
        if (hud_actor_status_masks[i] & mask) {
            s->status_icon_ids[i] = idx;
            s->status_icon_timers[i] = val;
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((hud_actor_status_effect_masks[i] & mask) && s->status_effect_handles[i] == 0) {
            s->status_effect_timers[i] = val;
            e = &D_803AA6C4[idx];
            hud_temp_vec.x = e->scale_x;
            hud_temp_vec.y = e->scale_y;
            hud_temp_vec.z = 1.0f;
            fx = &D_803AA690[e->visual_def_index];
            if (arg0->stats->unk0 == 1) {
                if (e->unk4 & 0x100) {
                    y = arg0->battle->unk94;
                } else {
                    y = arg0->battle->unk94 - arg0->stats->body_radius * arg0->scale;
                }
            } else if (e->unk4 & 0x100) {
                y = arg0->y + arg0->stats->body_height * 0.5 * arg0->scale;
            } else {
                y = arg0->y;
            }
            s->status_effect_handles[i] = Magic_CreateVisualEffect(e->unk2, e->unk4, arg0->x, y, arg0->z, 0.0f, fx, &hud_temp_vec, arg0);
            return;
        }
    }
}

typedef struct {
    /* 0x0 */ s16 s;
    /* 0x2 */ s16 t;
    /* 0x4 */ u16 width;
    /* 0x6 */ u16 height;
} Struct_803AA628;


extern Struct_803AA628 D_803AA628[];

void Hud_UpdateAndDrawActorStatusIndicators(Actor* arg0) {
    Struct_8002373C_68* s = (Struct_8002373C_68*)arg0->battle;
    f32 y;
    s32 vis;
    s32 sx;
    s32 sy;
    s32 pad1;
    s32 pad2;
    s16 u;
    s16 v;
    s32 ox;
    s32 oy;
    u32 i;
    Struct_803AA628* e;
    s32 w;
    s32 h;
    EffectModel* fx;

    if (!(core_flags & 0x800)) {
        if (arg0->stats->unk0 == 1) {
            y = arg0->battle->unk94;
        } else {
            y = arg0->y + arg0->stats->body_height * arg0->scale;
        }
        pad1 = pad2 = 0;
    vis = Camera_WorldToScreen(arg0->x, y, arg0->z, &sx, &sy);
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, D_803A4118);
        oy = 0;
        ox = 0;
        for (i = 0; i < 7; i++) {
            if (s->status_icon_ids[i] != 0) {
                e = &D_803AA628[s->status_icon_ids[i]];
                u = e->s;
                v = e->t;
                w = e->width;
                h = e->height;
                if (vis) {
                    Hud_DrawTextureTile(D_803A8728, sx + ox - (w >> 1), sy + oy - (h >> 1), w, h, u, v, 0x400, 0x400);
                }
                if (!(hud_actor_status_masks[i] & s->status_bits)) {
                    s->status_icon_ids[i] = 0;
                } else if (s->status_icon_timers[i] > 0) {
                    if (--s->status_icon_timers[i] == 0) {
                        s->status_icon_ids[i] = 0;
                    }
                }
                ox += w >> 1;
                oy -= h >> 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->status_effect_handles[i] != 0) {
            fx = (EffectModel*)((Struct_8002373C_68*)arg0->battle)->status_effect_handles[i];
            fx->x = arg0->x;
            fx->z = arg0->z;
            if (arg0->stats->unk0 == 1) {
                if (fx->flags & 0x100) {
                    fx->y = arg0->battle->unk94;
                } else {
                    fx->y = arg0->battle->unk94 - arg0->stats->body_radius * arg0->scale;
                }
            } else if (fx->flags & 0x100) {
                fx->y = arg0->y + arg0->stats->body_height * 0.5 * arg0->scale;
            } else {
                fx->y = arg0->y;
            }
            if (!(hud_actor_status_effect_masks[i] & s->status_bits)) {
                s->status_effect_handles[i] = 0;
                if (fx->flags & 1) {
                    fx->flags &= ~1;
                    fx->framesLeft = 8;
                }
            } else if (s->status_effect_timers[i] > 0) {
                if (--s->status_effect_timers[i] == 0) {
                    s->status_effect_handles[i] = 0;
                    if (fx->flags & 1) {
                        fx->flags &= ~1;
                        fx->framesLeft = 8;
                    }
                }
            }
        }
    }
}

void Hud_ClearActorStatusIndicators(Actor* arg0) {
    Struct_8002373C_68* s = (Struct_8002373C_68*)arg0->battle;
    u32 i;
    EffectModel* fx;

    for (i = 0; i < 7; i++) {
        if (s->status_icon_ids[i] != 0) {
            s->status_icon_ids[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->status_effect_handles[i] != 0) {
            fx = (EffectModel*)s->status_effect_handles[i];
            fx->framesLeft = 8;
            fx->flags &= ~1;
            s->status_effect_handles[i] = 0;
        }
    }
}

void func_80023DEC(void) {
}

void func_80023DF4(void) {
}

void func_80023DFC(void) {
}

void func_80023E04(void) {
}

void func_80023E0C(void) {
}



extern u8 D_8039ADB0[];
extern u8 D_8039EC90[];
extern HudTextureDesc D_803A86F8;
extern HudTextureDesc D_803A8718;

void Hud_DrawEnemyInfoPanel(void) {
    s32 d;

    hud_draw_origin_x = 0xB5;
    hud_draw_origin_y = 0x1A;
    d = hud_enemy_info_timer - 50;
    if (d > 0) {
        d *= d;
        hud_draw_origin_x += d * 120 / 100;
    }
    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039EC90);
    if (enemy_turn_current->battle.status_bits & 0x80) {
        Hud_DrawTextureTile(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x10, 0x6E, 0x10, 0x64, 0x2C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x20, 0x6E, 0x10, 0x64, 0x3C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x30, 0x6E, 4, 0x64, 0x4C, 0x400, 0x400);
    } else {
        Hud_DrawTextureTile(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x10, 0x6E, 0xA, 0x64, 0x2C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x1A, 0x6E, 2, 0x64, 0x4E, 0x400, 0x400);
    }
    Hud_DrawGlyphString(4, 0x11, 0, ((u8 **)enemy_names)[enemy_turn_current->def->anim_set_index]); /* enemy_names stores a pointer table in one s32 slot */
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_8039ADB0);
    if (enemy_turn_current->battle.status_bits & 0x80) {
        Hud_DrawNumber(3, 0x10, 0x1C, enemy_turn_current->def->max_hp);
        Hud_DrawNumber(3, 0x10, 0x26, enemy_turn_current->def->defense);
        Hud_DrawNumber(3, 0x46, 0x1C, enemy_turn_current->def->attack_power);
        Hud_DrawNumber(3, 0x46, 0x26, enemy_turn_current->def->agility);
        if (enemy_turn_current->def->element_index != 4) {
            Hud_DrawTextureTile(&D_803A86F8, 0x5B, 3, 0xC, 0xC, enemy_turn_current->def->element_index * 0xC + 0x20, 0x10, 0x400, 0x400);
        }
    }
}

void Hud_ResetPopups(void) {
    HudPopup* p = hud_popup_slots;
    s32 i = 8;

    while (i > 0) {
        p->remaining_frames = 0;
        p++;
        i--;
    }
}

void Hud_ShowActorPopup(Actor* arg0) {
    HudPopup* p = hud_popup_slots;
    s32 i = 7;

    while (i != 0 && p->remaining_frames != 0) {
        i--;
        p++;
    }
    p->remaining_frames = 0x2D;
    p->actor = arg0;
    p->offset_z = 0.0f;
    p->offset_x = 0.0f;
    if (arg0->stats->unk0 == 0) {
        p->offset_y = arg0->stats->body_height * arg0->scale;
    } else if (arg0->stats->unk0 == 1) {
        p->offset_y = arg0->battle->unk94 - arg0->y;
    } else {
        p->offset_y = arg0->scale * 600.0;
    }
    p->texture_s = 0x23;
    p->texture_t = 0x31;
    p->width = 0x29;
    p->height = 0xE;
}

void Hud_DrawPopups(void) {
    s32 i;
    HudPopup* p;
    f32 x;
    f32 y;
    s32 sx;
    s32 sy;
    f32 z;

    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, D_803A4118);
    p = hud_popup_slots;
    i = 8;
    do {
        if (p->remaining_frames != 0) {
            x = p->offset_x;
            y = p->offset_y;
            z = p->offset_z;
            if (p->actor != NULL) {
                x += ((Vec3f*) p->actor)->x;
                y += ((Vec3f*) p->actor)->y;
                z += ((Vec3f*) p->actor)->z;
            }
            Camera_WorldToScreen(x, y, z, &sx, &sy);
            Hud_DrawTextureTile(D_803A8728, sx - (p->width >> 1), sy - p->height, p->width, p->height, p->texture_s, p->texture_t, 0x400, 0x400);
            p->remaining_frames--;
        }
        i--;
        p++;
    } while (i != 0);
}

void Hud_DrawSpellLabel(s32 arg0, s32 arg1, u8* arg2, s32 arg3, u16 arg4) {
    u32 id;
    s32 w;
    u8 flags;
    u8* str;
    u32 tmp;

    id = Magic_LookupSpellSequence(arg3, (s32)arg2);
    flags = Magic_GetSpellRestrictionFlags(id, arg4);
    tmp = (id >> 8) & 0xF;
    id &= 0xFF;
    str = D_800C03D8[tmp][id];
    if (flags & 4) {
        str = hud_spell_locked_label;
    }
    w = Hud_MeasureGlyphString(str);
    arg0 = arg0 - w / 2 + 0x37;
    Hud_DrawGlyphString(arg0, arg1, hud_spell_label_palettes[flags], str);
}

void Hud_DrawGlyphString(s32 x, s32 y, s32 pal, u8* str) {
    s32 cur = 8;
    s32 col;
    s32 row;

    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_803A8778[pal]);
    while (*str != 0xFF) {
        if (*str == 0x80) {
            Hud_DrawClippedTextureRect(x - 2, y - 1, 8, 9, 0x78, row, 0x400, 0x400);
            x += 1;
        } else if (*str == 0x81) {
            Hud_DrawClippedTextureRect(x - 2, y - 1, 8, 9, 0x80, row, 0x400, 0x400);
            x += 1;
        } else if (*str == 0x82) {
            x += 4;
        } else {
            col = (*str & 0xF) * 8;
            row = (*str & 0x70) >> 4;
            if (row != cur) {
                Hud_LoadTextureTile(&D_803A8748, 0, row * 9, 0xA0, 9);
                cur = row;
            }
            row *= 9;
            Hud_DrawClippedTextureRect(x, y, 8, 9, col, row, 0x400, 0x400);
            x += 8;
        }
        str++;
    }
}

s32 Hud_MeasureGlyphString(u8* str) {
    s32 w = 0;

    while (*str != 0xFF) {
        if (!(*str & 0x80)) {
            w += 8;
        } else if (*str == 0x80 || *str == 0x81) {
            w += 1;
        } else if (*str == 0x82) {
            w += 4;
        }
        str++;
    }
    return w;
}

void Hud_DrawNumber(u16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    u8* p;
    u8 buf[8];

    p = buf;
    for (n = Text_FormatNumber(arg3, buf, arg0); n != 0; n--) {
        if (*p != 0x20) {
            Hud_DrawClippedTextureRect(arg1, arg2, 8, 0xA, *p * 8 + 0x20, 0x1D, 0x400, 0x400);
            arg1 += 7;
        } else if (arg0 & 6) {
            arg1 += 7;
        }
        p++;
    }
}

void func_80024A4C(void) {
}

void Hud_LoadTextureTile(HudTextureDesc* tex, s32 x, s32 y, s32 w, s32 h) {
    if (tex->is4b == 0) {
        gDPLoadTextureTile(gfx_dl_head++, tex->img, G_IM_FMT_CI, G_IM_SIZ_8b, tex->width, 0, x, y, x + w, y + h, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    } else {
        gDPLoadTextureTile_4b(gfx_dl_head++, tex->img, G_IM_FMT_CI, tex->width, 0, x, y, x + w - 1, y + h - 1, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
    }
}

void Hud_DrawClippedTextureRect(s32 x, s32 y, s32 x2, s32 y2, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    x += hud_draw_origin_x;
    x2 += x;
    y += hud_draw_origin_y;
    if (x2 < hud_clip_left) {
        return;
    }
    y2 += y;
    if (y2 < hud_clip_top) {
        return;
    }
    if (hud_clip_right < x) {
        return;
    }
    if (hud_clip_bottom < y) {
        return;
    }
    if (hud_clip_right < x2) {
        x2 = hud_clip_right;
    }
    if (hud_clip_bottom < y2) {
        y2 = hud_clip_bottom;
    }
    if (x < hud_clip_left) {
        s = s - x + hud_clip_left;
        x = hud_clip_left;
    }
    if (y < hud_clip_top) {
        t = t - y + hud_clip_top;
        y = hud_clip_top;
    }
    gSPTextureRectangle(gfx_dl_head++, x << 2, y << 2, x2 << 2, y2 << 2, 0, s << 5, t << 5, dsdx, dtdy);
}

void Hud_DrawTextureTile(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    Hud_LoadTextureTile(arg0, arg5, arg6, arg3, arg4);
    Hud_DrawClippedTextureRect(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game/ui/hud/D_8006F530.s")

/* .data 8004F2C0..8004F4A0 */
s32 D_8004F2C0 = 0; /* nothing references it */
u8 hud_spell_locked_label[8] = {
#include "assets/hud_spell_locked_label.inc.c"
};
u8 hud_element_colors[4][4] = {
    { 0xFF, 0x00, 0x00, 0x00 },
    { 0xFF, 0xC8, 0x00, 0x00 },
    { 0x00, 0x00, 0xFF, 0x00 },
    { 0x00, 0xFF, 0x00, 0x00 },
};
u16 hud_actor_status_masks[8] = { 0x4, 0x1, 0x400, 0x20, 0x10, 0x80, 0x40, 0x0 };
u16 hud_actor_status_effect_masks[4] = { 0x8, 0x2, 0x200, 0x100 };
s32 hud_element_max_level_masks[4] = { 0x1000, 0x2000, 0x4000, 0x8000 };
Vec2f hud_spell_input_icon_positions[4] = { { 17.0f, 5.0f }, { 5.0f, 17.0f }, { 17.0f, 30.0f }, { 30.0f, 17.0f } };
Vec2f hud_element_icon_positions[4] = { { 30.0f, 35.0f }, { 12.0f, 51.0f }, { 30.0f, 66.0f }, { 48.0f, 51.0f } };
s32 hud_element_max_level_set_masks[4] = { 0x1000, 0x2000, 0x4000, 0x8000 };
s32 D_8004F354[77] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 2, 0, 0, 5 }; /* nothing references it */
u8 D_8004F488[0x10] = { /* message text, nothing references it */
#include "assets/D_8004F488.inc.c"
};
u8 hud_spell_label_palettes[8] = { 0, 1, 2, 2, 2, 2, 2, 2 };
