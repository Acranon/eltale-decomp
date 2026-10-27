#include "common.h"

/*
 * Chests: sets an opened flag (the rest is in 140D0).
 * Folder: src/game/map/   (proposed for round 4)
 */

extern u8 D_80085988[];
extern u8 math_bit_masks[];

void Chest_SetOpened(u16 arg0) {
    D_80085988[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}
