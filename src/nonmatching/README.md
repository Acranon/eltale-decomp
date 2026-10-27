# Unmatched function handoff

As of 2026-10-26 at `f529079`, 874/896 functions match the Japanese retail ROM. The 22 records here are the complete remaining function queue for this snapshot. Each record includes the current byte or word gap, compiler-specific blocker, next test, prior attempts, an Equivalence section once its C is in the source, and otherwise a function-only C draft. Detailed reports are in [`reports/`](reports/).

D3 puts each function's C into its live module under `#ifdef NON_MATCHING`, with the retail asm (`#pragma GLOBAL_ASM`) in the `#else`. `./build.sh` builds the asm and matches retail; `NON_MATCHING=1 ./build.sh` builds the C instead (it links but is not compared with retail: the ROM shifts once a function's size changes). That C is meant to behave exactly like the retail asm (same loads, stores, calls, branches, constants and conversions); register allocation, scheduling and stack layout may differ. Each record's **Equivalence** section says what was checked and what was fixed. Rows whose "Live module" column names only the file still have their C in the record's `.draft.c` (research draft, not yet in the source; it may lack file-local context). Object word counts mask relocations, so use a full linked-ROM comparison before claiming a match.

## Queue

| Function | Live module | Current gap |
| --- | --- | --- |
| [`func_80011034`](func_80011034.md) | `src/113F0.c` | 164 object words; two extra instructions |
| [`func_80011AE0`](func_80011AE0.md) | `src/12610.c` | 8 object words; length exact |
| [`func_80011EF4`](func_80011EF4.md) | `src/12610.c` | 325 object words; retail no-frame leaf |
| [`func_80022658`](func_80022658.md) | `src/216E0.c` | 72 register words; instruction sequence exact |
| [`func_80025318`](func_80025318.md) | `src/25B20.c` | 742 valid object words with volatile n; code 0xCF8 vs 0xD28 |
| [`func_8002B844`](func_8002B844.md) | `src/2B530.c` | 44 object words; data addresses exact in test link |
| [`func_8002C598`](func_8002C598.md) | `src/2B530.c` | over 1100 object words; frame 0x130 vs 0x120 |
| [`func_8002DECC`](func_8002DECC.md) | `src/2B530.c` | 328 object words; code 0x55C vs 0x560 |
| [`func_80030D5C`](func_80030D5C.md) | `src/30600.c` | about 309 object words; code 24 bytes short |
| [`func_80031E10`](func_80031E10.md) | `src/30600.c` | 20 register words; length/frame match |
| [`func_80033050`](func_80033050.md) | C in `src/337B0.c` under NON_MATCHING | 18 object words; length exact, frame exact |
| [`func_8003453C`](func_8003453C.md) | C in `src/337B0.c` under NON_MATCHING | 221 object words; length exact, frame 0x40 vs 0x48 |
| [`func_80034C9C`](func_80034C9C.md) | C in `src/337B0.c` under NON_MATCHING | 91 object words; code 0x404 vs 0x400, frame 0xE0 vs 0xD8 |
| [`func_80007A8C`](func_80007A8C.md) | `src/3F50.c` | 5 object words |
| [`func_80007FD8`](func_80007FD8.md) | `src/3F50.c` | 235 object words; frame 0x50 vs 0x48 |
| [`func_8000CC78`](func_8000CC78.md) | `src/AEA0.c` | 30 object words; length exact |
| [`func_8000DE54`](func_8000DE54.md) | `src/E2A0.c` | 438 object words; code 8 bytes short |
| [`func_801009EC_ovl_DA4570`](func_801009EC_ovl_DA4570.md) | C in `src/ovl_DA4570/DA4570.c` under NON_MATCHING | 37 linked ROM words; length and frame exact |
| [`func_8020D98C_ovl_ending`](func_8020D98C_ovl_ending.md) | C in `src/ovl_ending/E22690.c` under NON_MATCHING | 25 linked ROM words; length and frame exact |
| [`func_8020E9C8_ovl_ending`](func_8020E9C8_ovl_ending.md) | C in `src/ovl_ending/E22690.c` under NON_MATCHING | 754 object words; code 0xC70 vs 0xCBC, frame 0x198 vs 0x1A8 |
| [`func_8020C6A8_ovl_intro`](func_8020C6A8_ovl_intro.md) | C in `src/ovl_intro/DC62B0.c` under NON_MATCHING | 608 masked object words; code 0x9D4 vs 0x9D0, frame 0xF0 exact |
| [`func_8020E108_ovl_intro`](func_8020E108_ovl_intro.md) | C in `src/ovl_intro/DC62B0.c` under NON_MATCHING | 23 linked ROM words; length and frame 0x648 exact |

## Recheck before promoting a draft

1. Update the checkout to current main and run a clean retail build.
2. Start from the NON_MATCHING C in the live module (or reapply the draft), with only the necessary context and data layout.
3. Compare with `tools/match.py`, then build and verify the linked ROM byte for byte.
4. When it matches, drop the `#ifdef NON_MATCHING`/`#else` pragma around it and remove that record from this queue.
