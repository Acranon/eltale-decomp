# Env_InitForMap

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/game/env/env.c`](../game/env/env.c)
- Retail assembly: [`asm/nonmatchings/game/env/env/Env_InitForMap.s`](../../asm/nonmatchings/game/env/env/Env_InitForMap.s)
- Retail code size: `0x180` bytes
- Current gap: 67 object words, length exact (0x17C). One real difference: the last phase's start time sits in v0 (a uopt register) where retail has it in the ugen temporary t6; the other 66 words are the t-register numbering shifted by that one temporary.
- Specific blocker: retail is `lw t6,last.startTime; sw t6,env_last_phase_start` with the first loop test reading t6 again and no address register for env_last_phase_start. uopt gives any value or address used twice in the first block a register, so that shape needs the reload of env_last_phase_start to be folded by ugen (it does that for a direct-symbol store followed by a direct-symbol load, see Map_LoadArea's `k = map_subarea = map_next_subarea`), which only happens when `&env_last_phase_start` is NOT given a register.
- Next discriminating test: retail needs `&env_last_phase_start` to have ONE register-candidate use in the entry block while ugen still sees a direct-symbol store followed by a direct-symbol load. In uopt that only happens when one of the two accesses comes from a pointer variable assigned in an earlier basic block, or from a function-scope static (see the Fable w1 entry below). Find what in the original puts a uopt block boundary before the store without a label that as1 sees, or what makes the address range lose (total uses minus reloads <= 0) in the entry block. Closest natural form: `n = env_last_phase_start = env_day_phases[3].startTime; i = 3; if (env_clock < n) { do {...} while (env_clock < p->startTime); }` (69 words, one instruction too long: `lui a2/addiu a2` + `sw t6,0(a2)`).
- C: in [`src/game/env/env.c`](../game/env/env.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/gfx-resume/func_80011AE0_8words.c` (SHA-256 `999660e1350c9eb9681e4fdfae30c28c933515033d6a7b5cb0d0bade94859641`)
- Detailed research reports: [ REPORT.txt ](reports/codex__gfx-resume__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the retail asm against the C: `env_last_phase_start = env_day_phase_last[0].unk0`, the backward walk (`p--`, test `i` before `i--`, stop when `env_clock >= p->unk0`), the `i < 0` fallback to entry 3, the 0x100-halfword copy from `map_backdrop_phase_tluts[p->unk4]` to `map_backdrop_tlut`, the `++env_next_phase >= 4` wrap, both `map_env_flags & 2` branches (last keyframe time of `env_area_settings`), `Env_ClearLightSlots()` and `env_play_time_ticks = 0`.
- Changed from the draft: it read `env_day_phases[3].unk0`, out of bounds of the 3-entry array; the C reads `env_day_phase_last[0].unk0`, the object retail's %hi/%lo name. Dropped the permuter leftovers (`(long long)` cast, `if (0) {}`). This cost words (draft: 8; keeping the leftovers with the fixed object gave 91).
- Open: the walk steps from `env_day_phase_last` back into `env_day_phases`, so it relies on the two tables being adjacent, as they are (defined together in this file's .data, as in retail).

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Env_InitForMap** (0x180 bytes)
  - w2 s2: 12610. The loop/copy structure matches. The search loop's dead `v0=i` copy and the separate lui for env_day_phase_last[0].unk0 are unresolved. env_day_phase_last is &env_day_phases[3] (12-byte entries).
  - w2 s3: 12610. Reading the first entry as `env_day_phases[3].unk0` (an alias of env_day_phase_last[0]) gives the target's direct lui/lw that does not share the &env_day_phase_last base. The remaining gap: v1/a0 are swapped for env_clock and i, and my `if (i-- == 0)` becomes sltiu where the target keeps a dead `move v0,a0` copy. Draft in stash/func_80011AE0_v2.c.
  - w2 s4: 12610. n = i--; if (n == 0) break; reproduces the target's dead move v0,a0 loop copy (if (i-- == 0) gives sltiu). Using a local k for env_day_phases[3].unk0 stops the env_last_phase_start address CSE, but k then gets a0 instead of the target's t6, which pushes i into v0. Draft in stash/func_80011AE0_v3.c.
  - w2 s5: 12610. The real problem is scheduling: the target stores env_last_phase_start (lui at) before loading env_clock through t0. Mine sinks the store after the compare and CSEs &env_last_phase_start into a0. Note that env_day_phase_last == &env_day_phases[3]. Tried: assignment inside the condition, a k temp (store fixed, but k gets a0 and not t6), p->unk0, swapped and negated compares, all orders of the head statements and no-op scans on two bases. Best is 44-47 words. Drafts: stash/func_80011AE0_v3.c and _v4k.c.
  - w2 s6: 12610, register-only diff now (42 words, same length and the same instructions apart from registers). Draft: stash/func_80011AE0_v6.c (`if (0) {}` after `i = 3;`, the copy loop uses i as its counter, and `e = ...` comes before `env_light_time = 0;`). i/n now get a0/v0 as in the target. The only root difference left: the env_day_phases[3].unk0 value gets a global register (v0), while the target keeps it in local t6. Assignment-in-condition does give t6, but then the store sinks into the delay slot with a materialized address. A permuter run on v6 found 8-9-word candidates (aln 16) at the very end; check ~/perm-w2/nonmatchings/Env_InitForMap/output-* (lowest score first) with scratchpad pout.sh.
  - Sol s1: Verified the old permuter outputs in the real build. Best is output-55-1: 8 words differ, frame/length/control flow and all later instructions match. Saved as ~/eltale-notes/sol/func_80011AE0_8words.c. Initial env_day_phases[3].unk0 gets a2 instead of retail t6, which also advances two later t-register choices. Explicit int new_var = (long long)env_clock (same-width result) gives this improvement. Removing the empty if (0) loses the loop-register match. Tried all 140 saved outputs, signed int/long/64-bit cast grids, 120 initial statement orders, and empty-block placements; none matched. No permuter launched because Claude already had a two-job run. The function remains GLOBAL_ASM.
  - Codex D1 implementation: D1 pass: initial table load is a constrained global expression rather than the target local temporary. Named caching, initialization seeds, volatile read, and removal of empty-if boundary with first-use initialization reconstruction did not improve8words. Faithful compiler traces saved in codex/d1-gfx/.
  - Claude D2: Not D2. With env_day_phases/DEF4 and env_clock.. defined in game/env/env.c, Sol's 8-word draft is still exactly 8 words (the env_day_phases[3].unk0 value in a2 instead of t6).
  - Claude retry: no change (Sol's 8 words). Natural `p = env_day_phase_last; env_last_phase_start = p->unk0; i = 3; while (env_clock < p->unk0) { p--; n = i--; if (n == 0) break; }` (rotated loop = retail shape) gives 83 words: the value is CSE'd through &env_day_phase_last into v0. Assignment in the condition (`(env_last_phase_start = env_day_phase_last[0].unk0) > env_clock`) gets the value in t6 as retail but the store goes to the branch delay slot through a materialized &env_last_phase_start (33 words). 15 min permuter on Sol's draft: nothing below its base. Draft unchanged: C:\Users\Sean\AppData\Local\Temp\claude\c--code\e28e4613-47ce-4c8d-9eb8-47918177bdc8\scratchpad\rpb\best_80011AE0_8w.c
  - Fable w2 (2026-11-10): 83 -> 67 words, and the 67 are one cause. Solved: the hidden extra temporary before `lw t1,4(a1)` is the palette row written as an offset, `map_backdrop_phase_tluts[0] + p->paletteIndex * 256` (as in Env_Update): ugen scales the index in two steps and as1 merges the shifts, which consumes one t-register. Read from ugen's temp FIFO (t6,t7,t8,t9,t1..t5 here): retail takes exactly one temp in block 0 (t6 = the loaded start time, used by the store and by the first test) and one hidden temp after `li t8,3`. Not solved: every form where uopt sees the start time twice (two loads, a local, `p->startTime`, typed loads, struct copy) puts it in v0; every form that reloads env_last_phase_start (direct, through `n`, chained assignment) gets retail's t6 and all later registers but colours `&env_last_phase_start` (2 uses in block 0, save 1), one instruction too many. Tried to make that address uncoloured: unused label / empty-if block boundaries (the reload then stays a real `lw`), later dead uses after the call (still coloured), file-static (same lda form), pointer locals (propagated). The natural `while` form is now the NON_MATCHING body.
  - Fable w1 (2026-11-10): still 67 words, body unchanged. What the compiler sources and traces say (uopt source in
    ~/eltale-notes/codex/d1-root/ido-uopt-source, cost traces with scratchpad w1/try.py --trace):
    - Every direct access to a global is turned into `lda` + `ilod/istr` by uopt (uoptinput.c, Ulod/Ustr cases, "kpicopt")
      unless the symbol is a function-scope static (FSYM). File-scope statics, externs, arrays and block-scope externs all
      get the address form. An address with two uses in one block always gets a register in the ENTRY block (save 1,
      cost 0). Map_LoadArea's `k = map_subarea = map_next_subarea` stays uncoloured only because that range comes in
      across calls: its piece carries reload-only blocks (-1 each) and the total goes negative. Nothing precedes the
      entry block, so that cannot happen here.
    - ugen reuses the stored register for a later load only when both are direct-symbol accesses (listing: `lw $14,X;
      sw $14,G; ... bge $3,$14`). Through an address register the reload is a real `lw` that as1 forwards (one hidden
      temporary, and the `la`).
    - Forms that DO give retail's `lw t6; lui at; sw t6,%lo(G)(at); slt at,v1,t6` and every later register: the store
      through a pointer variable that was assigned in an earlier basic block (uopt then emits the address inline, no
      candidate) and the test reading the global directly: `s32 *q = &env_last_phase_start; top:; *q = ...;
      if (env_clock < env_last_phase_start)`. But every block boundary uopt accepts (unused label, `do {} while (0)`,
      `for (;;) { ... break; }`) is also a label for as1, which then keeps `lui a3/addiu a3` out of the prologue
      (38 words, length exact). A nested declaration block is not a uopt boundary. So retail has no boundary there.
    - Tried and ruled out (all colour the address or put the value in v0): pointer local in the same block (substituted
      at input), store through pointer + direct reload and the reverse, typed reads (`*(u32 *)&...`: two loads, the
      table base gets v0), array-element read for the store with `p->` for the test (uopt normalises both to the same
      load), function-static stand-ins for the global (promoted to v0; file-static and static array: address form),
      address through an integer on either side (the `lda` under the casts still counts), assignment in the condition
      with u32/s16/s64 targets (cfe always reloads the target), a function-static last table entry (`last.startTime`
      direct + `p->startTime` via a3: two real loads).
