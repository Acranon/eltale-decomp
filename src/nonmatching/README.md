# Unmatched function handoff

As of 2026-10-26 at `f529079`, 874/896 functions match the Japanese retail ROM. The 22 records here are the remaining unmatched functions. Each record includes the current byte or word gap, compiler-specific blocker, next test, prior attempts and, once its C is in the source, an **Equivalence** section. Detailed reports are in [`reports/`](reports/).

Step D3 puts each function's C into its live `src/` module under `#ifdef NON_MATCHING`, with the retail `#pragma GLOBAL_ASM` in the `#else`. `./build.sh` still builds the asm and matches retail; `NON_MATCHING=1 ./build.sh` builds the C instead (not compared with retail). That C is **not** a byte match: it is checked to behave like the retail asm (same loads and stores, calls, branches, constants and conversions; registers, scheduling and stack may differ), and the record's Equivalence section says what was checked and what was fixed. A record that still has a `.draft.c` has not been moved yet; such a draft may lack file-local types, externs, macros and data definitions, and its record names the full source snapshot for replay. Prefer the current gap over historical diff counts. Object word counts may mask relocations, so use a full linked-ROM comparison before claiming a match.

## Queue

| Function | Live module | Current gap |
| --- | --- | --- |
| [`Coll_PushFromSegment`](Coll_PushFromSegment.md) | `src/game/map/collision.c`, C under `NON_MATCHING` | 164 object words; two extra instructions |
| [`Env_InitForMap`](Env_InitForMap.md) | `src/game/env/env.c`, C under `NON_MATCHING` | 83 object words; one instruction short |
| [`Env_InterpolateLighting`](Env_InterpolateLighting.md) | `src/game/env/env.c`, C under `NON_MATCHING` | 379 object words; retail no-frame leaf |
| [`Hud_DrawSpellName`](Hud_DrawSpellName.md) | `src/game/ui/hud.c`, C under `NON_MATCHING` | 72 register words; instruction sequence exact apart from one `sll` scheduled after the dead `sw id` instead of before |
| [`Item_UpdateInventoryMenu`](Item_UpdateInventoryMenu.md) | `src/game/item/item.c`, C under `NON_MATCHING` | 742 object words; code 0xCF8 vs 0xD28, frame 0x148 exact |
| [`Menu_UpdateOptionsPage`](Menu_UpdateOptionsPage.md) | `src/game/ui/menu.c`, C under `NON_MATCHING` | 112 object words; length and frame (0x48) exact |
| [`Menu_UpdateMapPage`](Menu_UpdateMapPage.md) | `src/game/ui/menu.c`, C under `NON_MATCHING` | 1129 object words; code 0x121C vs 0x1234, frame 0x138 vs 0x120 |
| [`Menu_DrawSprite`](Menu_DrawSprite.md) | `src/game/ui/menu.c`, C under `NON_MATCHING` | 328 object words; code 0x55C vs 0x560, frame 0xD8 exact |
| [`SaveMenu_UpdateSlotList`](SaveMenu_UpdateSlotList.md) | `src/game/save/save_menu.c`, C under `NON_MATCHING` | 309 object words; code 0xDB4 vs 0xDCC, frame 0x60 exact |
| [`SaveMenu_SaveSelectedFile`](SaveMenu_SaveSelectedFile.md) | `src/game/save/save_menu.c`, C under `NON_MATCHING` | 20 register words; length and frame (0x40) exact |
| [`Text_UpdateAndDrawWindows`](Text_UpdateAndDrawWindows.md) | `src/game/text/text_window.c`, C under `NON_MATCHING` | 18 object words; length exact, frame exact |
| [`Text_BuildVisiblePage`](Text_BuildVisiblePage.md) | `src/game/text/text_window.c`, C under `NON_MATCHING` | 221 object words; length exact, frame 0x40 vs 0x48 |
| [`Text_DrawTexturedRect`](Text_DrawTexturedRect.md) | `src/game/text/text_window.c`, C under `NON_MATCHING` | 92 object words; code 0x404 vs 0x400, frame 0xE0 vs 0xD8 |
| [`Player_FindMeleeTarget`](Player_FindMeleeTarget.md) | `src/game/player/player.c`, C under `NON_MATCHING` | 5 object words |
| [`Player_TakeDamage`](Player_TakeDamage.md) | `src/game/player/player.c`, C under `NON_MATCHING` | 235 object words; frame 0x50 vs 0x48 |
| [`Enemy_RunAttackScript`](Enemy_RunAttackScript.md) | `src/game/enemy/enemy.c`, C under `NON_MATCHING` | 78 object words; frame exact |
| [`MapObj_UpdateAndDrawNearby`](MapObj_UpdateAndDrawNearby.md) | `src/game/map/map.c`, C under `NON_MATCHING` | 437 object words; length exact |
| [`PakMenu_Run`](PakMenu_Run.md) | `src/overlays/pakmenu/pakmenu.c`, C under `NON_MATCHING` | 37 linked ROM words; length and frame exact |
| [`Ending_UpdateAndDrawSprites`](Ending_UpdateAndDrawSprites.md) | `src/overlays/ending/ending.c`, C under `NON_MATCHING` | 25 linked ROM words; length and frame exact |
| [`Ending_UpdateAndDrawScrollingBackdrop`](Ending_UpdateAndDrawScrollingBackdrop.md) | `src/overlays/ending/ending.c`, C under `NON_MATCHING` | 754 object words; code 0xC70 vs 0xCBC, frame 0x198 vs 0x1A8 |
| [`Intro_RunSpriteScript`](Intro_RunSpriteScript.md) | `src/overlays/intro/intro.c`, C under `NON_MATCHING` | 609 masked object words; code 0x9D4 vs 0x9D0, frame 0xF0 exact |
| [`Intro_UpdateAndDrawSprites`](Intro_UpdateAndDrawSprites.md) | `src/overlays/intro/intro.c`, C under `NON_MATCHING` | 23 linked ROM words; length and frame 0x648 exact |

## Recheck before promoting to a match

1. Update the checkout to current main and run a clean retail build.
2. Work on the `NON_MATCHING` C in its live module (or reapply the draft), keeping only the necessary context and data layout inside the `#ifdef`.
3. Compare with `tools/match.py`, then build and verify the linked ROM byte for byte.
4. When it matches, drop the `#ifdef NON_MATCHING`/`#else` pragma around the C and remove the record (and any draft) from this queue.
