#include "common.h"

/*
 * Items: the 150-slot inventory (item_inventory), the in-field inventory menu with its icon cache,
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
extern Struct_8007C288* map_subarea_def;
extern u16 map_flags;
extern u16 battle_flags;
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

extern s32 core_flags;
extern s32 core_transition_timer;
extern s16 fade_transition_style;
extern f32 player_spawn_x;
extern f32 player_spawn_z;
extern f32 player_spawn_rot;
extern s32 player_spawn_type;
extern s16 D_8007AA0E;
extern Struct_80084300 exit_destination;
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
Vec3f item_effect_scale;
s32 item_menu_scroll;
s32 item_menu_cursor;
s32 item_menu_stick_accum;
s32 D_8008C1A8; /* unreferenced */
s32 D_8008C1AC; /* unreferenced */
u8 item_icon_cache_ids[8];
u8 item_icon_cache_tex[0x800];
u8 item_inventory[0x97];

/* .data 8004F4A0..8004F4D0 */
ItemFunc item_can_use_handlers[] = {
    (ItemFunc) Item_CanUseNever,
    (ItemFunc) Item_CanUseRestore,
    (ItemFunc) Item_CanUseWarp,
    (ItemFunc) Item_CanUseSpell,
};
ItemFunc item_use_handlers[] = {
    (ItemFunc) Item_UseNothing,
    (ItemFunc) Item_UseRestore,
    (ItemFunc) Item_UseWarp,
    (ItemFunc) Item_UseSpell,
};
u16 item_menu_bob_phase = 0; /* only Item_UpdateInventoryMenu uses it */

void Item_InitInventory(void) {
    s32 i;
    u8* p;

    Dma_ReadRom(D_D384B0, D_803AC460, 0x400);
    i = 8;
    p = item_icon_cache_ids;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    i = 0x97;
    p = item_inventory;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    item_menu_scroll = 0;
    item_menu_cursor = 0;
    item_menu_stick_accum = 0;
}

s32 Item_HasInventoryRoom(void) {
    s32 ret;

    if (item_inventory[0x95] != 0xFF) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 Item_CountInInventory(u8 arg0) {
    s32 count = 0;
    s32 i = 0x96;
    u8* p = item_inventory;

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
    u8* p = item_inventory;

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
        if (item_inventory[i] == 0xFF) {
            break;
        }
    }
    item_inventory[i] = arg0;
}

s32 Item_TryUse(u8 arg0) {
    s32 ret = 0;
    Struct_803AAAA0* item = &D_803AAAA0[arg0];

    if ((battle_flags & 1) && (item->unk0 & 2)) {
        ret = 1;
    } else if (!(battle_flags & 1) && (item->unk0 & 1)) {
        ret = 1;
    }
    if (ret) {
        ret = item_can_use_handlers[item->unk2](D_8007AA20, item, arg0);
    }
    if (ret) {
        Player_StartUseItem(arg0);
    }
    return ret;
}

void Item_ApplyEffect(u8 arg0, void* arg1) {
    item_use_handlers[D_803AAAA0[arg0].unk2](arg1, &D_803AAAA0[arg0], arg0);
}

