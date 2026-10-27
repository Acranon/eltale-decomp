# PakMenu_Run

Current snapshot: 2026-10-26, main `f529079`. Historical measurements below may be from older compiler inputs or source layouts; the current gap takes precedence.

- Live source: [`src/overlays/pakmenu/pakmenu.c`](../overlays/pakmenu/pakmenu.c)
- Retail assembly: [`asm/nonmatchings/overlays/pakmenu/pakmenu/PakMenu_Run.s`](../../asm/nonmatchings/overlays/pakmenu/pakmenu/PakMenu_Run.s)
- Retail code size: `0x1294` bytes
- Current gap: 37 linked ROM words (NON_MATCHING C in the source); length and frame exact.
- Specific blocker: Explicit signedStick<33 XOR1 gives retail slti/xori separation. Cached signed Y is v1 as retail; pad pointer is s1 instead of s0, raw X a1 instead of s1, then partial-OR temporaries rotate.
- Next discriminating test: Use constrained allocation tracing on pointer/raw-X live ranges at +0x1154, preserving all now-matching operations and ABI.
- C: in [`src/overlays/pakmenu/pakmenu.c`](../overlays/pakmenu/pakmenu.c) under `#ifdef NON_MATCHING` (`NON_MATCHING=1 ./build.sh`)
- Original whole-source snapshot: `/home/sean/eltale-notes/codex/09ec-focus/func_801009EC_37words.c` (SHA-256 `4fa8eb94d8c2de18d3561e6db9e6b2b7eea5cd84060452501c3f6f684b27b82e`)
- Detailed research reports: [ REPORT.txt ](reports/codex__09ec-focus__REPORT.txt), [ REPORT-resume.txt ](reports/codex__overlay-oct26__REPORT-resume.txt)

## Equivalence

Verdict: **equivalent.**

- Checked: linked NON_MATCHING build against retail with asm-differ, every instruction. All 37 differing
  words are in the two pad-reading blocks at the loop bottom and are register numbers only (pad pointer s1
  vs s0, stick_x a1 vs s1, the partial-OR temps); the slti/xori/sll/or sequence and the lhu/lb loads are the
  same instructions in the same order.
- func_801008F0 takes `u8* arg0` in the NON_MATCHING build (its definition is switched with `#ifdef`); it
  only passes the pointer on to func_80101C80's `u8* str` and compiles to the same code either way.
- The draft uses the module's .bss objects (D_801072xx_ovl_DA4570) and the module's message arrays; the
  externs it adds (input_connected_port_bits, input_primary_port, input_controller_statuses, func_8003D0F0/D554/D6B0, func_8003EDC0) are in the
  file's NON_MATCHING block and match their definitions.
- Bugs fixed: none.
- Open doubts: none.

## Prior attempts and findings

This is the original worker history. Treat old D1/D2 labels and old best scores as historical.

