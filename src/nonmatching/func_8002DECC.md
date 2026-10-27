# func_8002DECC

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/2B530.c`](../2B530.c)
- Retail assembly: [`asm/nonmatchings/2B530/func_8002DECC.s`](../../asm/nonmatchings/2B530/func_8002DECC.s)
- Retail code size: `0x560` bytes
- Current gap: 328 object words; code 0x55C vs 0x560, frame 0xD8 exact. Retail keeps w, s, lrs and lrt in stack homes and reloads them; the C promotes some to registers.
- Specific blocker: Retail reloads w, s, lrs and lrt together from stack; compiler promotes some.
- Next discriminating test: Find a single local layout that keeps all four memory-resident with frame 0xD8 before tuning graphics macros.
- C: in [`src/2B530.c`](../2B530.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/decc-review/base.c` (SHA-256 `bc6255cd0bbb643e69643a85014208d8e9c627ea7abfe688050d8a6745d716cb`)
- Detailed research reports: [ REPORT.txt ](reports/codex__decc-review__REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the whole retail asm against the C: the `D_80060D74[id]` texture and `D_80060CB4[id]` size (`lbu`), the jump table (0x37..0x39 zero both scales, 0x3C alpha -0x80 and zero scales, 0x3D zero `dsdx`, 0x3E alpha 0x50) and the `id == 0` tiling case (masks 4, `s`/`t` from `x & 0xF`, `y & 0xF`), left clip (`ret = -1` if `x + w < 0`, else `s += -x << 5`, `w += x`, `x = 0`), right clip at 320 (`w = 320 - x`), `w <= 0 || h <= 0`, then PipeSync, RenderMode 0x504240, SetTextureFilter(bilerp), PipeSync, the `alpha == 0` display list choice (EnvColor 0xFFFFFF00 | alpha), the one-shot TLUT on `D_8008FB3E & 0x10` (sets the bit), every LoadTextureTile word (line `(lrs + 8) >> 3` with `sra`, maskt/masks fields), the TextureRectangle words (`s`/`t`, `dsdx`/`dtdy`) and the final PipeSync.
- Bugs fixed: none.
- Open: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **func_8002DECC** (0x588 bytes)
  - w5 s2: Generic sprite blit. The draft has the right C, with the switch cases in source order 0, 0x3C, 0x3E, 0x37-39, 0x3D. The target frame is 0x20 larger (0xD8) and keeps w in its home slot plus many named locals on the stack.
  - w5 s3: Drafts c/DECC_a.c and c/DECC_c1.c. The named-local layout found: 17 named locals ordered (top down) ret, alpha, xr, masks(0xC8), maskt(0xC4), ult, uls, s(0xB8), t(0xB4), dsdx(0xB0), dtdy(0xAC), texH, ?, lrs(0xA0), lrt(0x9C), tex(0x98), texW(0x94). x in s0, w memory-resident. Relative layout matches, but my frame is 8 bytes smaller (fewer temp slots at the bottom), and s is a register in mine where the target keeps it in memory.
  - w5 s4: Best draft w5s4/c/DL_2.c (noreg 95; 60 with stack offsets masked). It uses the E42C trick in the clip (`d = -x; ...` with d as the 17th local at 0xA4) and `lrt = D_80060CB4[id][1] - 1` (so lrt is computed at init like the target). Left: s must be memory-resident (target sw/lw 0xB8 five times; mine keeps it in a register and spills 3 gfx temps instead of 1), lrs is memory in the target, and the frame is 0xD0 against 0xD8.
  - w5 s5: Best so far is 118 difflines (52 if registers are ignored), down from 183 for draft w5s4/c/DY_0.c. DY_0 is DM_0 (DL_2 plus `s32 pad[2];` at the end of the locals, which fixes the 0xD8 frame and the stack-slot layout exactly) with `lrt = texH - 1` and `s = 0;` placed before `t = 0;`. The 118 came from a permuter run that added `if (1) {}` inside the gDPLoadTextureTile expansion; I did not keep that source. The core problem is unsolved. In the target, lrs (0xA0), lrt (0x9C) and s (0xB8) live in memory: they are stored at init and reloaded at use. Mine copy-propagates lrs/lrt as texW-1/texH-1 and keeps s in a register. Tried and not fixed: `lrs = D_80060CB4[id][0] - 1` (puts lrs in memory but takes w out of memory), s32 s[1], volatile s/lrs, lrs[1]/lrt[1] arrays (frame shrinks to 0xC8), dead `= 0` initializers on every local (no effect), enumerating types (s16 lrs/lrt reached 168, not believable), clip and xr statement forms, and two 25-30 minute permuter runs.
  - w5 s6: Not solved. New measurement tool: scratchpad w5s6/ps.py / ps.sh scores my own compiles with the permuter's Scorer (it strips the other functions). On that score DY_0 = 6179 is the best base. G6_D2 (lrs/lrt loaded straight from D_80060CB4 plus s/dsdx/dtdy as [1] arrays) is 6913, but only 51 difflines with registers masked. With G6_D2, lrs/lrt/texW stack slots match the target, but w (0xE4) and s get registers in the code before `if (ret >= 0)`, where the target keeps them in memory for the whole function. In DY_0 it is the other way round: w is in memory, but lrs/lrt are copy-propagated as texW-1. No source form found that gives both. A 25-minute permuter run reached 2740 (from 6900), but only by changing semantics or the gfx stores (duplicate w1 stores, volatile u8 texH, reordered gDP blocks), so that is not a usable path. Also tried with no effect: label/goto block splits (243 positions), array forms (`s32 dd[2]` etc.), types of texW/texH/lrs/lrt (225 combos), and clip-code statement forms.
  - Codex D1 implementation: D1 pass: the correctly ordered16-byte texW/tex/lrt/lrs aggregate is byte-identical to the old DY_0 draft and does not resolve memory residence. Real used pointer aliases and extended GBI packet scopes also failed to reproduce required stack accesses. No valid new match; report codex/decc-review/REPORT.txt. Target code length0x560 excludes migrated jump-table data.
  - Claude retry: not attempted (no D2 dependency; the memory-resident-locals problem is unchanged).
