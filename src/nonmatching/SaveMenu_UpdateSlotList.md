# SaveMenu_UpdateSlotList

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/30600.c`](../30600.c)
- Retail assembly: [`asm/nonmatchings/30600/SaveMenu_UpdateSlotList.s`](../../asm/nonmatchings/30600/SaveMenu_UpdateSlotList.s)
- Retail code size: `0xdcc` bytes
- Current gap: 309 object words; code 0xDB4 vs 0xDCC, frame 0x60 exact. Retail keeps the `~7` mask in s1 (`and`) where the C uses `andi 0xFFF8`, and spills the wobble value around the arrow calls; stack homes and registers differ.
- Specific blocker: 14-byte copy is known; pointer homes and late flag/cursor lifetimes differ.
- Next discriminating test: Recover named homes and six missing instructions before chasing registers.
- C: in [`src/30600.c`](../30600.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui-resume/30600.unmatched.c` (SHA-256 `dd034ae018369ae3d4a07eae226fd5ae74f39d224d09112c64727dc911383974`)
- Detailed research reports: [ REPORT.txt ](reports/codex-ui-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent** (one note).

- Read the whole retail asm against the C: the 14-byte copy of `D_80061650` to the stack, the `0x20` scroll case (`idx = save_menu_selected_slot - 1`, or 0 with `save_menu_flags &= 0xFFDF`), both save-slot blocks (`-2` empty slot shows the buffer text, `unk1 == -1` skips), the highlighted/plain call sets and colours (0xA / 0x48), the four `unk24..27` digits, both jump tables on `unk3C` (15..30, the nested `unk40` cases of 23), the minutes/seconds loop on `unk38`, `unk3A`, `unk4`, `unk8`, the second block guarded by `ptr->unk0 != -1 && flag == 0` with the buffer text at y 0x7F, the up/down arrows (`save_menu_selected_slot >= 2`, or `== 1` without `0x20`; `ptr < &save_menu_file_entries[16] && ptr[1].unk0 != -1`), the cursor, and the input part (`arg0 != 1`; `input_stick_y` +-20 with the `save_menu_stick_repeat_counter` repeat counter (`lbu`, `++`, `&= 0xF`, two stores), index moves with the `-1`/`< 0` limits, the `0x20`/mode-6 updates, `input_pressed_buttons & 0x8000` on `menu_flags & 0xC` (cases 0, 4, 8) and `& 0x5000`).
- Context (NON_MATCHING only): the draft's field view of `Unk8007A9D0` (same 0x38 size and alignment as the retail-build view), `D_80061650` defined as `Bytes14` with the same asset bytes so the struct copy reads the module's object, `save_menu_stick_repeat_counter` typed `u8` (retail reads it with `lbu`; the retail build keeps its `s8` definition, and the only other user stores 0), externs and prototypes as in the callees' definitions.
- Changed from the draft: dropped the unused `volatile s32 pad_y` (a temporary layout probe that grew the frame to 0x68; it had no accesses).
- Note: if `unk3C` hits a value with no case (or 23 with an unlisted `unk40`), retail reads `n` from its uninitialised stack home (in the second block, the minutes left from the first); the C keeps that read. It is undefined in C, so a PC port should give `n` a defined value there.
- Bugs fixed: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **SaveMenu_UpdateSlotList** (0xE50 bytes)
  - w6 s3: Not drafted (917 and 1052 instructions, -g3, several jump tables, same stack-slot problems as 800301DC). 80030D5C uses a 14-byte local copy of D_80061650 at sp+0x38 and indexes save_menu_save_headers entries by sp5C (0x68 stride).
  - w6 s4: 30600, 883 instructions, drafted for the first time: d5c3.c / drafts/SaveMenu_UpdateSlotList.c. It needs header changes, applied by hook scratchpad/w6/h5c.py: Unk8007A9D0 gets named fields (u16 unk4, unk8; u8 unk24..27; still 0x38 bytes), Bytes14 struct for the 14-byte copy of D_80061650 (a struct copy gives the retail lw/lw/lw/lhu), save_menu_stick_repeat_counter becomes u8, plus externs/prototypes. Frame 96 matches. Struct about 47 of 883. Left: p is register-then-spill in mine but memory-resident from its definition in retail; flag (second use, the cursor offset) is the reverse; one constant-store scheduling difference in block 2. Permuter 25 min: 6335 to 4950.
  - w6 s5: Needs one more named local between n and color and one between buf and p (retail homes are 0x5C, 0x58, 0x54, 0x50, 0x4C, 0x48, buf at 0x38, 0x34, 0x30), but adding them grows mine to 104 because mine has an extra reserved spill slot. Register allocation has to come closer first.
  - w6 s6: 30600. The old draft needs hook h5c.py (Bytes14 etc.) and is around 690 words off. Retail homes are idx 92, flag 88, 84, n 80, X 76, color 72, buf 56, Y 52, p 48, spill 44. There is no home for the e pointer, so retail has no e local; removing it is right. Even with padX/padY and no e, mine puts the spill at 48 with an empty slot at 52, which makes the frame 104 instead of 96.
  - Codex D1 implementation: D1 pass: valid storage-layout lead reduces697 to315 raw instruction words. Code remains3508 vs3532 bytes (24 short); do not include migrated rodata in code-size comparisons. Persistent pointer and color as one-element local arrays, removing e, and idx-before-pointer increment improve prefix. Draft codex-ui/round2/30D5C.best.c and full replay; still GLOBAL_ASM.
  - Claude retry: not attempted (315+ words).
