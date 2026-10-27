#include "game/map/chest.h"
#include "game/actor/actor.h"
#include "game/map/chest_flag.h"
#include "game/actor/anim.h"
#include "game/gfx/shadow.h"
#include "game/audio/sound.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/npc/npc.h"

/*
 * Chests: per-map placement, opened flags, the open interaction and animation, and the
 * item message text.
 * Original file: 140D0.c (ROM 0x140D0).
 */


/* This file's .bss, 80085290..800859B0, in address order (first declaration fixes the order). */
Actor chest_objects[16];
s32 chest_count;
Vec2f chest_local_offset;
u8 D_80085960[8]; /* unreferenced */
CollResult chest_coll;
u8 chest_opened_flags[0x20];
u8 D_800859A8[8];

extern AnimSet D_8010FDC4[]; /* overlay data (no module defines it) */
/* Message text around the name in Item_BuildMessage. */
u8 item_message_prefix[8] = {
#include "assets/item_message_prefix.inc.c"
};
u8 item_message_suffix[20] = {
#include "assets/item_message_suffix.inc.c"
};
/* Per-map placement groups (the group arrays are in the map overlays). */
ChestPlacement chest_map_placements[19] = {
    { 0x0D, (ChestGroup*) 0x80199140 },
    { 0x0E, (ChestGroup*) 0x801A3B44 },
    { 0x0F, (ChestGroup*) 0x801697A4 },
    { 0x11, (ChestGroup*) 0x8016AA24 },
    { 0x13, (ChestGroup*) 0x8015EB40 },
    { 0x15, (ChestGroup*) 0x801A6C18 },
    { 0x16, (ChestGroup*) 0x80183200 },
    { 0x17, (ChestGroup*) 0x8018CBAC },
    { 0x18, (ChestGroup*) 0x80166608 },
    { 0x19, (ChestGroup*) 0x80171794 },
    { 0x1A, (ChestGroup*) 0x8016D584 },
    { 0x1B, (ChestGroup*) 0x8016E9E4 },
    { 0x1C, (ChestGroup*) 0x80169D7C },
    { 0x1D, (ChestGroup*) 0x80133504 },
    { 0x1E, (ChestGroup*) 0x801527CC },
    { 0x1F, (ChestGroup*) 0x8014C030 },
    { 0x20, (ChestGroup*) 0x8013D5D4 },
    { 0x21, (ChestGroup*) 0x80143378 },
    { 0x09, (ChestGroup*) 0x8015F1E4 },
};
extern u8* D_803AB288[]; /* overlay data: the item names (no module defines it) */

void Chest_ClearOpenedFlags(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        chest_opened_flags[i] = 0;
    }
}

void Chest_LoadForMap(void) {
    ChestPlacement* entry;
    ChestGroup* group;
    ChestDef* def;
    Actor* p;
    u32 i;
    s32 id;
    s32 mode;

    for (id = map_id, entry = chest_map_placements, i = 0; i < 19; i++, entry++) {
        if (id == entry->mapId) {
            break;
        }
    }
    if (i != 19) {
        group = &entry->groups[map_subarea];
        chest_count = group->count;
        i = chest_count;
        def = group->defs;
        p = chest_objects;
        while (i != 0) {
            p->x = def->x;
            p->z = def->z;
            p->rotX = 0.0f;
            p->rotZ = 0.0f;
            p->rot = def->ry;
            Coll_ResolveFloorAndWalls(p->x, 0.0f, p->z, 0xA00, &chest_coll);
            p->y = chest_coll.y;
            p->nx = chest_coll.nx;
            p->ny = chest_coll.ny;
            p->nz = chest_coll.nz;
            p->unk1C = def->boxAngle;
            p->vx = def->boxHalfW;
            p->vz = def->boxHalfD;
            p->unk44 = def->boxX;
            p->unk4C = def->boxZ;
            p->scale = 0.07f;
            p->floorFlags = def->flagId;
            p->animSetIndex = def->animSetIndex;
            p->animFlags = 0;
            if (Chest_IsOpened(p->floorFlags)) {
                mode = 3;
            } else {
                mode = 0;
            }
            Anim_SetCurrentAndNext(p, mode, 1, mode, 1, 1);
            i--;
            p++;
            def++;
        }
    } else {
        chest_count = 0;
    }
}

void Chest_UpdateAll(struct GfxFrameData *arg0) {
    s32 n;
    Actor* p;
    u16 t;

    n = chest_count;
    p = chest_objects;
    while (n != 0) {
        if (p->animFlags & 0x8000) {
            t = p->animFlags & ~0x8000;
            t--;
            if (!t) {
                p->animFlags = 0;
                Anim_SetCurrentAndNext(p, 3, 1, 3, 1, 1);
            } else {
                p->animFlags = t | 0x8000;
            }
        }
        Anim_DrawModel(0, p, &D_8010FDC4[p->animIndex], arg0);
        Anim_AdvanceFrame(p->animStep, p, &D_8010FDC4[p->animIndex]);
        Shadow_Queue(p->x, p->y, p->z, p->nx, p->ny, p->nz, 6.0f);
        n--;
        p++;
    }
}

Actor* Chest_FindInFront(Actor* arg0) {
    s32 n = chest_count;
    Actor* obj = chest_objects;
    f32 d;
    f32 dx;
    f32 dz;

    while (n != 0) {
        if (Chest_IsOpened(obj->floorFlags) == 0) {
            d = arg0->rot - obj->unk1C;
            if (d > 3.141592653589793) {
                d = d - 3.141592653589793;
            } else if (d < -3.141592653589793) {
                d = d + 3.141592653589793;
            }
            if (d < 0.7853981633974483 && d > -0.7853981633974483) {
                dx = arg0->x - obj->unk44;
                dz = arg0->z - obj->unk4C;
                if (dx * dx + dz * dz < 300.0f) {
                    chest_local_offset.x = dx;
                    chest_local_offset.y = dz;
                    Math_RotateVec2(obj->unk1C, &chest_local_offset);
                    dx = chest_local_offset.x;
                    dz = chest_local_offset.y;
                    if (dx < 0.0f) {
                        dx = -dx;
                    }
                    if (dz < 0.0f) {
                        dz = -dz;
                    }
                    if (dx < obj->vx && dz < obj->vz) {
                        break;
                    }
                }
            }
        }
        n--;
        obj++;
    }
    if (n == 0) {
        obj = NULL;
    }
    return obj;
}

void Chest_Open(Actor* arg0) {
    Chest_SetOpened(arg0->floorFlags);
    arg0->animFlags = 0x805B;
    Anim_SetCurrentAndNext(arg0, 1, 1, 2, 1, 1);
    Sfx_Play(0x1A, 8, 0xFF);
}

void Item_BuildMessage(s32 arg0) {
    u8* src;
    u8* dst;

    src = item_message_prefix;
    dst = text_message_buf;
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    src = D_803AB288[arg0];
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    src = item_message_suffix;
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    *dst = *src;
    text_speaker_name[0] = 0xFF;
}

u8 Chest_IsOpened(u16 arg0) {
    return chest_opened_flags[arg0 >> 3] & math_bit_masks[arg0 & 7];
}
