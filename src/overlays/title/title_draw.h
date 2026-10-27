#ifndef OVERLAYS_TITLE_TITLE_DRAW_H
#define OVERLAYS_TITLE_TITLE_DRAW_H

#include "common.h"

typedef struct TitleFade {
    /* 0x00 */ u16 active;
    /* 0x02 */ u16 remaining_frames;
    /* 0x04 */ f32 alpha_step;
    /* 0x08 */ f32 alpha;
} TitleFade; /* 0xC bytes */

extern s32 title_draw_initialized;
extern Gfx title_frame_setup_dl[11];
extern Gfx title_menu_draw_setup_dl[4];
extern Gfx title_menu_sprite_setup_dl[5];
extern Gfx D_8020F2A8_ovl_title[11];
extern Gfx D_8020F300_ovl_title[11];
extern Gfx D_8020F358_ovl_title[11];
extern Gfx D_8020F3B0_ovl_title[21];
extern Gfx title_cursor_combine_dl[3];
extern Gfx title_screen_fade_combine_dl[3];
extern s32 D_8020F488_ovl_title[18];
extern s8 title_confirmation_row;
extern s32 title_confirm_cursor_alpha;
extern s32 title_screen_fade_state;
extern s32 title_screen_fade_frames;
extern s32 D_80226DC0_ovl_title;

void Title_DrawScreenAndMoveCursor(s32 arg0);
void Title_UpdateScreenFade(void);
void Title_StepAndDrawScreenFade(TitleFade* arg0);

#endif
