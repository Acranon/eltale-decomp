#include "common.h"

/*
 * In-game HUD: meters, compass, spell input, status indicators, and text primitives.
 * Folder: src/game/ui/
 */

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x1C - 0x8];
    /* 0x1C */ f32 unk1C;
} Struct_80024338_64;

typedef struct {
    /* 0x00 */ char unk0[0x94];
    /* 0x94 */ f32 unk94;
} Struct_80024338_68;

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x24 - 0x8];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x64 - 0x28];
    /* 0x64 */ u16* unk64;
    /* 0x68 */ Struct_80024338_68* unk68;
} Struct_8002433C_arg;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x04 */ Struct_8002433C_arg* unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
} Struct_8008C058;

typedef struct {
    f32 x, y, z;
} Vec3f_216E0;

/* This file's .bss, 8008C040..8008C190, in address order (first declaration fixes
 * the order). D_8008C164 is used only by 12610. */
u16 hud_npc_marker_phase;
u16 hud_element_allocation_flags;
s32 hud_clip_left; /* HUD clip bound, screen pixels */
s32 hud_clip_top;
s32 hud_clip_right;
u16 hud_spirit_marker_phase;
s32 hud_clip_bottom;
Struct_8008C058 hud_popup_slots[8];
u32 hud_element_gain_flash_timer;
u32 hud_selected_element_index;
Vec3f_216E0 hud_rotated_vector_scratch;
u16 hud_chest_text_marker_phases[2];
u16 hud_melee_marker_phase;
u16 hud_panel_transition_frame;
u16 hud_panel_transition_state;
u16 hud_hp_meter_width;
u16 hud_mp_meter_width;
u16 hud_element_allocation_timer;
u16 hud_element_allocation_mode_flags;
u16 hud_melee_hint_timer;
u16 hud_element_input_timer; /* eight-frame element input/fade timer */
u16 hud_battle_message_timer;
s32 D_8008C164;
s32 D_8008C168;
s32 D_8008C16C;
s32 hud_pending_sequence_id;
s32 hud_draw_origin_x;
s32 hud_draw_origin_y;
s32 hud_npc_marker_screen_y;
u16 hud_element_pulse_phase;
extern u8** D_800C03D8[];
extern u8 hud_digit_glyph_data[];
extern u8 hud_number_spacing[];

u32 Magic_LookupSpellSequence(u16, s32);
s32 Magic_GetSpellRestrictionFlags(u32, u16);
s32 Text_FormatNumber(s32, u8*, u16);
void Hud_DrawGlyphString(s32, s32, s32, u8*);
s32 Hud_MeasureGlyphString(u8*);
typedef struct {
    /* 0x00 */ void* img;
    /* 0x04 */ u16 is4b;
    /* 0x08 */ u32 width;
} Struct_80024A54;

void Hud_LoadTextureTile(Struct_80024A54*, s32, s32, s32, s32);
void Hud_DrawClippedTextureRect(s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ char unk0[0x1C];
    /* 0x1C */ f32 unk1C;
} Struct_8007AA08_7C;

typedef struct {
    /* 0x00 */ char unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x3C - 0x24];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ char unk40[0x7C - 0x40];
    /* 0x7C */ Struct_8007AA08_7C* unk7C;
} Struct_8007AA08;

extern Gfx* D_8007A184;
extern Struct_8007AA08 D_8007AA08;
extern Gfx D_803AA448[];
extern Gfx D_803AA4C0[];
extern Gfx D_803AA538[];

s32 Camera_WorldToScreen(f32, f32, f32, s32*, s32*);
s16 sins(u16);
void Hud_DrawClippedTextureRect(s32, s32, s32, s32, s32, s32, s32, s32);


extern u8 D_803A4118[];
extern u8 D_803A8728[];
extern u8* D_803A8778[];
extern Struct_80024A54 D_803A8748;

void Hud_DrawTextureTile(void*, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x18 - 0x2];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} Struct_8002373C_64;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x12 - 0x2];
    /* 0x12 */ u8 unk12[0x10];
    /* 0x22 */ s8 unk22[0x10];
    /* 0x32 */ s8 unk32[0x12];
    /* 0x44 */ s32 unk44[4];
    /* 0x54 */ char unk54[0x94 - 0x54];
    /* 0x94 */ f32 unk94;
} Struct_8002373C_68;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x24 - 0xC];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x64 - 0x28];
    /* 0x64 */ Struct_8002373C_64* unk64;
    /* 0x68 */ Struct_8002373C_68* unk68;
} Struct_8002373C;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AA6C4;

typedef struct {
    char unk0[0xA];
} Struct_803AA690;

extern u16 hud_actor_status_masks[];
extern u16 hud_actor_status_alt_masks[];
extern Struct_803AA690 D_803AA690[];
extern Struct_803AA6C4 D_803AA6C4[];

s32 Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, Struct_803AA690*, Vec3f_216E0*, Struct_8002373C*);

