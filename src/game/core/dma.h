#ifndef GAME_CORE_DMA_H
#define GAME_CORE_DMA_H

#include "common.h"

extern OSIoMesg dma_io_mesg;

void Dma_ReadRom(u8* devAddr, void* vAddr, s32 size);
s32 Text_FormatNumber(s32 value, u8* str_ptr, u16 flags);

#endif
