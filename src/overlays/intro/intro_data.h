#ifndef OVERLAYS_INTRO_INTRO_DATA_H
#define OVERLAYS_INTRO_INTRO_DATA_H

#include "common.h"

typedef struct IntroSpriteCue {
    /* 0x00 */ u16 anim_index;
    /* 0x02 */ s16 start_frame;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ s16 width;
    /* 0x0E */ s16 height;
    /* 0x10 */ s16 texture_s;
    /* 0x12 */ s16 texture_t;
    /* 0x14 */ s16 texture_width;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 texture_addr;
    /* 0x1C */ s32 palette_addr;
    /* 0x20 */ s16 anim_step_index;
    /* 0x22 */ s16 sprite_slot;
    /* 0x24 */ u16 previous_cue_index;
} IntroSpriteCue; /* size = 0x28 */

typedef struct IntroAnimStep {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s32 duration;
} IntroAnimStep; /* size = 0xC */

typedef struct IntroAnim {
    /* 0x00 */ IntroAnimStep *steps;
    /* 0x04 */ u32 count;
} IntroAnim; /* 0x8 bytes */

typedef struct IntroCueGroup {
    /* 0x00 */ IntroSpriteCue *cues;
    /* 0x04 */ u32 count;
} IntroCueGroup; /* 0x8 bytes */

