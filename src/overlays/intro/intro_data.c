#include "overlays/intro/intro_data.h"

/*
 * Intro overlay data: display lists, the sprite script and animation tables, images.
 * Original file: ovl_intro/DCC450.c (ROM 0xDCC450).
 */

/* ovl_intro .data 80212270..80268480: display lists, the sprite animation and layout tables,
   then the images and palettes. A data-only file, like ovl_title's DAEA30.c and ovl_ending's
   E25C80.c (the ROM can't tell it apart from DC9350.c's tail here). The 8-byte Gfx after
   many images is a gsSPEndDisplayList that follows each converted texture. */





Gfx intro_render_setup_dl[11] = {
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
Gfx D_802122C8_ovl_intro[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_802122E0_ovl_intro[4] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC129A25, 0xFF37FFFF }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0x00000000, 0x00000000 }},
};
IntroAnimStep intro_sprite_anim_steps_0[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 120, 480 },
    { 0x00800020, 0, 0, 90 },
};
IntroAnimStep intro_sprite_anim_steps_1[4] = {
    { 0x10800000, 0, 0, 456 },
    { 0x00800010, 0, 0, 90 },
    { 0x00801000, 0, 0, 435 },
    { 0x00800020, 0, 0, 150 },
};
IntroAnimStep intro_sprite_anim_steps_2[3] = {
    { 0x00000010, 0, 0, 90 },
    { 0x00001000, 0, 0, 840 },
    { 0x00000020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_3[4] = {
    { 0x20000010, 0, 0, 120 },
    { 0x00008000, 0, 63, 30 },
    { 0x00001000, 0, 0, 675 },
    { 0x00000020, 0, 0, 150 },
};
IntroAnimStep intro_sprite_anim_steps_4[2] = {
    { 0x00800010, 0, 0, 90 },
    { 0x00800020, 0, 0, 90 },
};
IntroAnimStep intro_sprite_anim_steps_5[1] = {
    { 0x00001000, 0, 0, 390 },
};
IntroAnimStep intro_sprite_anim_steps_6[3] = {
    { 0x00000010, 0, 0, 138 },
    { 0x00001000, 0, 0, 4680 },
    { 0x00000020, 0, 0, 318 },
};
IntroAnimStep intro_sprite_anim_steps_7[3] = {
    { 0x00800010, 0, 0, 138 },
    { 0x00801000, 0, 0, 1128 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_8[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 618 },
    { 0x00000020, 0, 0, 120 },
};
IntroAnimStep intro_sprite_anim_steps_33[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 225 },
    { 0x00000020, 0, 0, 105 },
};
IntroAnimStep intro_sprite_anim_steps_9[3] = {
    { 0x00000010, 0, 0, 78 },
    { 0x00001000, 0, 0, 156 },
    { 0x00000020, 0, 0, 78 },
};
IntroAnimStep intro_sprite_anim_steps_10[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 0, 654 },
    { 0x00800020, 0, 0, 90 },
};
IntroAnimStep intro_sprite_anim_steps_11[4] = {
    { 0x00004010, 115, 0, 60 },
    { 0x00004000, 190, 0, 120 },
    { 0x00001000, 0, 0, 396 },
    { 0x00000020, 0, 0, 72 },
};
IntroAnimStep intro_sprite_anim_steps_12[3] = {
    { 0x00000010, 0, 0, 90 },
    { 0x00001000, 0, 0, 300 },
    { 0x00000020, 0, 0, 108 },
};
IntroAnimStep intro_sprite_anim_steps_13[3] = {
    { 0x00800010, 0, 0, 90 },
    { 0x00801000, 0, 0, 264 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_14[3] = {
    { 0x00000010, 0, 0, 78 },
    { 0x00001000, 0, 0, 150 },
    { 0x00000020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_15[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 0, 660 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_16[4] = {
    { 0x00004010, 97, 0, 60 },
    { 0x00004000, 22, 0, 120 },
    { 0x00001000, 0, 0, 396 },
    { 0x00000020, 0, 0, 90 },
};
IntroAnimStep intro_sprite_anim_steps_17[3] = {
    { 0x00000010, 0, 0, 90 },
    { 0x00001000, 0, 0, 276 },
    { 0x00000020, 0, 0, 102 },
};
IntroAnimStep intro_sprite_anim_steps_18[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 0, 294 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_19[3] = {
    { 0x00000010, 0, 0, 90 },
    { 0x00001000, 0, 0, 150 },
    { 0x00000020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_20[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 0, 660 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_21[4] = {
    { 0x00004010, 115, 0, 72 },
    { 0x00004000, 190, 0, 120 },
    { 0x00001000, 0, 0, 396 },
    { 0x00000020, 0, 0, 90 },
};
IntroAnimStep intro_sprite_anim_steps_22[3] = {
    { 0x00000010, 0, 0, 96 },
    { 0x00001000, 0, 0, 276 },
    { 0x00000020, 0, 0, 108 },
};
IntroAnimStep intro_sprite_anim_steps_23[3] = {
    { 0x00800010, 0, 0, 60 },
    { 0x00801000, 0, 0, 642 },
    { 0x00800020, 0, 0, 318 },
};
IntroAnimStep intro_sprite_anim_steps_24[4] = {
    { 0x10800000, 0, 0, 690 },
    { 0x00800010, 0, 0, 324 },
    { 0x00801000, 0, 0, 972 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_25[1] = {
    { 0x00001000, 0, 0, 882 },
};
IntroAnimStep intro_sprite_anim_steps_26[3] = {
    { 0x10000000, 0, 0, 599 },
    { 0x00800010, 0, 0, 150 },
    { 0x00000820, -52, -78, 360 },
};
IntroAnimStep intro_sprite_anim_steps_27[3] = {
    { 0x10000000, 0, 0, 598 },
    { 0x00800010, 0, 0, 149 },
    { 0x00000820, 198, -78, 360 },
};
IntroAnimStep intro_sprite_anim_steps_28[3] = {
    { 0x10000000, 0, 0, 597 },
    { 0x00800010, 0, 0, 148 },
    { 0x00008020, 0, 172, 360 },
};
IntroAnimStep intro_sprite_anim_steps_29[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 306 },
    { 0x00000020, 0, 0, 120 },
};
IntroAnimStep intro_sprite_anim_steps_34[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 306 },
    { 0x00000020, 0, 0, 120 },
};
IntroAnimStep intro_sprite_anim_steps_30[3] = {
    { 0x00800010, 0, 0, 30 },
    { 0x00801000, 0, 0, 120 },
    { 0x00800020, 0, 0, 60 },
};
IntroAnimStep intro_sprite_anim_steps_31[2] = {
    { 0x00000010, 0, 0, 60 },
    { 0x00000020, 0, 0, 30 },
};
IntroAnimStep intro_sprite_anim_steps_32[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 426 },
    { 0x00000020, 0, 0, 120 },
};
IntroAnimStep intro_sprite_anim_steps_35[3] = {
    { 0x00000010, 0, 0, 120 },
    { 0x00001000, 0, 0, 306 },
    { 0x00000020, 0, 0, 120 },
};
IntroAnim intro_sprite_anim_table[36] = {
    { (IntroAnimStep*) intro_sprite_anim_steps_0, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_1, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_2, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_3, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_4, 0x2 },
    { (IntroAnimStep*) intro_sprite_anim_steps_5, 0x1 },
    { (IntroAnimStep*) intro_sprite_anim_steps_6, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_7, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_8, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_9, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_10, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_11, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_12, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_13, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_14, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_15, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_16, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_17, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_18, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_19, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_20, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_21, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_22, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_23, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_24, 0x4 },
    { (IntroAnimStep*) intro_sprite_anim_steps_25, 0x1 },
    { (IntroAnimStep*) intro_sprite_anim_steps_26, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_27, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_28, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_29, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_30, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_31, 0x2 },
    { (IntroAnimStep*) intro_sprite_anim_steps_32, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_33, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_34, 0x3 },
    { (IntroAnimStep*) intro_sprite_anim_steps_35, 0x3 },
};
IntroSpriteCue intro_sprite_cues[459] = {
    { 0x0, 0, 0x08000000, 8, 0, 304, 6, 0, 0, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 6, 304, 6, 0, 6, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 12, 304, 6, 0, 12, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 18, 304, 6, 0, 18, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 24, 304, 6, 0, 24, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 30, 304, 6, 0, 30, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 36, 304, 6, 0, 36, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 42, 304, 6, 0, 42, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 48, 304, 6, 0, 48, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 54, 304, 6, 0, 54, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 60, 304, 6, 0, 60, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 66, 304, 6, 0, 66, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 72, 304, 6, 0, 72, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 78, 304, 6, 0, 78, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 84, 304, 6, 0, 84, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 90, 304, 6, 0, 90, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 96, 304, 6, 0, 96, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 102, 304, 6, 0, 102, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 108, 304, 6, 0, 108, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 114, 304, 6, 0, 114, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 120, 304, 6, 0, 120, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 126, 304, 6, 0, 126, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 132, 304, 6, 0, 132, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 138, 304, 6, 0, 138, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 144, 304, 6, 0, 144, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 150, 304, 6, 0, 150, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 156, 304, 6, 0, 156, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 162, 304, 6, 0, 162, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 168, 304, 6, 0, 168, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 174, 304, 6, 0, 174, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 180, 304, 6, 0, 180, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 186, 304, 6, 0, 186, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 192, 304, 6, 0, 192, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 198, 304, 6, 0, 198, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 204, 304, 6, 0, 204, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 210, 304, 6, 0, 210, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 216, 304, 6, 0, 216, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x0, 0, 0x08000000, 8, 222, 304, 2, 0, 222, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) intro_sprite_anim_0_tlut, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 0, 304, 6, 0, 0, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 6, 304, 6, 0, 6, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 12, 304, 6, 0, 12, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 18, 304, 6, 0, 18, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 24, 304, 6, 0, 24, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 30, 304, 6, 0, 30, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 36, 304, 6, 0, 36, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 42, 304, 6, 0, 42, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 48, 304, 6, 0, 48, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 54, 304, 6, 0, 54, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 60, 304, 6, 0, 60, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 66, 304, 6, 0, 66, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 72, 304, 6, 0, 72, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 78, 304, 6, 0, 78, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 84, 304, 6, 0, 84, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 90, 304, 6, 0, 90, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 96, 304, 6, 0, 96, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 102, 304, 6, 0, 102, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 108, 304, 6, 0, 108, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 114, 304, 6, 0, 114, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 120, 304, 6, 0, 120, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 126, 304, 6, 0, 126, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 132, 304, 6, 0, 132, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 138, 304, 6, 0, 138, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 144, 304, 6, 0, 144, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 150, 304, 6, 0, 150, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 156, 304, 6, 0, 156, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 162, 304, 6, 0, 162, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 168, 304, 6, 0, 168, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 174, 304, 6, 0, 174, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 180, 304, 6, 0, 180, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 186, 304, 6, 0, 186, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 192, 304, 6, 0, 192, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 198, 304, 6, 0, 198, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 204, 304, 6, 0, 204, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 210, 304, 6, 0, 210, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 216, 304, 6, 0, 216, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1, 0, 0x08000000, 8, 222, 304, 2, 0, 222, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x3, 156, 0x08000000, 63, 85, 15, 76, 0, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 78, 85, 15, 76, 15, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 93, 85, 15, 76, 30, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 108, 85, 15, 76, 45, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 123, 85, 15, 76, 60, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 138, 85, 15, 76, 75, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 153, 85, 15, 76, 90, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 168, 85, 15, 76, 105, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 183, 85, 15, 76, 120, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 198, 85, 15, 76, 135, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 213, 85, 15, 76, 150, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 228, 85, 15, 76, 165, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x3, 0, 0x08000000, 243, 85, 14, 76, 180, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x4, 120, 0x04000000, 209, 24, 63, 21, 0, 0, 64, 64, (s32) intro_sprite_anim_4_tex, (s32) intro_sprite_anim_4_tlut, 0, -1, 0x0 },
    { 0x4, 0, 0x04000000, 209, 45, 63, 21, 0, 21, 64, 64, (s32) intro_sprite_anim_4_tex, (s32) intro_sprite_anim_4_tlut, 0, -1, 0x0 },
    { 0x4, 0, 0x04000000, 209, 66, 63, 21, 0, 42, 64, 64, (s32) intro_sprite_anim_4_tex, (s32) intro_sprite_anim_4_tlut, 0, -1, 0x0 },
    { 0x6, 840, 0x04000000, 40, 17, 10, 190, 0, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 50, 17, 10, 190, 10, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 60, 17, 10, 190, 20, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 70, 17, 10, 190, 30, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 80, 17, 6, 190, 40, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 27, 149, 10, 0, 0, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 37, 149, 10, 0, 10, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 47, 149, 4, 0, 20, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04020000, 234, 17, 6, 190, 40, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04020000, 240, 17, 10, 190, 30, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04020000, 250, 17, 10, 190, 20, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04020000, 260, 17, 10, 190, 10, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04020000, 270, 17, 10, 190, 0, 0, 48, 190, (s32) intro_sprite_anim_6_variant0_tex, (s32) intro_sprite_anim_6_variant0_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 173, 149, 10, 0, 0, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 183, 149, 10, 0, 10, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x6, 0, 0x04000000, 86, 193, 149, 4, 0, 20, 160, 24, (s32) intro_sprite_anim_6_variant1_tex, (s32) intro_sprite_anim_6_variant1_tlut, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x7, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x8, 137, 0x04000000, 63, 63, 194, 10, 0, 0, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 73, 194, 10, 0, 10, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 83, 194, 10, 0, 20, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 93, 194, 10, 0, 30, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 103, 194, 10, 0, 40, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 113, 194, 10, 0, 50, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 123, 194, 10, 0, 60, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 133, 194, 10, 0, 70, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 143, 194, 10, 0, 80, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 153, 194, 10, 0, 90, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 163, 194, 10, 0, 100, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x8, 0, 0x04000000, 63, 173, 194, 4, 0, 110, 208, 114, (s32) intro_sprite_anim_8_tex, (s32) intro_sprite_anim_8_tlut, 0, -1, 0x0 },
    { 0x9, 858, 0x08000000, 192, 57, 30, 30, 0, 0, 30, 30, (s32) D_8022CFA0_ovl_intro, (s32) D_8022CDA0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 270, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xA, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0xB, 90, 0x08000000, 78, 44, 109, 17, 0, 0, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 61, 109, 17, 0, 17, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 78, 109, 17, 0, 34, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 95, 109, 17, 0, 51, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 112, 109, 17, 0, 68, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 129, 109, 17, 0, 85, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 146, 109, 17, 0, 102, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 163, 109, 17, 0, 119, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 180, 109, 17, 0, 136, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 197, 109, 17, 0, 153, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xB, 0, 0x08000000, 78, 214, 109, 9, 0, 170, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0xC, 108, 0x04000000, 82, 71, 156, 10, 0, 0, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 81, 156, 10, 0, 10, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 91, 156, 10, 0, 20, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 101, 156, 10, 0, 30, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 111, 156, 10, 0, 40, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 121, 156, 10, 0, 50, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 131, 156, 10, 0, 60, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 141, 156, 10, 0, 70, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 151, 156, 10, 0, 80, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xC, 0, 0x04000000, 82, 161, 156, 9, 0, 90, 160, 99, (s32) intro_sprite_anim_12_tex, (s32) intro_sprite_anim_12_tlut, 0, -1, 0x0 },
    { 0xD, 480, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xD, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0xE, 138, 0x08000000, 186, 103, 30, 30, 0, 0, 30, 30, (s32) D_8022CFA0_ovl_intro, (s32) D_8022CDA0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 234, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0xF, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x10, 120, 0x08020000, 134, 44, 109, 17, 0, 0, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 61, 109, 17, 0, 17, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 78, 109, 17, 0, 34, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 95, 109, 17, 0, 51, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 112, 109, 17, 0, 68, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 129, 109, 17, 0, 85, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 146, 109, 17, 0, 102, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 163, 109, 17, 0, 119, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 180, 109, 17, 0, 136, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 197, 109, 17, 0, 153, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x10, 0, 0x08020000, 134, 214, 109, 9, 0, 170, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x11, 114, 0x04000000, 74, 81, 172, 10, 0, 0, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 91, 172, 10, 0, 10, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 101, 172, 10, 0, 20, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 111, 172, 10, 0, 30, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 121, 172, 10, 0, 40, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 131, 172, 10, 0, 50, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 141, 172, 10, 0, 60, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x11, 0, 0x04000000, 74, 151, 172, 8, 0, 70, 176, 78, (s32) intro_sprite_anim_17_tex, (s32) intro_sprite_anim_17_tlut, 0, -1, 0x0 },
    { 0x12, 480, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x12, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x13, 138, 0x08000000, 109, 122, 30, 30, 0, 0, 30, 30, (s32) D_8022CFA0_ovl_intro, (s32) D_8022CDA0_ovl_intro, 0, -1, 0x0 },
    { 0x14, 234, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x14, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x15, 144, 0x08000000, 78, 44, 109, 17, 0, 0, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 61, 109, 17, 0, 17, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 78, 109, 17, 0, 34, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 95, 109, 17, 0, 51, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 112, 109, 17, 0, 68, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 129, 109, 17, 0, 85, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 146, 109, 17, 0, 102, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 163, 109, 17, 0, 119, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 180, 109, 17, 0, 136, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 197, 109, 17, 0, 153, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x15, 0, 0x08000000, 78, 214, 109, 9, 0, 170, 109, 179, (s32) D_80238A90_ovl_intro, (s32) D_80238890_ovl_intro, 0, -1, 0x0 },
    { 0x16, 108, 0x04000000, 75, 88, 171, 10, 0, 0, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 98, 171, 10, 0, 10, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 108, 171, 10, 0, 20, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 118, 171, 10, 0, 30, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 128, 171, 10, 0, 40, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 138, 171, 10, 0, 50, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x16, 0, 0x04000000, 75, 148, 171, 5, 0, 60, 176, 65, (s32) intro_sprite_anim_22_tex, (s32) intro_sprite_anim_22_tlut, 0, -1, 0x0 },
    { 0x17, 480, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x17, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8022D530_ovl_intro, (s32) D_8022D330_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 0, 304, 6, 0, 0, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 6, 304, 6, 0, 6, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 12, 304, 6, 0, 12, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 18, 304, 6, 0, 18, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 24, 304, 6, 0, 24, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 30, 304, 6, 0, 30, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 36, 304, 6, 0, 36, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 42, 304, 6, 0, 42, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 48, 304, 6, 0, 48, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 54, 304, 6, 0, 54, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 60, 304, 6, 0, 60, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 66, 304, 6, 0, 66, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 72, 304, 6, 0, 72, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 78, 304, 6, 0, 78, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 84, 304, 6, 0, 84, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 90, 304, 6, 0, 90, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 96, 304, 6, 0, 96, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 102, 304, 6, 0, 102, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 108, 304, 6, 0, 108, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 114, 304, 6, 0, 114, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 120, 304, 6, 0, 120, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 126, 304, 6, 0, 126, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 132, 304, 6, 0, 132, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 138, 304, 6, 0, 138, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 144, 304, 6, 0, 144, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 150, 304, 6, 0, 150, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 156, 304, 6, 0, 156, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 162, 304, 6, 0, 162, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 168, 304, 6, 0, 168, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 174, 304, 6, 0, 174, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 180, 304, 6, 0, 180, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 186, 304, 6, 0, 186, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 192, 304, 6, 0, 192, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 198, 304, 6, 0, 198, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 204, 304, 6, 0, 204, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 210, 304, 6, 0, 210, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 216, 304, 6, 0, 216, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 8, 222, 304, 2, 0, 222, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 69, 92, 20, 0, 0, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 89, 92, 20, 0, 20, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 109, 92, 20, 0, 40, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 129, 92, 20, 0, 60, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 149, 92, 20, 0, 80, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x18, 0, 0x08000000, 114, 169, 92, 3, 0, 100, 92, 103, (s32) intro_sprite_anim_24_tex, (s32) intro_sprite_anim_24_tlut, 0, -1, 0x0 },
    { 0x1A, 1, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1A, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_80232FE0_ovl_intro, (s32) D_80232DE0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 1, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1B, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_8023D8D0_ovl_intro, (s32) D_8023D6D0_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 1, 0x08000000, 73, 47, 176, 10, 0, 0, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 57, 176, 10, 0, 10, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 67, 176, 10, 0, 20, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 77, 176, 10, 0, 30, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 87, 176, 10, 0, 40, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 97, 176, 10, 0, 50, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 107, 176, 10, 0, 60, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 117, 176, 10, 0, 70, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 127, 176, 10, 0, 80, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 137, 176, 10, 0, 90, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 147, 176, 10, 0, 100, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 157, 176, 10, 0, 110, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1C, 0, 0x08000000, 73, 167, 176, 9, 0, 120, 176, 129, (s32) D_80243380_ovl_intro, (s32) D_80243180_ovl_intro, 0, -1, 0x0 },
    { 0x1D, 135, 0x04000000, 83, 101, 155, 10, 0, 0, 160, 39, (s32) intro_sprite_anim_29_tex, (s32) intro_sprite_anim_29_tlut, 0, -1, 0x0 },
    { 0x1D, 0, 0x04000000, 83, 111, 155, 10, 0, 10, 160, 39, (s32) intro_sprite_anim_29_tex, (s32) intro_sprite_anim_29_tlut, 0, -1, 0x0 },
    { 0x1D, 0, 0x04000000, 83, 121, 155, 10, 0, 20, 160, 39, (s32) intro_sprite_anim_29_tex, (s32) intro_sprite_anim_29_tlut, 0, -1, 0x0 },
    { 0x1D, 0, 0x04000000, 83, 131, 155, 9, 0, 30, 160, 39, (s32) intro_sprite_anim_29_tex, (s32) intro_sprite_anim_29_tlut, 0, -1, 0x0 },
    { 0x22, 546, 0x04000000, 88, 101, 145, 10, 0, 0, 160, 39, (s32) intro_sprite_anim_34_tex, (s32) intro_sprite_anim_34_tlut, 0, -1, 0x0 },
    { 0x22, 0, 0x04000000, 88, 111, 145, 10, 0, 10, 160, 39, (s32) intro_sprite_anim_34_tex, (s32) intro_sprite_anim_34_tlut, 0, -1, 0x0 },
    { 0x22, 0, 0x04000000, 88, 121, 145, 10, 0, 20, 160, 39, (s32) intro_sprite_anim_34_tex, (s32) intro_sprite_anim_34_tlut, 0, -1, 0x0 },
    { 0x22, 0, 0x04000000, 88, 131, 145, 9, 0, 30, 160, 39, (s32) intro_sprite_anim_34_tex, (s32) intro_sprite_anim_34_tlut, 0, -1, 0x0 },
    { 0x20, 546, 0x04000000, 100, 99, 121, 10, 0, 0, 128, 43, (s32) intro_sprite_anim_32_tex, (s32) intro_sprite_anim_32_tlut, 0, -1, 0x0 },
    { 0x20, 0, 0x04000000, 100, 109, 121, 10, 0, 10, 128, 43, (s32) intro_sprite_anim_32_tex, (s32) intro_sprite_anim_32_tlut, 0, -1, 0x0 },
    { 0x20, 0, 0x04000000, 100, 119, 121, 10, 0, 20, 128, 43, (s32) intro_sprite_anim_32_tex, (s32) intro_sprite_anim_32_tlut, 0, -1, 0x0 },
    { 0x20, 0, 0x04000000, 100, 129, 121, 10, 0, 30, 128, 43, (s32) intro_sprite_anim_32_tex, (s32) intro_sprite_anim_32_tlut, 0, -1, 0x0 },
    { 0x20, 0, 0x04000000, 100, 139, 121, 3, 0, 40, 128, 43, (s32) intro_sprite_anim_32_tex, (s32) intro_sprite_anim_32_tlut, 0, -1, 0x0 },
    { 0x1F, 762, 0x08000000, 0, 0, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 6, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 12, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 18, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 24, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 30, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 36, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 42, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 48, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 54, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 60, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 66, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 72, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 78, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 84, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 90, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 96, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 102, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 108, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 114, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 120, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 126, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 132, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 138, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 144, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 150, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 156, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 162, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 168, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 174, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 180, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 186, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 192, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 198, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 204, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 210, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 216, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 222, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 228, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1F, 0, 0x08000000, 0, 234, 320, 6, 0, 0, 320, 6, (s32) intro_sprite_anim_31_tex, (s32) intro_sprite_anim_31_tlut, 0, -1, 0x0 },
    { 0x1E, 60, 0x08000000, 8, 0, 304, 6, 0, 0, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 6, 304, 6, 0, 6, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 12, 304, 6, 0, 12, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 18, 304, 6, 0, 18, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 24, 304, 6, 0, 24, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 30, 304, 6, 0, 30, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 36, 304, 6, 0, 36, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 42, 304, 6, 0, 42, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 48, 304, 6, 0, 48, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 54, 304, 6, 0, 54, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 60, 304, 6, 0, 60, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 66, 304, 6, 0, 66, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 72, 304, 6, 0, 72, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 78, 304, 6, 0, 78, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 84, 304, 6, 0, 84, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 90, 304, 6, 0, 90, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 96, 304, 6, 0, 96, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 102, 304, 6, 0, 102, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 108, 304, 6, 0, 108, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 114, 304, 6, 0, 114, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 120, 304, 6, 0, 120, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 126, 304, 6, 0, 126, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 132, 304, 6, 0, 132, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 138, 304, 6, 0, 138, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 144, 304, 6, 0, 144, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 150, 304, 6, 0, 150, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 156, 304, 6, 0, 156, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 162, 304, 6, 0, 162, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 168, 304, 6, 0, 168, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 174, 304, 6, 0, 174, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 180, 304, 6, 0, 180, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 186, 304, 6, 0, 186, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 192, 304, 6, 0, 192, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 198, 304, 6, 0, 198, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 204, 304, 6, 0, 204, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 210, 304, 6, 0, 210, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 216, 304, 6, 0, 216, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 8, 222, 304, 2, 0, 222, 304, 224, (s32) D_8021C3A0_ovl_intro, (s32) D_8021C1A0_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 63, 69, 15, 76, 0, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 78, 69, 15, 76, 15, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 93, 69, 15, 76, 30, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 108, 69, 15, 76, 45, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 123, 69, 15, 76, 60, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 138, 69, 15, 76, 75, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 153, 69, 15, 76, 90, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 168, 69, 15, 76, 105, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 183, 69, 15, 76, 120, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 198, 69, 15, 76, 135, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 213, 69, 15, 76, 150, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 228, 69, 15, 76, 165, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
    { 0x1E, 0, 0x08000000, 243, 69, 14, 76, 180, 0, 194, 76, (s32) D_80218800_ovl_intro, (s32) D_80218600_ovl_intro, 0, -1, 0x0 },
};
IntroCueGroup intro_cue_groups[1] = {
    { (IntroSpriteCue*) intro_sprite_cues, 0x1CB },
};
u32 intro_cue_group_count = 0x00000001;
/* not referenced by name */
u32 D_802170F4_ovl_intro[3] = { 0x00000024, 0x00000000, 0x00000000 };
/* palette, 256 colours */
u16 intro_sprite_anim_31_tlut[0x100] = {
#include "assets/intro_sprite_anim_31_tlut.inc.c"
};
/* texture */
u8 intro_sprite_anim_31_tex[0x780] = {
#include "assets/intro_sprite_anim_31_tex.inc.c"
};
/* palette, 256 colours */
u16 D_80217A80_ovl_intro[0x100] = {
#include "assets/D_80217A80_ovl_intro.inc.c"
};
/* texture */
u8 D_80217C80_ovl_intro[0x780] = {
#include "assets/D_80217C80_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 intro_sprite_anim_0_tlut[0x100] = {
#include "assets/intro_sprite_anim_0_tlut.inc.c"
};
/* palette, 256 colours */
u16 D_80218600_ovl_intro[0x100] = {
#include "assets/D_80218600_ovl_intro.inc.c"
};
/* texture */
u8 D_80218800_ovl_intro[0x39A0] = {
#include "assets/D_80218800_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_8021C1A0_ovl_intro[0x100] = {
#include "assets/D_8021C1A0_ovl_intro.inc.c"
};
/* texture */
u8 D_8021C3A0_ovl_intro[0x10A00] = {
#include "assets/D_8021C3A0_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_8022CDA0_ovl_intro[0x100] = {
#include "assets/D_8022CDA0_ovl_intro.inc.c"
};
/* texture */
u8 D_8022CFA0_ovl_intro[0x390] = {
#include "assets/D_8022CFA0_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_8022D330_ovl_intro[0x100] = {
#include "assets/D_8022D330_ovl_intro.inc.c"
};
/* texture */
u8 D_8022D530_ovl_intro[0x58B0] = {
#include "assets/D_8022D530_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_80232DE0_ovl_intro[0x100] = {
#include "assets/D_80232DE0_ovl_intro.inc.c"
};
/* texture */
u8 D_80232FE0_ovl_intro[0x58B0] = {
#include "assets/D_80232FE0_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_80238890_ovl_intro[0x100] = {
#include "assets/D_80238890_ovl_intro.inc.c"
};
/* texture */
u8 D_80238A90_ovl_intro[0x4C40] = {
#include "assets/D_80238A90_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_8023D6D0_ovl_intro[0x100] = {
#include "assets/D_8023D6D0_ovl_intro.inc.c"
};
/* texture */
u8 D_8023D8D0_ovl_intro[0x58B0] = {
#include "assets/D_8023D8D0_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 D_80243180_ovl_intro[0x100] = {
#include "assets/D_80243180_ovl_intro.inc.c"
};
/* texture */
u8 D_80243380_ovl_intro[0x58B0] = {
#include "assets/D_80243380_ovl_intro.inc.c"
};
/* palette, 256 colours */
u16 intro_sprite_anim_24_tlut[0x100] = {
#include "assets/intro_sprite_anim_24_tlut.inc.c"
};
/* texture */
u8 intro_sprite_anim_24_tex[0x2510] = {
#include "assets/intro_sprite_anim_24_tex.inc.c"
};
Gfx D_8024B340_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_4_tex[0x7E0] = {
#include "assets/intro_sprite_anim_4_tex.inc.c"
};
Gfx D_8024BB28_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_4_tlut[0x100] = {
#include "assets/intro_sprite_anim_4_tlut.inc.c"
};
Gfx D_8024BD30_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_8024BD38_ovl_intro[0x5A0] = {
#include "assets/D_8024BD38_ovl_intro.inc.c"
};
Gfx D_8024C2D8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_8024C2E0_ovl_intro[0x100] = {
#include "assets/D_8024C2E0_ovl_intro.inc.c"
};
Gfx D_8024C4E0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_6_variant1_tex[0x780] = {
#include "assets/intro_sprite_anim_6_variant1_tex.inc.c"
};
Gfx D_8024CC68_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_6_variant1_tlut[0x100] = {
#include "assets/intro_sprite_anim_6_variant1_tlut.inc.c"
};
Gfx D_8024CE70_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_6_variant0_tex[0x11D0] = {
#include "assets/intro_sprite_anim_6_variant0_tex.inc.c"
};
Gfx D_8024E048_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_6_variant0_tlut[0x100] = {
#include "assets/intro_sprite_anim_6_variant0_tlut.inc.c"
};
Gfx D_8024E250_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_8_tex[0x2E50] = {
#include "assets/intro_sprite_anim_8_tex.inc.c"
};
Gfx D_802510A8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_8_tlut[0x100] = {
#include "assets/intro_sprite_anim_8_tlut.inc.c"
};
Gfx D_802512B0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_12_tex[0x1EF0] = {
#include "assets/intro_sprite_anim_12_tex.inc.c"
};
Gfx D_802531A8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_12_tlut[0x100] = {
#include "assets/intro_sprite_anim_12_tlut.inc.c"
};
Gfx D_802533B0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_17_tex[0x1AD0] = {
#include "assets/intro_sprite_anim_17_tex.inc.c"
};
Gfx D_80254E88_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_17_tlut[0x100] = {
#include "assets/intro_sprite_anim_17_tlut.inc.c"
};
Gfx D_80255090_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_22_tex[0x1658] = {
#include "assets/intro_sprite_anim_22_tex.inc.c"
};
Gfx D_802566F0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_22_tlut[0x100] = {
#include "assets/intro_sprite_anim_22_tlut.inc.c"
};
Gfx D_802568F8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_29_tex[0xC30] = {
#include "assets/intro_sprite_anim_29_tex.inc.c"
};
Gfx D_80257530_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_29_tlut[0x100] = {
#include "assets/intro_sprite_anim_29_tlut.inc.c"
};
Gfx D_80257738_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_34_tex[0xC30] = {
#include "assets/intro_sprite_anim_34_tex.inc.c"
};
Gfx D_80258370_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_34_tlut[0x100] = {
#include "assets/intro_sprite_anim_34_tlut.inc.c"
};
Gfx D_80258578_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 intro_sprite_anim_32_tex[0xAC0] = {
#include "assets/intro_sprite_anim_32_tex.inc.c"
};
Gfx D_80259040_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 intro_sprite_anim_32_tlut[0x100] = {
#include "assets/intro_sprite_anim_32_tlut.inc.c"
};
Gfx D_80259248_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80259250_ovl_intro[0x2D80] = {
#include "assets/D_80259250_ovl_intro.inc.c"
};
Gfx D_8025BFD0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_8025BFD8_ovl_intro[0x100] = {
#include "assets/D_8025BFD8_ovl_intro.inc.c"
};
Gfx D_8025C1D8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_8025C1E0_ovl_intro[0x1110] = {
#include "assets/D_8025C1E0_ovl_intro.inc.c"
};
Gfx D_8025D2F0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_8025D2F8_ovl_intro[0x100] = {
#include "assets/D_8025D2F8_ovl_intro.inc.c"
};
Gfx D_8025D4F8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_8025D500_ovl_intro[0x2D80] = {
#include "assets/D_8025D500_ovl_intro.inc.c"
};
Gfx D_80260280_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80260288_ovl_intro[0x100] = {
#include "assets/D_80260288_ovl_intro.inc.c"
};
Gfx D_80260488_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80260490_ovl_intro[0x1110] = {
#include "assets/D_80260490_ovl_intro.inc.c"
};
Gfx D_802615A0_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_802615A8_ovl_intro[0x100] = {
#include "assets/D_802615A8_ovl_intro.inc.c"
};
Gfx D_802617A8_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_802617B0_ovl_intro[0x2D80] = {
#include "assets/D_802617B0_ovl_intro.inc.c"
};
Gfx D_80264530_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80264538_ovl_intro[0x100] = {
#include "assets/D_80264538_ovl_intro.inc.c"
};
Gfx D_80264738_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80264740_ovl_intro[0x750] = {
#include "assets/D_80264740_ovl_intro.inc.c"
};
Gfx D_80264E90_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80264E98_ovl_intro[0x100] = {
#include "assets/D_80264E98_ovl_intro.inc.c"
};
Gfx D_80265098_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_802650A0_ovl_intro[0x1FA0] = {
#include "assets/D_802650A0_ovl_intro.inc.c"
};
Gfx D_80267040_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80267048_ovl_intro[0x100] = {
#include "assets/D_80267048_ovl_intro.inc.c"
};
Gfx D_80267248_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80267250_ovl_intro[0xDC0] = {
#include "assets/D_80267250_ovl_intro.inc.c"
};
Gfx D_80268010_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80268018_ovl_intro[0x100] = {
#include "assets/D_80268018_ovl_intro.inc.c"
};
Gfx D_80268218_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80268220_ovl_intro[0x58] = {
#include "assets/D_80268220_ovl_intro.inc.c"
};
Gfx D_80268278_ovl_intro[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80268280_ovl_intro[0x100] = {
#include "assets/D_80268280_ovl_intro.inc.c"
};
