#include "overlays/title/title_data.h"

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
u16 title_initial_screen_image_tlut[0x100] = {
#include "assets/title_initial_screen_image_tlut.inc.c"
};
/* texture */
u8 title_initial_screen_image_tex[0x5E0] = {
#include "assets/title_initial_screen_image_tex.inc.c"
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
u16 title_menu_atlas_tlut[0x10] = {
#include "assets/title_menu_atlas_tlut.inc.c"
};
/* texture */
u8 title_menu_atlas_tex[0x420] = {
#include "assets/title_menu_atlas_tex.inc.c"
};
Gfx D_80211140_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 title_menu_item_cursor_tex[0x58] = {
#include "assets/title_menu_item_cursor_tex.inc.c"
};
Gfx D_802111A0_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* palette, 256 colours */
u16 title_menu_item_cursor_tlut[0x100] = {
#include "assets/title_menu_item_cursor_tlut.inc.c"
};
/* message text */
u8 title_menu_state6_message[0x80] = {
#include "assets/title_menu_state6_message.inc.c"
};
/* message text */
u8 title_menu_state7_message[0x3C] = {
#include "assets/title_menu_state7_message.inc.c"
};
/* message text */
u8 title_menu_state8_message[0x7C] = {
#include "assets/title_menu_state8_message.inc.c"
};
/* message text */
u8 title_menu_state9_message[0x2C] = {
#include "assets/title_menu_state9_message.inc.c"
};
/* message text */
u8 title_menu_state10_message[0x34] = {
#include "assets/title_menu_state10_message.inc.c"
};
/* message text */
u8 title_confirmation_row0_text[0x8] = {
#include "assets/title_confirmation_row0_text.inc.c"
};
/* message text */
u8 title_confirmation_row1_text[0x8] = {
#include "assets/title_confirmation_row1_text.inc.c"
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
u16 title_message_box_border_tlut[0x100] = {
#include "assets/title_message_box_border_tlut.inc.c"
};
Gfx D_80226CF8_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 title_message_box_top_left_border_tex[0x10] = {
#include "assets/title_message_box_top_left_border_tex.inc.c"
};
Gfx D_80226D10_ovl_title[1] = {
    {{ 0xB8000000, 0x00000000 }},
};
/* texture */
u8 title_message_box_bottom_right_border_tex[0x10] = {
#include "assets/title_message_box_bottom_right_border_tex.inc.c"
};
