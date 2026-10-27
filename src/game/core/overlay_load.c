#include "game/core/overlay_load.h"
#include "game/core/dma.h"

/*
 * Load the title, intro, and ending ROM overlays into the shared overlay region.
 * Original file: 36DB0.c (ROM 0x36DB0).
 */

/* The overlays' ROM ranges (linker symbols, no module defines them) and the shared
 * overlay entry point: Title_Init, Intro_Init and Ending_Init all sit at 0x8020C0D0,
 * so the main segment calls it by address. */
extern u8 D_DAB5F0[];
extern u8 D_DC62B0[];
extern u8 D_E22690[];
extern u8 D_E420D0[];
void func_8020C0D0(void);

void Overlay_LoadTitle(void) {
    Dma_ReadRom(D_DAB5F0, func_8020C0D0, D_DC62B0 - D_DAB5F0);
}

void Overlay_LoadIntro(void) {
    Dma_ReadRom(D_DC62B0, func_8020C0D0, D_E22690 - D_DC62B0);
}

void Overlay_LoadEnding(void) {
    Dma_ReadRom(D_E22690, func_8020C0D0, D_E420D0 - D_E22690);
}
