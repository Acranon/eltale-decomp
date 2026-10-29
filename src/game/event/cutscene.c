#include "game/event/cutscene.h"
#include "game/audio/audio.h"
#include "game/camera/camera.h"
#include "game/core/main.h"
#include "game/enemy/enemy.h"
#include "game/env/env.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/npc/npc.h"
#include "game/player/player.h"
#include "game/text/text_window.h"

/*
 * Cutscene scene sequencing, camera tracks, and timed image cue drawing.
 * Original file: 36E60.c (ROM 0x36E60).
 */



/* .bss 80092ED0..80092FF0 */
s32 cutscene_sequence_index;
s32 cutscene_camera_frame; /* current camera-track frame */
s32 cutscene_camera_end_frame;
KfAnim *cutscene_camera_track;
s32 cutscene_image_frame;
CutsceneImageCue *cutscene_next_image_cue;
CutsceneImageCueSlot cutscene_image_cue_slots[32];
/* This file's .data, 80061850..8006CD00: textures and palettes (assets; the
 * converter put a gsSPEndDisplayList word after most images), message text
 * (assets), the message pointer tables and layouts, flags and a display list. */
u16 text_window_tlut[0x100] = {
#include "assets/text_window_tlut.inc.c"
};
u8 text_window_fill_tex[0x100] = {
#include "assets/text_window_fill_tex.inc.c"
};
u8 text_speaker_name_bg_tex[0x208] = {
#include "assets/text_speaker_name_bg_tex.inc.c"
};
u8 text_advance_icon_tex[0x90] = {
#include "assets/text_advance_icon_tex.inc.c"
};
u8 text_window_line_tex[0x10] = {
#include "assets/text_window_line_tex.inc.c"
};
u8 text_choice_cursor_tex[0xA0] = {
#include "assets/text_choice_cursor_tex.inc.c"
};
u16 menu_sprite_tlut[0x104] = {
#include "assets/menu_sprite_tlut.inc.c"
};
u8 menu_sprite_00_tex[0x108] = {
#include "assets/menu_sprite_00_tex.inc.c"
};
u8 menu_sprite_01_tex[0xD8] = {
#include "assets/menu_sprite_01_tex.inc.c"
};
u8 menu_sprite_02_tex[0x10] = {
#include "assets/menu_sprite_02_tex.inc.c"
};
u8 menu_sprite_03_tex[0x10] = {
#include "assets/menu_sprite_03_tex.inc.c"
};
u8 menu_sprite_04_tex[0x98] = {
#include "assets/menu_sprite_04_tex.inc.c"
};
u8 menu_sprite_05_tex[0x48] = {
#include "assets/menu_sprite_05_tex.inc.c"
};
u8 menu_sprite_06_tex[0xB8] = {
#include "assets/menu_sprite_06_tex.inc.c"
};
u8 menu_sprite_07_tex[0xB8] = {
#include "assets/menu_sprite_07_tex.inc.c"
};
u8 menu_sprite_08_tex[0x10] = {
#include "assets/menu_sprite_08_tex.inc.c"
};
u8 menu_sprite_09_tex[0x10] = {
#include "assets/menu_sprite_09_tex.inc.c"
};
u8 menu_sprite_10_tex[0x58] = {
#include "assets/menu_sprite_10_tex.inc.c"
};
u8 menu_sprite_11_tex[0x58] = {
#include "assets/menu_sprite_11_tex.inc.c"
};
u8 menu_sprite_12_tex[0x58] = {
#include "assets/menu_sprite_12_tex.inc.c"
};
u8 menu_sprite_13_tex[0x58] = {
#include "assets/menu_sprite_13_tex.inc.c"
};
u8 menu_sprite_14_tex[0x58] = {
#include "assets/menu_sprite_14_tex.inc.c"
};
u8 menu_sprite_15_tex[0x58] = {
#include "assets/menu_sprite_15_tex.inc.c"
};
u8 menu_sprite_16_tex[0x58] = {
#include "assets/menu_sprite_16_tex.inc.c"
};
u8 menu_sprite_17_tex[0x58] = {
#include "assets/menu_sprite_17_tex.inc.c"
};
u8 menu_sprite_18_tex[0x58] = {
#include "assets/menu_sprite_18_tex.inc.c"
};
u8 menu_sprite_19_tex[0x58] = {
#include "assets/menu_sprite_19_tex.inc.c"
};
u8 menu_sprite_20_tex[0x58] = {
#include "assets/menu_sprite_20_tex.inc.c"
};
u8 menu_sprite_21_tex[0x58] = {
#include "assets/menu_sprite_21_tex.inc.c"
};
u8 menu_sprite_22_tex[0x58] = {
#include "assets/menu_sprite_22_tex.inc.c"
};
u8 menu_sprite_23_tex[0x58] = {
#include "assets/menu_sprite_23_tex.inc.c"
};
u8 menu_sprite_24_tex[0x58] = {
#include "assets/menu_sprite_24_tex.inc.c"
};
u8 menu_sprite_25_tex[0x58] = {
#include "assets/menu_sprite_25_tex.inc.c"
};
u8 menu_sprite_26_tex[0x438] = {
#include "assets/menu_sprite_26_tex.inc.c"
};
u8 menu_sprite_27_tex[0x170] = {
#include "assets/menu_sprite_27_tex.inc.c"
};
u8 menu_sprite_28_tex[0x178] = {
#include "assets/menu_sprite_28_tex.inc.c"
};
u8 menu_sprite_29_tex[0x228] = {
#include "assets/menu_sprite_29_tex.inc.c"
};
u8 menu_sprite_30_tex[0x1B0] = {
#include "assets/menu_sprite_30_tex.inc.c"
};
u8 menu_sprite_31_tex[0x10] = {
#include "assets/menu_sprite_31_tex.inc.c"
};
u8 menu_sprite_32_tex[0xE8] = {
#include "assets/menu_sprite_32_tex.inc.c"
};
u8 menu_sprite_33_tex[0x4C0] = {
#include "assets/menu_sprite_33_tex.inc.c"
};
u8 menu_sprite_34_tex[0x290] = {
#include "assets/menu_sprite_34_tex.inc.c"
};
u8 menu_sprite_35_tex[0x200] = {
#include "assets/menu_sprite_35_tex.inc.c"
};
u8 menu_sprite_36_tex[0x258] = {
#include "assets/menu_sprite_36_tex.inc.c"
};
u8 menu_sprite_37_tex[0xF8] = {
#include "assets/menu_sprite_37_tex.inc.c"
};
u8 menu_sprite_38_tex[0x60] = {
#include "assets/menu_sprite_38_tex.inc.c"
};
u8 menu_sprite_39_tex[0x60] = {
#include "assets/menu_sprite_39_tex.inc.c"
};
u8 menu_sprite_40_tex[0x60] = {
#include "assets/menu_sprite_40_tex.inc.c"
};
u8 menu_sprite_41_tex[0xF8] = {
#include "assets/menu_sprite_41_tex.inc.c"
};
u8 menu_sprite_42_tex[0xF8] = {
#include "assets/menu_sprite_42_tex.inc.c"
};
u8 menu_sprite_43_tex[0x3A8] = {
#include "assets/menu_sprite_43_tex.inc.c"
};
u8 menu_sprite_44_tex[0xC8] = {
#include "assets/menu_sprite_44_tex.inc.c"
};
u8 menu_sprite_45_tex[0x468] = {
#include "assets/menu_sprite_45_tex.inc.c"
};
u8 menu_sprite_46_tex[0x98] = {
#include "assets/menu_sprite_46_tex.inc.c"
};
u8 menu_sprite_47_tex[0x98] = {
#include "assets/menu_sprite_47_tex.inc.c"
};
u8 menu_sprite_48_tex[0x98] = {
#include "assets/menu_sprite_48_tex.inc.c"
};
u8 menu_sprite_49_tex[0x98] = {
#include "assets/menu_sprite_49_tex.inc.c"
};
u8 menu_sprite_50_tex[0x1E8] = {
#include "assets/menu_sprite_50_tex.inc.c"
};
u8 menu_sprite_51_tex[0xA8] = {
#include "assets/menu_sprite_51_tex.inc.c"
};
u8 menu_sprite_52_tex[0x10] = {
#include "assets/menu_sprite_52_tex.inc.c"
};
u8 menu_sprite_53_tex[0x10] = {
#include "assets/menu_sprite_53_tex.inc.c"
};
u8 menu_sprite_54_tex[0x178] = {
#include "assets/menu_sprite_54_tex.inc.c"
};
u8 menu_sprite_55_tex[0x18] = {
#include "assets/menu_sprite_55_tex.inc.c"
};
u8 menu_sprite_56_tex[0x18] = {
#include "assets/menu_sprite_56_tex.inc.c"
};
u8 menu_sprite_57_tex[0x18] = {
#include "assets/menu_sprite_57_tex.inc.c"
};
u8 menu_sprite_58_tex[0x18] = {
#include "assets/menu_sprite_58_tex.inc.c"
};
u8 menu_sprite_59_tex[0x18] = {
#include "assets/menu_sprite_59_tex.inc.c"
};
u8 menu_sprite_60_tex[0x18] = {
#include "assets/menu_sprite_60_tex.inc.c"
};
u8 menu_sprite_61_tex[0x18] = {
#include "assets/menu_sprite_61_tex.inc.c"
};
u8 menu_sprite_62_tex[0x10] = {
#include "assets/menu_sprite_62_tex.inc.c"
};
u8 menu_sprite_63_tex[0x138] = {
#include "assets/menu_sprite_63_tex.inc.c"
};
u8 menu_sprite_64_tex[0x10] = {
#include "assets/menu_sprite_64_tex.inc.c"
};
u8 menu_sprite_65_tex[0x10] = {
#include "assets/menu_sprite_65_tex.inc.c"
};
u8 menu_sprite_66_tex[0x5D8] = {
#include "assets/menu_sprite_66_tex.inc.c"
};
u8 menu_sprite_67_tex[0x190] = {
#include "assets/menu_sprite_67_tex.inc.c"
};
u8 menu_sprite_68_tex[0x190] = {
#include "assets/menu_sprite_68_tex.inc.c"
};
u8 menu_sprite_69_tex[0x178] = {
#include "assets/menu_sprite_69_tex.inc.c"
};
u8 menu_sprite_70_tex[0x120] = {
#include "assets/menu_sprite_70_tex.inc.c"
};
u8 menu_sprite_71_tex[0x158] = {
#include "assets/menu_sprite_71_tex.inc.c"
};
u8 menu_sprite_72_tex[0x58] = {
#include "assets/menu_sprite_72_tex.inc.c"
};
u8 menu_sprite_73_tex[0x58] = {
#include "assets/menu_sprite_73_tex.inc.c"
};
u8 menu_sprite_74_tex[0x58] = {
#include "assets/menu_sprite_74_tex.inc.c"
};
u8 menu_sprite_75_tex[0x58] = {
#include "assets/menu_sprite_75_tex.inc.c"
};
u8 menu_sprite_76_tex[0x58] = {
#include "assets/menu_sprite_76_tex.inc.c"
};
u8 menu_sprite_77_tex[0x58] = {
#include "assets/menu_sprite_77_tex.inc.c"
};
u8 menu_sprite_78_tex[0x58] = {
#include "assets/menu_sprite_78_tex.inc.c"
};
u8 menu_sprite_79_tex[0x58] = {
#include "assets/menu_sprite_79_tex.inc.c"
};
u8 menu_sprite_80_tex[0x58] = {
#include "assets/menu_sprite_80_tex.inc.c"
};
u8 menu_sprite_81_tex[0x58] = {
#include "assets/menu_sprite_81_tex.inc.c"
};
u8 menu_sprite_82_tex[0x58] = {
#include "assets/menu_sprite_82_tex.inc.c"
};
u8 menu_sprite_83_tex[0xC8] = {
#include "assets/menu_sprite_83_tex.inc.c"
};
u8 menu_sprite_84_tex[0xC8] = {
#include "assets/menu_sprite_84_tex.inc.c"
};
u8 menu_sprite_85_tex[0x10] = {
#include "assets/menu_sprite_85_tex.inc.c"
};
u8 menu_sprite_86_tex[0xF8] = {
#include "assets/menu_sprite_86_tex.inc.c"
};
u8 menu_sprite_87_tex[0x3A0] = {
#include "assets/menu_sprite_87_tex.inc.c"
};
u16 menu_bg_tlut[0x104] = {
#include "assets/menu_bg_tlut.inc.c"
};
u8 menu_bg_strip_tex_0[0x808] = {
#include "assets/menu_bg_strip_tex_0.inc.c"
};
u8 menu_bg_strip_tex_1[0x808] = {
#include "assets/menu_bg_strip_tex_1.inc.c"
};
u8 menu_bg_strip_tex_2[0x808] = {
#include "assets/menu_bg_strip_tex_2.inc.c"
};
u8 menu_bg_strip_tex_3[0x608] = {
#include "assets/menu_bg_strip_tex_3.inc.c"
};
u16 menu_exp_gauge_layer_0_tlut[0x104] = {
#include "assets/menu_exp_gauge_layer_0_tlut.inc.c"
};
u8 menu_exp_gauge_layer_0_0_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_0_0_tex.inc.c"
};
u8 menu_exp_gauge_layer_0_1_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_0_1_tex.inc.c"
};
u16 menu_exp_gauge_layer_3_tlut[0x104] = {
#include "assets/menu_exp_gauge_layer_3_tlut.inc.c"
};
u8 menu_exp_gauge_layer_3_0_tex[0x628] = {
#include "assets/menu_exp_gauge_layer_3_0_tex.inc.c"
};
u8 menu_exp_gauge_layer_3_1_tex[0x628] = {
#include "assets/menu_exp_gauge_layer_3_1_tex.inc.c"
};
u16 menu_exp_gauge_layer_1_tlut[0x104] = {
#include "assets/menu_exp_gauge_layer_1_tlut.inc.c"
};
u8 menu_exp_gauge_layer_1_0_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_1_0_tex.inc.c"
};
u8 menu_exp_gauge_layer_1_1_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_1_1_tex.inc.c"
};
u16 menu_exp_gauge_layer_2_tlut[0x104] = {
#include "assets/menu_exp_gauge_layer_2_tlut.inc.c"
};
u8 menu_exp_gauge_layer_2_0_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_2_0_tex.inc.c"
};
u8 menu_exp_gauge_layer_2_1_tex[0x4F0] = {
#include "assets/menu_exp_gauge_layer_2_1_tex.inc.c"
};
u8 save_menu_operation_panel_message_0[0x2C] = {
#include "assets/save_menu_operation_panel_message_0.inc.c"
};
u8 save_menu_operation_panel_message_1[0x20] = {
#include "assets/save_menu_operation_panel_message_1.inc.c"
};
u8 save_menu_operation_panel_message_2[0x1C] = {
#include "assets/save_menu_operation_panel_message_2.inc.c"
};
u8 save_menu_operation_panel_message_3[0x1C] = {
#include "assets/save_menu_operation_panel_message_3.inc.c"
};
u8 save_menu_operation_panel_message_4[0x28] = {
#include "assets/save_menu_operation_panel_message_4.inc.c"
};
u8 D_8006C16C[0x8] = {
#include "assets/D_8006C16C.inc.c"
};
u8 D_8006C174[0xC] = {
#include "assets/D_8006C174.inc.c"
};
u8 D_8006C180[0x8] = {
#include "assets/D_8006C180.inc.c"
};
u8 D_8006C188[0x8] = {
#include "assets/D_8006C188.inc.c"
};
u8 D_8006C190[0x2C] = {
#include "assets/D_8006C190.inc.c"
};
u8 D_8006C1BC[0x24] = {
#include "assets/D_8006C1BC.inc.c"
};
u8 D_8006C1E0[0x78] = {
#include "assets/D_8006C1E0.inc.c"
};
u8 D_8006C258[0x28] = {
#include "assets/D_8006C258.inc.c"
};
u8 D_8006C280[0x4C] = {
#include "assets/D_8006C280.inc.c"
};
u8 D_8006C2CC[0xA4] = {
#include "assets/D_8006C2CC.inc.c"
};
u8 D_8006C370[0x20] = {
#include "assets/D_8006C370.inc.c"
};
u8 D_8006C390[0x28] = {
#include "assets/D_8006C390.inc.c"
};
u8 D_8006C3B8[0x50] = {
#include "assets/D_8006C3B8.inc.c"
};
u8 D_8006C408[0x50] = {
#include "assets/D_8006C408.inc.c"
};
u8 D_8006C458[0x6C] = {
#include "assets/D_8006C458.inc.c"
};
u8 D_8006C4C4[0x4] = {
#include "assets/D_8006C4C4.inc.c"
};
u8 D_8006C4C8[0x44] = {
#include "assets/D_8006C4C8.inc.c"
};
u8 D_8006C50C[0x54] = {
#include "assets/D_8006C50C.inc.c"
};
u8 D_8006C560[0x4] = {
#include "assets/D_8006C560.inc.c"
};
u8 D_8006C564[0x94] = {
#include "assets/D_8006C564.inc.c"
};
u8 D_8006C5F8[0x44] = {
#include "assets/D_8006C5F8.inc.c"
};
u8 D_8006C63C[0x1C] = {
#include "assets/D_8006C63C.inc.c"
};
u8 D_8006C658[0x20] = {
#include "assets/D_8006C658.inc.c"
};
u8 D_8006C678[0x54] = {
#include "assets/D_8006C678.inc.c"
};
u8 D_8006C6CC[0x18C] = {
#include "assets/D_8006C6CC.inc.c"
};
u8 D_8006C858[0x28] = {
#include "assets/D_8006C858.inc.c"
};
u8 D_8006C880[0x78] = {
#include "assets/D_8006C880.inc.c"
};
u8 *save_menu_operation_panel_messages[5] = {
    save_menu_operation_panel_message_0, save_menu_operation_panel_message_1, save_menu_operation_panel_message_2, save_menu_operation_panel_message_3, save_menu_operation_panel_message_4,
};
s16 save_menu_operation_panel_rects[5][4] = {
    { 44, 107, 232, 25 }, { 79, 107, 162, 25 }, { 84, 107, 152, 25 }, { 84, 107, 152, 25 }, { 54, 107, 212, 25 },
};
u8 *save_menu_dialog_messages_save[25] = {
    D_8006C16C, D_8006C174, D_8006C180,
    D_8006C188, D_8006C190, D_8006C1BC, D_8006C1E0, D_8006C858, D_8006C280,
    D_8006C2CC, D_8006C2CC, D_8006C370, D_8006C390, D_8006C3B8, D_8006C408,
    D_8006C458, D_8006C4C4, D_8006C4C8, D_8006C50C, D_8006C560, D_8006C564,
    D_8006C5F8, D_8006C63C, D_8006C658, D_8006C6CC,
};
u8 *save_menu_dialog_messages_load_delete[25] = {
    D_8006C16C, D_8006C174, D_8006C180, D_8006C188, D_8006C190, D_8006C1BC,
    D_8006C880, D_8006C258, D_8006C280, D_8006C2CC, D_8006C2CC, D_8006C370,
    D_8006C390, D_8006C3B8, D_8006C408, D_8006C458, D_8006C4C4, D_8006C4C8,
    D_8006C678, D_8006C560, D_8006C564, D_8006C5F8, D_8006C63C, D_8006C658,
    D_8006C6CC,
};
s16 save_menu_dialog_rects[25][4] = {
    { 220, 160, 42, 38 }, { 220, 160, 42, 38 }, { 220, 160, 42, 38 }, { 220, 160, 42, 38 },
    { 44, 107, 232, 25 }, { 64, 107, 192, 25 }, { 54, 94, 212, 51 }, { 59, 107, 202, 25 },
    { 59, 101, 202, 38 }, { 49, 101, 222, 38 }, { 49, 101, 222, 38 }, { 79, 107, 162, 25 },
    { 54, 107, 212, 25 }, { 54, 101, 212, 38 }, { 34, 101, 252, 38 }, { 14, 101, 292, 38 },
    { 46, 89, 228, 62 }, { 64, 101, 192, 38 }, { 49, 101, 222, 38 }, { 49, 76, 228, 54 },
    { 49, 86, 222, 68 }, { 64, 101, 192, 38 }, { 84, 107, 152, 25 }, { 84, 107, 152, 25 },
    { 29, 37, 262, 166 },
};
s16 save_menu_choice_cursor_positions[4][2] = {
    { 258, 163 }, { 258, 176 }, { 258, 162 }, { 258, 175 },
};
u8 save_menu_slot_map_label_0[0x14] = {
#include "assets/save_menu_slot_map_label_0.inc.c"
};
u8 save_menu_slot_map_label_1[0x10] = {
#include "assets/save_menu_slot_map_label_1.inc.c"
};
u8 save_menu_slot_map_label_2[0x18] = {
#include "assets/save_menu_slot_map_label_2.inc.c"
};
u8 save_menu_slot_map_label_3[0x1C] = {
#include "assets/save_menu_slot_map_label_3.inc.c"
};
u8 save_menu_slot_map_label_4[0x14] = {
#include "assets/save_menu_slot_map_label_4.inc.c"
};
u8 save_menu_slot_map_label_5[0x14] = {
#include "assets/save_menu_slot_map_label_5.inc.c"
};
u8 save_menu_slot_map_label_6[0x14] = {
#include "assets/save_menu_slot_map_label_6.inc.c"
};
u8 save_menu_slot_map_label_7[0x20] = {
#include "assets/save_menu_slot_map_label_7.inc.c"
};
u8 save_menu_slot_map_label_8[0x14] = {
#include "assets/save_menu_slot_map_label_8.inc.c"
};
u8 save_menu_slot_map_label_9[0x10] = {
#include "assets/save_menu_slot_map_label_9.inc.c"
};
u8 save_menu_slot_map_label_10[0x14] = {
#include "assets/save_menu_slot_map_label_10.inc.c"
};
u8 save_menu_slot_map_label_11[0x18] = {
#include "assets/save_menu_slot_map_label_11.inc.c"
};
u8 save_menu_slot_map_label_12[0x14] = {
#include "assets/save_menu_slot_map_label_12.inc.c"
};
u8 save_menu_slot_map_label_13[0x10] = {
#include "assets/save_menu_slot_map_label_13.inc.c"
};
u8 save_menu_slot_map_label_14[0xC] = {
#include "assets/save_menu_slot_map_label_14.inc.c"
};
u8 save_menu_slot_map_label_15[0x10] = {
#include "assets/save_menu_slot_map_label_15.inc.c"
};
u8 save_menu_slot_map_label_16[0x10] = {
#include "assets/save_menu_slot_map_label_16.inc.c"
};
u8 *save_menu_slot_map_labels[19] = {
    save_menu_slot_map_label_0, save_menu_slot_map_label_1, save_menu_slot_map_label_2, save_menu_slot_map_label_3, save_menu_slot_map_label_4, save_menu_slot_map_label_5,
    save_menu_slot_map_label_6, save_menu_slot_map_label_7, save_menu_slot_map_label_8, save_menu_slot_map_label_9, save_menu_slot_map_label_10, save_menu_slot_map_label_11,
    save_menu_slot_map_label_12, save_menu_slot_map_label_13, save_menu_slot_map_label_14, save_menu_slot_map_label_15, save_menu_slot_map_label_16, NULL,
    NULL,
};
u8 D_8006CC74 = 0;
u8 intro_first_frame_skipped = 0;
u8 intro_pak_check_done = 0;
s8 D_8006CC80[0x10] = { 0 };
Gfx cutscene_image_setup_dl[14] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000004 }},
    {{ 0xBA000402, 0x00000030 }},
    {{ 0xB9000002, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xBA000C02, 0x00000000 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0x00000000, 0x00000000 }},
};
extern CutsceneSequenceEntry D_801D8620[];


