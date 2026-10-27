#ifndef OVERLAYS_TITLE_TITLE_DATA_H
#define OVERLAYS_TITLE_TITLE_DATA_H

#include "common.h"

extern u16 title_confirm_cursor_tlut[0x100];
extern u8 title_confirm_cursor_tex[0x700];
extern u16 title_initial_screen_image_tlut[0x100];
extern u8 title_initial_screen_image_tex[0x5E0];
extern Gfx D_802105F0_ovl_title[1];
extern u8 title_lower_strip_tex[0x500];
extern Gfx D_80210AF8_ovl_title[1];
extern u16 title_lower_strip_tlut[0x100];
extern u16 title_menu_atlas_tlut[0x10];
extern u8 title_menu_atlas_tex[0x420];
extern Gfx D_80211140_ovl_title[1];
extern u8 title_menu_item_cursor_tex[0x58];
extern Gfx D_802111A0_ovl_title[1];
extern u16 title_menu_item_cursor_tlut[0x100];
extern u8 title_menu_state6_message[0x80];
extern u8 title_menu_state7_message[0x3C];
extern u8 title_menu_state8_message[0x7C];
extern u8 title_menu_state9_message[0x2C];
extern u8 title_menu_state10_message[0x34];
extern u8 title_confirmation_row0_text[0x8];
extern u8 title_confirmation_row1_text[0x8];
extern u16 title_center_image_tlut[0x100];
extern u8 title_center_image_tex[0x39A0];
extern u16 title_background_tlut[0x100];
extern u8 title_background_tex[0x11800];
extern Gfx D_80226AF0_ovl_title[1];
extern u16 title_message_box_border_tlut[0x100];
extern Gfx D_80226CF8_ovl_title[1];
extern u8 title_message_box_top_left_border_tex[0x10];
extern Gfx D_80226D10_ovl_title[1];
extern u8 title_message_box_bottom_right_border_tex[0x10];

#endif
