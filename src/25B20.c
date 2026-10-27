#include "common.h"

/*
 * Items: the 150-slot inventory (D_8008C9B8), the in-field inventory menu with its icon cache,
 * and the per-kind "can use" / "use" handlers (restore, warp, spell).
 * Folder: src/game/item/   (proposed for round 4)
 */

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ char unk8[4];
} Struct_803AAAA0;

typedef struct {
    char unk0[4];
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} Struct_80026054_64;

typedef struct {
    char unk0[0x64];
    Struct_80026054_64* unk64;
} Struct_80026054;

typedef struct {
    char unk0[0x14];
    u16 unk14;
} Struct_8007C288;

typedef s32 (*ItemFunc)(void*, Struct_803AAAA0*, u8);

extern u8 D_D384B0[];
extern u8 D_8007AA20[];
extern Struct_8007C288* D_8007C288;
extern u16 D_800842B8;
extern u16 D_8008BE52;
extern u8 D_8008CA4E;
extern u8 D_803AC460[];
extern Struct_803AAAA0 D_803AAAA0[];

void Dma_ReadRom(void*, void*, s32);
void Player_StartUseItem(u8);
void Magic_CreateCastEffect(s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x64 - 0xC];
    /* 0x64 */ Struct_80026054_64* unk64;
} Struct_80026140;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AB36C;

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AAA40;

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Struct_80084300;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    char unk0[0xA];
} Struct_803AB358;

extern s32 D_8004DCA0;
extern s32 D_8007A174;
extern s16 D_8007A178;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern s16 D_8007AA0E;
extern Struct_80084300 D_80084300;
extern Struct_803AAA40 D_803AAA40[];
extern Struct_803AB358 D_803AB358[];
extern Struct_803AB36C D_803AB36C[];

void Effect_AddFloatingNumber(Struct_80026140*, s32, s32);
void Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, Struct_803AB358*, Vec3f*, Struct_80026140*);
void Sfx_Play(s32, s32, s32);

s32 Item_CanUseNever(s32 arg0, Struct_803AAAA0* arg1);
s32 Item_CanUseRestore(Struct_80026054* arg0, Struct_803AAAA0* arg1);
s32 Item_CanUseWarp(s32 arg0, Struct_803AAAA0* arg1);
s32 Item_CanUseSpell(s32 arg0, Struct_803AAAA0* arg1);
void Item_UseNothing(s32 arg0, Struct_803AAAA0* arg1);
void Item_UseRestore(Struct_80026140* arg0, Struct_803AAAA0* arg1);
void Item_UseWarp(Struct_80026140* arg0, Struct_803AAAA0* arg1);
void Item_UseSpell(s32 arg0, Struct_803AAAA0* arg1);

/* .bss 8008C190..8008CA50, in address order (IDO emits .bss by first declaration). */
Vec3f D_8008C190;
s32 D_8008C19C;
s32 D_8008C1A0;
s32 D_8008C1A4;
s32 D_8008C1A8; /* unreferenced */
s32 D_8008C1AC; /* unreferenced */
u8 D_8008C1B0[8];
u8 D_8008C1B8[0x800];
u8 D_8008C9B8[0x97];

/* .data 8004F4A0..8004F4D0 */
ItemFunc D_8004F4A0[] = {
    (ItemFunc) Item_CanUseNever,
    (ItemFunc) Item_CanUseRestore,
    (ItemFunc) Item_CanUseWarp,
    (ItemFunc) Item_CanUseSpell,
};
ItemFunc D_8004F4B0[] = {
    (ItemFunc) Item_UseNothing,
    (ItemFunc) Item_UseRestore,
    (ItemFunc) Item_UseWarp,
    (ItemFunc) Item_UseSpell,
};
u16 D_8004F4C0 = 0; /* only Item_UpdateInventoryMenu uses it */

void Item_InitInventory(void) {
    s32 i;
    u8* p;

    Dma_ReadRom(D_D384B0, D_803AC460, 0x400);
    i = 8;
    p = D_8008C1B0;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    i = 0x97;
    p = D_8008C9B8;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    D_8008C19C = 0;
    D_8008C1A0 = 0;
    D_8008C1A4 = 0;
}