void Cutscene_ResetSequence(void) {
    cutscene_sequence_index = 0;
    env_clock = 0x34BC;
}

void Cutscene_StartNextScene(void) {
    CutsceneSequenceEntry *e = &D_801D8620[cutscene_sequence_index++];
    s32 i;

    cutscene_camera_track = e->camera_track;
    cutscene_camera_frame = 0;
    cutscene_camera_end_frame = cutscene_camera_track->last;
    map_id = -1;
    map_next_id = e->map_id;
    map_next_subarea = e->subarea;
    Text_ResetAllWindows(0);
    text_active_window_count = 0;
    exit_destination.entry = -1;
    Map_LoadArea();
    if (e->flags & 1) {
        player_spawn_x = e->spawn_x;
        player_spawn_z = e->spawn_z;
        player_spawn_rot = e->spawn_rot;
        player_spawn_type = 0x108;
        player_stats.hp = player_stats.max_hp;
        player_state.unk6 = 0;
        Player_Spawn();
    } else {
        core_flags |= 0x10000;
    }
    Camera_InitForMap();
    camera_state.mode = 3;
    camera_fovy = 35.0f;
    Cutscene_ApplyCameraFrame(cutscene_camera_track, cutscene_camera_frame);
    npc_count = 0;
    enemy_count = 0;
    cutscene_image_frame = 0;
    cutscene_next_image_cue = e->image_cues;
    for (i = 0; i < 32; i++) {
        cutscene_image_cue_slots[i].remaining_frames = 0;
    }
}