void Hud_ResetState(void) {
    D_8008C168 = 0;
    D_8008C16C = 0;
    hud_pending_sequence_id = -1;
    hud_draw_origin_y = 0;
    hud_draw_origin_x = hud_draw_origin_y;
    hud_clip_top = 0;
    hud_clip_left = hud_clip_top;
    hud_clip_right = 0x140;
    hud_clip_bottom = 0xF0;
    hud_battle_message_timer = 0;
    hud_melee_hint_timer = 0;
    hud_element_allocation_mode_flags = 0;
    hud_element_allocation_timer = hud_element_allocation_mode_flags;
    hud_element_gain_flash_timer = 0;
    hud_element_allocation_flags = 0;
}

typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

typedef struct {
    /* 0x000 */ char unk0[0x2C];
    /* 0x02C */ char unk2C[0x7C - 0x2C];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ char unk7E[0x130 - 0x7E];
} Struct_8007B908_216E0;

typedef struct {
    /* 0x00 */ char unk0[0x14];
    /* 0x14 */ u16 unk14;
} Struct_8007C288;

extern Unk2000000 D_2000000;
extern s32 D_8004DCA0;
extern s32 D_8007A180;
extern s32 D_8007A9C0;
extern s32 D_8007A9C4;
extern s32 D_8007A9C8;
extern s32 D_8007A9CC;
extern u16 D_8007AA0A;
extern s32 D_8007AA10;
extern s32 D_8007AA1C;
extern u8 D_8007AA20[];
extern u16 D_8007AA80;
extern s32 D_8007B900;
extern Struct_8007B908_216E0 D_8007B908[];
extern Struct_8007C288* D_8007C288;
extern u16 D_800842B8;
extern s32 D_80085F90;
extern u16 battle_flags;
extern Gfx D_803A8788[];

struct Struct_80021030;
void Hud_DrawPlayerMeters(struct Struct_80021030* arg0);
void Hud_DrawElementLevels(Unk2000000* arg0, s32 arg1);
void Hud_DrawCompass(Unk2000000* buf);
struct Struct_80021C04;
void Hud_DrawSpellInput(Unk2000000* arg0, struct Struct_80021C04* arg1);
void Hud_DrawSpellName(void* arg0);
struct Struct_80022970;
void Hud_UpdateElementAllocation(Unk2000000* arg0, struct Struct_80022970* arg1);
void Hud_DrawNpcTalkMarker(void);
void Hud_DrawSpiritMarker(void);
void Hud_DrawChestMarker(void);
void Hud_DrawTextSpotMarker(void);
void Hud_DrawMeleeTargetMarker(u16 arg0);
void Hud_DrawOutOfRangeIcon(void);
void Hud_UpdateAndDrawActorStatusIndicators(Struct_8002373C* arg0);
void Hud_DrawEnemyInfoPanel(void);
void Hud_DrawPopups(void);

