#include "libultra/sdk_names.h"
#include "PR/os_internal.h"

/* ultralib's kdebugserver.c keeps __osThreadSave in the final ROM (everything
 * else is #ifndef _FINALROM): a data-only file, .bss 80095900..80095AB0.
 * exceptasm uses splat's name. */
OSThread D_80095900; /* __osThreadSave */