extern Gfx intro_render_setup_dl[11];
extern Gfx D_802122C8_ovl_intro[3];
extern Gfx D_802122E0_ovl_intro[4];
extern IntroAnimStep intro_sprite_anim_steps_0[3];
extern IntroAnimStep intro_sprite_anim_steps_1[4];
extern IntroAnimStep intro_sprite_anim_steps_2[3];
extern IntroAnimStep intro_sprite_anim_steps_3[4];
extern IntroAnimStep intro_sprite_anim_steps_4[2];
extern IntroAnimStep intro_sprite_anim_steps_5[1];
extern IntroAnimStep intro_sprite_anim_steps_6[3];
extern IntroAnimStep intro_sprite_anim_steps_7[3];
extern IntroAnimStep intro_sprite_anim_steps_8[3];
extern IntroAnimStep intro_sprite_anim_steps_33[3];
extern IntroAnimStep intro_sprite_anim_steps_9[3];
extern IntroAnimStep intro_sprite_anim_steps_10[3];
extern IntroAnimStep intro_sprite_anim_steps_11[4];
extern IntroAnimStep intro_sprite_anim_steps_12[3];
extern IntroAnimStep intro_sprite_anim_steps_13[3];
extern IntroAnimStep intro_sprite_anim_steps_14[3];
extern IntroAnimStep intro_sprite_anim_steps_15[3];
extern IntroAnimStep intro_sprite_anim_steps_16[4];
extern IntroAnimStep intro_sprite_anim_steps_17[3];
extern IntroAnimStep intro_sprite_anim_steps_18[3];
extern IntroAnimStep intro_sprite_anim_steps_19[3];
extern IntroAnimStep intro_sprite_anim_steps_20[3];
extern IntroAnimStep intro_sprite_anim_steps_21[4];
extern IntroAnimStep intro_sprite_anim_steps_22[3];
extern IntroAnimStep intro_sprite_anim_steps_23[3];
extern IntroAnimStep intro_sprite_anim_steps_24[4];
extern IntroAnimStep intro_sprite_anim_steps_25[1];
extern IntroAnimStep intro_sprite_anim_steps_26[3];
extern IntroAnimStep intro_sprite_anim_steps_27[3];
extern IntroAnimStep intro_sprite_anim_steps_28[3];
extern IntroAnimStep intro_sprite_anim_steps_29[3];
extern IntroAnimStep intro_sprite_anim_steps_34[3];
extern IntroAnimStep intro_sprite_anim_steps_30[3];
extern IntroAnimStep intro_sprite_anim_steps_31[2];
extern IntroAnimStep intro_sprite_anim_steps_32[3];
extern IntroAnimStep intro_sprite_anim_steps_35[3];
extern IntroAnim intro_sprite_anim_table[36];
extern IntroSpriteCue intro_sprite_cues[459];
extern IntroCueGroup intro_cue_groups[1];
extern u32 intro_cue_group_count;
extern u32 D_802170F4_ovl_intro[3];
extern u16 intro_sprite_anim_31_tlut[0x100];
extern u8 intro_sprite_anim_31_tex[0x780];
extern u16 D_80217A80_ovl_intro[0x100];
extern u8 D_80217C80_ovl_intro[0x780];
extern u16 intro_sprite_anim_0_tlut[0x100];
extern u16 D_80218600_ovl_intro[0x100];
extern u8 D_80218800_ovl_intro[0x39A0];
extern u16 D_8021C1A0_ovl_intro[0x100];
extern u8 D_8021C3A0_ovl_intro[0x10A00];
extern u16 D_8022CDA0_ovl_intro[0x100];
extern u8 D_8022CFA0_ovl_intro[0x390];
extern u16 D_8022D330_ovl_intro[0x100];
extern u8 D_8022D530_ovl_intro[0x58B0];
extern u16 D_80232DE0_ovl_intro[0x100];
extern u8 D_80232FE0_ovl_intro[0x58B0];
extern u16 D_80238890_ovl_intro[0x100];
extern u8 D_80238A90_ovl_intro[0x4C40];
extern u16 D_8023D6D0_ovl_intro[0x100];
extern u8 D_8023D8D0_ovl_intro[0x58B0];
extern u16 D_80243180_ovl_intro[0x100];
extern u8 D_80243380_ovl_intro[0x58B0];
extern u16 intro_sprite_anim_24_tlut[0x100];
extern u8 intro_sprite_anim_24_tex[0x2510];
extern Gfx D_8024B340_ovl_intro[1];
extern u8 intro_sprite_anim_4_tex[0x7E0];
extern Gfx D_8024BB28_ovl_intro[1];
extern u16 intro_sprite_anim_4_tlut[0x100];
extern Gfx D_8024BD30_ovl_intro[1];
extern u8 D_8024BD38_ovl_intro[0x5A0];
extern Gfx D_8024C2D8_ovl_intro[1];
extern u16 D_8024C2E0_ovl_intro[0x100];
extern Gfx D_8024C4E0_ovl_intro[1];
extern u8 intro_sprite_anim_6_variant1_tex[0x780];
extern Gfx D_8024CC68_ovl_intro[1];
extern u16 intro_sprite_anim_6_variant1_tlut[0x100];
extern Gfx D_8024CE70_ovl_intro[1];
extern u8 intro_sprite_anim_6_variant0_tex[0x11D0];
extern Gfx D_8024E048_ovl_intro[1];
extern u16 intro_sprite_anim_6_variant0_tlut[0x100];
extern Gfx D_8024E250_ovl_intro[1];
extern u8 intro_sprite_anim_8_tex[0x2E50];
extern Gfx D_802510A8_ovl_intro[1];
extern u16 intro_sprite_anim_8_tlut[0x100];
extern Gfx D_802512B0_ovl_intro[1];
extern u8 intro_sprite_anim_12_tex[0x1EF0];
extern Gfx D_802531A8_ovl_intro[1];
extern u16 intro_sprite_anim_12_tlut[0x100];
extern Gfx D_802533B0_ovl_intro[1];
extern u8 intro_sprite_anim_17_tex[0x1AD0];
extern Gfx D_80254E88_ovl_intro[1];
extern u16 intro_sprite_anim_17_tlut[0x100];
extern Gfx D_80255090_ovl_intro[1];
extern u8 intro_sprite_anim_22_tex[0x1658];
extern Gfx D_802566F0_ovl_intro[1];
extern u16 intro_sprite_anim_22_tlut[0x100];
extern Gfx D_802568F8_ovl_intro[1];
extern u8 intro_sprite_anim_29_tex[0xC30];
extern Gfx D_80257530_ovl_intro[1];
extern u16 intro_sprite_anim_29_tlut[0x100];
extern Gfx D_80257738_ovl_intro[1];
extern u8 intro_sprite_anim_34_tex[0xC30];
extern Gfx D_80258370_ovl_intro[1];
extern u16 intro_sprite_anim_34_tlut[0x100];
extern Gfx D_80258578_ovl_intro[1];
extern u8 intro_sprite_anim_32_tex[0xAC0];
extern Gfx D_80259040_ovl_intro[1];
extern u16 intro_sprite_anim_32_tlut[0x100];
extern Gfx D_80259248_ovl_intro[1];
extern u8 D_80259250_ovl_intro[0x2D80];
extern Gfx D_8025BFD0_ovl_intro[1];
extern u16 D_8025BFD8_ovl_intro[0x100];
extern Gfx D_8025C1D8_ovl_intro[1];
extern u8 D_8025C1E0_ovl_intro[0x1110];
extern Gfx D_8025D2F0_ovl_intro[1];
extern u16 D_8025D2F8_ovl_intro[0x100];
extern Gfx D_8025D4F8_ovl_intro[1];
extern u8 D_8025D500_ovl_intro[0x2D80];
extern Gfx D_80260280_ovl_intro[1];
extern u16 D_80260288_ovl_intro[0x100];
extern Gfx D_80260488_ovl_intro[1];
extern u8 D_80260490_ovl_intro[0x1110];
extern Gfx D_802615A0_ovl_intro[1];
extern u16 D_802615A8_ovl_intro[0x100];
extern Gfx D_802617A8_ovl_intro[1];
extern u8 D_802617B0_ovl_intro[0x2D80];
extern Gfx D_80264530_ovl_intro[1];
extern u16 D_80264538_ovl_intro[0x100];
extern Gfx D_80264738_ovl_intro[1];
extern u8 D_80264740_ovl_intro[0x750];
extern Gfx D_80264E90_ovl_intro[1];
extern u16 D_80264E98_ovl_intro[0x100];
extern Gfx D_80265098_ovl_intro[1];
extern u8 D_802650A0_ovl_intro[0x1FA0];
extern Gfx D_80267040_ovl_intro[1];
extern u16 D_80267048_ovl_intro[0x100];
extern Gfx D_80267248_ovl_intro[1];
extern u8 D_80267250_ovl_intro[0xDC0];
extern Gfx D_80268010_ovl_intro[1];
extern u16 D_80268018_ovl_intro[0x100];
extern Gfx D_80268218_ovl_intro[1];
extern u8 D_80268220_ovl_intro[0x58];
extern Gfx D_80268278_ovl_intro[1];
extern u16 D_80268280_ovl_intro[0x100];

#endif
