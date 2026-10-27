# Unmatched function handoff

As of 2026-10-26 at `f529079`, 874/896 functions match the Japanese retail ROM. The 22 records here are the remaining unmatched functions. Each record includes the current byte or word gap, compiler-specific blocker, next test, prior attempts and, once its C is in the source, an **Equivalence** section. Detailed reports are in [`reports/`](reports/).

Step D3 puts each function's C into its live `src/` module under `#ifdef NON_MATCHING`, with the retail `#pragma GLOBAL_ASM` in the `#else`. `./build.sh` still builds the asm and matches retail; `NON_MATCHING=1 ./build.sh` builds the C instead (not compared with retail). That C is **not** a byte match: it is checked to behave like the retail asm (same loads and stores, calls, branches, constants and conversions; registers, scheduling and stack may differ), and the record's Equivalence section says what was checked and what was fixed. A record that still has a `.draft.c` has not been moved yet; such a draft may lack file-local types, externs, macros and data definitions, and its record names the full source snapshot for replay. Prefer the current gap over historical diff counts. Object word counts may mask relocations, so use a full linked-ROM comparison before claiming a match.

## Queue

| Function | Live module | Current gap |
| --- | --- | --- |
| [`func_80011034`](func_80011034.md) | `src/113F0.c`, C under `NON_MATCHING` | 164 object words; two extra instructions |
| [`func_80011AE0`](func_80011AE0.md) | `src/12610.c`, C under `NON_MATCHING` | 83 object words; one instruction short |
| [`func_80011EF4`](func_80011EF4.md) | `src/12610.c`, C under `NON_MATCHING` | 379 object words; retail no-frame leaf |
| [`func_80022658`](func_80022658.md) | `src/216E0.c` | 72 register words; instruction sequence exact |
| [`func_80025318`](func_80025318.md) | `src/25B20.c` | 742 valid object words with volatile n; code 0xCF8 vs 0xD28 |
| [`func_8002B844`](func_8002B844.md) | `src/2B530.c` | 44 object words; data addresses exact in test link |
| [`func_8002C598`](func_8002C598.md) | `src/2B530.c` | over 1100 object words; frame 0x130 vs 0x120 |
| [`func_8002DECC`](func_8002DECC.md) | `src/2B530.c` | 328 object words; code 0x55C vs 0x560 |
| [`func_80030D5C`](func_80030D5C.md) | `src/30600.c` | about 309 object words; code 24 bytes short |
| [`func_80031E10`](func_80031E10.md) | `src/30600.c` | 20 register words; length/frame match |
| [`func_80033050`](func_80033050.md) | `src/337B0.c`, C under `NON_MATCHING` | 18 object words; length exact, frame exact |
| [`func_8003453C`](func_8003453C.md) | `src/337B0.c`, C under `NON_MATCHING` | 221 object words; length exact, frame 0x40 vs 0x48 |
| [`func_80034C9C`](func_80034C9C.md) | `src/337B0.c`, C under `NON_MATCHING` | 92 object words; code 0x404 vs 0x400, frame 0xE0 vs 0xD8 |
| [`func_80007A8C`](func_80007A8C.md) | `src/3F50.c`, C under `NON_MATCHING` | 5 object words |
| [`func_80007FD8`](func_80007FD8.md) | `src/3F50.c`, C under `NON_MATCHING` | 235 object words; frame 0x50 vs 0x48 |
| [`func_8000CC78`](func_8000CC78.md) | `src/AEA0.c`, C under `NON_MATCHING` | 78 object words; frame exact |
| [`func_8000DE54`](func_8000DE54.md) | `src/E2A0.c`, C under `NON_MATCHING` | 437 object words; length exact |
| [`func_801009EC_ovl_DA4570`](func_801009EC_ovl_DA4570.md) | `src/ovl_DA4570/DA4570.c`, C under `NON_MATCHING` | 37 linked ROM words; length and frame exact |
| [`func_8020D98C_ovl_ending`](func_8020D98C_ovl_ending.md) | `src/ovl_ending/E22690.c`, C under `NON_MATCHING` | 25 linked ROM words; length and frame exact |
| [`func_8020E9C8_ovl_ending`](func_8020E9C8_ovl_ending.md) | `src/ovl_ending/E22690.c`, C under `NON_MATCHING` | 754 object words; code 0xC70 vs 0xCBC, frame 0x198 vs 0x1A8 |
| [`func_8020C6A8_ovl_intro`](func_8020C6A8_ovl_intro.md) | `src/ovl_intro/DC62B0.c`, C under `NON_MATCHING` | 609 masked object words; code 0x9D4 vs 0x9D0, frame 0xF0 exact |
| [`func_8020E108_ovl_intro`](func_8020E108_ovl_intro.md) | `src/ovl_intro/DC62B0.c`, C under `NON_MATCHING` | 23 linked ROM words; length and frame 0x648 exact |

## Recheck before promoting to a match

1. Update the checkout to current main and run a clean retail build.
2. Work on the `NON_MATCHING` C in its live module (or reapply the draft), keeping only the necessary context and data layout inside the `#ifdef`.
3. Compare with `tools/match.py`, then build and verify the linked ROM byte for byte.
4. When it matches, drop the `#ifdef NON_MATCHING`/`#else` pragma around the C and remove the record (and any draft) from this queue.
