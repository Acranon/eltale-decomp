# Text_DrawTexturedRect

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/337B0.c`](../337B0.c)
- Retail assembly: [`asm/nonmatchings/337B0/Text_DrawTexturedRect.s`](../../asm/nonmatchings/337B0/Text_DrawTexturedRect.s)
- Retail code size: `0x400` bytes
- Current gap: 92 object words (NON_MATCHING C in the source); code 0x404 vs 0x400, frame 0xE0 vs 0xD8.
- Specific blocker: Texture-pointer spill and original-type branch are wrong. A 25-word candidate truncated a command opcode and was rejected.
- Next discriminating test: Keep the valid pointer alias; recover GBI macro homes without narrowing the display-list command.
- C: in [`src/337B0.c`](../337B0.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui/round2/34C9C.repaired.best.c` (SHA-256 `9356b907f2a8077a0a3ad49686d0cc30dc52653839305df5d1fa5fc33ffc7f45`)
- Detailed research reports: [ REPORT.txt ](reports/codex-ui-resume__REPORT.txt), [ REPORT.txt ](reports/codex-ui__round2__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: whole function side by side with retail (linked build). The local copies of text_rect_texture_ptrs and
  text_rect_texture_params, every display-list word (E7, FD, F5 with masks/cms/maskt/cmt order, E6, F4, F2, E4/B4/B3) and
  the h argument read from the caller's stack are the same. Differences: frame 0xE0 vs 0xD8 (so h is read
  at sp+0xF0 instead of sp+0xE8, the same incoming argument); retail stores one more `_g` pointer to a dead
  stack home (sp+0x24); retail tests `type != 0` with `bnez a0`, the C compiles `type == 0` as
  `&tex.p[type] == &tex.p[0]` (same result for every type); then register numbering.
- The RDPHALF_1 word of the type-0 rectangle is `((x & 0xF) << 5) << 16 | ((y & 0xF) << 5)` in both.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Text_DrawTexturedRect** (0x400 bytes)
  - w6 s2: 337B0 tile loader using local struct copies of text_rect_texture_ptrs/text_rect_texture_params (TexPtrs5/TexParams5 are declared). Only the evaluation order of the OR terms in gDPSetTile/gDPLoadTile w1 differs: retail puts masks first and lrt before lrs. The permuter changed that order by going through a pointer (new_var=&t->h), but only got the score from 3015 to 1910.
  - w6 s3: Not retried this session beyond the previous notes; drafts unchanged in drafts/.
  - w6 s4: 337B0. Frame fixed by declaring `TexParam *t` first (tex at sp+192, prm at sp+72). Passing masks as prm.e[type].masks while the other fields go through t-> gives the retail SetTile w1 order (draft c9cc.c in scratchpad, struct 12). Left: LoadTile/SetTileSize compute lrt before lrs in retail. Also IDO turns `type == 0` into a pointer compare against &tex.p[0], where retail uses bnez a0.
  - w6 s5: 337B0. Passing lrt as `prm.e[type].h - 1` fixes the LoadTile/SetTileSize lrt-before-lrs order (struct 4, drafts/Text_DrawTexturedRect.c = c9e1.c). The frame is now 224 but retail is 216. Retail stores the PipeSync gfx pointer at sp+36 and tests `bnez a0` on type; mine compares a pointer reloaded from sp+8.
  - w6 s6: 337B0. Struct 4. Retail's frame layout is: one unused local at the top (sp+212), tex at 192, prm at 72, four -g3 _g homes at 36-48, and &tex.p[type] stored to sp+4 and never reloaded. Mine (t pointer) has a 224 frame and rewrites type==0 as a comparison of the spilled &tex.p[type] against &tex. Without t the frame is 216 but the LoadTile order breaks. Declaring ty = type and using it everywhere gives the four homes but loses the sp+4 store (n9/e2.c, struct 3, 209 words). Tried: !type, switch, swapped branches, pad locals, img variable. 15 minutes of permuter gave junk.
  - Codex D1 implementation: D1 pass: valid partial improvement136 to92 raw words, still1028 vs1024 bytes. Stack-aware, macro-line-faithful search replayed12 candidates. Rejected25-word candidate because it truncated the E4000000 command opcode through volatileu16; semantically repaired source returns to92 words. Saved codex-ui/round2/34C9C.repaired.best.c.
  - Claude retry: w6 draft still 136 raw words against the current file (frame 224 vs 216); not pursued.
