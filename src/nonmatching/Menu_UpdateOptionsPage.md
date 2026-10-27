# Menu_UpdateOptionsPage

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/2B530.c`](../2B530.c)
- Retail assembly: [`asm/nonmatchings/2B530/Menu_UpdateOptionsPage.s`](../../asm/nonmatchings/2B530/Menu_UpdateOptionsPage.s)
- Retail code size: `0xd54` bytes
- Current gap: 112 object words; length and frame (0x48) exact. Stack homes and register choice differ in the cursor-slide part (about +0x6E0 on).
- Specific blocker: An extra pos home shifts repeated x+constant spills by 4 bytes; later register/scheduling gaps remain.
- Next discriminating test: Reuse an existing home for pos while keeping its branch updates. Replace compiler symbol-table padding with a defensible layout mechanism.
- C: in [`src/2B530.c`](../2B530.c) under `#ifdef NON_MATCHING` (draft removed).
- Original whole-source snapshot: `/home/sean/eltale-notes/codex-ui-resume/2B530.b844-exact-layout-44words.c` (SHA-256 `ece11e9e46071d1b2a50e2f985837e506a82530a2929f9b9944700c55c7df9d8`)
- Detailed research reports: [ 2B530-REPORT.txt ](reports/codex-ui-resume__2B530-REPORT.txt), [ B844_REPORT.txt ](reports/codex__gfx-resume__B844_REPORT.txt)

## Equivalence

Verdict: **equivalent.**

- Read the whole retail asm against the C: the `menu_text_delay_option = 4 - menu_text_delay_option` flip on entry and on every exit (both early returns and the end), all 31 frame/label `Menu_DrawSprite` calls with their constants, the wobble `menu_wobble_offsets[(menu_frame_counter >> 2) & 0xF]` (and `>> 1` for the cursor), the two marker draws (`ids[menu_options_bgm_row_pos[menu_bgm_volume_option][1]]`, `ids[menu_options_top_row_pos[menu_text_delay_option][1]]`, signed `lh` table reads) with the `0x200`/`0x100` selection, the `0x2000` early return, the page-turn tests (`input_stick_x > 20 || input_held_buttons & 0x10`, `< -20 || & 0x2000`; `|= 0x2000`/`0x3000`, `menu_slide_timer = 0x1F`), the `0x8000` confirm (`|= 0x820`) and cancel (`&= 0xF6DF`, `Sfx_Play(0, 2, 0xFF)`), the slide arrival test and both `input_stick_y`/`input_stick_x` selection blocks (post-increment/decrement table reads, clamps 0..4, every two-store flag update), the slide step (`menu_options_marker_x +- 1`, `pos`, the `[i - 1]`/`[i + 1]` id reads) and the final cursor `Menu_DrawSprite(1, x - wob + 0x1E, y, 0x10, 0xD)`.
- Data: retail keeps `menu_options_marker_x` in a register across calls and writes it back (a promoted function static), and copies the three ids from `menu_options_marker_sprites` to the stack with `lwr`/`swr` (a local aggregate initializer). The C writes them that way, `static s32 menu_options_marker_x;` and `u8 ids[3] = { 0x28, 0x27, 0x26 };`; the NON_MATCHING build leaves out the file-scope `menu_options_marker_x` and `menu_options_marker_sprites` definitions the retail build keeps, so each object still has one definition. No other code uses either.
- Bugs fixed: none in the logic. The draft's static had to replace, not duplicate, the module's `menu_options_marker_x`.
- Open: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Menu_UpdateOptionsPage** (0xD54 bytes)
  - w5 s2: Only skimmed, no real attempt: large menu/cursor logic (853 and 1167 instructions). B844 copies a 3-byte local array from menu_options_marker_sprites.
  - w5 s3: Draft c/B844_g.c and c/B844_st.c (853 instructions). The first ~200 instructions match exactly. menu_options_marker_x is used only by this function, and the target code is the promoted-static pattern: lui/%lo access, write-back at merges, reload after calls. Making it `static s32` inside B844 reproduces that, so it needs D2. Two issues remain: wob should get t1 for the whole function but my build uses v0 or memory, and in the 3rd part the target puts per-branch write-backs and computes a1 = pos + x before the branch. Frame: 4 named locals plus the reserved switch slot (0x34). Locals ids (3-byte struct copy), sel and y are memory-resident.
  - w5 s4: Rechecked: blocked on D2. menu_options_marker_x is clearly a promoted static: kept in t2, written back at merges, reloaded after calls.
  - w5 s5: Still blocked on D2: menu_options_marker_x is a promoted static.
  - w5 s6: Blocked on D2: menu_options_marker_x must be a static.
  - Claude retry: 555 -> 44 words (draft ~/eltale-notes/claude/rpc/b844_44w.c, needs the data split in 2B530_data_split_for_B844_C598.c: data up to menu_map_small_pos before B844, menu_options_top_row_pos/CC between B844 and C598). Fixes: `static s32 menu_options_marker_x;` in B844; ids as local `u8 ids[3] = { 0x28, 0x27, 0x26 }` (its hidden .data object is 800615A8); the wobble written sibling-style (`wob = menu_frame_counter; wob = (wob >> 1) & 0xF; wob = menu_wobble_offsets[wob];`, both places) gives wob t1 / FB58 t2; the third part's per-branch FB58 write-backs and `a1 = FB58 + x` computed before the branch with a1 +-1 in the branches come only from a local `pos = menu_options_marker_x + x;` with `pos++`/`pos--` next to the FB58 changes and `Menu_DrawSprite(sel, pos, ...)` (tiny test reproduces it exactly; no other spelling does). Left: pos takes a -g3 home, so the two compiler temps (x+const spills) sit at 0x2c/0x28 instead of retail 0x30/0x2c (retail's frame has only wob/sel/y/ids homes per .mdebug; block-scope, register, s16/u16 pos all still take a slot; s8 pos packs but adds sign extensions), plus a 3-instruction scheduling swap at the part-3 entry. A 15-min --stack-diffs permuter run from the 44-word base found only a fake ( around part 3 case 0: 39 words, the temp-slot shift unchanged). Also: with the static, .bss order comes out FB58 (and FB5C/60 if declared later) before FB30..54 (256-block rule); a k-typedef scan before B844 needs ~208 declarations to fix it. Permuter: see below.
