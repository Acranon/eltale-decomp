#include "game/core/dma.h"
#include "game/core/main.h"

/*
 * Blocking ROM-to-RAM DMA, and integer-to-digit-string conversion for the game's text encoding.
 * Original file: 28D20.c (ROM 0x28D20).
 */

OSIoMesg dma_io_mesg; /* .bss 8008CEA0..8008CEC0 */

void Dma_ReadRom(u8* devAddr, void* vAddr, s32 size) {
    u32 mesgSize;

    osInvalICache(vAddr, size);
    osInvalDCache(vAddr, size);

    while (size != 0) {
        if (size > 0x4000) {
            mesgSize = 0x4000;
        } else {
            mesgSize = size;
        }
        osPiStartDma(&dma_io_mesg, 0, 0, (u32) devAddr, vAddr, mesgSize, &dma_mesg_queue);
        osRecvMesg(&dma_mesg_queue, NULL, 1);
        size -= mesgSize;
        devAddr = devAddr + mesgSize;
        vAddr = (u8*) vAddr + mesgSize;
    }
}

s32 Text_FormatNumber(s32 value, u8* str_ptr, u16 flags) {
    u32 char_count;
    s32 continue_loop;
    s32 power;
    u8* i_ptr;
    u32 i;

    if (flags & 2) {
        power = 10000;
        char_count = 4;
    } else if (flags & 4) {
        power = 10;
        char_count = 1;
    } else {
        char_count = 0;
        for (power = 10; power <= value; power *= 10) {
            char_count++;
        }
        power /= 10;
    }

    i_ptr = str_ptr;

    for (i = char_count; i > 0; i--) { *i_ptr = value / power;
        value %= power;
        power /= 10;
        i_ptr += 1;
    }

    i_ptr[0] = (u8) value;
    i_ptr[1] = 0xFF;

    if (flags & 1) {
        continue_loop = 0;
        continue_loop = 1;
        i_ptr = str_ptr;
        for (i = char_count; (i != 0) && continue_loop; i--) {
            if (!(*i_ptr)) {
                *i_ptr = ' ';
            } else {
                continue_loop = 0;
            }
            i_ptr += 1;
        }
    }
    return char_count + 1;
}
