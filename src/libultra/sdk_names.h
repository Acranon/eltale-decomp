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

/* io/siacs.c data */
#define siAccessBuf D_800957E0
#define __osSiAccessQueue D_800957E8
#define __osSiAccessQueueEnabled D_8006EB20

/* io/pfsisplug.c */
#define __osPfsGetInitData func_8004B600

/* io/contpfs.c data (J inode cache) */
#define __osPfsInodeCacheBank D_8006EB44
#define __osPfsInodeCacheChannel D_8006EB40
#define __osPfsInodeCache D_80095800

/* controller */
#define __osContPifRam D_800956F0

/* io/siacs.c, io/sirawdma.c  */
#define __osSiCreateAccessQueue func_80046BD0
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
#define __additional_scanline D_8006DEEC

/* os/initialize.c data */
#define osViClock D_8006CD08

/* symbol_addrs names __osSiRawReadIo/__osSiRawWriteIo as the Sp ones */
#define __osSiRawReadIo __osSpRawReadIo
#define __osSiRawWriteIo __osSpRawWriteIo

#define bzero _bzero
#define bcmp func_8004B6D0

/* gu/sintable.h */
#define sintable D_8006DEF0

/* controller pak (J-era io files) */
#define __osPfsGetStatus func_80046C90
#define __osPfsRequestOneChannel func_80046D60
#define __osPfsGetOneChannelData func_80046E24
#define __osPfsSelectBank func_80046EC0
#define __osContRamRead func_80046F40
#define __osPfsLastChannel D_8006EB30
#define __osSumcalc func_80047170
#define __osIdCheckSum func_800471E4
#define __osRepairPackId func_800472E0
#define __osCheckPackId func_80047630
#define __osGetId func_80047794
#define __osCheckId func_80047940
#define __osPfsRWInode func_80047A14
#define __osContAddressCrc func_80048740
#define __osContDataCrc func_80048810
#define __osContRamWrite func_800488B0

#define osPfsFileState func_8003DEA0
#define osPfsFreeBlocks func_8003E080
#define osPfsAllocateFile func_8003E220
#define osPfsDeleteFile func_8003E6A0
#define osPfsReadWriteFile func_8003E9E4
#define osPfsRepairId func_8003ED60
#define osPfsNumFiles func_8003EDC0
#define osPfsChecker func_80047CF0
#define osPfsFindFile func_80048BE0

#endif
