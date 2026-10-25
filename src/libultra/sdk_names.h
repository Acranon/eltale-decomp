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

/* audio: synthesizer.c */
#define _collectPVoices func_80039F18
#define __freeParam func_80039F78
#define alAudioFrame func_80039FC8

/* audio: event.c (evtq) */
#define alEvtqFlushType func_80042130
#define alEvtqNextEvent func_80042370
#define alEvtqNew func_800423FC

/* audio: cseq.c */
#define alCSeqGetLoc func_8003BAF0
#define alCSeqSetLoc func_8003BB90
#define alCSeqNextEvent func_8003BD54
#define alCSeqNew func_8003C04C
#define alCSeqNewMarker func_8003C160
#define alCSeqGetTicks func_8003C2CC
#define alCSeqSecToTicks func_8003C2D4
#define alCSeqTicksToSec func_8003C3D0
#define __alCSeqNextDelta func_8003C43C

/* audio: seq.c */
#define alSeqGetLoc func_8004AD60
#define alSeqSetLoc func_8004AD7C
#define alSeqGetTicks func_8004AD98
#define alSeqNextEvent func_8004ADF4
#define alSeqNewMarker func_8004AF78
#define alSeqSecToTicks func_8004B098
#define alSeqTicksToSec func_8004B17C
#define __alSeqNextDelta func_8004B1D0
#define alSeqNew func_8004B2A8

/* audio: seqplayer.c (shared with csplayer.c) */
#define __setInstChanState func_80044AB0
#define __resetPerfChanState func_80044B04
#define __initFromBank func_80044B84
#define __vsDelta func_80044C40
#define __vsVol func_80044C64
#define __seqpReleaseVoice func_80044CEC
#define __voiceNeedsNoteKill func_80044E18
#define __unmapVoice func_80044EC0
#define __postNextSeqEvent func_80044F30
#define __vsPan func_80045084
#define __lookupVoice func_800450CC
#define __mapVoice func_80045140
#define __lookupSoundQuick func_800451B0
#define __seqpStopOsc func_800460F0
#define __initChanState func_800461F4
#define alSeqpNew func_80046264

/* audio: load.c, env.c, sndplayer.c */
#define alRaw16Pull func_80042FD4
#define alAdpcmPull func_800434AC
#define _ldexpf func_80043C50
#define _frexpf func_80043C78
#define alEnvmixerPull func_8004435C
#define alSndpNew func_8003CC94

/* audio: drvrNew.c references (pull/handler functions) */
#define alSavePull func_800449F4
#define alMainBusPull func_80042CE0
#define alResamplePull func_80043A3C
#define alFxPull func_8004AA1C
#define alFxParamHdl func_8004A7A8
#define init_lpfilter _init_lpfilter

#endif
