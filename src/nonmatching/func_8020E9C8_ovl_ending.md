# func_8020E9C8_ovl_ending

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/ovl_ending/E22690.c`](../ovl_ending/E22690.c)
- Retail assembly: [`asm/nonmatchings/ovl_ending/E22690/func_8020E9C8_ovl_ending.s`](../../asm/nonmatchings/ovl_ending/E22690/func_8020E9C8_ovl_ending.s)
- Retail code size: `0xcbc` bytes
- Current best gap: 757 object words; frame 0x198 vs 0x1A8.
- Specific blocker: Statics are available but TLUT/settile pointer homes and arg0 reloads are wrong; code is 0x24 bytes short.
- Next discriminating test: Reconstruct first texture command and stack homes before register tuning.
- Saved function-only C attempt: [`func_8020E9C8_ovl_ending.draft.c`](func_8020E9C8_ovl_ending.draft.c)
- Original whole-source snapshot: `/home/sean/eltale-notes/claude/d2r2/e9c8_statics_757.c` (SHA-256 `05d0d0a397362b07e3c71c451d40eae8675f5c2cfa13280e9b1e5c3e514ef32f`)
- Detailed research reports: [ REPORT-resume.txt ](reports/codex__overlay-oct26__REPORT-resume.txt)

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **func_8020E9C8_ovl_ending** (0xCD8 bytes)
  - w7 s1: Large GBI function that uses .data statics D_8020F69C..F6B4, likely function statics. Not attempted beyond m2c.
  - w7 s2: First attempt: full C draft (e9c8.c) written from GBI macros: gDPLoadTLUT_pal256, two gDPLoadTextureTile CI 8b plus gSPTextureRectangle per 6-line strip, y < 222, render mode G_RM_AA_XLU_SURF/2. Its 31 static accesses (F69C..F6B4) are rewritten through 31 unique symbols by gen_e9c8.py, and scroll is a local because retail keeps F69C in f16. Still about 700 words off: frame 0x1A0 vs 0x1A8, retail hoists B3/B4 into fp/s7 where mine hoists E7/0x04000400, and retail moves the D_8022BAF0 load above the F6B4 store. Wait for D2.
  - w7 s3: Not re-drafted. Its statics are accessed with separate lui instructions, so the AT trick can work. The blocker is register priority: retail hoists 0xB3000000/0xB4000000 (texrect RDPHALF words) into fp/s7, and the draft hoists E7 and 0x04000400. Each constant has 2 uses per loop iteration, so this is a tie. Draft: scratchpad w7s2/e9c8b.c.
  - w7 s4: Its D_8020F69C..F6B4 are function-local statics (ending .data). A statics version (scratchpad w7s4/e9s1.c) is still far off (757 words): retail spills arg0 to its home slot (frame 0x1A8) and keeps B3/B4 in fp/s7, and mine keeps arg0 in s2. This needs D2 and real work. The AT draft from w7s2/e9c8b.c scores 703.
  - w7 s5: Not retried in depth. The best AT draft (w7s2/e9c8b.c) is still about 700 words / normalized 365. It needs D2 statics (D_8020F69C..F6B4).
  - Claude D2r2: not matched. Data is in place (F69C..F6B4 are globals in E22690.c right before its pragma; make them function statics with their initializers 32767.0f/0/0/0/1/0/0 when it becomes C). The w7s4 statics draft with initializers (~/eltale-notes/claude/d2r2/e9c8_statics_757.c) is still 757 words: frame 0x198 vs 0x1A8, arg0 kept in s2 (retail spills it to its home and reloads it twice), B3/B4 not hoisted into fp/s7. Not register-only; needs the missing 16 bytes of homes found first.
  - Claude retry: D2r2 statics draft ported (757 words, unchanged). Retail keeps the TLUT/settile _g pointers in a3/t0/t1 and stores w1 late, which the draft doesn't; not pursued.
