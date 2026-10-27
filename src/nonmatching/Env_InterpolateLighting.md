# Env_InterpolateLighting

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/12610.c`](../12610.c)
- Retail assembly: [`asm/nonmatchings/12610/Env_InterpolateLighting.s`](../../asm/nonmatchings/12610/Env_InterpolateLighting.s)
- Retail code size: `0x5f4` bytes
- Current gap: 379 object words; 0x620 vs 0x5F4 (an 8-byte frame with one saved register where retail is a no-frame leaf).
- Specific blocker: The 12-byte color copies are understood but a saved cursor and base rematerialization remain wrong.
- Next discriminating test: Use short caller-register cursors and straight aggregate groups; stabilize no-frame copy before interpolation.
- C: in [`src/12610.c`](../12610.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_80011EF4_325words.c` (SHA-256 `0b95e70f942012795be5ad0fa1a0e23d798fe42d139b0cc6ed7d8437abc53414`)
- Detailed research reports: [ REPORT.txt ](reports/codex__d1-gfx__REPORT.txt), [ REPORT.txt ](reports/codex__gfx-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the retail asm against the C: the `count == 1` copy (ambient from +4, three lights from +0x10..+0x30 to `D_80084B24..`, fog from +0x34/+0x38 to `D_80084B78/7C`), the keyframe search `while (t >= k->time) k++`, `span`/`off`/`rem`, and the twelve `(prev * rem + next * off) / span` signed divisions with their targets `D_80084B18..D_80084B44`, `D_80084B78`, `D_80084B7C`.
- Changed from the draft: the lights went through `D_80084B24` (splat's interior label, an alias of `D_80084B18[1]` in undefined_syms.txt) with a `(u32)x / 1` permuter leftover; the C uses `D_80084B18[1]`, the module's object at that address. This cost words (draft: 325).
- Open: nothing.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Env_InterpolateLighting** (0x5F4 bytes)
  - w2 s2: 12610. Keyframe interpolation: struct Keyframe {time; Color3 amb; LightSet3 lights (0x24); FogSet fog}, with D_80084B24 as a separate symbol. The target copies 36 bytes straight-line with lui/at pointer splitting, and my struct copies come out as loops. Draft in scratch g7.c.
  - w2 s3: Not retried this session beyond rerunning the stash drafts after the prototype fixes. C528 is at 311 words, D6A0 at 422 (register-heavy), 104C0 at 159. 11C60 has no draft file left; its asm rematerializes &D_80084988 after every call. 11EF4 is probably in the same lui-sharing (D2) family.
  - w2 s4: Shared lui at across consecutive symbol accesses. In standalone tests, extern scalars, extern structs (base CSE) and locally defined scalars or statics never share a lui, so this still looks like D2 (data defined in the same file, layout-dependent). Not retried beyond those checks.
  - w2 s5: D2-blocked. Confirmed on 11A60 and FC50: stores share one lui at for 8-byte-aligned pairs (B18/B1C, B20/B24, DE60/DE64) using sym+offset relocations. This only happens for data defined in the same file (as1 knows the alignment). An extern of any type (int array, long long, double, struct) gives base CSE instead.
  - w2 s6: Still blocked on D2 (function-scope static or same-file data for the shared-lui pairs). Not retried.
  - Codex review: Audit correction: actual assembly has no shared-lui pair requiring same-object data; prior D2 label borrowed evidence from 11A60/FC50. Try explicit 12-byte aggregate copy units and pointer lifetimes. Isolated probes support three-word copy groups but do not yet reproduce full-function pointer scheduling. D1, fresh hypothesis.
  - Codex D1 implementation: D1 pass: explicit12-byte copies and cursor walk reproduce the distinctive copy triplets/duplicated moves, but selective base rematerialization and pointer lifetimes remain structurally different. No exact match or proven new D2 blocker. Valid and diagnostic drafts clearly separated in codex/d1-gfx/.

  - Claude b5: No change. A three-iteration loop over the Color3 records is not unrolled by IDO here (0x3D4 vs 0x5F4), so the duplicated moves are not loop-unroll artefacts; codex's cursor drafts stay the best. Copy-branch variants (k->lights.l cursor, indexed copies, explicit ++) do not move it.
  - Claude retry: not attempted (far from a match; time spent on the near misses).
