# Item_UpdateInventoryMenu

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/25B20.c`](../25B20.c)
- Retail assembly: [`asm/nonmatchings/25B20/Item_UpdateInventoryMenu.s`](../../asm/nonmatchings/25B20/Item_UpdateInventoryMenu.s)
- Retail code size: `0xd28` bytes
- Current gap: 742 object words; code 0xCF8 vs 0xD28, frame 0x148 exact. Retail keeps the counters in registers and unrolls the 0x95-entry shift loop by 4; the C's `volatile n` keeps the counter in memory and the loop rolled, and later homes and registers differ.
- Specific blocker: The base draft has two extra saved registers and frame 0x158 vs retail 0x148. Volatile count matches the prologue; volatile n gets the frame but puts scroll X in ra and expands the first loop.
- Next discriminating test: Recover the texture-pointer, counter and scroll-value lifetimes together; then reconstruct command macros and local homes.
- C: in [`src/25B20.c`](../25B20.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_80025318_volatile_n_742words.c` (SHA-256 `f1579fdc231611e3e7c7b6a4e32c2b4b807737585f9265de788c9bda6a7a5dc1`)
- Detailed research reports: [ REPORT.txt ](reports/codex__gfx-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent** (one note).

- Read the whole retail asm against the C: the three display lists and two `Item_DrawMenuFrame` boxes; scroll `x` from `input_stick_x` (dead zone +-5); the count loop over `item_inventory[item_menu_scroll]` (stop at 0xFF, at most 8); the `item_menu_stick_accum` accumulator (reset on sign change, +-250 thresholds), the `item_menu_cursor`/`item_menu_scroll` cursor and window moves with the `item_inventory[item_menu_scroll + count - 1] == 0xFF` undo and the `changed` counter guarding `Sfx_Play(0, 3, 0xFF)`; the free-slot scan into `freeSlots[]` (`8 - n`); the item loop (slot lookup in `item_icon_cache_ids`, reuse of `*--fp` with `item_icon_cache_ids[k] = *p` and `Dma_ReadRom(&D_D384B0[(*p << 8) + 0x400], tex, 0x100)`, else `item_icon_cache_tex[(8 - k) * 0x100]`), every Gfx word of LoadTextureBlock (CI 8b 16x16), the highlight EnvColor/TLUT switch on `item_menu_cursor == count - n` with the pre-decrement `n`, TextureRectangle at `x, 0x20C` step 0x44; the cursor `x = item_menu_cursor * 0x44 + 0x1D4`, `y = 0x1F0 - (((sins(item_menu_bob_phase & 0x7FFF) >> 13) << 2) & 0xFFFF)` (retail `sra 11` + `andi 0xFFFC`, same value); the `count == 8` arrows (`sins((item_menu_bob_phase * 2) & 0x7FFF) >> 13`, LoadTextureTile words, the four rectangles and their tests on `item_menu_scroll` and `item_inventory[item_menu_scroll + 8]`); the two `Text_DrawEncodedString` texts; the delete path (`input_pressed_buttons & 0xA000`, `Item_TryUse`, shift of `0x95 - item_menu_scroll - item_menu_cursor` bytes, `0xFF` terminator, `D_8004DCA0 &= ~1`, `Fade_Start(6, 4, fade_black_ramp_dim)`, cursor/window fix-up) and `item_menu_bob_phase += 0x300`, skipped (as in retail) when the count is 0.
- Note: `n` is `volatile` (from the closest draft). It only keeps the counter on the stack; the values, loads and stores of game data are the same.
- Bugs fixed: none.
- Open: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Item_UpdateInventoryMenu** (0xD28 bytes)
  - w4 s2: Not attempted (0x1118 and 0xD28 bytes). Item_UpdateInventoryMenu also has the static-style RMW pattern on item_menu_scroll/C1A0/C1B0/item_menu_bob_phase.
  - w4 s3: Probably D2-blocked: item_menu_bob_phase is in .data and only this function references it, so it looks like a function-local initialised static. Making it a local static reproduces the retail RMW exactly; as an extern it gets CSE'd into an s-reg. Draft at about 800 words (frame 0x158 vs 0x148; the extra s-regs hold the 0xFF constant and count) in wip/func_80025318_draft_e.c. Findings: scroll and x are one variable (s1). The flag is `changed++` (not `= 1`) so the `changed--` survives. The second loop counts n down with `*fp++ = 8 - n`. The item loop is `n = count; while (n != 0 && *p != 0xFF)` with i written as `count - n`. Use &D_D384B0[(*p << 8) + 0x400]. item_menu_scroll/C1A0/C1A4/C1B0/C1B8 are shared with other functions in the file, so they are not local statics.
  - w4 s4: Still waiting on D2. They need function-local statics. .bss is one blob (yaml line 315), and the guide forbids moving data now, so these cannot land in D1. Ready C is in scratchpad wip/D2_*.c and wip/func_80025318_draft_e.c.
  - w4 s5: Still blocked until D2, and I confirmed why this session. With `extern u16 hud_spirit_marker_phase` instead of `static`, IDO computes the address once into a register (lui/addiu t2, then lhu/sh 0(t2)). Retail uses a separate lui/%lo pair for each access, which is the file-static pattern. 19 diff rows, and every extern variant I tried gave the same or worse ([] array, s16, pointer, explicit x = x + c). Ready C is still in scratchpad wip/D2_*.c.
  - w4 s6: Also needs D2, confirmed from the asm. item_menu_cursor and item_menu_scroll use the static-style separate lui/%lo for each load and store, while item_menu_stick_accum uses the extern-style shared address register, so some of its variables are function-local statics. Separately, draft_e is far from matching: 902 diff lines, frame 344 against retail 328, and it uses s6/s7 where retail uses only s0-s5.
  - Codex review: Audit classification: D2 companion only, dependency suspected. C19C/C1A0 and related state have shared users; repeated direct lui accesses alone do not prove function-local statics. Test private 4F4C0 separately and repair the substantial frame/structure mismatch.
  - Claude D2r2: Audit done, data landed (main 844bac5); function still GLOBAL_ASM. Users: item_menu_scroll/C1A0/C1A4/C1B0 are shared with Item_InitInventory, item_inventory with 113F0/30600, so they are file-scope; item_icon_cache_tex (u8[8][0x100], the draft's type), C9B7/C9C0 (interior labels) and item_menu_bob_phase are used only here. 25B20.c now owns .data 8004F4A0..8004F4D0 (item_can_use_handlers/B0 handler tables, item_menu_bob_phase u16 file-scope for now) and .bss 8008C190..8008CA50. draft_e with the data in the file: 801 words (item_menu_bob_phase as a function static: 803; local pointers for C19C/C1A0: 796-798). Still diverges from +0 (frame 0x158 vs 0x148, s6/s7). Retail stores C19C and reloads it with a fresh lui; the draft CSEs &C19C into a register. It needs structural work, it is not a data problem. Copy of the draft: ~/eltale-notes/claude/d2r2/func_80025318_draft_e.c.
  - Claude retry: not attempted (structural, frame 0x158 vs 0x148).
