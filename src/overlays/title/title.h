#ifndef OVERLAYS_TITLE_TITLE_H
#define OVERLAYS_TITLE_TITLE_H

#include "common.h"

extern s32 title_flow_state;
extern s32 title_state_timer;
extern s32 D_80226D98_ovl_title;
extern s32 title_pulse_alpha;
extern s32 title_pulse_step;
extern s32 title_menu_state;
extern s32 title_transition_state;

void Title_Init(void);
s32 Title_Update(void);
s32 Title_RunPhase(void);
void Title_UpdateScreen(void);
void Title_UpdateSelectionExit(void);

#endif
