/* Unmatched research draft for func_80011AE0. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80011AE0_8words.c
 * Snapshot SHA-256: 999660e1350c9eb9681e4fdfae30c28c933515033d6a7b5cb0d0bade94859641
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80011AE0(void)
{
  Unk8004DEF4 *p;
  s32 i;
  u16 *src;
  u16 *dst;
  s32 n;
  int new_var;
  s32 k;
  Unk80084994Elem *e;
  D_80084334 = D_8004DED0[3].unk0;
  p = D_8004DEF4;
  i = 3;
  if (0)
  {
  }
  new_var = (long long) D_80084980;
  if (new_var < D_8004DED0[3].unk0)
  {
    do
    {
      p--;
      n = i--;
      if (n == 0)
      {
        break;
      }
    }
    while (D_80084980 < p->unk0);
  }
  if (i < 0)
  {
    p = D_8004DEF4;
    D_80084330 = 3;
  }
  else
  {
    D_80084330 = i;
  }
  src = D_800808B0[p->unk4];
  dst = D_800806B0;
  i = 0x100;
  do
  {
    *(dst++) = *(src++);
    i--;
  }
  while (i != 0);
  D_8008433C = 0;
  if ((++D_80084330) >= 4)
  {
    D_80084330 = 0;
  }
  if (D_8007C280 & 2)
  {
    D_80084988 = D_80084980;
    D_8008498C = D_80084984;
  }
  else
  {
    e = &D_80084994->unk0[D_80084994->unk4 - 1];
    D_80084988 = 0;
    D_8008498C = e->unk0;
  }
  func_80012A60();
  D_80084338 = 0;
}
