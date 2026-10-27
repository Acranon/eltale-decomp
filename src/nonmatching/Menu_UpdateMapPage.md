# Menu_UpdateMapPage

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/2B530.c`](../2B530.c)
- Retail assembly: [`asm/nonmatchings/2B530/Menu_UpdateMapPage.s`](../../asm/nonmatchings/2B530/Menu_UpdateMapPage.s)
- Retail code size: `0x1234` bytes
- Current gap: 1129 object words; code 0x121C vs 0x1234, frame 0x138 vs 0x120. Retail hoists the four scale/offset loads into registers and has fewer named homes; most words differ from the frame offsets.
- Specific blocker: Private static and following data can be placed exactly, but draft code is 0x44 bytes short with extra homes.
- Next discriminating test: Recover four hoisted scale/offset locals and remove four incorrect homes; match each draw branch separately.
- C: in [`src/2B530.c`](../2B530.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui-resume/2B530.b844-c598.draft.c` (SHA-256 `51131a3a841d98c58a67b22dc9fdafb9ad1a5727aed73b139ea268b03d846706`)
- Detailed research reports: [ 2B530-REPORT.txt ](reports/codex-ui-resume__2B530-REPORT.txt)

## Equivalence

Verdict: **equivalent after one fix.**

- Read the whole retail asm against the C. Map branch (`menu_map_region < 6`): the `menu_map_loaded_region` load cache (`Dma_ReadRom(start, dst, end - start)` from `menu_map_picture_dma`), clipping at 0/320 (`s = -x << 5`, `w = 320 - x`), PipeSync + LoadTLUT_pal256(`menu_map_tluts[n]`), 24 strips of 244x8 (last one 1 line) from `menu_map_strips[n * 24 + i]` with every LoadTextureTile/TextureRectangle/PipeSync word, `SaveMenu_SetTextDrawState()`. Picture branch: the 11 frame calls, the same cache, size and position from `menu_map_small_sizes[n]`/`menu_map_small_pos[n]`, clipping, LoadTLUT_pal256(`menu_map_small_tluts[n]`), `menu_flags &= ~0x10`, top and bottom halves (`menu_map_small_tex[2n]`, `[2n + 1]`, heights `[n][1]`, `[n][2]`, the bottom rectangle at `y + h1` to `y + h + h2`). Common part: the four calls with the wobble, the cursor position (`(s32)player_state.x / menu_map_world_scale[n] + menu_map_origin[n]`, `.z` with `[n + 6]`, signed divide; or `menu_map_spot_coords[n * 18 + k * 2]`), the blink on `menu_frame_counter & 0x20`, the free cursor (`-1.0f` init, stick dead zone of 5, `+= f * 0.08` / `-= f * 0.08` in double, clamps 6..236 and 6..178), `menu_map_marker_x`/`menu_map_marker_z` (int product converted to float), the two cursor sprites (float sums in retail order, `ox = -2`, `y`/`h` from `menu_map_cursor_active`), and the input tail (page turn, `menu_map_cursor_saved_x`/`menu_map_cursor_saved_y` save, `0x8000` toggle with `Sfx_Play(0, 0x17, 0xFF)`, `0x4000` restore with `0x13`).
- Bug fixed: the draft lacked the `gDPPipeSync` that retail emits after each of the two `gDPLoadTextureTile` in the picture branch (two display-list commands); added.
- Data: retail keeps `menu_map_loaded_region` in a register across `Dma_ReadRom` (a function static); the C has `static s32 menu_map_loaded_region = -1;` and the NON_MATCHING build leaves out the retail build's file-scope definition. The draft's struct views were rewritten to the module's D2 definitions (`D2DstRom`, flat `s16`/pointer arrays, `u8 menu_map_small_sizes[4][3]`); `D2DstRom` is declared before the function in the NON_MATCHING build only.
- Open: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Menu_UpdateMapPage** (0x1234 bytes)
  - w5 s2: Only skimmed, no real attempt: large menu/cursor logic (853 and 1167 instructions). B844 copies a 3-byte local array from menu_options_marker_sprites.
  - w5 s3: Looked at only (1167 instructions, m2c output in c598_m2c.txt). Probably blocked on D2: menu_map_cursor_saved_x and menu_map_cursor_saved_y (bss) and menu_map_loaded_region (.data, -1) are used only here, which points to function statics, as in B844.
  - w5 s4: Previously untried. It is blocked on D2: menu_map_loaded_region must be a function static (`static s32 menu_map_loaded_region = -1;`). With an extern, IDO CSEs its address into s0 across the Dma_ReadRom call. With the static, that part matches (tested, not committed). The draft is good for D2: w5s4/c/C598_e0.c and C598_d2.c (noreg 130-132 of 1165 instructions). Structure is known: two map branches (24 strips of 244x8 in branch 1; two halves from menu_map_small_sizes/98/5C/6C in branch 2), wobble, cursor, input tail. Also found: the 4 scale/offset loads (menu_map_world_scale/CC[n], [n+6]) are hoisted before `if (menu_map_cursor_x == -1.0f)`, which reproduces only with 4 new named locals. The frame (0x120) then needs 4 fewer locals elsewhere. The -2 in the first cursor call is a variable (`ox = -2`), not a literal. Each gDP macro's `_g` block local takes a stack slot under -g3.
  - w5 s5: Still blocked on D2: it needs `static s32 menu_map_loaded_region = -1;`. The drafts are w5s4/c/C598_e0.c and C598_d2.c.
  - w5 s6: Blocked on D2: needs `static s32 menu_map_loaded_region = -1;`. Confirmed from the asm: the value is kept across the jal Dma_ReadRom. Drafts are w5s4/c/C598_e0.c and C598_d2.c.
  - Claude retry: not attempted beyond reading; the D2 statics are now possible (menu_map_loaded_region needs to be a C598 static, so .data menu_options_top_row_pos/CC must be defined between B844 and C598, menu_exp_gauge_tluts.. after; 2B530_data_split_for_B844_C598.c has that layout). The draft's extern types (Unk800614E4, Unk8006158C, ...) must be reconciled with the file's D2 types first.