void Hud_Draw(Unk2000000* buf) {
    s32 n;
    Struct_8007B908_216E0* e;

    gSPMatrix(D_8007A184++, &D_2000000.unk0[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guTranslate(&buf->unkC0[D_8007A180], -160.0f, -120.0f, 0.0f);
    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    hud_clip_right = 0x140;
    hud_clip_bottom = 0xF0;
    gSPDisplayList(D_8007A184++, D_803A8788);
    if ((D_8004DCA0 & 2) && hud_panel_transition_state != 1) {
        hud_panel_transition_state = 1;
    } else if (!(D_8004DCA0 & 2) && hud_panel_transition_state == 1) {
        hud_panel_transition_state = 2;
    }
    if (!(D_8004DCA0 & 0xC00)) {
        Hud_DrawPlayerMeters((struct Struct_80021030*)D_8007AA20);
        Hud_DrawElementLevels(buf, D_8007AA1C);
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
    if ((D_800842B8 & 0xD) && !(battle_flags & 1) && !(D_8007C288->unk14 & 8) && !(D_8004DCA0 & 2)) {
        Hud_DrawCompass(buf);
    }
    if ((battle_flags & 1) && hud_battle_message_timer) {
        Hud_DrawEnemyInfoPanel();
        hud_battle_message_timer--;
    }
    hud_draw_origin_x = hud_draw_origin_y = 0;
    if (battle_flags & 1) {
        Hud_DrawPopups();
        if (!(battle_flags & 2) && D_8007AA0A && !(D_8007AA80 & 1) && !(D_80085F90 & 1)) {
            Hud_DrawMeleeTargetMarker(D_8007AA0A - 1);
        }
        if ((D_8007AA10 & 0x20) && !(D_8004DCA0 & 0x800)) {
            Hud_DrawOutOfRangeIcon();
        }
        Hud_UpdateAndDrawActorStatusIndicators((Struct_8002373C*)D_8007AA20);
        n = D_8007B900;
        e = D_8007B908;
        while (n != 0) {
            if (e->unk7C != -1) {
                Hud_UpdateAndDrawActorStatusIndicators((Struct_8002373C*)e->unk2C);
                n--;
            }
            e++;
        }
    } else if (!(D_8004DCA0 & 0x87) && !(D_8007AA80 & 1)) {
        if (D_8007A9C0) {
            Hud_DrawNpcTalkMarker();
        } else if (D_8007A9C4 && !(D_8004DCA0 & 8)) {
            Hud_DrawSpiritMarker();
        } else if (D_8007A9C8) {
            Hud_DrawChestMarker();
        } else if (D_8007A9CC) {
            Hud_DrawTextSpotMarker();
        }
    }
    if (D_8004DCA0 & 4) {
        Hud_DrawSpellInput(buf, (struct Struct_80021C04*)&D_8007AA08);
    } else if (D_8004DCA0 & 8) {
        Hud_UpdateElementAllocation(buf, (struct Struct_80022970*)&D_8007AA08);
    }
    if (hud_melee_hint_timer) {
        Hud_DrawSpellName(&D_8007AA08);
        hud_melee_hint_timer--;
    }
}

typedef struct {
    /* 0x0 */ char unk0[4];
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 unk8;
    /* 0xA */ u16 unkA;
} Struct_80021030_64;

typedef struct Struct_80021030 {
    /* 0x00 */ char unk0[0x64];
    /* 0x64 */ Struct_80021030_64* unk64;
} Struct_80021030;

extern Struct_80024A54 D_803A86F8;
void Hud_DrawNumber(u16 arg0, s32 arg1, s32 arg2, s32 arg3);

void Hud_DrawPlayerMeters(Struct_80021030* arg0) {
    Struct_80021030_64* st;
    s32 w;
    s32 d;

    hud_draw_origin_x = 0x1C;
    hud_draw_origin_y = 0x18;
    if (hud_panel_transition_state != 0) {
        w = hud_panel_transition_frame * hud_panel_transition_frame;
        hud_draw_origin_x -= w * 150 / 144;
    }
    st = arg0->unk64;
    Hud_DrawTextureTile(&D_803A86F8, 0, 1, 0x3E, 0x11, 0x20, 0x27, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A86F8, 0, 0x12, 0x3E, 0x12, 0x20, 0x38, 0x400, 0x400);
    w = st->unk4 * 56 / st->unk6;
    d = w - hud_hp_meter_width;
    if (d >= 2 || d < -1) {
        hud_hp_meter_width += d >> 1;
    } else {
        hud_hp_meter_width = w;
    }
    if (hud_hp_meter_width) {
        Hud_DrawTextureTile(&D_803A86F8, 3, 0xB, hud_hp_meter_width, 5, 0x5E, 0x27, 0x400, 0x400);
    }
    w = st->unk8 * 56 / st->unkA;
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
    Hud_DrawNumber(3, 0xC, 0, st->unk4);
    Hud_DrawNumber(1, 0x36, 0, st->unk6);
    Hud_DrawNumber(3, 0xC, 0x1B, st->unk8);
    Hud_DrawNumber(1, 0x36, 0x1B, st->unkA);
    Hud_DrawClippedTextureRect(0x2F, 0, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
    Hud_DrawClippedTextureRect(0x2F, 0x1B, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
}

extern s32 hud_element_unlock_masks[];
extern Gfx D_803AA3C8[];
extern u8 hud_element_colors[][4];
extern Gfx D_803AA2F8[];

void Hud_DrawElementLevels(Unk2000000* buf, s32 arg1) {
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
        if (((s32*)&D_8007AA08)[2] & hud_element_unlock_masks[i]) {
            col = &hud_element_colors[0][i];
            fx = i * 22.0f + 5.0 + (f32)hud_draw_origin_x;
            fy = hud_draw_origin_y + 5.0f;
            guTranslate(&buf->unkC0[D_8007A180], fx, fy, 0.0f);
            gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gDPPipeSync(D_8007A184++);
            gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], (sins(*angle) >> 10) + 0x88);
            gSPDisplayList(D_8007A184++, D_803AA3C8);
        }
    }
    *angle += 0x444;
    if (hud_element_gain_flash_timer) {
        col = hud_element_colors[hud_selected_element_index];
        fx = hud_selected_element_index * 22.0f + 5.0 + (f32)hud_draw_origin_x;
            fy = hud_draw_origin_y + 5.0f;
            guTranslate(&buf->unkC0[D_8007A180], fx, fy, 0.0f);
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], hud_element_gain_flash_timer * 255 / 30);
        gSPDisplayList(D_8007A184++, D_803AA2F8);
        hud_element_gain_flash_timer--;
    }
}


extern f32 D_80085E74;
extern f32 D_8008FB48;
extern f32 D_8008FB4C;
extern s32 D_8008FB50;
extern s32 D_8008FB54;
extern Gfx D_803AA758[];
extern Struct_80024A54 D_803A86F8;
f32 sqrtf(f32);
f32 Math_Atan2(f32, f32);
void Math_RotateVec2(f32, Vec3f_216E0*);
void Math_MtxFRotate(f32 (*)[4], f32, f32, f32);

