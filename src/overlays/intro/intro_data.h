#ifndef OVERLAYS_INTRO_INTRO_DATA_H
#define OVERLAYS_INTRO_INTRO_DATA_H

#include "common.h"

typedef struct IntroSpriteCue {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 unk24;
} IntroSpriteCue; /* size = 0x28 */

typedef struct IntroAnimStep {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 unk8;
} IntroAnimStep; /* size = 0xC */

typedef struct IntroAnim {
    /* 0x00 */ IntroAnimStep *unk0;
    /* 0x04 */ u32 unk4;
} IntroAnim; /* 0x8 bytes */

typedef struct IntroCueGroup {
    /* 0x00 */ IntroSpriteCue *unk0;
    /* 0x04 */ u32 unk4;
} IntroCueGroup; /* 0x8 bytes */

extern Gfx intro_render_setup_dl[11];
extern Gfx D_802122C8_ovl_intro[3];
extern Gfx D_802122E0_ovl_intro[4];
extern IntroAnimStep D_80212300_ovl_intro[3];
extern IntroAnimStep D_80212324_ovl_intro[4];
extern IntroAnimStep D_80212354_ovl_intro[3];
extern IntroAnimStep D_80212378_ovl_intro[4];
extern IntroAnimStep D_802123A8_ovl_intro[2];
extern IntroAnimStep D_802123C0_ovl_intro[1];
extern IntroAnimStep D_802123CC_ovl_intro[3];
extern IntroAnimStep D_802123F0_ovl_intro[3];
extern IntroAnimStep D_80212414_ovl_intro[3];
extern IntroAnimStep D_80212438_ovl_intro[3];
extern IntroAnimStep D_8021245C_ovl_intro[3];
extern IntroAnimStep D_80212480_ovl_intro[3];
extern IntroAnimStep D_802124A4_ovl_intro[4];
extern IntroAnimStep D_802124D4_ovl_intro[3];
extern IntroAnimStep D_802124F8_ovl_intro[3];
extern IntroAnimStep D_8021251C_ovl_intro[3];
extern IntroAnimStep D_80212540_ovl_intro[3];
extern IntroAnimStep D_80212564_ovl_intro[4];
extern IntroAnimStep D_80212594_ovl_intro[3];
extern IntroAnimStep D_802125B8_ovl_intro[3];
extern IntroAnimStep D_802125DC_ovl_intro[3];
extern IntroAnimStep D_80212600_ovl_intro[3];
extern IntroAnimStep D_80212624_ovl_intro[4];
extern IntroAnimStep D_80212654_ovl_intro[3];
extern IntroAnimStep D_80212678_ovl_intro[3];
extern IntroAnimStep D_8021269C_ovl_intro[4];
extern IntroAnimStep D_802126CC_ovl_intro[1];
extern IntroAnimStep D_802126D8_ovl_intro[3];
extern IntroAnimStep D_802126FC_ovl_intro[3];
extern IntroAnimStep D_80212720_ovl_intro[3];
extern IntroAnimStep D_80212744_ovl_intro[3];
extern IntroAnimStep D_80212768_ovl_intro[3];
extern IntroAnimStep D_8021278C_ovl_intro[3];
extern IntroAnimStep D_802127B0_ovl_intro[2];
extern IntroAnimStep D_802127C8_ovl_intro[3];
extern IntroAnimStep D_802127EC_ovl_intro[3];
extern IntroAnim intro_sprite_anim_table[36];
extern IntroSpriteCue D_80212930_ovl_intro[459];
extern IntroCueGroup intro_cue_groups[1];
extern u32 intro_cue_group_count;
extern u32 D_802170F4_ovl_intro[3];
extern u16 D_80217100_ovl_intro[0x100];
extern u8 D_80217300_ovl_intro[0x780];
extern u16 D_80217A80_ovl_intro[0x100];
extern u8 D_80217C80_ovl_intro[0x780];
extern u16 D_80218400_ovl_intro[0x100];
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
extern u16 D_80248C30_ovl_intro[0x100];
extern u8 D_80248E30_ovl_intro[0x2510];
extern Gfx D_8024B340_ovl_intro[1];
extern u8 D_8024B348_ovl_intro[0x7E0];
extern Gfx D_8024BB28_ovl_intro[1];
extern u16 D_8024BB30_ovl_intro[0x100];
extern Gfx D_8024BD30_ovl_intro[1];
extern u8 D_8024BD38_ovl_intro[0x5A0];
extern Gfx D_8024C2D8_ovl_intro[1];
extern u16 D_8024C2E0_ovl_intro[0x100];
extern Gfx D_8024C4E0_ovl_intro[1];
extern u8 D_8024C4E8_ovl_intro[0x780];
extern Gfx D_8024CC68_ovl_intro[1];
extern u16 D_8024CC70_ovl_intro[0x100];
extern Gfx D_8024CE70_ovl_intro[1];
extern u8 D_8024CE78_ovl_intro[0x11D0];
extern Gfx D_8024E048_ovl_intro[1];
extern u16 D_8024E050_ovl_intro[0x100];
extern Gfx D_8024E250_ovl_intro[1];
extern u8 D_8024E258_ovl_intro[0x2E50];
extern Gfx D_802510A8_ovl_intro[1];
extern u16 D_802510B0_ovl_intro[0x100];
extern Gfx D_802512B0_ovl_intro[1];
extern u8 D_802512B8_ovl_intro[0x1EF0];
extern Gfx D_802531A8_ovl_intro[1];
extern u16 D_802531B0_ovl_intro[0x100];
extern Gfx D_802533B0_ovl_intro[1];
extern u8 D_802533B8_ovl_intro[0x1AD0];
extern Gfx D_80254E88_ovl_intro[1];
extern u16 D_80254E90_ovl_intro[0x100];
extern Gfx D_80255090_ovl_intro[1];
extern u8 D_80255098_ovl_intro[0x1658];
extern Gfx D_802566F0_ovl_intro[1];
extern u16 D_802566F8_ovl_intro[0x100];
extern Gfx D_802568F8_ovl_intro[1];
extern u8 D_80256900_ovl_intro[0xC30];
extern Gfx D_80257530_ovl_intro[1];
extern u16 D_80257538_ovl_intro[0x100];
extern Gfx D_80257738_ovl_intro[1];
extern u8 D_80257740_ovl_intro[0xC30];
extern Gfx D_80258370_ovl_intro[1];
extern u16 D_80258378_ovl_intro[0x100];
extern Gfx D_80258578_ovl_intro[1];
extern u8 D_80258580_ovl_intro[0xAC0];
extern Gfx D_80259040_ovl_intro[1];
extern u16 D_80259048_ovl_intro[0x100];
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
