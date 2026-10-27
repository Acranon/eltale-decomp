# Ending_DrawSprites

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/ovl_ending/E22690.c`](../ovl_ending/E22690.c)
- Retail assembly: [`asm/nonmatchings/ovl_ending/E22690/Ending_DrawSprites.s`](../../asm/nonmatchings/ovl_ending/E22690/Ending_DrawSprites.s)
- Retail code size: `0x103c` bytes
- Current gap: 25 linked ROM words (NON_MATCHING C in the source); length and frame exact.
- Specific blocker: Second packed texrect step folds an extra temporary and rotates t3/t4 thereafter.
- Next discriminating test: Use stock-verified ugen trace to alter the one temp release without changing command value.
- C: in [`src/ovl_ending/E22690.c`](../ovl_ending/E22690.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/d1-overlay/func_8020D98C_ovl_ending_25words.c` (SHA-256 `866f6f94c888dd7c8ec9819fb994083132383c5511a7f4d526fad6c1908e4a7e`)
- Detailed research reports: [ REPORT.txt ](reports/codex__d98c-focus__REPORT.txt), [ REPORT-resume.txt ](reports/codex__overlay-oct26__REPORT-resume.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: linked NON_MATCHING build against retail with asm-differ, every instruction. The 25 words are
  t4/t9 and t3/t5 swapped in the flipped texrect block and at the loop end. The data addresses that show as
  different (D_8022BB10.., D_8022BB38, D_8020F718/F748) are all 0x30 lower because func_8020E9C8 is shorter
  in this build and the overlay's data moves up; the symbols are the same.
- The draft used the pre-D2 names (D_8022BB10.., D_8022BB38): renamed to the module's `_ovl_ending`
  objects. GFX_TEXRECT_STEPS is defined in the file's NON_MATCHING block.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Ending_DrawSprites** (0x103C bytes)
  - w7 s1: Sprite renderer (bubble sort plus texrect). Draft is 106 words off, all register renaming starting at the flipY gSPTextureRectangle (retail puts -0x400 in t3, ours t4). Scratch d98c_q.c. Facts found: render mode is G_RM_XLU_SURF/G_RM_XLU_SURF2. flags must be s32 and the clip adds are written as shift + frac. IDO gives every function-scope scalar a stack slot in declaration order (first declared = highest address), so the frame only matched with this order: s32 i; rect; 7 scalars + 2 unused; list[150]; tmp; 2 unused. Without those unused scalars the frame size and offsets do not match.
  - w7 s2: Unchanged at 106 register words, starting at the flipY li -0x400 (t3 vs t4). Swept 'if (!x) { }' fakes after every statement for obj/flags/fadeDone/idx/entry: nothing below 106.
  - w7 s3: Still 106 words: t-register numbering from the flip block's B3 word on (retail t9/t5, mine t8/t7). All earlier instructions match register for register, so the cause is not visible in the output. Tried rect.dsdx = -rect.dsdx, the order of the dsdx/dtdy init, combined init, and do{}while(0) wrappers. Warning: permuter results for ovl_ending GBI functions do not carry over. Its preprocessed base scores 184 words in the real file (106 for the hand version), so its macro expansion or context differs.
  - w7 s4: Still 106 words. It is not a statics problem: function-local statics for BB10..BB1C make it worse. The first ugen-order divergence is the flip-s block's RDPHALF_2 word, where rect.dtdy/dsdx load into t9/t5 in retail and t8/t7 in mine. Everything scheduled before it is identical. Tried with no effect: joining macro invocation lines, reordering/reassociating (s+sw-1), and '*4' for '<<2'. A fake 'if (rect.dsdx){}' only made it worse.
  - w7 s5: Still 106 words (normalized diff 0, registers only). One ugen temp in the dsdx/fallthrough texrect's RDPHALF_2 word (t8/t7 where retail has t9/t5) shifts everything after it. Tried with no fix: casts and masks on every macro argument (two hill-climbs, best 69 using invalid lh casts), constant spellings for -0x400, empty-if insertions, hand-expanded texrect macros with join/split line search, operand orders. decomp-permuter is useless here: it scores deleting code as better.
  - Codex D1 implementation: D1 pass:106 to25 actual differing ROM words, full link verified with no collateral differences. Same split high-half shift technique as intro E108. Remaining ugen/as1 temporary rotation is shared with E108; exact masks/identity forms and safe temps tried are listed in codex/d1-overlay/REPORT.txt.
  - Claude retry: codex 25-word draft reproduced in the D2 file (draft ~/eltale-notes/claude/rpc/d98c_25w_ovlnames.c, bss names with _ovl_ending). A 128-variant sweep of RDPHALF_2 spellings per texrect (stock _SHIFTL, (u32)<<16, codex 13+3 split, plain <<16; masked/unmasked dtdy) found nothing below 25; the third (plain) texrect's dsdx load needs t7 where we get t4.