void Hud_DrawCompass(Unk2000000* buf) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ang;
    f32 mf[4][4];

    hud_draw_origin_x = 0x104;
    hud_draw_origin_y = 0x18;
    Math_MtxFRotate(mf, 0.0f, 0.0f, D_80085E74);
    mf[3][0] = hud_draw_origin_x + 17;
    mf[3][1] = hud_draw_origin_y + 17;
    mf[3][2] = 0.0f;
    guMtxF2L(mf, &buf->unkC0[D_8007A180]);
    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(D_8007A184++, D_803AA758);
    Hud_DrawTextureTile(&D_803A86F8, 13, 10, 11, 14, 0x93, 0, 0x400, 0x400);
    if (D_8008FB50 < 6 && D_8008FB54 < 0 && !(D_8004DCA0 & 0x80)) {
        dx = D_8008FB48 - D_8007AA08.unk18;
        dz = D_8008FB4C - D_8007AA08.unk20;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist > 10.0) {
            ang = Math_Atan2(dx, dz) - D_80085E74;
            if (ang < -3.141592653589793) {
                ang += 6.283185307179586;
            } else if (ang > 3.141592653589793) {
                ang -= 6.283185307179586;
            }
            hud_rotated_vector_scratch.x = 0.0f;
            hud_rotated_vector_scratch.y = 18.0f;
            Math_RotateVec2(ang, &hud_rotated_vector_scratch);
            Hud_DrawTextureTile(&D_803A86F8, hud_rotated_vector_scratch.x + 14.0f, hud_rotated_vector_scratch.y + 13.0f, 8, 8, 0, 0x32, 0x400, 0x400);
        }
    }
}

extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A8718;

typedef struct {
    /* 0x0 */ char unk0[8];
    /* 0x8 */ u16 unk8;
} Struct_80021C04_14;

typedef struct Struct_80021C04 {
    /* 0x000 */ char unk0[0x14];
    /* 0x014 */ Struct_80021C04_14* unk14;
    /* 0x018 */ char unk18[0x11D - 0x18];
    /* 0x11D */ u8 unk11D[3];
    /* 0x120 */ u16 unk120;
} Struct_80021C04;

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
} Struct_8004F324;

void Hud_DrawSpellLabel(s32 arg0, s32 arg1, u8* arg2, s32 arg3, u16 arg4);
extern Struct_8004F324 hud_spell_input_icon_positions[];
extern u8 hud_element_colors[][4];
extern Gfx D_803AA2F8[];

void Hud_DrawSpellInput(Unk2000000* buf, Struct_80021C04* arg1) {
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
    gDPPipeSync(D_8007A184++);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    if (hud_element_allocation_timer && (hud_element_allocation_mode_flags & 2)) {
        i = hud_element_allocation_timer * hud_element_allocation_timer;
        x0 = 0x47 - i * 20 / 64;
        y0 = -(i * 10 / 64);
        x1 = 0 - i * 10 / 64;
        y1 = i * 20 / 64 + 0x18;
        x2 = i * 20 / 64 + 0x47;
        y2 = i * 10 / 64 + 0x31;
        x3 = i * 10 / 64 + 0x91;
        y3 = 0x18 - i * 20 / 64;
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        /* Keep this block on one line for IDO scheduling. */
        { Gfx* _g = D_8007A184++; if (i) {} _g->words.w0 = 0xFCFF9BFF; _g->words.w1 = 0xFF34FE7F; }
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, 255 - i * 255 / 64);
    }
    if (arg1->unk120 < 3) {
        Hud_DrawTextureTile(&D_803A8718, x0, y0, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x1, y1, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x2, y2, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, x3, y3, 0x6E, 0xE, 0x64, 0, 0x400, 0x400);
        for (i = 0; i < arg1->unk120; i++) {
            str[i] = arg1->unk11D[i];
        }
        str[i] = 0;
        Hud_DrawSpellLabel(x0, y0 + 3, str, i + 1, arg1->unk14->unk8);
        str[i] = 1;
        Hud_DrawSpellLabel(x1, y1 + 3, str, i + 1, arg1->unk14->unk8);
        str[i] = 2;
        Hud_DrawSpellLabel(x2, y2 + 3, str, i + 1, arg1->unk14->unk8);
        str[i] = 3;
        Hud_DrawSpellLabel(x3, y3 + 3, str, i + 1, arg1->unk14->unk8);
    }
    hud_draw_origin_x = 0x69;
    hud_draw_origin_y = 0x32;
    if (hud_element_allocation_timer && (hud_element_allocation_mode_flags & 2)) {
        i = hud_element_allocation_timer * hud_element_allocation_timer;
        yoff = i * 40 / 64;
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetCombine(D_8007A184++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, 255 - i * 255 / 64);
    }
    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x6E, 0xE, 0x64, 0xE, 0x400, 0x400);
    x0 = 0x37 - arg1->unk120 * 6;
    for (i = 0; i < arg1->unk120; i++) {
        y0 = arg1->unk11D[i];
        Hud_DrawTextureTile(&D_803A8718, x0, yoff + 0xD, 0xB, 0xB, 0x40, y0 * 0xB + 0x24, 0x400, 0x400);
        x0 += 0xC;
    }
    Hud_DrawSpellLabel(0, yoff + 3, arg1->unk11D, arg1->unk120, arg1->unk14->unk8);
    hud_draw_origin_x = 0x22;
    hud_draw_origin_y = 0x8C;
    if (arg1->unk120 != 3) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x0F0A4000, 0);
        gDPSetCombine(D_8007A184++, 0xFFFFFF, 0xFFFCF279);
        gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
        Hud_DrawTextureTile(&D_803A8718, 0x6D, 0xD, 0x24, 0x24, 0x40, 0, 0x400, 0x400);
    }
    if (hud_element_allocation_timer && (hud_element_allocation_mode_flags & 1)) {
        col = hud_element_colors[arg1->unk11D[arg1->unk120 - 1]];
        pos = (f32*)hud_spell_input_icon_positions + arg1->unk11D[arg1->unk120 - 1] * 2;
        fx = pos[0] + 109.0f + hud_draw_origin_x;
        fy = pos[1] + 13.0f + hud_draw_origin_y;
        guTranslate(&buf->unkC0[D_8007A180], fx, fy, 0.0f);
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], hud_element_allocation_timer * 255 / 8);
        gSPDisplayList(D_8007A184++, D_803AA2F8);
    }
    if (hud_element_allocation_timer) {
        hud_element_allocation_timer--;
    }
}


