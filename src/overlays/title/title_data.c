#include "common.h"

/*
 * Title overlay data: the title screen's images, palettes and message text.
 * Original file: ovl_title/DAEA30.c (ROM 0xDAEA30).
 */

/* ovl_title .data 8020F510..80226D30: the title screen's images, palettes and message text.
   A data-only file: DAC190.c's .data ends at 8020F504 and this starts 16-aligned at 8020F510.
   The 8-byte Gfx after some images is a gsSPEndDisplayList that follows the converted texture. */

/* palette, 256 colours */
u16 title_confirm_cursor_tlut[0x100] = {
#include "assets/title_confirm_cursor_tlut.inc.c"
};
/* texture */
u8 title_confirm_cursor_tex[0x700] = {
#include "assets/title_confirm_cursor_tex.inc.c"
};
/* palette, 256 colours */
u16 D_8020FE10_ovl_title[0x100] = {
#include "assets/D_8020FE10_ovl_title.inc.c"
};
/* texture */
u8 D_80210010_ovl_title[0x5E0] = {
#include "assets/D_80210010_ovl_title.inc.c"
};
Gfx D_802105F0_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 title_lower_strip_tex[0x500] = {
#include "assets/title_lower_strip_tex.inc.c"
};
Gfx D_80210AF8_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 title_lower_strip_tlut[0x100] = {
#include "assets/title_lower_strip_tlut.inc.c"
};
/* palette, 16 colours */
u16 D_80210D00_ovl_title[0x10] = {
#include "assets/D_80210D00_ovl_title.inc.c"
};
/* texture */
u8 D_80210D20_ovl_title[0x420] = {
#include "assets/D_80210D20_ovl_title.inc.c"
};
Gfx D_80211140_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80211148_ovl_title[0x58] = {
#include "assets/D_80211148_ovl_title.inc.c"
};
Gfx D_802111A0_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_802111A8_ovl_title[0x100] = {
#include "assets/D_802111A8_ovl_title.inc.c"
};
/* message text */
u8 D_802113A8_ovl_title[0x80] = {
#include "assets/D_802113A8_ovl_title.inc.c"
};
/* message text */
u8 D_80211428_ovl_title[0x3C] = {
#include "assets/D_80211428_ovl_title.inc.c"
};
/* message text */
u8 D_80211464_ovl_title[0x7C] = {
#include "assets/D_80211464_ovl_title.inc.c"
};
/* message text */
u8 D_802114E0_ovl_title[0x2C] = {
#include "assets/D_802114E0_ovl_title.inc.c"
};
/* message text */
u8 D_8021150C_ovl_title[0x34] = {
#include "assets/D_8021150C_ovl_title.inc.c"
};
/* message text */
u8 D_80211540_ovl_title[0x8] = {
#include "assets/D_80211540_ovl_title.inc.c"
};
/* message text */
u8 D_80211548_ovl_title[0x8] = {
#include "assets/D_80211548_ovl_title.inc.c"
};
/* palette, 256 colours */
u16 title_center_image_tlut[0x100] = {
#include "assets/title_center_image_tlut.inc.c"
};
/* texture */
u8 title_center_image_tex[0x39A0] = {
#include "assets/title_center_image_tex.inc.c"
};
/* palette, 256 colours */
u16 title_background_tlut[0x100] = {
#include "assets/title_background_tlut.inc.c"
};
/* texture */
u8 title_background_tex[0x11800] = {
#include "assets/title_background_tex.inc.c"
};
Gfx D_80226AF0_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80226AF8_ovl_title[0x100] = {
#include "assets/D_80226AF8_ovl_title.inc.c"
};
Gfx D_80226CF8_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80226D00_ovl_title[0x10] = {
#include "assets/D_80226D00_ovl_title.inc.c"
};
Gfx D_80226D10_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 D_80226D18_ovl_title[0x10] = {
#include "assets/D_80226D18_ovl_title.inc.c"
};
