#include "common.h"

/*
 * Title overlay data: the title screen's images, palettes and message text.
 * Folder: src/game/title/   (proposed for round 4)
 */

/* ovl_title .data 8020F510..80226D30: the title screen's images, palettes and message text.
   A data-only file: DAC190.c's .data ends at 8020F504 and this starts 16-aligned at 8020F510.
   The 8-byte Gfx after some images is a gsSPEndDisplayList that follows the converted texture. */

/* palette, 256 colours */
u16 D_8020F510_ovl_title[0x100] = {
#include "assets/D_8020F510_ovl_title.inc.c"
};
/* texture */
u8 D_8020F710_ovl_title[0x700] = {
#include "assets/D_8020F710_ovl_title.inc.c"
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
u8 D_802105F8_ovl_title[0x500] = {
#include "assets/D_802105F8_ovl_title.inc.c"
};
Gfx D_80210AF8_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 D_80210B00_ovl_title[0x100] = {
#include "assets/D_80210B00_ovl_title.inc.c"
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
u16 D_80211550_ovl_title[0x100] = {
#include "assets/D_80211550_ovl_title.inc.c"
};
/* texture */
u8 D_80211750_ovl_title[0x39A0] = {
#include "assets/D_80211750_ovl_title.inc.c"
};
/* palette, 256 colours */
u16 D_802150F0_ovl_title[0x100] = {
#include "assets/D_802150F0_ovl_title.inc.c"
};
/* texture */
u8 D_802152F0_ovl_title[0x11800] = {
#include "assets/D_802152F0_ovl_title.inc.c"
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
