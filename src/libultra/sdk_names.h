#ifndef SDK_NAMES_H
#define SDK_NAMES_H

/*
 * Real libultra names for symbols that symbol_addrs.txt still calls func_/D_.
 * Included first by the SDK files that use them. Once the names are applied to
 * symbol_addrs.txt (D3), delete the matching lines here (and this file when empty).
 */

/* os/thread.c data */

/* io/piacs.c data */

/* io/siacs.c data */

/* io/pfsisplug.c */

/* io/contpfs.c data (J inode cache) */

/* controller */

/* io/siacs.c, io/sirawdma.c  */

/* io/spgetstat.c (libultra/41240.c) */

/* io/epirawwrite.c, io/epirawread.c (libultra/49B30.c) */

/* io/viswapcontext.c (libultra/41A70.c) */

/* os/initialize.c data */

/* symbol_addrs names __osSiRawReadIo/__osSiRawWriteIo as the Sp ones */

#define bzero _bzero

/* gu/sintable.h */

/* controller pak (J-era io files) */


/* audio: synthesizer.c */

/* audio: event.c (evtq) */

/* audio: cseq.c */

/* audio: seq.c */

/* audio: seqplayer.c (shared with csplayer.c) */

/* audio: load.c, env.c, sndplayer.c */

/* audio: drvrNew.c references (pull/handler functions) */
#define init_lpfilter _init_lpfilter

#endif
