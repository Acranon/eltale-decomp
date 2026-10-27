#ifndef GAME_ITEM_ITEM_H
#define GAME_ITEM_ITEM_H

#include "common.h"
#include "game/actor/actor.h"
#include "game/math/math.h"

typedef struct ItemDef {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ char unk8[4];
} ItemDef; /* 0xC bytes */

typedef s32 (*ItemHandler)(void *, ItemDef *, u8);

extern Vec3f item_effect_scale;
extern s32 item_menu_scroll;
extern s32 item_menu_cursor;
extern s32 item_menu_stick_accum;
extern s32 D_8008C1A8;
extern s32 D_8008C1AC;
extern u8 item_icon_cache_ids[8];
extern u8 item_icon_cache_tex[0x800];
extern u8 item_inventory[0x97];
extern ItemHandler item_can_use_handlers[];
extern ItemHandler item_use_handlers[];
extern u16 item_menu_bob_phase;

void Item_InitInventory(void);
s32 Item_HasInventoryRoom(void);
s32 Item_CountInInventory(u8 arg0);
s32 Item_GetInventoryCount(void);
void Item_AddToInventory(u8 arg0);
s32 Item_TryUse(u8 arg0);
void Item_ApplyEffect(u8 arg0, void* arg1);
s32 func_80025228(u16 arg0);
void Item_UpdateInventoryMenu(void);
s32 Item_CanUseNever(s32 arg0, ItemDef* arg1);
s32 Item_CanUseRestore(Actor* arg0, ItemDef* arg1);
s32 Item_CanUseWarp(s32 arg0, ItemDef* arg1);
s32 Item_CanUseSpell(s32 arg0, ItemDef* arg1);
void Item_UseNothing(s32 arg0, ItemDef* arg1);
void Item_UseRestore(Actor* arg0, ItemDef* arg1);
void Item_UseWarp(Actor* arg0, ItemDef* arg1);
void Item_UseSpell(s32 arg0, ItemDef* arg1);
void Item_DrawMenuFrame(s32 x, s32 y, s32 w, s32 h);

#endif