- **PakMenu_Run** (0x12C4 bytes)
  - w7 s1: Large (0x1290) controller-pak boot screen. Not attempted beyond m2c.
  - w7 s2: Controller-pak screen, first real attempt. A full C draft is structurally right. Locals found: OSContPad pads[4] at 0x168; one u16 var at 0x162 that holds prev buttons, then pressed buttons; repeat 0x15C; blink 0x15A; u32 timer 0x154; OSPfs pfs at 0xEC and pfs2 at 0x84; count 0x80; maxFiles 0x7C. At -g3 every declared local gets a slot, so the frame only fits with exactly 10 locals below count. Blocked: the message strings D_80105408/448/4B0/4E8/578/608 are statics in the original. Retail builds each address right at its call; IDO hoists extern addresses into s-registers, even with a different symbol for each use. That uses up the register that holds &pfs in $fp in retail.
  - w7 s3: Down from 1101 to 971 words. The string addresses are not a statics problem. Micro-tests show IDO hoists extern, static and literal LDAs alike whenever an s-register is free. Retail just has none left. Two fixes put fp = &pfs and the early s-registers in line with retail: (1) the 0x80200000 clear loop needs its own 'u32* p' pointer in place of the 'unused1' slot, while-loop form '*p++ = 0'; (2) func_8003DEA0's third argument is 'D_80107080 + i', which keeps IDO from strength-reducing it. Remaining: retail never uses t0, so held is in t1. btn is in a3 and the CE copy in a2; mine has them the other way round. Strings still get hoisted in some cases. Best draft: scratchpad w7s3/pb_r1.c.
  - w7 s4: Still 971 words. Retail evaluates PAD_BUTTONS with stick_y>32 first. In isolation '((x>32)|((y>32)<<3)|((y<-32)<<2)|((x<-32)<<1)) | button' (button last) reproduces that order. In the full function it made no difference. The rest is a one-register shift: retail has held in t1 and cur (u16) in t0, mine has held in t0 and cur in a3. Making the 09EC-only globals (72CC/72CF/72D4/72D8/72E4) function-local statics made it worse (1087).
  - w7 s5: Down from 971 to 50 words, all register-only, all in the two pad-reading blocks at the loop bottom. Draft: ~/eltale-w7-drafts/09ec_50words_padregs.c (57-word base: 09ec_57words_base.c). It needs func_801008F0 (already matched) changed to take u8* arg0, and the calls passing D_801054xx without the (s32) cast; 08F0 still matches. What fixed the rest: (1) the u8* signature stops IDO hoisting the message address into an s-register. (2) D_801072D0 = (D_801072D4 == 0) ? 0x60 : 0xA6 ternaries at some sites. (3) count = D_801072D8 = 0; sub++; in cases 5 and 8. (4) a break at the end of case 5's sub==1 branch. (5) count--; first in case 3's else branch. (6) 'D_801072D8 += (u8)((D_80107080[ret2].unk0 + 0xFF) >> 8)' in place of file->unk0: a load through the file pointer stops IDO promoting the address-taken local count into v1. (7) (D_801072CA != D_801072CC) || (D_801072CE != D_801072CF). (8) 'if (1) {}' between count = 0; and the func_8003EDC0 call. (9) Pad bits built in an s16 local, dir (replacing unused2): dir = (x > 32) | ((y > 32) << 3); dir |= (y < -32) << 2; dir |= (x < -32) << 1; btn = pads[input_primary_port].button | dir;. Still wrong: retail has the pad pointer in s0, stick_x in s1 and stick_y in v1. Mine gets s1, a1 and v1 (or s1 for x when it is assigned through i first). Tried with no fix: block-scoped or new locals (the frame grows 8 bytes under -g3), reusing ret/ret2/ret3/file/i for x, y or the pointer, all 72 term orders, line splits, empty-if insertions, coordinate descent and a random search.
  - Codex D1 implementation: D1 pass: saved48-word source reproduced, improved to42 actual ROM words with pad pointer/stick-x now in correct s0/s1. Nested s16 partial-OR conversions avoid direction accumulator taking s0. Corrected stale SDK names/prototypes before linking; complete replay and retained48-word base in codex/d1-overlay/. Remaining operation ordering/register differences.
  - Claude D2: not attempted. DA4570.c now defines the overlay bss (80107080..80107300) and .data 80105660..80107050 (main 3f3f002), so the bss names are D_801072xx_ovl_DA4570: rename them in the saved drafts. The 50-word remainder is register-only and doesn't depend on data placement.
  - Claude retry: codex 42-word draft reproduced in the D2 file (rename bss names to _ovl_DA4570, change func_801008F0's definition to `u8* arg0`: it passes it to func_80101C80's u8* str, so that is its real type). Draft ~/eltale-notes/claude/rpc/09ec_42w_ovlnames.c. Expression forms of the pad direction bits (plain/ternary/reversed/u16, with and without the dir local) were no better (57+); not pursued further.
