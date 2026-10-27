#include "game/map/chest_flag.h"
#include "game/map/chest.h"
#include "game/math/math.h"

/*
 * Chests: sets an opened flag (the rest is in 140D0).
 * Original file: 14760.c (ROM 0x14760).
 */

void Chest_SetOpened(u16 arg0) {
    chest_opened_flags[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}
