#ifndef OVERLAYS_PAKMENU_PAKMENU_H
#define OVERLAYS_PAKMENU_PAKMENU_H

#include "common.h"
#include "game/text/text.h"

typedef struct PakMenuSprite {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u8 w;
    /* 0x05 */ u8 h;
    /* 0x06 */ char unk6[2];
    /* 0x08 */ u8 *pixels;
    /* 0x0C */ u16 *palette;
} PakMenuSprite; /* 0x10 bytes */

typedef struct PakMenuNoteState {
    /* 0x00 */ u32 file_size;
    /* 0x04 */ u32 game_code;
    /* 0x08 */ u16 company_code;
    /* 0x0A */ u8 ext_name[4];
    /* 0x0E */ u8 name[18];
} PakMenuNoteState; /* 0x20 bytes */

extern u16 pak_menu_cursor_tlut[0x10];
extern u8 pak_menu_cursor_tex[0x70];
extern u16 pak_menu_screen_frame_tlut[0x10];
extern u8 pak_menu_screen_frame_main_tex[0x200];
extern u8 pak_menu_screen_frame_right_tex[0x200];
extern u16 D_80102450_ovl_DA4570[0x10];
extern u8 D_80102470_ovl_DA4570[0x80];
extern u8 D_801024F0_ovl_DA4570[0x80];
extern u8 D_80102570_ovl_DA4570[0x80];
extern u8 D_801025F0_ovl_DA4570[0x80];
extern u8 D_80102670_ovl_DA4570[0x80];
extern u8 D_801026F0_ovl_DA4570[0x80];
extern u8 D_80102770_ovl_DA4570[0x80];
extern u8 D_801027F0_ovl_DA4570[0x80];
extern u8 D_80102870_ovl_DA4570[0x80];
extern u8 D_801028F0_ovl_DA4570[0x90];
extern u8 D_80102980_ovl_DA4570[0x90];
extern u8 D_80102A10_ovl_DA4570[0x90];
extern u16 D_80102AA0_ovl_DA4570[0x10];
extern u8 D_80102AC0_ovl_DA4570[0x80];
extern u8 D_80102B40_ovl_DA4570[0x80];
extern u8 D_80102BC0_ovl_DA4570[0x80];
extern u8 D_80102C40_ovl_DA4570[0x80];
extern u8 D_80102CC0_ovl_DA4570[0x80];
extern u8 D_80102D40_ovl_DA4570[0x80];
extern u8 D_80102DC0_ovl_DA4570[0x80];
extern u8 D_80102E40_ovl_DA4570[0x80];
extern u8 D_80102EC0_ovl_DA4570[0x80];
extern u16 D_80102F40_ovl_DA4570[0x10];
extern u8 D_80102F60_ovl_DA4570[0x78];
extern u8 D_80102FD8_ovl_DA4570[0xB0];
extern u16 D_80103088_ovl_DA4570[0x10];
extern u8 D_801030A8_ovl_DA4570[0x460];
extern u16 D_80103508_ovl_DA4570[0x10];
extern u8 D_80103528_ovl_DA4570[0x180];
extern u16 D_801036A8_ovl_DA4570[0x10];
extern u8 D_801036C8_ovl_DA4570[0xC0];
extern u16 D_80103788_ovl_DA4570[0x10];
extern u8 D_801037A8_ovl_DA4570[0xB0];
extern u16 D_80103858_ovl_DA4570[0x10];
extern u8 D_80103878_ovl_DA4570[0xC0];
extern u16 D_80103938_ovl_DA4570[0x10];
extern u8 D_80103958_ovl_DA4570[0xC0];
extern u16 D_80103A18_ovl_DA4570[0x10];
extern u8 D_80103A38_ovl_DA4570[0x1E0];
extern u16 D_80103C18_ovl_DA4570[0x10];
extern u8 D_80103C38_ovl_DA4570[0x180];
extern u16 D_80103DB8_ovl_DA4570[0x10];
extern u8 D_80103DD8_ovl_DA4570[0xC0];
extern u16 D_80103E98_ovl_DA4570[0x10];
extern u8 D_80103EB8_ovl_DA4570[0x70];
extern PakMenuSprite pak_menu_screen_sprites[235];
extern PakMenuSprite pak_menu_message_window_sprites[75];
extern PakMenuSprite pak_menu_message_lower_window_sprites[22];
extern PakMenuSprite pak_menu_previous_rows_sprite[1];
extern PakMenuSprite pak_menu_more_rows_sprite[1];
extern u8 pak_menu_delete_confirmation_message[0x40];
extern u8 pak_menu_reinitialize_confirmation_message[0x68];
extern u8 pak_menu_operation_error_message[0x38];
extern u8 pak_menu_repair_confirmation_message[0x90];
extern u8 D_80105578_ovl_DA4570[0x90];
extern u8 D_80105608_ovl_DA4570[0x58];
extern s32 pak_menu_framebuffer_index;
extern u16 *pak_menu_framebuffers[2];
extern TextFontMetrics pak_menu_font_metrics[1];
extern u16 D_8010567C_ovl_DA4570[8];
extern u8 pak_menu_font_bitmap[0x1980];
extern u16 pak_menu_font_tluts[28];
extern u16 *pak_menu_active_font_tlut;
extern PakMenuNoteState pak_menu_note_states[16];
extern s32 pak_menu_max_glyph_code;
extern s32 D_80107284_ovl_DA4570;
extern s32 pak_menu_note_errors[16];
extern s16 pak_menu_state;
extern s16 pak_menu_selected_row;
extern s16 pak_menu_previous_row;
extern u8 pak_menu_list_offset;
extern u8 pak_menu_previous_offset;
extern s16 pak_menu_cursor_x;
extern s16 pak_menu_cursor_y;
extern s16 pak_menu_dialog_selection;
extern s32 pak_menu_free_pages;
extern s32 pak_menu_redraw_pending;
extern u16 *pak_menu_draw_framebuffer;
extern OSMesgQueue *pak_menu_si_queue;
extern OSMesgQueue *pak_menu_vi_queue;
extern OSMesg pak_menu_mesg;
extern u16 *pak_menu_text_pixel_cursor;
extern s16 pak_menu_text_x;
extern s16 pak_menu_text_y;

void PakMenu_FormatNumber(u16 arg0, u8* arg1);
void PakMenu_DrawChar(s32 arg0);
void PakMenu_SetCursor(s16 arg0, s16 arg1);
void func_80100284_ovl_DA4570(void);
void PakMenu_DrawString(u8* arg0, s32 arg1);
void PakMenu_SetTextPalette(s32 arg0);
void PakMenu_BlitImage(s16 x, s16 y, s16 w, s16 h, u8* pixels, u16* palette, u8 mode);
void PakMenu_DrawSprites(PakMenuSprite* arg0, s32 arg1);
void PakMenu_WaitFrame(void);
void PakMenu_DrawNoteRow(s32 arg0);
void PakMenu_DrawFreePages(u16 arg0);
void PakMenu_DrawCursor(void);
void PakMenu_DrawScreen(void);
s32 PakMenu_Run(OSMesgQueue* mq, OSMesgQueue* arg1);
void PakMenu_DrawText(s32 x, s32 y, u8* str);

#ifdef NON_MATCHING
void PakMenu_DrawMessageBox(u8 *arg0);
#else
void PakMenu_DrawMessageBox(s32 arg0);
#endif

#endif
