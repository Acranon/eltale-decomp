# MapObj_DrawNearby

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/E2A0.c`](../E2A0.c)
- Retail assembly: [`asm/nonmatchings/E2A0/MapObj_DrawNearby.s`](../../asm/nonmatchings/E2A0/MapObj_DrawNearby.s)
- Retail code size: `0x9c8` bytes
- Current gap: 437 object words; length exact (0x9C8).
- Specific blocker: Address D_80082058 stays hoisted in s7 across calls; retail rematerializes it.
- Next discriminating test: Express the correct owned-state identity without cross-object pointer arithmetic, then restore grid-loop bytes.
- C: in [`src/E2A0.c`](../E2A0.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_8000DE54_438words.c` (SHA-256 `0ec099a6fe47a584f0a50b4fa903aaaa9afdbb6430624551df94f6591c1179b0`)
- Detailed research reports: [ REPORT.txt ](reports/codex__gfx-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the whole asm in order against the C: the counter/pointer resets and the `600.0f`/`-1` stores, the four grid cases (`trunc.w.s` of the cell coordinates, offset tables and counts 0x9D/0x59/9/0x15, default one cell at 0,0), the signed `lb` offsets and the `w`/`h` bounds, `MapObj_CollectCell(*list, list + 1)` and the `unk2` call, the `gSPDisplayList`/`gSPFogPosition` words, the first object loop (anim frame `(flags & 0xFF) + 1` wrapped at `unk6`, `unk16` written back with the high byte reloaded, the `0x100` offset branch with `D_80084238[i - 1]` x/z and the `0.0174...` double), the `guPosition` argument order, `gSPMatrix` 0x01020040, the second loop, `MapObj_DrawSpinners`, the render-mode block and the four `MapObj_DrawBillboards` calls, the texture filter/LUT words, the `D_80082048 += D_8004DD74` pairs loop, and the sound tail (`200.0`, `(600.0 - d) * 0.6375`, `n >= 2`, `-1` stored to B4 then B0).
- Fixed for the live module: `D_8004DD88` is now defined in this file as `s32[4]`; retail reads `lb D_8004DD8B + 4 * i`, the low byte of each word. The C passes `(s8)D_8004DD88[i]`, which IDO compiles to the same `lb +3`. The context the draft needed (`CellOffset`, `AnimInfo20`, the offset tables, prototypes of the later functions) is inside the `#ifdef`.
- Open: `D_8004DD74` (`s32[4]`) is read as four `u16` pairs and `D_8004DD88` by its low byte; both are big-endian data layouts a PC port has to keep in mind.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **MapObj_DrawNearby** (0x9C8 bytes)
  - w2 s2: E2A0, 630 instructions. Not attempted (size).
  - w2 s3: E2A0, 626 instructions. This was the only untried function and it now has a full draft (scratch w2/stash/MapObj_DrawNearby.c), at about 567 differing words. The control flow is right. All four grid cases match apart from registers, and the px/pz locals before the switch reproduce the hoisted D_80085E48 loads. What is left is mostly callee-saved register numbering: in the target a shared u16 temp lives in s0 and holds both the cell count and the anim frame, and IDO sinks my frame+1 below the Math_EvalTcbSpline call. The target also rematerializes &D_80082058, where my build keeps it in a register. Unk8007C28C now has named grid fields (committed).
  - w2 s4: E2A0. Same length as the target now (626). The D_80082048 += D_8004DD74 loop is a pointer loop for (a = D_80082048, b = D_8004DD74; b < &D_8004DD74[4]; a++, b++). The volume reuses n (target s6). The tail is D_800842B4 = -1; D_800842B0 = -1; in that order. About 537 register-numbering diffs remain: t should be s0 in both the cell loop and the frame code. Draft in stash/func_8000DE54_v2.c.
  - w2 s5: E2A0. Root cause found: in the target the count t is never forward-substituted. It stays one variable in s0 through the cell loop (lhu s0; addiu a1,a1,2; jal; move a0,s0), the unk2 call and the frame code (t = flags; a2 = t & 0xFF; t = a2 + 1 before the Math_EvalTcbSpline call). Mine substitutes t into the arguments. t = *list++, MapObj_CollectCell(t = *list++, list) (which gives t1, not s0) and frame folded into t were all tried. A 15-minute permuter run was useless (scores in the thousands because of macro reformatting). Draft: stash/func_8000DE54_v3.c, which needs its typedef header (stash/func_8000DE54_v2.c has it).
  - w2 s6: E2A0, 506 words (2 instructions short, register allocation diverges from the prologue). Draft: de54_full.c in the scratchpad. It needs `extern s8 D_8004DD8B[]; #define D_8004DD88 ((Unk8004DD88 *)(D_8004DD8B - 3))` because splat names that symbol D_8004DD8B. The permuter (with the line fix) got the score from 4920 to 2285, but only through semantics-breaking edits. Not close.
  - Claude b3: E2A0, now the same length as the target (626) but still ~520 register words; 26 structural diffs left. New: the s0 count/frame `t` comes back once t has to survive the Math_EvalTcbSpline call: `t = flags; t = (t & 0xFF) + 1; Math_EvalTcbSpline(anim, &D_80082020, flags & 0xFF); ... flags = t; if (t >= anim->unk6) flags = 0; s->unk16 = (s->unk16 & 0xFF00) | flags;` (reusing flags as the frame stops IDO forward-substituting t), with `t = *list; MapObj_CollectCell(t, list + 1);` in the cell loop. That gives `lhu sN; move a0,sN` in the cell loop as in the target, but the callee-saved numbering is still shuffled. Local pointers are not needed here: D_80081CC8 must stay direct (the first loop's per-iteration la only appears then), and the D_800842B0/B4 tail was already right with direct names. Still open: &D_80082058 is CSE'd into a saved reg (the target rematerializes it), and in the D_80082048 loop the target issues all four loads before the stores (u16 temps fix the load order, not the store order). Draft: C:\Users\Sean\AppData\Local\Temp\claude\c--code\e28e4613-47ce-4c8d-9eb8-47918177bdc8\scratchpad\b3\de54_b3_best.c.
  - Codex D1 implementation: D1 pass: valid tail loop now reproduces operation ordering by precomputing loop predicate before stores; draft codex/d1-gfx/MapObj_DrawNearby.best_valid.c. A cross-object pointer alias diagnostically suppresses82058 address CSE and gives244words/exact size, but it is NOT approved source and was not landed. The missing address identity remains unresolved.
  - Claude retry: not attempted (500+ register words).
