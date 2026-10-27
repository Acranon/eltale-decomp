#include "game/item/item.h"
#include "game/audio/sound.h"
#include "game/battle/battle.h"
#include "game/core/dma.h"
#include "game/core/main.h"
#include "game/env/env.h"
#include "game/gfx/effect.h"
#include "game/gfx/fade.h"
#include "game/input/input.h"
#include "game/magic/magic.h"
#include "game/map/map.h"
#include "game/player/player.h"
#include "game/text/text.h"
#include "game/ui/menu.h"

/*
 * Items: the 150-slot inventory (item_inventory), the in-field inventory menu with its icon cache,
 * and the per-kind "can use" / "use" handlers (restore, warp, spell).
 * Original file: 25B20.c (ROM 0x25B20).
 */


extern u8 D_D384B0[];
extern u8 D_803AC460[];
extern ItemDef D_803AAAA0[];



typedef struct {
    /* 0x0 */ u16 map_id;
    /* 0x2 */ u16 subarea;
    /* 0x4 */ f32 spawn_x;
    /* 0x8 */ f32 spawn_z;
    /* 0xC */ f32 spawn_rot;
} Struct_803AAA40;


extern Struct_803AAA40 D_803AAA40[];
extern MagicVisualDef D_803AB358[];
extern EnemyEffectDef D_803AB36C[];



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
ItemHandler item_can_use_handlers[] = {
    (ItemHandler) Item_CanUseNever,
    (ItemHandler) Item_CanUseRestore,
    (ItemHandler) Item_CanUseWarp,
    (ItemHandler) Item_CanUseSpell,
};
ItemHandler item_use_handlers[] = {
    (ItemHandler) Item_UseNothing,
    (ItemHandler) Item_UseRestore,
    (ItemHandler) Item_UseWarp,
    (ItemHandler) Item_UseSpell,
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
    ItemDef* item = &D_803AAAA0[arg0];

    if ((battle_flags & 1) && (item->use_flags & 2)) {
        ret = 1;
    } else if (!(battle_flags & 1) && (item->use_flags & 1)) {
        ret = 1;
    }
    if (ret) {
        ret = item_can_use_handlers[item->handler_index](&player_state.actor, item, arg0);
    }
    if (ret) {
        Player_StartUseItem(arg0);
    }
    return ret;
}

void Item_ApplyEffect(u8 arg0, void* arg1) {
    item_use_handlers[D_803AAAA0[arg0].handler_index](arg1, &D_803AAAA0[arg0], arg0);
}

s32 func_80025228(u16 arg0) {
    s32 found = 0;
    u8* p = item_inventory;
    s32 i = 0x96;
    ItemDef* e;

    while (!found && *p != 0xFF) {
        e = &D_803AAAA0[*p++];
        if (e->handler_index == 0xF) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game/item/item/Item_UpdateInventoryMenu.s")
#endif

s32 Item_CanUseNever(s32 arg0, ItemDef* arg1) {
    return 0;
}

s32 Item_CanUseRestore(Actor* arg0, ItemDef* arg1) {
    s32 ret = 0;
    ActorStats* temp = arg0->stats;

    if ((arg1->unk4 != 0) && (temp->max_hp != temp->hp)) {
        ret = 1;
    }
    if ((arg1->unk6 != 0) && (temp->max_mp != temp->mp)) {
        ret = 1;
    }
    return ret;
}

s32 Item_CanUseWarp(s32 arg0, ItemDef* arg1) {
    s32 ret;

    if ((map_flags & 0xA) || (map_subarea_def->flags & 4)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 Item_CanUseSpell(s32 arg0, ItemDef* arg1) {
    s32 ret = 1;

    if ((battle_flags & 0x100) && (arg1->use_flags & 8)) {
        ret = 0;
    }
    return ret;
}

// empty
void Item_UseNothing(s32 arg0, ItemDef* arg1) {
}

void Item_UseRestore(Actor* arg0, ItemDef* arg1) {
    u16 amt;
    ActorStats* st = arg0->stats;
    MagicVisualDef* fx;

    if (arg1->unk4 != 0) {
        amt = st->max_hp - st->hp;
        if (arg1->unk4 < amt) {
            amt = arg1->unk4;
        }
        st->hp += amt;
        Effect_AddFloatingNumber(arg0, 1, amt);
    }
    if (arg1->unk6 != 0) {
        amt = st->max_mp - st->mp;
        if (arg1->unk6 < amt) {
            amt = arg1->unk6;
        }
        st->mp += amt;
        Effect_AddFloatingNumber(arg0, 2, amt);
    }
    item_effect_scale.x = D_803AB36C[0].scale_x;
    item_effect_scale.y = D_803AB36C[0].scale_y;
    fx = &D_803AB358[D_803AB36C[0].visual_def_index];
    item_effect_scale.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[0].color_index, D_803AB36C[0].flags, arg0->x, arg0->y, arg0->z, 0.0f, fx, &item_effect_scale, arg0);
    Sfx_Play(0, 0xB, 0xFF);
}

void Item_UseWarp(Actor* arg0, ItemDef* arg1) {
    MagicVisualDef* fx;

    core_flags |= 0x80;
    core_transition_timer = 0x16;
    exit_destination.map = D_803AAA40[arg1->unk4].map_id;
    exit_destination.subarea = D_803AAA40[arg1->unk4].subarea;
    exit_destination.entry = -1;
    player_spawn_x = D_803AAA40[arg1->unk4].spawn_x;
    player_spawn_z = D_803AAA40[arg1->unk4].spawn_z;
    player_spawn_rot = D_803AAA40[arg1->unk4].spawn_rot;
    player_spawn_type = 0x108;
    player_state.unk6 = 0;
    fade_transition_style = 1;
    item_effect_scale.x = D_803AB36C[1].scale_x;
    item_effect_scale.y = D_803AB36C[1].scale_y;
    fx = &D_803AB358[D_803AB36C[1].visual_def_index];
    item_effect_scale.z = 1.0f;
    Magic_CreateVisualEffect(D_803AB36C[1].color_index, D_803AB36C[1].flags, arg0->x, arg0->y, arg0->z, 0.0f, fx, &item_effect_scale, arg0);
    Sfx_Play(0, 0x3B, 0xFF);
}

void Item_UseSpell(s32 arg0, ItemDef* arg1) {
    Magic_CreateCastEffect(arg0, arg1->unk4, 0, 4);
}

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
