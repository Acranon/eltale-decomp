# Text_BuildVisiblePage

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/337B0.c`](../337B0.c)
- Retail assembly: [`asm/nonmatchings/337B0/Text_BuildVisiblePage.s`](../../asm/nonmatchings/337B0/Text_BuildVisiblePage.s)
- Retail code size: `0x37c` bytes
- Current gap: 221 object words (NON_MATCHING C in the source); length exact, frame 0x40 vs 0x48.
- Specific blocker: Rows should stay in a home and be reloaded; draft strengthens the loop and uses extra saved register.
- Next discriminating test: Match the row spill and loop test before adjusting graphics body.
- C: in [`src/337B0.c`](../337B0.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui-resume/337B0.unmatched.c` (SHA-256 `e55ea00712e5e50cfdb80e6a3b365fbaf398022f087263d1addc98ec8bebb2a0`)
- Detailed research reports: [ REPORT.txt ](reports/codex-ui-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: the whole function side by side with retail (linked build). Every load/store (lbu/sb of
  unk9C/unk54C, lhu/sh unk12, lbu/sb unk14, the unk0 OR/AND masks), every constant (0x80, 0xE0, 0xF0,
  0xFF), the signed divisions by 10 and 13, the unrolled copy loop and the Text_ResetStickAdvanceTimer call with the store
  in its delay slot are the same. Differences: one more saved register (s4) and frame 0x40 vs 0x48; cols
  in s0 vs ra; the row loop is laid out as `row + 1 != rows + 1` (retail `row < rows` with rows reloaded
  from sp+0x28), which runs the same rows because row starts at 1 and the loop is skipped when rows <= 0;
  the 0xE0 scan reloads unk9C[j] a little differently (same bytes read, same exit tests).
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Text_BuildVisiblePage** (0x37C bytes)
  - w6 s3: 337B0 text wrap. Logic is complete (drafts/Text_BuildVisiblePage.c, 223/223 instructions). Uses pre-increment indexing `text_window_slots[idx].unk54C[++dst] = ...unk9C[++src]`, which matches the retail address shape. Retail uses 4 saved registers with frame 72 and rows at sp+40; mine uses 5 with frame 64. Permuter (10 min) found that sharing one s32 variable for c and the copy count helps (3480 to 2330) but did not converge.
  - w6 s4: Register pressure and constant-hoisting differences. Retail rematerializes constants and addresses where mine hoists them into s-registers. Permuter: 32D20 7375 to 4015, 35A24 5015 to 1380, only with unnatural edits. 35A24: `if ((p->unk13 = i / 256) < 2)` removes the reload.
  - w6 s5: Unchanged at struct 16 and struct 20. Line-join and operand-order variants on 35350 change nothing.
  - w6 s6: 337B0. Struct 18-20, frame 64 where retail has 72. Retail keeps rows spilled at sp+40 and tests row<rows with slt each iteration, using only 4 s-registers (0xE0 in t5, cols in ra). Mine LFTRs to rows+1 and needs s4. Loop-form variants, variable merges with pads, and 15 minutes of permuter did not help.
  - Claude retry: not attempted beyond reading (retail spills rows to sp+0x28 and reloads idx from its arg home; needs a different register-pressure shape, not a near miss).
