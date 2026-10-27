#include "overlays/ending/ending_data.h"

/*
 * Ending overlay data: display lists, the sprite script and animation tables, images.
 * Original file: ovl_ending/E25C80.c (ROM 0xE25C80).
 */

/* ovl_ending .data 8020F6C0..8022BB00: display lists, credit scroll tables and images.
   A data-only file: E22690.c's .data ends at 8020F6B5 and this starts 16-aligned at 8020F6C0.
   The 8-byte Gfx after some tables and images is a gsSPEndDisplayList that follows them. */





Gfx ending_sprite_setup_dl[11] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xB6000000, 0xFFFFFFFF }},
    {{ 0xB7000000, 0x00000204 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xBA000903, 0x00000C00 }},
    {{ 0xBA001102, 0x00020000 }},
    {{ 0xB9000002, 0x0C087008 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xBA000C02, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx ending_sprite_default_combine_dl[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx ending_scroll_backdrop_combine_dl[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx ending_sprite_fade_combine_dl[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC129A25, 0xFF37FFFF }},
    {{ 0xB8000000, 0x00000000 }},
};
EndingAnimStep ending_sprite_anim_steps_0[3] = {
    { 0x00800010, 0, 0, 360 },
    { 0x00801000, 0, 0, 2280 },
    { 0x00800020, 0, 0, 360 },
};
EndingAnimStep ending_sprite_anim_steps_1[3] = {
    { 0x00008010, 0, 170, 120 },
    { 0x00008000, 0, -240, 2790 },
    { 0x00008020, 0, -262, 120 },
};
EndingAnimStep ending_sprite_anim_steps_2[4] = {
    { 0x00800010, 0, 0, 360 },
    { 0x00801000, 0, 0, 390 },
    { 0x00800020, 0, 0, 180 },
    { 0x10000000, 0, 0, 300 },
};
EndingAnimStep ending_sprite_anim_steps_3[3] = {
    { 0x00000010, 0, 0, 60 },
    { 0x00001000, 0, 0, 180 },
    { 0x00000020, 0, 0, 60 },
};
EndingAnimStep ending_sprite_anim_steps_4[3] = {
    { 0x00000010, 0, 0, 180 },
    { 0x00001000, 0, 0, 4680 },
    { 0x00000020, 0, 0, 180 },
};
EndingAnimStep ending_sprite_anim_steps_5[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 180 },
    { 0x00000020, 0, 0, 120 },
};
EndingAnimStep ending_sprite_anim_steps_6[3] = {
    { 0x00000010, 0, 0, 90 },
    { 0x00001000, 0, 0, 300 },
    { 0x00000020, 0, 0, 600 },
};
EndingAnimStep ending_sprite_anim_steps_7[2] = {
    { 0x00000010, 0, 0, 180 },
    { 0x00000020, 0, 0, 180 },
};
EndingAnim ending_sprite_anim_table[8] = {
    { (EndingAnimStep*) ending_sprite_anim_steps_0, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_1, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_2, 0x4 },
    { (EndingAnimStep*) ending_sprite_anim_steps_3, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_4, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_5, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_6, 0x3 },
    { (EndingAnimStep*) ending_sprite_anim_steps_7, 0x2 },
};
EndingSpriteCue ending_sprite_cues[97] = {
    { 0x0, 1, 0x08000000, 8, 30, 304, 6, 0, 0, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 36, 304, 6, 0, 6, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 42, 304, 6, 0, 12, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 48, 304, 6, 0, 18, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 54, 304, 6, 0, 24, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 60, 304, 6, 0, 30, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 66, 304, 6, 0, 36, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 72, 304, 6, 0, 42, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 78, 304, 6, 0, 48, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 84, 304, 6, 0, 54, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 90, 304, 6, 0, 60, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 96, 304, 6, 0, 66, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 102, 304, 6, 0, 72, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 108, 304, 6, 0, 78, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 114, 304, 6, 0, 84, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 120, 304, 6, 0, 90, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 126, 304, 6, 0, 96, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 132, 304, 6, 0, 102, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 138, 304, 6, 0, 108, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 144, 304, 6, 0, 114, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 150, 304, 6, 0, 120, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 156, 304, 6, 0, 126, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 162, 304, 6, 0, 132, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 168, 304, 6, 0, 138, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 174, 304, 6, 0, 144, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 180, 304, 6, 0, 150, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 186, 304, 6, 0, 156, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 192, 304, 6, 0, 162, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 198, 304, 6, 0, 168, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 204, 304, 6, 0, 174, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 210, 304, 6, 0, 180, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 216, 304, 6, 0, 186, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x0, 0, 0x08000000, 8, 222, 304, 6, 0, 192, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_first_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 360, 0x04000000, 27, 192, 267, 10, 0, 0, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 202, 267, 10, 0, 10, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 212, 267, 10, 0, 20, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 222, 267, 10, 0, 30, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 232, 267, 10, 0, 40, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 242, 267, 10, 0, 50, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 252, 267, 10, 0, 60, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 262, 267, 10, 0, 70, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 272, 267, 10, 0, 80, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 282, 267, 10, 0, 90, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 292, 267, 10, 0, 100, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 302, 267, 10, 0, 110, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 312, 267, 10, 0, 120, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 322, 267, 10, 0, 130, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 332, 267, 10, 0, 140, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 342, 267, 10, 0, 150, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 352, 267, 10, 0, 160, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 362, 267, 10, 0, 170, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 372, 267, 10, 0, 180, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 382, 267, 10, 0, 190, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 392, 267, 10, 0, 200, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 402, 267, 10, 0, 210, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 412, 267, 10, 0, 220, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 422, 267, 10, 0, 230, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 432, 267, 10, 0, 240, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 442, 267, 10, 0, 250, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 452, 267, 10, 0, 260, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 462, 267, 10, 0, 270, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 472, 267, 10, 0, 280, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 482, 267, 10, 0, 290, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x1, 0, 0x04000000, 27, 492, 267, 10, 0, 300, 267, 310, (s32) ending_sprite_anim_1_tex, (s32) ending_sprite_anim_1_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 2280, 0x08000000, 8, 30, 304, 6, 0, 0, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 36, 304, 6, 0, 6, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 42, 304, 6, 0, 12, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 48, 304, 6, 0, 18, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 54, 304, 6, 0, 24, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 60, 304, 6, 0, 30, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 66, 304, 6, 0, 36, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 72, 304, 6, 0, 42, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 78, 304, 6, 0, 48, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 84, 304, 6, 0, 54, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 90, 304, 6, 0, 60, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 96, 304, 6, 0, 66, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 102, 304, 6, 0, 72, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 108, 304, 6, 0, 78, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 114, 304, 6, 0, 84, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 120, 304, 6, 0, 90, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 126, 304, 6, 0, 96, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 132, 304, 6, 0, 102, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 138, 304, 6, 0, 108, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 144, 304, 6, 0, 114, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 150, 304, 6, 0, 120, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 156, 304, 6, 0, 126, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 162, 304, 6, 0, 132, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 168, 304, 6, 0, 138, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 174, 304, 6, 0, 144, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 180, 304, 6, 0, 150, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 186, 304, 6, 0, 156, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 192, 304, 6, 0, 162, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 198, 304, 6, 0, 168, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 204, 304, 6, 0, 174, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 210, 304, 6, 0, 180, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 216, 304, 6, 0, 186, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
    { 0x2, 0, 0x08000000, 8, 222, 304, 6, 0, 192, 304, 224, (s32) ending_scroll_backdrop_tex, (s32) ending_scroll_backdrop_second_tlut, 0, -1, 0x0, { 0 } },
};
Gfx D_802107E8_ovl_ending[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* D_802107F4_ovl_ending is ending_cue_groups + 0x4 */
EndingCueGroup ending_cue_groups[1] = {
    { (EndingSpriteCue*) ending_sprite_cues, 0x61 },
};
u32 ending_cue_group_count = 0x00000001;
/* not referenced by name */
u32 D_802107FC_ovl_ending[1] = { 0x00000008 };
u32 ending_picture_defs[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
/* palette, 256 colours */
u16 ending_scroll_backdrop_first_tlut[0x100] = {
#include "assets/ending_scroll_backdrop_first_tlut.inc.c"
};
/* texture */
u8 ending_scroll_backdrop_tex[0x10A00] = {
#include "assets/ending_scroll_backdrop_tex.inc.c"
};
/* palette, 256 colours */
u16 ending_scroll_backdrop_second_tlut[0x100] = {
#include "assets/ending_scroll_backdrop_second_tlut.inc.c"
};
Gfx D_80221610_ovl_ending[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 ending_sprite_anim_1_tex[0xA4B0] = {
#include "assets/ending_sprite_anim_1_tex.inc.c"
};
Gfx D_8022BAC8_ovl_ending[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 16 colours */
u16 ending_sprite_anim_1_tlut[0x10] = {
#include "assets/ending_sprite_anim_1_tlut.inc.c"
};
f32 D_8022BAF0_ovl_ending = 32767.0f;
f64 D_8022BAF8_ovl_ending = 10530.0;
