# Text_UpdateAndDrawWindows

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/337B0.c`](../337B0.c)
- Retail assembly: [`asm/nonmatchings/337B0/Text_UpdateAndDrawWindows.s`](../../asm/nonmatchings/337B0/Text_UpdateAndDrawWindows.s)
- Retail code size: `0xfec` bytes
- Current gap: 18 object words (NON_MATCHING C in the source); length exact, frame exact.
- Specific blocker: Global value, old/new cursor and final constant have wrong constrained allocations.
- Next discriminating test: Use the saved optimizer trace at first divergence while preserving proven field widths and neighboring matches.
- C: in [`src/337B0.c`](../337B0.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui-resume/337B0.unmatched.c` (SHA-256 `e55ea00712e5e50cfdb80e6a3b365fbaf398022f087263d1addc98ec8bebb2a0`)
- Detailed research reports: [ REPORT.txt ](reports/codex-ui-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: linked NON_MATCHING build against retail with asm-differ, every instruction. All 18 differing
  words are register numbers only (D_800616B0 in a1 vs a2, the text-cursor index in v1/s1 vs a1/v0 in the
  two cursor advances, the closing 0xE7000000 in a2 vs a3); opcodes, offsets, constants, branch targets,
  data addresses and call arguments are identical (the jal words differ only because Text_DrawTexturedRect grew by
  4 bytes in this build).
- The C needs the field widths the asm uses (unk10 s8, unk12 u16, unk15 s8). They are set in the struct
  under `#ifdef NON_MATCHING`; every other C function in 337B0.c still compiles byte-identical with them.
  The Bytes4 union and the externs/prototypes are in the file's NON_MATCHING block.
- save_menu_choice_cursor is declared `u8` (its definition in 30600.c); it is only stored (sb), so the draft's `s8` made no
  difference. The unused D_80090E6C/D_80091868/D_80092264 alias externs were dropped.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Text_UpdateAndDrawWindows** (0x106C bytes)
  - w6 s3: Not drafted (917 and 1052 instructions, -g3, several jump tables, same stack-slot problems as 800301DC). 80030D5C uses a 14-byte local copy of D_80061650 at sp+0x38 and indexes save_menu_save_headers entries by sp5C (0x68 stride).
  - w6 s4: 1052-instruction message-window manager, not drafted (m2c output in scratchpad m3050.c).
  - w6 s5: 337B0, 1019 instructions. Drafted for the first time this session; now 18 words differ. Three of those are only relocation forms (D_80090E6C vs text_window_slots+0x9FC) and should be identical after linking. Draft: scratchpad/w6/drafts/Text_UpdateAndDrawWindows.c (= s3050J0.c). It needs the header hook drafts/hook_80033050.py (= h3050i.py), which changes the Unk80090470 fields to unk10 s8, unk12 u16, unk15 s8, makes text_reveal_speed_steps an s8[], adds a Bytes4 union {s8 v[4]; struct {s8 a,b,c,d} s; s32 w;}, and adds externs (D_800616B4 as s32, D_80090E6C, D_80091868, D_80092264, input_pressed_buttons, save_menu_choice_cursor, text_last_choice_index, text_glyph_setup_dl) and prototypes. The frame and every stack slot match. What fixed things: (1) the first block is an unrolled `for (j...)` loop with `u8 c`; (2) window types 1-3 are read through separate externs; (3) all accesses are text_window_slots[idx].x, with no p pointer; (4) the order is a union, and the main loop is an index loop that reads order.v[w]; (5) 0xFF is a literal everywhere (this gives the two hoisted 0xFF registers s5 and s7); (6) the reverse loop is a do/while; (7) `x = D.unk12++; D.unk9C[x++] = D.unk14; c = D.unk14; D.unk14 = D.unk9C[x]; *(D.unk9C + x) = 0xFF;`; (8) `col = text_reveal_speed_steps[c & 7] * D_800616B0; D.unk10 = D.unkF = col;`; (9) the BA4 loop tests D.unk9C[j] directly, with no char variable; (10) `case 1: order.s.a = j; break;` is written on one line (this is -g3 line scheduling); (11) the last two gfx commands are written by hand through a `Gfx *gfx` variable, which gives 2 fewer _g homes. Left, all register coloring: D_800616B0 is in a1 but retail has a2, the advance's old index is in v1 but retail has a1, adv2's new index is in s1 but retail has v0, and the closing 0xE7000000 constant is in a2 but retail has a3.
  - w6 s6: 337B0. Unchanged at 18 words. The hook drafts/hook_80033050.py had to be fixed: it declared Text_OpenWindow as void, which conflicts now that 32D20 is matched (s32). Tried with no effect: a copy variable for D_800616B0, multu operand order, using one variable for both unk12 advances (col/x/y/m/i/tab/max), and a 182-pair variable-merge sweep with pads that keep the frame (best was i<->j at 24 words).
  - Claude b5: No change, 18 words. Splitting the cursor (old = unk12++; [old] / [old + 1]) as u16 or s32 makes IDO CSE more and shortens the function (400+ words); the col++ form is right. Callee prototypes match their definitions. Warning: hook_80033050.py's struct type changes (unk10 s8, unk12 u16, unk15 s8) now break the matched Text_OpenWindow (21 words), so a match here would also need those types via casts inside 33050.
  - Claude retry: hook_80033050's types (unk10 s8, unk12 u16, unk15 s8, Bytes4, externs) no longer break Text_OpenWindow: with them applied via in-file edits, match.py diff shows every other C function in 337B0.c OK, and 33050 is 18 words (a1/a2/a3 vs v1/a1/a2 rotation for D_800616B0, the cursor index and 0xE7000000). A 156-variant declaration-order sweep (no homes change for register locals) and D_800616B0 expression forms (operand order, cast, `if (D_800616B0)`) all stay at 18. Draft with the edits as //SUB lines: C:\Users\Sean\AppData\Local\Temp\claude\c--code\e28e4613-47ce-4c8d-9eb8-47918177bdc8\scratchpad\rpb\best_80033050_18w.c