void Cutscene_UpdateScene(void) {
    Cutscene_ApplyCameraFrame(cutscene_camera_track, cutscene_camera_frame++);
    if (cutscene_camera_end_frame - cutscene_camera_frame == 0x31) {
        if (!(core_flags & 0x80)) {
            core_flags |= 0x80;
            fade_transition_style = 2;
            if (cutscene_sequence_index >= 14) {
                core_transition_timer = 0x14E;
                core_fade_out_time = 0x14C;
                Audio_StartSeqFadeOut(0x12C);
            } else {
                core_transition_timer = 0x31;
                core_fade_out_time = 0x2F;
            }
        }
    }
}

void Cutscene_EndScene(void) {
    if (cutscene_sequence_index < 14) {
        core_flags |= 0x60;
    } else {
        core_game_mode = 0;
        core_flags |= 0x8240;
    }
}

void Cutscene_ApplyCameraFrame(KfAnim *arg0, s32 frame) {
    f32 buf[9];
    f32 m[4][4];

    if (arg0->last < frame) {
        frame = arg0->last;
    }
    Math_EvalTcbSpline(arg0, buf, frame);
    camera_state.eyeX = buf[0];
    camera_state.eyeY = buf[1];
    camera_state.eyeZ = buf[2];
    Math_MtxFRotate((MtxF *)m, -buf[4] * 0.0174532925199432955, -buf[3] * 0.0174532925199432955, buf[5] * 0.0174532925199432955);
    Math_MtxFMulVecNegZ((MtxF *)m, 0.0f, 0.0f, -100.0f, &camera_state.atX, &camera_state.atY, &camera_state.atZ);
    camera_state.atX += camera_state.eyeX;
    camera_state.atY += camera_state.eyeY;
    camera_state.atZ = camera_state.eyeZ - camera_state.atZ;
}