s32 Item_HasInventoryRoom(void) {
    s32 ret;

    if (D_8008C9B8[0x95] != 0xFF) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 Item_CountInInventory(u8 arg0) {
    s32 count = 0;
    s32 i = 0x96;
    u8* p = D_8008C9B8;

    while (i != 0 && *p != 0xFF) {
        i--;
        if (arg0 == *p) {
            count++;
        }
        p++;
    }
    return count;
}

s32 Item_GetInventoryCount(void) {
    s32 count = 0;
    s32 i = 0x96;
    u8* p = D_8008C9B8;

    while (i != 0 && *p != 0xFF) {
        i--;
        count++;
        p++;
    }
    return count;
}

void Item_AddToInventory(u8 arg0) {
    s32 i;

    for (i = 0; i < 0x96; i++) {
        if (D_8008C9B8[i] == 0xFF) {
            break;
        }
    }
    D_8008C9B8[i] = arg0;
}

s32 Item_TryUse(u8 arg0) {
    s32 ret = 0;
    Struct_803AAAA0* item = &D_803AAAA0[arg0];

    if ((D_8008BE52 & 1) && (item->unk0 & 2)) {
        ret = 1;
    } else if (!(D_8008BE52 & 1) && (item->unk0 & 1)) {
        ret = 1;
    }
    if (ret) {
        ret = D_8004F4A0[item->unk2](D_8007AA20, item, arg0);
    }
    if (ret) {
        Player_StartUseItem(arg0);
    }
    return ret;
}

void Item_ApplyEffect(u8 arg0, void* arg1) {
    D_8004F4B0[D_803AAAA0[arg0].unk2](arg1, &D_803AAAA0[arg0], arg0);
}

s32 func_80025228(u16 arg0) {
    s32 found = 0;
    u8* p = D_8008C9B8;
    s32 i = 0x96;
    Struct_803AAAA0* e;

    while (!found && *p != 0xFF) {
        e = &D_803AAAA0[*p++];
        if (e->unk2 == 0xF) {
            found = (arg0 == e->unk4);
        }
        i--;
    }
    if (found) {
        p--;
        while (i != 0) {
            *p = *(p + 1);
            p++;
            i--;
        }
        *p = 0xFF;
    }
    return found;
}

#ifdef NON_MATCHING
/* stack homes, saved registers and frame differ; code is equivalent */
void Item_DrawMenuFrame(s32, s32, s32, s32);
void Text_DrawEncodedString(s32, s32, void*);
void Fade_Start(s32, s32, void*);
extern Gfx* D_8007A184;
extern s8 D_80092C81;
extern u16 D_80092C86;
extern u8 D_8004F5B4[];
extern Gfx D_1000388[];
extern u8 D_8039AFB0[];
extern Gfx D_803AA7C0[];
extern Gfx D_803AA828[];
extern Gfx D_803AA940[];
extern Gfx D_803AA998[];
extern Gfx D_803AA9F0[];
extern u8 D_803AC660[];
extern void* D_803AB288[];
extern void* D_803AB2F0[];


void Item_UpdateInventoryMenu(void) {
    volatile s32 n;
    u8* list;
    s32 count;
    s32 changed;
    u8* slot;
    s32 k;
    s32 x;
    s32 hl;
    u8* p;
    u8* tex;
    u8* fp;
    u8 freeSlots[8];
    s32 y;
    s32 b;

    gSPDisplayList(D_8007A184++, D_803AA7C0);
    Item_DrawMenuFrame(0x46, 0x7F, 0xB2, 0x16);
    Item_DrawMenuFrame(0x48, 0x44, 0xAD, 0x36);
    gSPDisplayList(D_8007A184++, D_803AA940);
    gSPDisplayList(D_8007A184++, D_803AA998);
    x = D_80092C81;
    if (x > 5) {
        x -= 5;
    } else if (x < -5) {
        x += 5;
    } else {
        x = 0;
    }
    list = &D_8008C9B8[D_8008C19C];
    p = list;
    n = 8;
    while (n != 0 && *p != 0xFF) {
        n--;
        p++;
    }
    count = 8 - n;
    if (count != 0) {
        changed = 0;
        if (x != 0) {
            if (D_8008C1A4 != 0 && (x ^ D_8008C1A4) < 0) {
                D_8008C1A4 = 0;
            } else {
                D_8008C1A4 += x;
                if (D_8008C1A4 > 250) {
                    D_8008C1A4 = 0;
                    changed++;
                    if (++D_8008C1A0 >= count) {
                        D_8008C1A0 = count - 1;
                        if (D_8008C19C < 0x96 - count) {
                            D_8008C19C++;
                            if (D_8008C9B8[D_8008C19C + count - 1] == 0xFF) {
                                D_8008C19C--;
                                changed--;
                            }
                        }
                    }
                } else if (D_8008C1A4 < -250) {
                    D_8008C1A4 = 0;
                    changed++;
                    if (--D_8008C1A0 < 0) {
                        D_8008C1A0 = 0;
                        if (D_8008C19C > 0) {
                            D_8008C19C--;
                        } else {
                            changed--;
                        }
                    }
                }
                if (changed) {
                    Sfx_Play(0, 3, 0xFF);
                }
            }
            list = &D_8008C9B8[D_8008C19C];
            p = list;
        } else {
            D_8008C1A4 = 0;
            p = list;
        }
        fp = freeSlots;
        slot = D_8008C1B0;
        n = 8;
        do {
            k = count;
            while (k != 0 && *slot != *p) {
                k--;
                p++;
            }
            slot++;
            if (k == 0) {
                *fp++ = 8 - n;
                list = &D_8008C9B8[D_8008C19C];
            }
            n--;
            p = list;
        } while (n != 0);
        x = 0x1AC;
        gSPDisplayList(D_8007A184++, D_803AA9F0);
        hl = 0;
        n = count;
        while (n != 0 && *p != 0xFF) {
            k = 8;
            slot = D_8008C1B0;
            while (k != 0 && *p != *slot) {
                k--;
                slot++;
            }
            if (k == 0) {
                k = *--fp;
                D_8008C1B0[k] = *p;
                tex = ((u8 (*)[0x100])D_8008C1B8)[k];
                Dma_ReadRom(&D_D384B0[(*p << 8) + 0x400], tex, 0x100);
            } else {
                tex = ((u8 (*)[0x100])D_8008C1B8)[8 - k];
            }
            gDPLoadTextureBlock(D_8007A184++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            p++;
            if (D_8008C1A0 == count - n) {
                gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
                gDPLoadTLUT_pal256(D_8007A184++, D_803AC460);
                hl = 1;
            } else if (hl) {
                gDPSetEnvColor(D_8007A184++, 0x7F, 0x7F, 0x7F, 0xFF);
                gDPLoadTLUT_pal256(D_8007A184++, D_803AC660);
                hl = 0;
            }
            gSPTextureRectangle(D_8007A184++, x, 0x20C, x + 0x40, 0x24C, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
            x += 0x44;
            n--;
        }
        x = D_8008C1A0 * 0x44 + 0x1D4;
        y = 0x1F0 - (u16)((sins(D_8004F4C0 & 0x7FFF) >> 13) << 2);
        gSPDisplayList(D_8007A184++, D_803AA828);
        gSPTextureRectangle(D_8007A184++, x, y, x + 0x30, y + 0x30, G_TX_RENDERTILE, 0x9C0, 0, 0x400, 0x400);
        if (count == 8) {
            b = sins((D_8004F4C0 * 2) & 0x7FFF);
            gDPLoadTextureTile(D_8007A184++, D_8039AFB0, G_IM_FMT_CI, G_IM_SIZ_8b, 176, 0, 90, 0, 146, 13, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            if (D_8008C19C != 0) {
                gSPTextureRectangle(D_8007A184++, 0x218, 0x250, 0x234, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(D_8007A184++, (0x77 - (b >> 13)) * 4, 0x248, (0x85 - (b >> 13)) * 4, 0x274,
                                    G_TX_RENDERTILE, 0xEE0, 0, 0x400, 0x400);
            }
            if (D_8008C9B8[D_8008C19C + 8] != 0xFF) {
                gSPTextureRectangle(D_8007A184++, 0x348, 0x250, 0x364, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(D_8007A184++, ((b >> 13) + 0xDA) * 4, 0x248, ((b >> 13) + 0xE8) * 4, 0x274,
                                    G_TX_RENDERTILE, 0x10A0, 0, 0x400, 0x400);
            }
        }
        gSPDisplayList(D_8007A184++, D_1000388);
        Text_DrawEncodedString(0x77, 0x48, D_803AB288[D_8008C9B8[D_8008C19C + D_8008C1A0]]);
        Text_DrawEncodedString(0x4E, 0x5A, D_803AB2F0[D_8008C9B8[D_8008C19C + D_8008C1A0]]);
        if ((D_80092C86 & 0xA000) && Item_TryUse(D_8008C9B8[D_8008C19C + D_8008C1A0])) {
            p = &D_8008C9B8[D_8008C19C + D_8008C1A0];
            for (n = 0x95 - D_8008C19C - D_8008C1A0; n != 0; n--) {
                *p = p[1];
                p++;
            }
            *p = 0xFF;
            D_8004DCA0 &= ~1;
            Fade_Start(6, 4, D_8004F5B4);
            list = &D_8008C9B8[D_8008C19C];
            if (list[D_8008C1A0] == 0xFF) {
                if (D_8008C19C > 0) {
                    D_8008C19C--;
                } else if (D_8008C1A0 > 0) {
                    D_8008C1A0--;
                }
            } else if (list[7] == 0xFF && D_8008C19C > 0) {
                D_8008C19C--;
            }
        }
        D_8004F4C0 += 0x300;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/25B20/Item_UpdateInventoryMenu.s")
#endif

s32 Item_CanUseNever(s32 arg0, Struct_803AAAA0* arg1) {
    return 0;
}

s32 Item_CanUseRestore(Struct_80026054* arg0, Struct_803AAAA0* arg1) {
    s32 ret = 0;
    Struct_80026054_64* temp = arg0->unk64;

    if ((arg1->unk4 != 0) && (temp->unk6 != temp->unk4)) {
        ret = 1;
    }
    if ((arg1->unk6 != 0) && (temp->unkA != temp->unk8)) {
        ret = 1;
    }
    return ret;
}

s32 Item_CanUseWarp(s32 arg0, Struct_803AAAA0* arg1) {
    s32 ret;

    if ((D_800842B8 & 0xA) || (D_8007C288->unk14 & 4)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 Item_CanUseSpell(s32 arg0, Struct_803AAAA0* arg1) {
    s32 ret = 1;

    if ((D_8008BE52 & 0x100) && (arg1->unk0 & 8)) {
        ret = 0;
    }
    return ret;
}

// empty
void Item_UseNothing(s32 arg0, Struct_803AAAA0* arg1) {
}

void Item_UseRestore(Struct_80026140* arg0, Struct_803AAAA0* arg1) {
    u16 amt;
    Struct_80026054_64* st = arg0->unk64;
    Struct_803AB358* fx;

    if (arg1->unk4 != 0) {
        amt = st->unk6 - st->unk4;
        if (arg1->unk4 < amt) {
            amt = arg1->unk4;
        }
        st->unk4 += amt;
        Effect_AddFloatingNumber(arg0, 1, amt);
    }
    if (arg1->unk6 != 0) {
        amt = st->unkA - st->unk8;
        if (arg1->unk6 < amt) {
            amt = arg1->unk6;
        }
        st->unk8 += amt;
        Effect_AddFloatingNumber(arg0, 2, amt);
    }
    D_8008C190.x = D_803AB36C[0].unk8;
    D_8008C190.y = D_803AB36C[0].unkC;
    fx = &D_803AB358[D_803AB36C[0].unk0];
    D_8008C190.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[0].unk2, D_803AB36C[0].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &D_8008C190, arg0);
    Sfx_Play(0, 0xB, 0xFF);
}

void Item_UseWarp(Struct_80026140* arg0, Struct_803AAAA0* arg1) {
    Struct_803AB358* fx;

    D_8004DCA0 |= 0x80;
    D_8007A174 = 0x16;
    D_80084300.unk0 = D_803AAA40[arg1->unk4].unk0;
    D_80084300.unk4 = D_803AAA40[arg1->unk4].unk2;
    D_80084300.unk8 = -1;
    D_8007A98C = D_803AAA40[arg1->unk4].unk4;
    D_8007A990 = D_803AAA40[arg1->unk4].unk8;
    D_8007A994 = D_803AAA40[arg1->unk4].unkC;
    D_8007A998 = 0x108;
    D_8007AA0E = 0;
    D_8007A178 = 1;
    D_8008C190.x = D_803AB36C[1].unk8;
    D_8008C190.y = D_803AB36C[1].unkC;
    fx = &D_803AB358[D_803AB36C[1].unk0];
    D_8008C190.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[1].unk2, D_803AB36C[1].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &D_8008C190, arg0);
    Sfx_Play(0, 0x3B, 0xFF);
}

void Item_UseSpell(s32 arg0, Struct_803AAAA0* arg1) {
    Magic_CreateCastEffect(arg0, arg1->unk4, 0, 4);
}

extern Gfx* D_8007A184;
extern Gfx D_803AA8A8[];

void Item_DrawMenuFrame(s32 x, s32 y, s32 w, s32 h) {
    gDPPipeSync(D_8007A184++);
    gDPSetCycleType(D_8007A184++, G_CYC_FILL);
    gDPSetRenderMode(D_8007A184++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetFillColor(D_8007A184++, 0x00010001);
    gDPFillRectangle(D_8007A184++, x, y, (x + w), y);
    gDPFillRectangle(D_8007A184++, x, (y + h), (x + w), (y + h));
    gDPFillRectangle(D_8007A184++, x, y, x, (y + h));
    gDPFillRectangle(D_8007A184++, (x + w), y, (x + w), (y + h));
    gDPFillRectangle(D_8007A184++, x + 3, (y + h) + 1, (x + w) + 2, (y + h) + 2);
    gDPFillRectangle(D_8007A184++, (x + w) + 1, y + 3, (x + w) + 2, (y + h) + 1);
    gSPDisplayList(D_8007A184++, D_803AA8A8);
    gSPTextureRectangle(D_8007A184++, (x + 1) << 2, (y + 1) << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}
