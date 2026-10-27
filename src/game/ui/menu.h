#ifndef GAME_UI_MENU_H
#define GAME_UI_MENU_H

#include "common.h"
#include "game/actor/actor.h"
#include "game/enemy/enemy.h"
#include "game/map/map.h"

typedef struct MenuPictureDma {
    /* 0x00 */ void *dst;
    /* 0x04 */ u32 start;
    /* 0x08 */ u32 end;
} MenuPictureDma; /* 0xC bytes */

typedef struct MenuRomRange {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
} MenuRomRange; /* 0x8 bytes */

typedef struct SaveSpawnPoint {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 rot;
} SaveSpawnPoint; /* 0x10 bytes */

typedef struct EnemyEffectDef {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} EnemyEffectDef; /* 0x10 bytes */

typedef struct MapObjAnimDef {
    /* 0x00 */ void *keys;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 frames;
    /* 0x08 */ s32 pad[6];
} MapObjAnimDef; /* 0x20 bytes */

typedef struct MenuMapLocation {
    /* 0x00 */ s8 a;
    /* 0x01 */ s8 b;
} MenuMapLocation; /* 0x2 bytes */

typedef struct MenuExpGaugePalettes { /* 0x00 */ u16 *v[4]; } MenuExpGaugePalettes; /* 0x10 bytes */
typedef struct MenuExpGaugeTextures { /* 0x00 */ u8 *v[4][2]; } MenuExpGaugeTextures; /* 0x20 bytes */
typedef struct MenuFourWords { /* 0x00 */ s32 v[4]; } MenuFourWords; /* 0x10 bytes */
typedef struct MenuFourPointers { /* 0x00 */ u8 *v[4]; } MenuFourPointers; /* 0x10 bytes */