s32 func_80025228(u16 arg0) {
    s32 found = 0;
    u8* p = item_inventory;
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
extern Gfx* gfx_dl_head;
extern s8 input_stick_x;
extern u16 input_pressed_buttons;
extern u8 fade_black_ramp_dim[];
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

    gSPDisplayList(gfx_dl_head++, D_803AA7C0);
    Item_DrawMenuFrame(0x46, 0x7F, 0xB2, 0x16);
    Item_DrawMenuFrame(0x48, 0x44, 0xAD, 0x36);
    gSPDisplayList(gfx_dl_head++, D_803AA940);
    gSPDisplayList(gfx_dl_head++, D_803AA998);
    x = input_stick_x;
    if (x > 5) {
        x -= 5;
    } else if (x < -5) {
        x += 5;
    } else {
        x = 0;
    }
    list = &item_inventory[item_menu_scroll];
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
            if (item_menu_stick_accum != 0 && (x ^ item_menu_stick_accum) < 0) {
                item_menu_stick_accum = 0;
            } else {
                item_menu_stick_accum += x;
                if (item_menu_stick_accum > 250) {
                    item_menu_stick_accum = 0;
                    changed++;
                    if (++item_menu_cursor >= count) {
                        item_menu_cursor = count - 1;
                        if (item_menu_scroll < 0x96 - count) {
                            item_menu_scroll++;
                            if (item_inventory[item_menu_scroll + count - 1] == 0xFF) {
                                item_menu_scroll--;
                                changed--;
                            }
                        }
                    }
                } else if (item_menu_stick_accum < -250) {
                    item_menu_stick_accum = 0;
                    changed++;
                    if (--item_menu_cursor < 0) {
                        item_menu_cursor = 0;
                        if (item_menu_scroll > 0) {
                            item_menu_scroll--;
                        } else {
                            changed--;
                        }
                    }
                }
                if (changed) {
                    Sfx_Play(0, 3, 0xFF);
                }
            }
            list = &item_inventory[item_menu_scroll];
            p = list;
        } else {
            item_menu_stick_accum = 0;
            p = list;
        }
        fp = freeSlots;
        slot = item_icon_cache_ids;
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
                list = &item_inventory[item_menu_scroll];
            }
            n--;
            p = list;
        } while (n != 0);
        x = 0x1AC;
        gSPDisplayList(gfx_dl_head++, D_803AA9F0);
        hl = 0;
        n = count;
        while (n != 0 && *p != 0xFF) {
            k = 8;
            slot = item_icon_cache_ids;
            while (k != 0 && *p != *slot) {
                k--;
                slot++;
            }
            if (k == 0) {
                k = *--fp;
                item_icon_cache_ids[k] = *p;
                tex = ((u8 (*)[0x100])item_icon_cache_tex)[k];
                Dma_ReadRom(&D_D384B0[(*p << 8) + 0x400], tex, 0x100);
            } else {
                tex = ((u8 (*)[0x100])item_icon_cache_tex)[8 - k];
            }
            gDPLoadTextureBlock(gfx_dl_head++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            p++;
            if (item_menu_cursor == count - n) {
                gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xFF);
                gDPLoadTLUT_pal256(gfx_dl_head++, D_803AC460);
                hl = 1;
            } else if (hl) {
                gDPSetEnvColor(gfx_dl_head++, 0x7F, 0x7F, 0x7F, 0xFF);
                gDPLoadTLUT_pal256(gfx_dl_head++, D_803AC660);
                hl = 0;
            }
            gSPTextureRectangle(gfx_dl_head++, x, 0x20C, x + 0x40, 0x24C, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
            x += 0x44;
            n--;
        }
        x = item_menu_cursor * 0x44 + 0x1D4;
        y = 0x1F0 - (u16)((sins(item_menu_bob_phase & 0x7FFF) >> 13) << 2);
        gSPDisplayList(gfx_dl_head++, D_803AA828);
        gSPTextureRectangle(gfx_dl_head++, x, y, x + 0x30, y + 0x30, G_TX_RENDERTILE, 0x9C0, 0, 0x400, 0x400);
        if (count == 8) {
            b = sins((item_menu_bob_phase * 2) & 0x7FFF);
            gDPLoadTextureTile(gfx_dl_head++, D_8039AFB0, G_IM_FMT_CI, G_IM_SIZ_8b, 176, 0, 90, 0, 146, 13, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            if (item_menu_scroll != 0) {
                gSPTextureRectangle(gfx_dl_head++, 0x218, 0x250, 0x234, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(gfx_dl_head++, (0x77 - (b >> 13)) * 4, 0x248, (0x85 - (b >> 13)) * 4, 0x274,
                                    G_TX_RENDERTILE, 0xEE0, 0, 0x400, 0x400);
            }
            if (item_inventory[item_menu_scroll + 8] != 0xFF) {
                gSPTextureRectangle(gfx_dl_head++, 0x348, 0x250, 0x364, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(gfx_dl_head++, ((b >> 13) + 0xDA) * 4, 0x248, ((b >> 13) + 0xE8) * 4, 0x274,
                                    G_TX_RENDERTILE, 0x10A0, 0, 0x400, 0x400);
            }
        }
        gSPDisplayList(gfx_dl_head++, D_1000388);
        Text_DrawEncodedString(0x77, 0x48, D_803AB288[item_inventory[item_menu_scroll + item_menu_cursor]]);
        Text_DrawEncodedString(0x4E, 0x5A, D_803AB2F0[item_inventory[item_menu_scroll + item_menu_cursor]]);
        if ((input_pressed_buttons & 0xA000) && Item_TryUse(item_inventory[item_menu_scroll + item_menu_cursor])) {
            p = &item_inventory[item_menu_scroll + item_menu_cursor];
            for (n = 0x95 - item_menu_scroll - item_menu_cursor; n != 0; n--) {
                *p = p[1];
                p++;
            }
            *p = 0xFF;
            core_flags &= ~1;
            Fade_Start(6, 4, fade_black_ramp_dim);
            list = &item_inventory[item_menu_scroll];
            if (list[item_menu_cursor] == 0xFF) {
                if (item_menu_scroll > 0) {
                    item_menu_scroll--;
                } else if (item_menu_cursor > 0) {
                    item_menu_cursor--;
                }
            } else if (list[7] == 0xFF && item_menu_scroll > 0) {
                item_menu_scroll--;
            }
        }
        item_menu_bob_phase += 0x300;
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

    if ((map_flags & 0xA) || (map_subarea_def->unk14 & 4)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 Item_CanUseSpell(s32 arg0, Struct_803AAAA0* arg1) {
    s32 ret = 1;

    if ((battle_flags & 0x100) && (arg1->unk0 & 8)) {
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
    item_effect_scale.x = D_803AB36C[0].unk8;
    item_effect_scale.y = D_803AB36C[0].unkC;
    fx = &D_803AB358[D_803AB36C[0].unk0];
    item_effect_scale.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[0].unk2, D_803AB36C[0].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &item_effect_scale, arg0);
    Sfx_Play(0, 0xB, 0xFF);
}

void Item_UseWarp(Struct_80026140* arg0, Struct_803AAAA0* arg1) {
    Struct_803AB358* fx;

    core_flags |= 0x80;
    core_transition_timer = 0x16;
    exit_destination.unk0 = D_803AAA40[arg1->unk4].unk0;
    exit_destination.unk4 = D_803AAA40[arg1->unk4].unk2;
    exit_destination.unk8 = -1;
    player_spawn_x = D_803AAA40[arg1->unk4].unk4;
    player_spawn_z = D_803AAA40[arg1->unk4].unk8;
    player_spawn_rot = D_803AAA40[arg1->unk4].unkC;
    player_spawn_type = 0x108;
    D_8007AA0E = 0;
    fade_transition_style = 1;
    item_effect_scale.x = D_803AB36C[1].unk8;
    item_effect_scale.y = D_803AB36C[1].unkC;
    fx = &D_803AB358[D_803AB36C[1].unk0];
    item_effect_scale.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[1].unk2, D_803AB36C[1].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &item_effect_scale, arg0);
    Sfx_Play(0, 0x3B, 0xFF);
}

void Item_UseSpell(s32 arg0, Struct_803AAAA0* arg1) {
    Magic_CreateCastEffect(arg0, arg1->unk4, 0, 4);
}

extern Gfx* gfx_dl_head;
extern Gfx D_803AA8A8[];

void Item_DrawMenuFrame(s32 x, s32 y, s32 w, s32 h) {
    gDPPipeSync(gfx_dl_head++);
    gDPSetCycleType(gfx_dl_head++, G_CYC_FILL);
    gDPSetRenderMode(gfx_dl_head++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetFillColor(gfx_dl_head++, 0x00010001);
    gDPFillRectangle(gfx_dl_head++, x, y, (x + w), y);
    gDPFillRectangle(gfx_dl_head++, x, (y + h), (x + w), (y + h));
    gDPFillRectangle(gfx_dl_head++, x, y, x, (y + h));
    gDPFillRectangle(gfx_dl_head++, (x + w), y, (x + w), (y + h));
    gDPFillRectangle(gfx_dl_head++, x + 3, (y + h) + 1, (x + w) + 2, (y + h) + 2);
    gDPFillRectangle(gfx_dl_head++, (x + w) + 1, y + 3, (x + w) + 2, (y + h) + 1);
    gSPDisplayList(gfx_dl_head++, D_803AA8A8);
    gSPTextureRectangle(gfx_dl_head++, (x + 1) << 2, (y + 1) << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}
