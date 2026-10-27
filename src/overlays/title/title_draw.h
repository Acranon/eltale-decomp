#ifndef OVERLAYS_TITLE_TITLE_DRAW_H
#define OVERLAYS_TITLE_TITLE_DRAW_H

#include "common.h"

typedef struct TitleFade {
    /* 0x00 */ u16 active;
    /* 0x02 */ u16 remaining_frames;
    /* 0x04 */ f32 alpha_step;
    /* 0x08 */ f32 alpha;
} TitleFade; /* 0xC bytes */

extern s32 D_8020F200_ovl_title;
extern Gfx D_8020F208_ovl_title[11];
extern Gfx D_8020F260_ovl_title[4];
extern Gfx D_8020F280_ovl_title[5];
extern Gfx D_8020F2A8_ovl_title[11];
extern Gfx D_8020F300_ovl_title[11];
extern Gfx D_8020F358_ovl_title[11];
extern Gfx D_8020F3B0_ovl_title[21];
extern Gfx D_8020F458_ovl_title[3];
extern Gfx D_8020F470_ovl_title[3];
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
