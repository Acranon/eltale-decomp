# Ending_UpdateAndDrawScrollingBackdrop

Current snapshot: 2026-11-10 (worker w5). Earlier measurements are in the history at the end.

- Live source: [`src/overlays/ending/ending.c`](../overlays/ending/ending.c)
- Retail assembly: [`asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawScrollingBackdrop.s`](../../asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawScrollingBackdrop.s)
- Retail code size: `0xcbc` bytes
- Current gap: 537 masked object words, but that number is one missing instruction shifting the tail. Aligned by mnemonic:
  **27 instructions differ in kind/position, 386 differ only in a register**. Code 0xCB8 vs 0xCBC; frame 0x1A8 exact;
  the six spill slots (sp+0x40/44/4C/54/60/6C) and width's home (sp+0x184) exact; the loop bodies are retail's instruction
  for instruction (t-registers rotated by one).
- Before this pass: 754 words, 410 structural, code 0xC70, frame 0x198.
- C: in the source under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`). The seven statics are function statics there;
  the file-scope copies are `#ifndef NON_MATCHING`.

## What the source is (established this pass, each one checked against retail's code)

1. **Seven function statics** (scroll, frame, the two alphas, the two modes, the state), written directly: `alpha1 += delta;`
   then the clamp on the static, `frame++`, `scroll -= (f32) width / (f32) arg1`. The second `swc1` of each alpha is the
   write-back at the end of the block that last uses it, not a second assignment.
2. **`for (i = 0; i < 37; i++)` with `i * 6` spelled out in the macro arguments** (as in the intro's fade loop). uopt hoists
   the derived inductions' initial values (0, 5, 6) and leaves a dead `move tN,zero` for `i` above the `if`: retail's
   `or t2,zero,zero`.
3. **`x = (s32) scroll % width;` is the first statement inside the loop**, not before it. This decides the order in which
   the loop-invariant words are built before the loop (see "copy propagation order" below). With `x` assigned before the loop
   the order is (x-1 words, x+7, 304-x, x<<5, 311-x, x<<2 words); inside, it is retail's (311-x, x<<2 words, x-1 words, x+7,
   304-x, x<<5) and the temp slots come out exactly.
4. **The picture's fields are read as `ending_picture_defs[arg0].width / .tlut / .img` into locals, and the 4th field is read
   too** (into a local nothing uses; no code). That read is what puts the basic-block boundary after the LoadTLUT command and
   before the PipeSync of `gDPLoadTLUT_pal256` (see "varrefs" below); without it the boundary falls inside that PipeSync.
5. Eleven named locals with `width` the ninth (its home is sp+0x184); which of the others are unused is not visible.
6. The float literals: 32767.0f (8022BAF0) and the double 10530.0 (8022BAF8, `frame == 10530.0`) are this function's
   .rodata, now defined as data in ending_data.c. **For the final match**: write them as literals (the draft does), delete
   D_8022BAF0/BAF8 from ending_data.c/.h, and move this file's .rodata start in eltale.jp.yaml from 0xE420C0 to 0xE420B0.

## What is left

All of it follows from the colouring of a few low-priority candidates in the two straight-line blocks before each loop:

- Retail keeps `(s32) scroll` in **a2** (`mfc1 a2`; in the second block also a copy `or s0,a2,zero` before the loop). Ours
  computes it into a t-register in the first block and into s0 in the second. With a2 taken, retail's later candidates each
  move up one: the x copy a3 (ours a2), `(x<<2 & 0xFFF)<<12` t0 (a3), the x-1 word t1 (t0), `i` t2 (t1), width t3 (t2), tlut
  t5 (t4), and the `_g` of SetEnvColor/SetTextureImage/TileSync shift the same way. Everything else (the `lui 0xE700`
  position, where s1=5/t5=0 are loaded, the t-register rotation in the loops, the missing instruction) is a consequence.
- From the cost trace: the conversion candidate (bit 151, `ucvt` of the truncation) has adjsave 1.00 and blocks 42..43 only.
  For retail's a2 it must be coloured after the `_g` of the PipeSync that ends the first block (a1, save 3.00, lower bit) and
  before the `_g`s of the second picture's first block (save 3.00, higher bits): that is **save exactly 3.00, i.e. two uses
  and one definition per block, and a live range that includes the first picture's pre-loop block**. Something in the source
  uses `(s32) scroll` twice. Tried without effect (uopt forwards them away): `x = (s32) scroll; x %= width;`, a u32
  temporary, a dead `unused = (s32) scroll;` before/after, `(u32)` casts. A variable assigned before the loop
  (`sx = (s32) scroll;`) breaks point 3 above.
- Next test: find the second use. Candidates: the quotient (`(s32) scroll / width` gave a different word order, but only
  that spelling was tried), a comparison on `(s32) scroll` whose body is empty, or `x` computed in a second place (e.g.
  once before the loop for the TLUT block and again inside the loop).

## Tools for this function

- `scratchpad w5/b1.py` builds the function from a template with knobs (`gen({...})`), `tryf.py -v -c 100` prints the
  listing aligned by mnemonic with a "structural / operand-only" score, `tr.sh` + `lr.py` print every candidate with
  register, colouring order, save, temp slot and blocks (uses `~/w5tmp/uoptw5`, built by `mkuopt.sh`).

## General findings (also in FABLE_FINDINGS.md)

- **uopt ends a basic block after 20 variable reads** (`varreflimit`, uoptinput.c: checked between statements; a read
  counts when the variable was not assigned earlier in the same block by a forwardable assignment; loads through a global's
  address do not count, locals/params/statics do; each GBI `_g->words.wN = ...` is one read of `_g`). GBI-heavy code is
  therefore cut into blocks at places that depend on the number of variable reads, and register save/reload points, `_g`
  copies (`or a3,v0,zero`), and candidate live ranges all move with them. One extra or missing read of any variable, even in
  a statement that generates no code, moves every later boundary.
- **Copy propagation walks the blocks from the last to the first** (statements forward inside a block) and creates the
  replacement expressions in that order; hoisted loop invariants are then emitted, and given temp slots, in that creation
  order. A variable assigned in the same block as its uses is forwarded when the block is read, in source order.

## Equivalence

Verdict: **equivalent.** Same checks as the previous draft (every command word and every static update compared with the
retail asm); the differences from the previous draft are the loop variable (`i`, 37 strips of 6 lines = y 0..216), `x`
recomputed each iteration from values that do not change in the loop, and a field read whose value is unused.

## Earlier history

- w7 s1-s5, Claude D2r2, Claude retry, codex overlay-oct26: drafts from the GBI macros with the statics as globals or as
  statics, 700-757 words; frame 0x198-0x1A0; arg0 kept in s2, B3/B4 not hoisted, `y` as the loop variable, `x` computed
  before the loop, picture read through a `pic` pointer. A volatile pad made the frame match but nothing else.
