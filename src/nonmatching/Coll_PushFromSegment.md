# Coll_PushFromSegment

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/113F0.c`](../113F0.c)
- Retail assembly: [`asm/nonmatchings/113F0/Coll_PushFromSegment.s`](../../asm/nonmatchings/113F0/Coll_PushFromSegment.s)
- Retail code size: `0x618` bytes
- Current gap: 164 object words; two extra instructions (0x620 vs 0x618), FP registers and stack homes.
- Specific blocker: FP endpoint expressions take f0 and force az reload; the named variables would use retail f18/f14.
- Next discriminating test: Reconstruct endpoint value webs with the saved uopt cost trace, keeping az live across the check.
- C: in [`src/113F0.c`](../113F0.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_80011034_164words.c` (SHA-256 `bf071c71ac2bd20fa7c13d7c4a8438fde44e283d890e47e925ca79c0105d3530`)
- Detailed research reports: [ REPORT.txt ](reports/codex__d1-gfx__REPORT.txt), [ REPORT.txt ](reports/codex__gfx-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the retail asm against the C: min/max with `<=` for the minimum and `<` for the maximum, the four early-out compares, the three line forms (vertical, horizontal, slope `-(bz - az) / (bx - ax)`), `|a*x + b*z + c| / sqrtf(a*a + b*b)`, the perpendicular line and the intersection quotients, the second min/max, the double `(r + 0.1) - dist` push-out, the `dist != 0` skip, and the `*px`/`*pz` reloads after each call.
- Retail quirk kept: when the foot point is outside the segment and end point **b** is within `r`, retail still pushes away from **a** (`ax - *px`, `az - *pz`); only the distance test uses b. The C does the same, with a comment.
- Open: nothing.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Coll_PushFromSegment** (0x618 bytes)
  - w2 s2: 113F0. Full draft written (circle vs segment push). The target frame is 0x60 with exactly 16 local slots; mine has 22 locals, so the frame is 0x80. Needs a variable-reuse layout.
  - w2 s3: Not retried this session beyond rerunning the stash drafts after the prototype fixes. C528 is at 311 words, D6A0 at 422 (register-heavy), 104C0 at 159. 11C60 has no draft file left; its asm rematerializes &env_light_time after every call. 11EF4 is probably in the same lui-sharing (D2) family.
  - w2 s4: 113F0, about 138 words, mostly register numbering, with the frame (96) and layout matching. The source reuses four generic f32 temps (a, b, c, d) as bbox min/max, line coefficients, endpoint deltas and sqrt result, and computes d = a * *px + b * *pz + c. Stash: Coll_PushFromSegment.c, plus func_80011034_perm.c, a permuter variant at about 80 words that uses semantically dubious copies.
  - w2 s5: 113F0, 138 words. The block layout of the endpoint-distance section differs: mine is 5 instructions longer and orders the two endpoint blocks differently, and the target keeps ix/iz in f12/f16 across the bbox recheck. A no-op scan (207 variants) changed nothing. This needs a structural rewrite of that section.
  - w2 s6: 113F0, 392 against 390 words, aln 34 (was 213). Draft: stash/func_80011034_v3.c. The fixes were `ix = dx*dx + dz*dz; k = ... / sqrtf(ix);` in the final block, and in the first endpoint `dz = az; b = dz - cz;` with both pushes using `dz = dz - *pz` (this is equivalent). Remaining: (1) the endpoint `a = ax - cx` lands in f0, but the target uses f18 and keeps az in f0, so mine reloads az; (2) the final block computes dz into f0 and then does mov.s f14. A permuter run on v3 was in progress.
  - Codex D1 implementation: D1 pass: faithful cost traces distinguish named a/dz from separately promoted arithmetic expressions. Endpoint expression winsf0 over az, causing reload; final delta is separately allocatedf0 then copiedtof14. This is constrained expression priority, so declaration seeds do not fix it. Draft unchanged; detailed costs and rejected hypotheses in codex/d1-gfx/REPORT.txt.
  - Claude retry: no change (163-165 words aligned, 391 vs 389). Retail keeps az in f0 from the bbox recheck's ternaries and puts the endpoint `a = ax - cx` in f18 (the register of the old max-x `b`); moving `dz = az` earlier, `b = (dz = az) - cz`, dz in the ternaries, and renaming the endpoint variables (a->b, b->c, c->d) all fail (renaming pushes values into s-regs, +6 words). Draft: C:\Users\Sean\AppData\Local\Temp\claude\c--code\e28e4613-47ce-4c8d-9eb8-47918177bdc8\scratchpad\rpb\best_80011034_163w.c (dz in the ternaries, 163 words)