typedef struct {
    /* 0x000 */ char unk0[0x122];
    /* 0x122 */ u16 unk122;
} Struct_80022658;

extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A8718;

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
    w = ((Struct_80022658*)arg0)->unk122;
    id = (u8)w;
    str = D_800C03D8[(u8)(w >> 8) & 0xF][(u8)w];
    gDPPipeSync(D_8007A184++);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    yoff = 0;
    if (hud_element_allocation_timer && (hud_element_allocation_mode_flags & 2)) {
        w = hud_element_allocation_timer;
        t = w * w;
        yoff = t * 40 / 64;
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetCombine(D_8007A184++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, 255 - t * 255 / 64);
        hud_element_allocation_timer--;
    }
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x6E, 0xE, 0x64, 0xE, 0x400, 0x400);
    Hud_DrawGlyphString(0x37 - Hud_MeasureGlyphString(str) / 2, yoff + 3, 0, str);
    gDPPipeSync(D_8007A184++);
    gDPSetRenderMode(D_8007A184++, 0x0F0A4000, 0);
    gDPSetCombine(D_8007A184++, 0xFFFFFF, 0xFFFCF279);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/216E0/Hud_DrawSpellName.s")
#endif

typedef struct {
    /* 0x00 */ char unk0[0x24];
    /* 0x24 */ u8 unk24[4];
} Struct_80022970_14;

typedef struct Struct_80022970 {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ char unkC[0x14 - 0xC];
    /* 0x14 */ Struct_80022970_14* unk14;
} Struct_80022970;


extern u8 hud_element_colors[][4];
extern Struct_8004F324 hud_element_icon_positions[];
extern s32 hud_element_milestone_masks[];
extern u8 D_8007A9F4;
extern u8 D_8007A9F5;
extern u8 D_8007A9F6;
extern u8 D_8007A9F7;
extern u16 input_pressed_buttons;
extern u8 D_8039ADB0[];
extern Gfx D_803AA2F8[];
void Sfx_Play(s32, s32, s32);

void Hud_UpdateElementAllocation(Unk2000000* buf, Struct_80022970* pl) {
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
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetCombine(D_8007A184++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, alpha);
    }
    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff, 0x40, 0x14, 0, 0, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x14, 0x40, 0x14, 0, 0x14, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x28, 0x40, 0x14, 0, 0x28, 0x400, 0x400);
    Hud_DrawTextureTile(&D_803A8718, 0, yoff + 0x3C, 0x40, 0x14, 0, 0x3C, 0x400, 0x400);
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039ADB0);
    Hud_DrawNumber(5, 0x1C, yoff + 0x24, D_8007A9F4);
    Hud_DrawNumber(5, 0xA, yoff + 0x34, D_8007A9F5);
    Hud_DrawNumber(5, 0x1C, yoff + 0x43, D_8007A9F6);
    Hud_DrawNumber(5, 0x2E, yoff + 0x34, D_8007A9F7);
    if (hud_element_input_timer && (hud_element_allocation_flags & 1)) {
        col = hud_element_colors[hud_selected_element_index];
        pos = (f32*)hud_element_icon_positions + hud_selected_element_index * 2;
        x = pos[0] + hud_draw_origin_x;
        y = pos[1] + hud_draw_origin_y;
        guTranslate(&buf->unkC0[D_8007A180], x, y, 0.0f);
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], hud_element_input_timer * 255 / 8);
        gSPDisplayList(D_8007A184++, D_803AA2F8);
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
            if (pl->unk14->unk24[hud_selected_element_index] < 50) {
                pl->unk14->unk24[hud_selected_element_index]++;
                if (pl->unk14->unk24[hud_selected_element_index] == 50) {
                    pl->unk8 |= hud_element_milestone_masks[hud_selected_element_index];
                    if ((pl->unk8 & 0xF000) == 0xF000) {
                        pl->unk8 |= 0x10000;
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
            D_8004DCA0 &= ~8;
            hud_element_allocation_flags ^= 1;
        }
    }
}