extern s32 menu_slide_right_x;
extern s32 menu_slide_left_x;
extern s32 menu_slide_timer;
extern u16 menu_map_cursor_active;
extern u16 menu_flags;
extern s8 menu_save_loaded;
extern s32 menu_frame_counter;
extern f32 menu_map_marker_x;
extern f32 menu_map_marker_z;
extern s32 menu_map_region;
extern s32 menu_map_spot;
#ifndef NON_MATCHING
extern s32 menu_options_marker_x;
#endif
extern f32 menu_map_cursor_saved_x;
extern f32 menu_map_cursor_saved_y;
extern void *player_char_data[1];
extern ActorStats player_default_stats;
extern u32 player_level_exp_table[100];
extern u16 player_stat_xp_costs[70];
extern MenuRomRange player_anim_rom_ranges[30];
extern SaveSpawnPoint player_save_spawn_points[17];
extern u32 D_80056198[2];
extern EnemyAreaSet enemy_area_sets[6];
extern EnemyScriptCmd enemy_attack_script_0[6];
extern EnemyScriptCmd enemy_attack_script_1[1];
extern EnemyScriptCmd enemy_attack_script_2[5];
extern EnemyScriptCmd enemy_attack_script_3[1];
extern EnemyScriptCmd enemy_attack_script_5[6];
extern EnemyScriptCmd enemy_attack_script_7[1];
extern EnemyScriptCmd enemy_attack_script_8[5];
extern EnemyScriptCmd enemy_attack_script_10[6];
extern EnemyScriptCmd enemy_attack_script_11[4];
extern EnemyScriptCmd enemy_attack_script_12[4];
extern EnemyScriptCmd enemy_attack_script_13[5];
extern EnemyScriptCmd enemy_attack_script_14[2];
extern EnemyScriptCmd enemy_attack_script_16[4];
extern EnemyScriptCmd *enemy_attack_scripts[20];
extern EnemyEffectDef enemy_effect_defs[22];
extern s32 D_80056878[2];
extern MenuRomRange npc_area_set_rom_ranges[7];
extern u8 npc_area_entry_message[0x2F8];
extern MapAreaDef map_area_defs[36];
extern MapRomRange map_extra_rom_ranges[6];
extern u32 mapobj_cell_single;
extern s8 mapobj_cell_disc_r7[158][2];
extern s8 mapobj_cell_disc_r5[90][2];
extern s8 mapobj_cell_square_3x3[10][2];
extern s8 mapobj_cell_disc_r2[22][2];
extern u32 mapobjanim_type23_keys[0x8F];
extern MapObjAnimDef mapobjanim_type23_anim;
extern u32 D_80057A18[0xC3];
extern MapObjAnimDef D_80057D24;
extern u32 mapobjanim_type23_odd_keys[0x8F];
extern MapObjAnimDef mapobjanim_type23_odd_anim;
extern u32 mapobjanim_type4_keys[0x1A];
extern MapObjAnimDef mapobjanim_type4_anim;
extern u32 mapobj_loop_anim0_keys[0x27];
extern u32 mapobj_loop_anim1_keys[0x34];
extern u32 mapobj_loop_anim2_keys[0x41];
extern u32 mapobj_loop_anim3_keys[0x41];
extern MapObjAnimDef mapobj_loop_anims[4];
extern u16 mapobj_kind11_tlut[0x200];
extern u8 mapobj_kind11_tex_0[0x600];
extern u8 mapobj_kind11_tex_1[0x600];
extern u8 mapobj_kind11_tex_2[0x600];
extern u8 mapobj_kind11_tex_3[0x600];
extern u8 mapobj_kind11_tex_4[0x600];
extern u8 mapobj_kind11_tex_5[0x600];
extern u8 mapobj_kind11_tex_6[0x600];
extern u8 mapobj_kind11_tex_7[0x200];
extern u16 mapobj_kind12_tlut[0x200];
extern u8 mapobj_kind12_tex_0[0x600];
extern u8 mapobj_kind12_tex_1[0x600];
extern u8 mapobj_kind12_tex_2[0x600];
extern u8 mapobj_kind12_tex_3[0x600];
extern u8 mapobj_kind12_tex_4[0x600];
extern u8 mapobj_kind12_tex_5[0x600];
extern u8 mapobj_kind12_tex_6[0x600];
extern u8 mapobj_kind12_tex_7[0x200];
extern Vtx mapobj_kind11_vtx[4];
extern Vtx mapobj_kind12_vtx[4];
extern Gfx mapobj_kind11_setup_dl[13];
extern Gfx mapobj_kind12_setup_dl[13];
extern Gfx mapobj_kind11_quad_dl[3];
extern Gfx mapobj_kind12_quad_dl[3];
extern u8 **mapobj_animtex_frame_tables[2];
extern MapDlPair mapobj_animtex_dls[2];
extern u8 *mapobj_kind11_frames[8];
extern u8 *mapobj_kind12_frames[8];
extern u16 mapobj_arc_sprite_tlut[0x200];
extern u8 mapobj_arc_sprite_tex[0x2000];
extern Vtx mapobj_arc_sprite_vtx[4];
extern Gfx mapobj_arc_sprite_dl[16];
extern u8 mapobj_drop_sprite_tex[0x100];
extern Vtx mapobj_drop_sprite_vtx[4];
extern Gfx mapobj_drop_sprite_dl[10];
extern MapBackdropDef map_backdrop_defs[8];
extern u8 mapobj_translucent_alpha[40];
extern s8 menu_bgm_volume_option;
extern u8 menu_sprite_sizes[88][2];
extern s8 menu_wobble_offsets[16];
extern u8 *menu_sprite_tex[89];
extern Gfx menu_sprite_opaque_dl[3];
extern Gfx menu_sprite_alpha_dl[7];
extern f32 menu_map_cursor_x;
extern f32 menu_map_cursor_y;
extern MenuMapLocation menu_map_location_list[298];
extern s16 menu_map_spot_coords[108];
extern void *menu_map_tluts[6];
extern void *menu_map_strips[144];
extern s16 menu_map_world_scale[12];
extern s16 menu_map_origin[12];
extern MenuPictureDma menu_map_picture_dma[10];
extern void *menu_map_small_tluts[4];
extern void *menu_map_small_tex[8];
extern u8 menu_map_small_sizes[4][3];
extern s16 menu_map_small_pos[8];
extern u8 menu_options_marker_sprites[4];
extern s16 menu_options_top_row_pos[8][2];
extern s16 menu_options_bgm_row_pos[5][2];
extern s32 menu_map_loaded_region;
extern MenuExpGaugePalettes menu_exp_gauge_tluts;
extern MenuExpGaugeTextures menu_exp_gauge_tex;
extern MenuFourWords menu_bg_strip_tex_heights;
extern MenuFourWords menu_bg_strip_heights;
extern MenuFourPointers menu_bg_strip_tex;

void Menu_Init(void);
void Menu_ResetKeepPage(void);
void Menu_Update(s32 arg0);
void Menu_UpdatePageSlide(void);
void Menu_UpdateStatsPage(s32 x);
void Menu_UpdateOptionsPage(s32 x);
void Menu_UpdateMapPage(s32 arg0);
void Menu_UpdateElementsPage(s32 x);
void Menu_DrawSprite(s32 id, s32 x, s32 y, s32 w, s32 h);
void Menu_DrawExpGauge(s32 arg0, s32 arg1);
void Menu_DrawBackground(void);
void Menu_DrawNumber(s32 ndigits, s32 x, s32 y, u32 value, s32 pal);
void Menu_DrawNumberZeroPad(s32 ndigits, s32 x, s32 y, u32 value, s32 pal);
void Menu_PrintNumber(s32 ndigits, s32 x, s32 y, u32 value);
void Menu_FindMapPageLocation(void);

#endif
