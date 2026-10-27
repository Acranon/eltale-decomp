# Intro_UpdateAndDrawSprites

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/overlays/intro/intro.c`](../overlays/intro/intro.c)
- Retail assembly: [`asm/nonmatchings/overlays/intro/intro/Intro_UpdateAndDrawSprites.s`](../../asm/nonmatchings/overlays/intro/intro/Intro_UpdateAndDrawSprites.s)
- Retail code size: `0x1060` bytes
- Current gap: 23 linked ROM words (NON_MATCHING C in the source); length and frame 0x648 exact.
- Specific blocker: Second texrect step folds one temporary differently and rotates t3/t4.
- Next discriminating test: Find an equivalent C tree that releases the temp while preserving both packed command words.
- C: in [`src/overlays/intro/intro.c`](../overlays/intro/intro.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/d1-overlay/func_8020E108_ovl_intro_23words.c` (SHA-256 `f30153240cc1b752691108033100c33ff5162d83ae85b6d67f47e7cc7ca54321`)
- Detailed research reports: [ REPORT-resume.txt ](reports/codex__overlay-oct26__REPORT-resume.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: linked NON_MATCHING build against retail with asm-differ, every instruction. The 23 words are
  t3/t4 swapped in the flipped (G_RDPHALF_2) texrect block; everything else is identical (jal targets
  differ by the 4 bytes func_8020C6A8 grew in this build).
- The draft used the pre-D2 names (D_802684E0, D_802684B0..BC): renamed to the module's `_ovl_intro`
  objects. GFX_TEXRECT_STEPS is defined in the file's NON_MATCHING block.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Intro_UpdateAndDrawSprites** (0x1068 bytes)
  - w6 s3: DC62B0 sprite renderer (bubble sort + clip + texture load). Draft drafts/Intro_UpdateAndDrawSprites.c is 1047 vs 1048 instructions and the structure is right. It uses IntroRect extended to 14 ints, SortEnt {u32 key; u16 idx}, gDPLoadTextureTile/_4b/pal16/pal256 and gSPTextureRectangle. Remaining: (1) stack layout: retail has r at 0x60C, ents at 0x138, the loop pointer spilled at 0x5C and a 36-byte gap between ents and r; mine has the pointer spilled right under tmp and a frame of 1600 vs 1608; (2) the fade block uses two separate `li 255` registers in retail; (3) temp register renumbering after that point.
  - w6 s4: Stack layout explained. Retail frame 1608 is r (14 ints) on top, then 9 words of scalar homes, then ents[150] at 0x138, then tmp. Scalars declared between r and ents get homes, and each gbi macro's block-scoped `_g` gets a home below the arrays. Moving the scalar declarations between r and ents gives ents at 312 / tmp at 304 exactly; frame 1600 because 8 homes vs 9 (draft e108z.c). Retail spills the loop pointer at sp+92, a compiler temp; an index loop reproduces that but raises struct to 44 through register pressure.
  - w6 s5: Unchanged at struct 16 with a frame of 1600 against retail's 1608. In -O2 overlays an unused pad variable gets no home, so it does not help.
  - w6 s6: DC62B0 (now builds without a hook; the header is in the file). Retail stack: spill 92, tmp 304, ents 312..1512, a 36-byte object at 1512..1548, r 1548..1604. Mine: spill 328, tmp 336, ents 344..1544, r 1544..1600. Adding s32 pad[9] after r does produce the 36-byte gap, but mine's region below tmp is 28 bytes larger than retail's (frame 1632).
  - Codex D1 implementation: D1 pass: now exactly23 differing words in a fully linked ROM, no collateral differences. Retail frame0x648, rect0x60C, sort array0x138, tmp0x130 and iterator spill0x5C all reproduced. Correct clip/fade order plus split unsigned13+3 high-half shifts in first two texrects fix most remaining code. Last issue is ugen temp allocation and as1 folding near second packed word. Readable draft/full replay in codex/d1-overlay/.
  - Claude retry: not attempted (shares D98C's ugen residual).
