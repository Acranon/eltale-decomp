/* Unmatched research draft for func_80022658. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/216E0.unmatched.c
 * Snapshot SHA-256: 7ff9fe03d31676f3169fb29b16ae3844a590e79894fed6fd6bd408dbebeef7f8
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80022658(void* arg0) {
    s32 tmp;
    volatile s32 id;
    s32 t;
    s32 w;
    s32 yoff;
    u8* str;

    D_8008C174 = 0x69;
    D_8008C178 = 0x32;
    w = ((Struct_80022658*)arg0)->unk122;
    id = (u8)w;
    str = D_800C03D8[(u8)(w >> 8) & 0xF][(u8)w];
    gDPPipeSync(D_8007A184++);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    yoff = 0;
    if (D_8008C15A && (D_8008C15C & 2)) {
        w = D_8008C15A;
        t = w * w;
        yoff = t * 40 / 64;
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetCombine(D_8007A184++, 0xFF9BFF, 0xFF34FE7F);
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, 255 - t * 255 / 64);
        D_8008C15A--;
    }
    func_80024EB0(&D_803A8718, 0, yoff, 0x6E, 0xE, 0x64, 0xE, 0x400, 0x400);
    func_80024694(0x37 - func_80024904(str) / 2, yoff + 3, 0, str);
    gDPPipeSync(D_8007A184++);
    gDPSetRenderMode(D_8007A184++, 0x0F0A4000, 0);
    gDPSetCombine(D_8007A184++, 0xFFFFFF, 0xFFFCF279);
}
