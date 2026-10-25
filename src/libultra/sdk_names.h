#ifndef SDK_NAMES_H
#define SDK_NAMES_H

/*
 * Real libultra names for symbols that symbol_addrs.txt still calls func_/D_.
 * Included first by the SDK files that use them. Once the names are applied to
 * symbol_addrs.txt (D3), delete the matching lines here (and this file when empty).
 */

/* os/thread.c data */
#define __osRunQueue D_8006E758
#define __osActiveQueue D_8006E75C
#define __osRunningThread D_8006E760
#define __osFaultedThread D_8006E764

/* io/piacs.c data */
#define __osPiAccessQueueEnabled D_8006E770
#define piAccessBuf D_80095780
#define __osPiAccessQueue D_80095788

/* controller */
#define __osContPifRam D_800956F0

/* io/siacs.c, io/sirawdma.c (libultra/477D0.c, libultra/49290.c) */
#define __osSiGetAccess func_80046C20
#define __osSiRelAccess func_80046C64
#define __osSiRawStartDma func_80048690

/* io/spgetstat.c (libultra/41240.c) */
#define __osSpGetStatus func_80040640

/* io/epirawwrite.c, io/epirawread.c (libultra/49B30.c) */
#define __osEPiRawWriteIo func_80048F30
#define __osEPiRawReadIo func_800490C0

/* io/viswapcontext.c (libultra/41A70.c) */
#define __osViSwapContext func_80040E70

/* symbol_addrs names __osSiRawReadIo/__osSiRawWriteIo as the Sp ones */
#define __osSiRawReadIo __osSpRawReadIo
#define __osSiRawWriteIo __osSpRawWriteIo

#define bzero _bzero

/* gu/sintable.h */
#define sintable D_8006DEF0

#endif
