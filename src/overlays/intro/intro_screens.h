#ifndef OVERLAYS_INTRO_INTRO_SCREENS_H
#define OVERLAYS_INTRO_INTRO_SCREENS_H

#include "common.h"

extern s32 intro_splash_fade_alpha;
extern s32 intro_splash_phase;

void Intro_RunSplash1(void);
void Intro_RunSplash2(void);
void Intro_RunSplash3(void);
void Intro_DrawSplash1(void);
void Intro_DrawSplash2(void);
void Intro_DrawSplash3(void);
s32 Intro_RunNoPakScreen(void);
void Intro_DrawNoControllerMessage(void);
s32 Intro_RunPakFullScreen(void);
s32 Intro_RunPakErrorScreen(void);

#endif
