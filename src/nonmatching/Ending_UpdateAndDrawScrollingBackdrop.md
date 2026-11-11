# Ending_UpdateAndDrawScrollingBackdrop

Current snapshot: 2026-11-11 (worker w5). Earlier measurements are in the history at the end.

- Live source: [`src/overlays/ending/ending.c`](../overlays/ending/ending.c)
- Retail assembly: [`asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawScrollingBackdrop.s`](../../asm/nonmatchings/overlays/ending/ending/Ending_UpdateAndDrawScrollingBackdrop.s)
- Retail code size: `0xcbc` bytes
- Current gap: **1 masked object word, same size, same frame.** At +0x978 retail has `or s0,a2,zero` and the draft has
  `sw a2,0x1A0(sp)`. Every other word is identical.
- Before this pass: 537 words (27 structural, 386 register-only), code 0xCB8. Before that: 754 words, code 0xC70.
- C: in the source under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`). The seven statics are function statics there;
  the file-scope copies are `#ifndef NON_MATCHING`. The draft is equivalent to retail (the extra statements are dead stores to
  locals and one empty `if`).

## What the source is (each point checked against retail's code)

1. **Seven function statics** (scroll, frame, the two alphas, the two modes, the state), written directly.
2. **`for (i = 0; i < 37; i++)` with `i * 6` spelled out in the macro arguments.** The dead `move t2,zero` is `i = 0`.
3. **`x = (s32) scroll % width;` is the first statement inside each loop** (decides the order of the hoisted words and the
   six spill slots).
4. **The picture's four fields are read into locals** (`width`, `tlut`, `img`, and a 4th nothing uses). The 4th read puts the
   20-variable-read block boundary after the LoadTLUT command and before the PipeSync of `gDPLoadTLUT_pal256`.
5. Eleven named locals with `width` the ninth (home sp+0x184).
6. **One tail: `if (...) { scroll -= ...; } else if (frame == 0x26E8) { state = 1; } return 0;`** (a single `return 0`). With a
   `return 0` inside the first branch there is a second `move v0,zero`, and as1 places `lui t6,0xE700` in a delay slot 0x5C
   earlier (that one placement had been costing an instruction and most of the 537 words).
7. **A dead copy of `(s32) scroll` before each loop.** In the first block it leaves no instruction but gives the conversion a
   second use, which is what makes it a register candidate in a2 there (`mfc1 a2`) and shifts every later candidate up by
   one (x copy a3, the hoisted words t0/t1, `i` t2, width t3, tlut t5, the `_g`s). In the second block retail keeps the copy:
   `or s0,a2,zero`.
8. The float literals 32767.0f (8022BAF0) and 10530.0 (8022BAF8) are this function's .rodata. **For the final match**:
   delete D_8022BAF0/BAF8 from ending_data.c/.h and move this file's .rodata start in eltale.jp.yaml from 0xE420C0 to
   0xE420B0.

## The one word left

Retail's second block has a store-only register variable: `(s32) scroll` copied to s0 at the end of the block before the loop
and never read (s0 is reused inside the loop for `(i * 6) << 5`).

What the as1 lab shows (assembling the `cc -K` ugen listing with one line edited, see Tools): a `move $16,$6` placed in the
block that computes the conversion (block 42), in the loop's pre-header (block 43), or in both, gives **0 differing words**
together with width in t3. So the remaining question is only uopt's: a dead-out variable assigned the conversion, coloured
s0, with width's reload in t3.

What uopt does with the forms tried:

- A dead `v = (s32) scroll` whose only reader is another dead store (`unused = v;` after the loops) survives redundant-store
  elimination. If it is then moved by PRE it stays as a register store; if it is not moved it leaves no store, only the extra
  use of the conversion. Same variable before both loops: PRE puts the second block's store into block 42, where only ra is
  free: `move ra,a2` (149 words; as1 then hoists `li ra,6` above it, which is wrong code). A second variable assigned inside
  the second loop: the store is hoisted to block 43 and takes t3, pushing width to t4 (17 words).
- For s0 the variable needs t3 and t4 unavailable while width still gets t3. Both variables have adjusted save 1.00 and the
  dead variable has the lower bit, so in block 43 alone it is always coloured first. Its live range must therefore cover two
  nodes: block 42 (where t3/t4 hold the `_g`s of LoadSync and LoadTLUTCmd) or the loop's first block (same), with no code in
  the second node. Not found: a second PRE insertion of the same store is impossible, a `* 1` copy changes real code, reads
  that copy propagation removes leave no live unit.
- An empty `if (v) {}` after the loops keeps the variable live with no load instruction, but then it is live across the loop,
  has no profitable register, and is stored to its home: `sw a2,0x1A0(sp)` at exactly retail's slot. That is the landed
  draft (1 word). The same empty `if` before or inside the loop adds a flow-graph node there and changes ~700 words.
- A dead induction variable (`for (i = 0; i < 37; i++, v++)` with `v = (s32) scroll` before it, no reader at all) gives the
  same code as the dead-reader form minus the copy (212 words, one instruction short): the natural-looking symmetric source
  that produces everything except `or s0,a2,zero`.

Next idea: the copy survives the way `i = 0` does (`move t2,zero`): a variable whose readers exist at redundant-store
elimination and are removed afterwards by induction-variable elimination or test replacement. Look for a second-loop-only use
of a `(s32) scroll` variable that strength reduction removes and that puts a (code-free) access in block 42 or in the loop's
first block.

## Tools for this function

- `scratchpad w5/b31.py` (`mk`/`go`: per-block knobs for statements after the fetch, before the loop, loop head/top/bottom,
  and the tail), `tryf.py -v -c 100` (listing aligned by mnemonic), `tr.sh` + `lr.py` + `inblk.py` (every candidate with
  register, order, save, blocks; candidates live in a given block), `cm.py` (code-motion sets per node from `-zdbug:3`).
- **as1 lab**: `asl.py NAME [--rep/--ins/--del line text]` takes the full `cc -K` listing, edits lines of this function,
  runs `as0` + `as1` with the compiler's flags (`as1 -elf -G 0 -p0 -r4300_mul -mips2 -EB -g0 -O2`; the `cc x.s` route adds
  `-noglobal` and does not optimise the same way) and diffs against retail. Unedited it reproduces the compiler's object
  exactly.

## History

- 2026-11-11 (w5): 537 -> 1 word. Single-return tail; dead copies of the conversion; as1 lab.
- 2026-11-10 (w5): 754 -> 537 words, code 0xC70 -> 0xCB8, frame exact. Statics, `for`/`i * 6`, x inside the loop, 4th field
  read, eleven locals.
