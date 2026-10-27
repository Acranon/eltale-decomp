# Enemy_RunAttackScript

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/game/enemy/enemy.c`](../game/enemy/enemy.c)
- Retail assembly: [`asm/nonmatchings/game/enemy/enemy/Enemy_RunAttackScript.s`](../../asm/nonmatchings/game/enemy/enemy/Enemy_RunAttackScript.s)
- Retail code size: `0x264` bytes
- Current gap: 78 object words; frame 0x68 exact (a CSE'd &enemy_script_time for the ++ shifts the temporaries by one).
- Specific blocker: A label fixes FP call timing; d->unk0 uses t6 instead of t7 and m/hi/low/row still occupy wrong GPRs.
- Next discriminating test: Trace the first table-index temporary and constrained row ranges on the 30-word source.
- C: in [`src/game/enemy/enemy.c`](../game/enemy/enemy.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_8000CC78_30words.c` (SHA-256 `25d989fb6e13ddb8d63310dff0b5b36ea1b320113c334b82fe864dc986ea5329`)
- Detailed research reports: [ CC78_TRACE_REPORT.txt ](reports/codex__gfx-resume__CC78_TRACE_REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the retail asm against the C: `++enemy_script_time` (u16, compared after masking with the script's `time`), the flag tests 8/2/4/1 (each reloaded as in retail), the `SpawnDef` index into the table at `enemy_effect_defs` (16-byte entries), `D_800C18D8` (10-byte entries), `D_800C185C[(m >> 8) & 0xF][m & 0xFF].unk1C` (0x44 stride), the float sums with `obj->unk24`, both `Math_RotateVec2` calls, the 9 arguments of `Magic_CreateVisualEffect`, and the script cursor advancing by 0x18 or clearing.
- Changed from the draft: it read `enemy_script_time..enemy_script_obj` through an `Unk8007C060` struct laid over `&enemy_script_time`; the C now uses the module's own scalars (`enemy_script_time`, `enemy_script_cmd`, `enemy_script_enemy`, `enemy_script_obj`), the objects the asm's %hi/%lo name. Same addresses, but it no longer depends on the .bss layout. Dropped the dummy label. This cost words (draft: 30).
- Open: the spawn table is read through `(SpawnDef *)&enemy_effect_defs`, an extern typed as a different struct (same address as the asm).

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Enemy_RunAttackScript** (0x268 bytes)
  - w2 s2: AEA0. Frame matched with pads (stash_cc78.c). The ++ on the timer at enemy_script_time still CSEs the address (lui+addiu) in mine, while the target uses a direct lui/%lo load and a lui at store. enemy_script_time is now `extern u16` with CC40 casting to the struct. Tried statement forms, +=, and volatile.
  - w2 s3: AEA0. The ++enemy_script_time address CSE is still unresolved. Struct-cast load/store forms and mixed forms make no difference. The target also keeps e in t6 for the early part and copies it to s1 later (live-range split). Note: enemy_effect_defs is now a struct in game/enemy/enemy.c, so the old stash needs `&((SpawnDef *)&enemy_effect_defs)[e->unk2]`.
  - w2 s4: AEA0. Same no-address-CSE signature as the static family on enemy_script_time/enemy_script_cmd. Function statics reproduce it (no CSE, lui at, e in v1 then copied to s1), but these symbols are also used by an init function in game/enemy/enemy.c. Probably a D2 question too.
  - w2 s5: D2-blocked (function-scope static data). Re-checked 10768: even with the value read once into a temp (t = D_8004DEC8; ... D_8004DEC8 = t + 1), IDO CSEs &D_8004DEC8 for a load plus two stores, while the target uses lui at for every access. The loop itself is the DDBC rotate pattern, so use the DDBC trick (i = N; p = D + i) for it once D2 allows the static.
  - w2 s6: Still blocked on D2 (function-scope static or same-file data for the shared-lui pairs). Not retried.
  - Codex review: Confirmed shared-lui requirement at CD04 for B928/B92C; D2 appropriate. C060/C064 timer/state are also written by CC40, so do not assume private function statics.
  - Claude retry: 47 words, front now exact up to +0xB4. Draft scratchpad rpa/cc78_c.c: `Unk8007C060 *p = (Unk8007C060 *) &enemy_script_time;` (CC40's view) with `if (p->unk4 != 0) { e = (SpawnScript *) p->unk4; ... ++p->unk0 ... obj = p->unkC; ... ((Enemy *) p->unk8)->unk1C ... p->unk4 = 0 / += sizeof(SpawnScript)`, and `Enemy *en = enemy_slots; en->unk20/unk24` for the B928/B92C shared lui. That fixes the C060 address CSE and the e t6->s1 split. Left: in the m (enemy_script_enemy->unk1C->unk0) block retail keeps m in a3, m>>8 in a0, m&0xFF in a1 and the row pointer in a2 (uopt variables), so x/y move to a2/a3 only at the call; ours forward-substitutes them into t registers and moves x/y into a2/a3 early. Locals hi/lo/q of every width, before or inside the if, change nothing. Also one FIFO temp off from +0xB4 (lh t7 vs t6).
