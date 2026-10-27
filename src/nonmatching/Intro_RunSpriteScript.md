# Intro_RunSpriteScript

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/overlays/intro/intro.c`](../overlays/intro/intro.c)
- Retail assembly: [`asm/nonmatchings/overlays/intro/intro/Intro_RunSpriteScript.s`](../../asm/nonmatchings/overlays/intro/intro/Intro_RunSpriteScript.s)
- Retail code size: `0x9d0` bytes
- Current gap: 609 masked object words (NON_MATCHING C in the source; one extra instruction near the top shifts the rest); code 0x9D4 vs 0x9D0, frame 0xF0 exact.
- Specific blocker: The only differences are sw/lw v1 at sp+0x74 instead of retail sp+0x70. Uopt first assigns temp id0 to first-loop entries[index] and temp id1 to steps[index]; the later spill reuses id0.
- Next discriminating test: Find an equivalent first-loop source that changes the temp reuse/order without changing code, saved registers or packet values.
- C: in [`src/overlays/intro/intro.c`](../overlays/intro/intro.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/overlay-oct26/c6_2words.full.c` (SHA-256 `ff4622b99e946b3188e3e98f355af7eb38d69e2140aa012219085e8801b1a9a7`)
- Detailed research reports: [ C6A8-focused-report.txt ](reports/codex__overlay-oct26__C6A8-focused-report.txt)

## Equivalence

Verdict: **equivalent.**

- One object, one definition: the draft made D_80276F44 (and the unreferenced D_80276F48 gap) function
  statics and re-declared D_80277074/D_80277078 as block externs. In the source they are the module's
  existing .bss globals, so those declarations were dropped. With a global, IDO keeps &D_80276F44 in a
  register (lui/addiu once) instead of a lui/%lo per access: that is the extra instruction, and the two
  increments at the top load/store D_802684C0, D_80276F44 and D_802684D4 in a different interleaving (same
  values, same final stores).
- Checked: linked NON_MATCHING build against retail with asm-differ, every instruction. Apart from the
  above, the only differences are the v1 spill at sp+0x74 vs 0x70 and jal targets shifted by the 4 bytes.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Intro_RunSpriteScript** (0x9D0 bytes)
  - w6 s3: DC62B0 cutscene/cue engine. Full draft in drafts/Intro_RunSpriteScript.c, 627 of 628 instructions. Blocked on data: retail never keeps the address of D_80276F44 / D_80277074 / D_80277078 in a register (a separate lui/%lo on every access), while D_802684C0 and the other D_802684xx are kept in one. A test showed that IDO does exactly this for function-scope `static` locals and for nothing else (extern, volatile, file-static and block-scope extern all keep the address in a register). With static locals the start of the function matches. So these are probably static locals, which means moving data/bss (step D2). Frame is 248 vs 240.
  - Claude D2r2: not matched; it is Ending_RunSpriteScript's twin. DC62B0.c owns intro .bss 802684B0..80277080 and .data 80212230..80212250; 76F44, an unreferenced 0x12C-byte gap (76F48), 77074 and 77078 are file globals until this is C (then move them in as statics, in that order). Best draft ~/eltale-notes/claude/d2r2/c6a8_28struct_frame8.c: the C254 C ported (same types: 684C0/CC/D0/D8 u32, do-while loop, the same empty `if (D_802684D8) {}` fake for the tail, entries[entries[j].unk24] without the cast), 76F44 static, 77074/77078 `static volatile` (retail reloads 77078 right after storing it and never keeps 77074 in a register). Left: frame 0xF8 vs 0xF0 (8 bytes of homes below the spill: spill 0x78 vs 0x70, grp 0xEC vs 0xE4; each GBI macro in the fade block costs 8, removing any one gives 0xF0), the `slot == -1` break laid out inline instead of as a stub after the loop, ~0x800000 not hoisted into s7, the fade block's constant hoists, and s-register numbering.
  - Claude retry: 470 -> 37 words, all s0/s1 (entries/steps swapped through both loops) plus an 8-byte frame (0xF8 vs 0xF0). Draft ~/eltale-notes/claude/rpc/c6a8_37w.c (remove the file's D_80276F44/D_80276F48 globals; D_80277074/78 stay file globals). Fixes: the `slot == -1` stub is `if (slot != -1) { body; D_802684D4 = 0; } else { break; }` inside the do-while; 76F44 (and the 76F48 gap) are function statics but 77074/77078 are plain file globals (not static, not volatile: retail stores 77074 then compares the register, reloads it after the Gfx stores); `s32 j` (not u32; permuter) fixes the s3/s4/s5 rotation and the loop-2 shift-add; GFX_WORDS(0xB900031D, 0x504240) is gDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2). Frame: the extra 8 bytes are below the v1 spill (ours 0x78 vs 0x70, listIdx 0xEC vs 0xE4); removing any one fade-block GBI macro or one named local fixes the size but puts the spill at 0x74, so it is not that. Two 15-min permuter runs (--stack-diffs) found only fade-block scheduling.
