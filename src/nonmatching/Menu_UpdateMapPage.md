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

- Read the whole retail asm against the C. Map branch (`D_8008FB50 < 6`): the `D_800615E0` load cache (`Dma_ReadRom(start, dst, end - start)` from `D_800614E4`), clipping at 0/320 (`s = -x << 5`, `w = 320 - x`), PipeSync + LoadTLUT_pal256(`D_8006125C[n]`), 24 strips of 244x8 (last one 1 line) from `D_80061274[n * 24 + i]` with every LoadTextureTile/TextureRectangle/PipeSync word, `SaveMenu_SetTextDrawState()`. Picture branch: the 11 frame calls, the same cache, size and position from `D_8006158C[n]`/`D_80061598[n]`, clipping, LoadTLUT_pal256(`D_8006155C[n]`), `D_8008FB3E &= ~0x10`, top and bottom halves (`D_8006156C[2n]`, `[2n + 1]`, heights `[n][1]`, `[n][2]`, the bottom rectangle at `y + h1` to `y + h + h2`). Common part: the four calls with the wobble, the cursor position (`(s32)D_8007AA08.x / D_800614B4[n] + D_800614CC[n]`, `.z` with `[n + 6]`, signed divide; or `D_80061184[n * 18 + k * 2]`), the blink on `D_8008FB44 & 0x20`, the free cursor (`-1.0f` init, stick dead zone of 5, `+= f * 0.08` / `-= f * 0.08` in double, clamps 6..236 and 6..178), `D_8008FB48`/`D_8008FB4C` (int product converted to float), the two cursor sprites (float sums in retail order, `ox = -2`, `y`/`h` from `D_8008FB3C`), and the input tail (page turn, `D_8008FB5C`/`D_8008FB60` save, `0x8000` toggle with `Sfx_Play(0, 0x17, 0xFF)`, `0x4000` restore with `0x13`).
- Bug fixed: the draft lacked the `gDPPipeSync` that retail emits after each of the two `gDPLoadTextureTile` in the picture branch (two display-list commands); added.
- Data: retail keeps `D_800615E0` in a register across `Dma_ReadRom` (a function static); the C has `static s32 D_800615E0 = -1;` and the NON_MATCHING build leaves out the retail build's file-scope definition. The draft's struct views were rewritten to the module's D2 definitions (`D2DstRom`, flat `s16`/pointer arrays, `u8 D_8006158C[4][3]`); `D2DstRom` is declared before the function in the NON_MATCHING build only.
- Open: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **Menu_UpdateMapPage** (0x1234 bytes)
  - w5 s2: Only skimmed, no real attempt: large menu/cursor logic (853 and 1167 instructions). B844 copies a 3-byte local array from D_800615A8.
  - w5 s3: Looked at only (1167 instructions, m2c output in c598_m2c.txt). Probably blocked on D2: D_8008FB5C and D_8008FB60 (bss) and D_800615E0 (.data, -1) are used only here, which points to function statics, as in B844.
  - w5 s4: Previously untried. It is blocked on D2: D_800615E0 must be a function static (`static s32 D_800615E0 = -1;`). With an extern, IDO CSEs its address into s0 across the Dma_ReadRom call. With the static, that part matches (tested, not committed). The draft is good for D2: w5s4/c/C598_e0.c and C598_d2.c (noreg 130-132 of 1165 instructions). Structure is known: two map branches (24 strips of 244x8 in branch 1; two halves from D_8006158C/98/5C/6C in branch 2), wobble, cursor, input tail. Also found: the 4 scale/offset loads (D_800614B4/CC[n], [n+6]) are hoisted before `if (D_80060F28 == -1.0f)`, which reproduces only with 4 new named locals. The frame (0x120) then needs 4 fewer locals elsewhere. The -2 in the first cursor call is a variable (`ox = -2`), not a literal. Each gDP macro's `_g` block local takes a stack slot under -g3.
  - w5 s5: Still blocked on D2: it needs `static s32 D_800615E0 = -1;`. The drafts are w5s4/c/C598_e0.c and C598_d2.c.
  - w5 s6: Blocked on D2: needs `static s32 D_800615E0 = -1;`. Confirmed from the asm: the value is kept across the jal Dma_ReadRom. Drafts are w5s4/c/C598_e0.c and C598_d2.c.
  - Claude retry: not attempted beyond reading; the D2 statics are now possible (D_800615E0 needs to be a C598 static, so .data D_800615AC/CC must be defined between B844 and C598, D_800615E4.. after; 2B530_data_split_for_B844_C598.c has that layout). The draft's extern types (Unk800614E4, Unk8006158C, ...) must be reconciled with the file's D2 types first.