typedef struct {
    /* 0x00 */ char unk0[0x14];
    /* 0x14 */ Vec3f_216E0 unk14;
    /* 0x20 */ char unk20[0x84 - 0x20];
} Struct_8007ABF0;

extern s32 D_8007A9C0;
extern Struct_8007ABF0 D_8007ABF0[];

void Hud_DrawNpcTalkMarker(void) {
    s32 sx;
    s32 bob;
    Vec3f_216E0* p;
    u16 *angle = &hud_npc_marker_phase;

    p = &D_8007ABF0[D_8007A9C0 - 1].unk14;
    if (Camera_WorldToScreen(p->x, p->y + 14.0, p->z, &sx, &hud_npc_marker_screen_y)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA448);
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

    if (Camera_WorldToScreen(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA538);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 24, 30, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawChestMarker(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &hud_chest_text_marker_phases[0];

    if (Camera_WorldToScreen(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA4C0);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 0x10, 30, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawTextSpotMarker(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &hud_chest_text_marker_phases[1];

    if (Camera_WorldToScreen(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(D_8007A184++, D_803AA448);
        Hud_DrawClippedTextureRect(sx, sy - bob - 30, 0x40, 29, 0, 0, 0x400, 0x400);
    }
}


extern Gfx D_803AA5B0[];

void Hud_DrawMeleeTargetMarker(u16 arg0) {
    s32 sx;
    s32 sy;
    s32 bob;
    f32 y;
    Struct_8002373C* a;
    u16 *angle = &hud_melee_marker_phase;

    a = (Struct_8002373C*)D_8007B908[arg0].unk2C;
    if (a->unk64->unk0 == 1) {
        y = a->unk68->unk94;
    } else if (a->unk64->unk0 == 2) {
        y = a->unk4 + 350.0 * a->unk24;
    } else {
        y = a->unk4 + a->unk64->unk1C * a->unk24;
    }
    if (Camera_WorldToScreen(a->unk0, y, a->unk8, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(D_8007A184++, D_803AA5B0);
        Hud_DrawClippedTextureRect(sx - 4, sy - bob - 42, 24, 42, 0, 0, 0x400, 0x400);
    }
}

void Hud_DrawOutOfRangeIcon(void) {
    s32 sx;
    s32 sy;
    f32 y;
    f32 h;

    h = D_8007AA08.unk7C->unk1C * D_8007AA08.unk3C;
    y = D_8007AA08.unk1C + h;
    if (Camera_WorldToScreen(D_8007AA08.unk18, y, D_8007AA08.unk20, &sx, &sy) != 0) {
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
        Hud_DrawTextureTile(D_803A8728, sx - 0x17, sy - 0xF, 0x2E, 0xF, 0x51, 0x31, 0x400, 0x400);
    }
}

void Hud_StartActorStatusIndicator(Struct_8002373C* arg0, u16 mask, u16 idx, s16 val) {
    Struct_8002373C_68* s = arg0->unk68;
    u32 i;
    Struct_803AA6C4* e;
    f32 y;
    Struct_803AA690* fx;

    for (i = 0; i < 7; i++) {
        if (hud_actor_status_masks[i] & mask) {
            s->unk12[i] = idx;
            s->unk22[i] = val;
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((hud_actor_status_alt_masks[i] & mask) && s->unk44[i] == 0) {
            s->unk32[i] = val;
            e = &D_803AA6C4[idx];
            hud_rotated_vector_scratch.x = e->unk8;
            hud_rotated_vector_scratch.y = e->unkC;
            hud_rotated_vector_scratch.z = 1.0f;
            fx = &D_803AA690[e->unk0];
            if (arg0->unk64->unk0 == 1) {
                if (e->unk4 & 0x100) {
                    y = arg0->unk68->unk94;
                } else {
                    y = arg0->unk68->unk94 - arg0->unk64->unk18 * arg0->unk24;
                }
            } else if (e->unk4 & 0x100) {
                y = arg0->unk4 + arg0->unk64->unk1C * 0.5 * arg0->unk24;
            } else {
                y = arg0->unk4;
            }
            s->unk44[i] = Magic_CreateVisualEffect(e->unk2, e->unk4, arg0->unk0, y, arg0->unk8, 0.0f, fx, &hud_rotated_vector_scratch, arg0);
            return;
        }
    }
}

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
} Struct_803AA628;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x8 - 0x2];
    /* 0x08 */ u16 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Struct_80023930_fx;

extern Struct_803AA628 D_803AA628[];

void Hud_UpdateAndDrawActorStatusIndicators(Struct_8002373C* arg0) {
    Struct_8002373C_68* s = arg0->unk68;
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
    Struct_80023930_fx* fx;

    if (!(D_8004DCA0 & 0x800)) {
        if (arg0->unk64->unk0 == 1) {
            y = arg0->unk68->unk94;
        } else {
            y = arg0->unk4 + arg0->unk64->unk1C * arg0->unk24;
        }
        pad1 = pad2 = 0;
    vis = Camera_WorldToScreen(arg0->unk0, y, arg0->unk8, &sx, &sy);
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
        oy = 0;
        ox = 0;
        for (i = 0; i < 7; i++) {
            if (s->unk12[i] != 0) {
                e = &D_803AA628[s->unk12[i]];
                u = e->unk0;
                v = e->unk2;
                w = e->unk4;
                h = e->unk6;
                if (vis) {
                    Hud_DrawTextureTile(D_803A8728, sx + ox - (w >> 1), sy + oy - (h >> 1), w, h, u, v, 0x400, 0x400);
                }
                if (!(hud_actor_status_masks[i] & s->unk0)) {
                    s->unk12[i] = 0;
                } else if (s->unk22[i] > 0) {
                    if (--s->unk22[i] == 0) {
                        s->unk12[i] = 0;
                    }
                }
                ox += w >> 1;
                oy -= h >> 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->unk44[i] != 0) {
            fx = (Struct_80023930_fx*)arg0->unk68->unk44[i];
            fx->unkC = arg0->unk0;
            fx->unk14 = arg0->unk8;
            if (arg0->unk64->unk0 == 1) {
                if (fx->unk8 & 0x100) {
                    fx->unk10 = arg0->unk68->unk94;
                } else {
                    fx->unk10 = arg0->unk68->unk94 - arg0->unk64->unk18 * arg0->unk24;
                }
            } else if (fx->unk8 & 0x100) {
                fx->unk10 = arg0->unk4 + arg0->unk64->unk1C * 0.5 * arg0->unk24;
            } else {
                fx->unk10 = arg0->unk4;
            }
            if (!(hud_actor_status_alt_masks[i] & s->unk0)) {
                s->unk44[i] = 0;
                if (fx->unk8 & 1) {
                    fx->unk8 &= ~1;
                    fx->unk0 = 8;
                }
            } else if (s->unk32[i] > 0) {
                if (--s->unk32[i] == 0) {
                    s->unk44[i] = 0;
                    if (fx->unk8 & 1) {
                        fx->unk8 &= ~1;
                        fx->unk0 = 8;
                    }
                }
            }
        }
    }
}

void Hud_ClearActorStatusIndicators(Struct_8002373C* arg0) {
    Struct_8002373C_68* s = arg0->unk68;
    u32 i;
    Struct_80023930_fx* fx;

    for (i = 0; i < 7; i++) {
        if (s->unk12[i] != 0) {
            s->unk12[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->unk44[i] != 0) {
            fx = (Struct_80023930_fx*)s->unk44[i];
            fx->unk0 = 8;
            fx->unk8 &= ~1;
            s->unk44[i] = 0;
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

typedef struct {
    /* 0x00 */ char unk0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[2];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ char unk8[4];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ char unk10[0x26 - 0x10];
    /* 0x26 */ u16 unk26;
    /* 0x28 */ char unk28[2];
    /* 0x2A */ u16 unk2A;
} Struct_8007C028_28;

typedef struct {
    /* 0x00 */ char unk0[0x28];
    /* 0x28 */ Struct_8007C028_28* unk28;
    /* 0x2C */ char unk2C[0x98 - 0x2C];
    /* 0x98 */ u16 unk98;
} Struct_8007C028;

extern Struct_8007C028* D_8007C028;
extern u8** D_8007C04C;
extern u8 D_8039ADB0[];
extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A86F8;
extern Struct_80024A54 D_803A8718;
void Hud_DrawNumber(u16 arg0, s32 arg1, s32 arg2, s32 arg3);

void Hud_DrawEnemyInfoPanel(void) {
    s32 d;

    hud_draw_origin_x = 0xB5;
    hud_draw_origin_y = 0x1A;
    d = hud_battle_message_timer - 50;
    if (d > 0) {
        d *= d;
        hud_draw_origin_x += d * 120 / 100;
    }
    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    if (D_8007C028->unk98 & 0x80) {
        Hud_DrawTextureTile(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x10, 0x6E, 0x10, 0x64, 0x2C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x20, 0x6E, 0x10, 0x64, 0x3C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x30, 0x6E, 4, 0x64, 0x4C, 0x400, 0x400);
    } else {
        Hud_DrawTextureTile(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x10, 0x6E, 0xA, 0x64, 0x2C, 0x400, 0x400);
        Hud_DrawTextureTile(&D_803A8718, 0, 0x1A, 0x6E, 2, 0x64, 0x4E, 0x400, 0x400);
    }
    Hud_DrawGlyphString(4, 0x11, 0, D_8007C04C[D_8007C028->unk28->unk2]);
    Hud_LoadTextureTile(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039ADB0);
    if (D_8007C028->unk98 & 0x80) {
        Hud_DrawNumber(3, 0x10, 0x1C, D_8007C028->unk28->unk6);
        Hud_DrawNumber(3, 0x10, 0x26, D_8007C028->unk28->unkE);
        Hud_DrawNumber(3, 0x46, 0x1C, D_8007C028->unk28->unk2A);
        Hud_DrawNumber(3, 0x46, 0x26, D_8007C028->unk28->unkC);
        if (D_8007C028->unk28->unk26 != 4) {
            Hud_DrawTextureTile(&D_803A86F8, 0x5B, 3, 0xC, 0xC, D_8007C028->unk28->unk26 * 0xC + 0x20, 0x10, 0x400, 0x400);
        }
    }
}

void Hud_ResetPopups(void) {
    Struct_8008C058* p = hud_popup_slots;
    s32 i = 8;

    while (i > 0) {
        p->unk0 = 0;
        p++;
        i--;
    }
}

void Hud_ShowActorPopup(Struct_8002433C_arg* arg0) {
    Struct_8008C058* p = hud_popup_slots;
    s32 i = 7;

    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unk0 = 0x2D;
    p->unk4 = arg0;
    p->unk10 = 0.0f;
    p->unk8 = 0.0f;
    if (*arg0->unk64 == 0) {
        p->unkC = ((Struct_80024338_64*) arg0->unk64)->unk1C * arg0->unk24;
    } else if (*arg0->unk64 == 1) {
        p->unkC = arg0->unk68->unk94 - arg0->unk4;
    } else {
        p->unkC = arg0->unk24 * 600.0;
    }
    p->unk14 = 0x23;
    p->unk16 = 0x31;
    p->unk18 = 0x29;
    p->unk1A = 0xE;
}

void Hud_DrawPopups(void) {
    s32 i;
    Struct_8008C058* p;
    f32 x;
    f32 y;
    s32 sx;
    s32 sy;
    f32 z;

    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
    p = hud_popup_slots;
    i = 8;
    do {
        if (p->unk0 != 0) {
            x = p->unk8;
            y = p->unkC;
            z = p->unk10;
            if (p->unk4 != NULL) {
                x += ((Vec3f_216E0*) p->unk4)->x;
                y += ((Vec3f_216E0*) p->unk4)->y;
                z += ((Vec3f_216E0*) p->unk4)->z;
            }
            Camera_WorldToScreen(x, y, z, &sx, &sy);
            Hud_DrawTextureTile(D_803A8728, sx - (p->unk18 >> 1), sy - p->unk1A, p->unk18, p->unk1A, p->unk14, p->unk16, 0x400, 0x400);
            p->unk0--;
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
        str = hud_digit_glyph_data;
    }
    w = Hud_MeasureGlyphString(str);
    arg0 = arg0 - w / 2 + 0x37;
    Hud_DrawGlyphString(arg0, arg1, hud_number_spacing[flags], str);
}

void Hud_DrawGlyphString(s32 x, s32 y, s32 pal, u8* str) {
    s32 cur = 8;
    s32 col;
    s32 row;

    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_803A8778[pal]);
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

void Hud_LoadTextureTile(Struct_80024A54* tex, s32 x, s32 y, s32 w, s32 h) {
    if (tex->is4b == 0) {
        gDPLoadTextureTile(D_8007A184++, tex->img, G_IM_FMT_CI, G_IM_SIZ_8b, tex->width, 0, x, y, x + w, y + h, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    } else {
        gDPLoadTextureTile_4b(D_8007A184++, tex->img, G_IM_FMT_CI, tex->width, 0, x, y, x + w - 1, y + h - 1, 0,
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
    gSPTextureRectangle(D_8007A184++, x << 2, y << 2, x2 << 2, y2 << 2, 0, s << 5, t << 5, dsdx, dtdy);
}

void Hud_DrawTextureTile(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    Hud_LoadTextureTile(arg0, arg5, arg6, arg3, arg4);
    Hud_DrawClippedTextureRect(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/D_8006F530.s")

/* .data 8004F2C0..8004F4A0 */
s32 D_8004F2C0 = 0; /* nothing references it */
u8 hud_digit_glyph_data[8] = {
#include "assets/hud_digit_glyph_data.inc.c"
};
u8 hud_element_colors[4][4] = {
    { 0xFF, 0x00, 0x00, 0x00 },
    { 0xFF, 0xC8, 0x00, 0x00 },
    { 0x00, 0x00, 0xFF, 0x00 },
    { 0x00, 0xFF, 0x00, 0x00 },
};
u16 hud_actor_status_masks[8] = { 0x4, 0x1, 0x400, 0x20, 0x10, 0x80, 0x40, 0x0 };
u16 hud_actor_status_alt_masks[4] = { 0x8, 0x2, 0x200, 0x100 };
s32 hud_element_unlock_masks[4] = { 0x1000, 0x2000, 0x4000, 0x8000 };
Struct_8004F324 hud_spell_input_icon_positions[4] = { { 17.0f, 5.0f }, { 5.0f, 17.0f }, { 17.0f, 30.0f }, { 30.0f, 17.0f } };
Struct_8004F324 hud_element_icon_positions[4] = { { 30.0f, 35.0f }, { 12.0f, 51.0f }, { 30.0f, 66.0f }, { 48.0f, 51.0f } };
s32 hud_element_milestone_masks[4] = { 0x1000, 0x2000, 0x4000, 0x8000 };
s32 D_8004F354[77] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 2, 0, 0, 5 }; /* nothing references it */
u8 D_8004F488[0x10] = { /* message text, nothing references it */
#include "assets/D_8004F488.inc.c"
};
u8 hud_number_spacing[8] = { 0, 1, 2, 2, 2, 2, 2, 2 };