void Cutscene_UpdateAndDrawImageCues(void) {
    CutsceneImageCue *cue;
    CutsceneImageCueSlot *slot;
    s32 n;
    s32 a;
    u16 d;
    s32 xr;
    s32 t;

    n = 31;
    slot = cutscene_image_cue_slots;
    if (cutscene_image_frame == cutscene_next_image_cue->frame) {
        do {
            while (n != 0 && slot->remaining_frames != 0) {
                n--;
                slot++;
            }
            cutscene_next_image_cue->tlut[0] = 0;
            slot->remaining_frames = cutscene_next_image_cue->dur;
            slot->cue = cutscene_next_image_cue;
            cutscene_next_image_cue++;
        } while (cutscene_image_frame == cutscene_next_image_cue->frame);
    }
    slot = cutscene_image_cue_slots;
    gSPDisplayList(gfx_dl_head++, cutscene_image_setup_dl);
    for (n = 32; n != 0; slot++) {
        n--;
        d = slot->remaining_frames;
        if (slot->remaining_frames) {
            cue = slot->cue;
            if (d < 16) {
                a = d * 16;
            } else {
                t = cue->dur - d;
                if (t < 32) {
                    a = t * 8;
                } else {
                    a = 0xFF;
                }
            }
            gDPLoadTextureTile_4b(gfx_dl_head++, cue->img, G_IM_FMT_CI, (cue->w + 15) & ~15, cue->h, 0, 0, cue->w - 1, cue->h - 1, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, cue->tlut);
            gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, a);
            xr = (cue->x + cue->w) & ~1;
            gSPTextureRectangle(gfx_dl_head++, cue->x << 2, cue->y << 2, xr << 2, (cue->y + cue->h) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            slot->remaining_frames--;
        }
    }
    cutscene_image_frame++;
}
