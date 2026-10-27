#include "common.h"

/*
 * Shadows: clears the shadow queue (the queue and drawing are in 13DF0).
 * Folder: src/game/gfx/   (proposed for round 4)
 */

extern s32 D_80085280;

void func_800131E0(void) {
    D_80085280 = 0;
}
