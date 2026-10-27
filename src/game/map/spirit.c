#include "game/map/spirit.h"
#include "game/actor/actor.h"

/*
 * Spirits: per-map placement, collected flags, the pick-up test and the sparkle particles.
 * Original file: 147A0.c (ROM 0x147A0).
 */


/* This file's .bss, 800859B0..80085AB0, in address order (first declaration fixes
 * the order). Splat's D_80085AA8 is Spirit_ClearCollectedFlags's loop end, &spirit_collected_flags[0x10]. */
s32 spirit_count;
SpiritObj spirit_objects[8];
CollResult spirit_coll;
u8 spirit_collected_flags[0x10];

extern u8 math_bit_masks[];
extern s32 map_id;
extern s32 map_subarea;

extern Gfx* gfx_dl_head;

f32 sinf(f32);

SpiritPlacement spirit_map_placements[0x2B] = {
    { 0x0, 0x0, 1, (SpiritDef*)0x80154860 },
    { 0x0, 0x1, 1, (SpiritDef*)0x80154870 },
    { 0x1, 0x0, 1, (SpiritDef*)0x80141CB0 },
    { 0x2, 0x0, 2, (SpiritDef*)0x80146140 },
    { 0x3, 0x0, 3, (SpiritDef*)0x8013E480 },
    { 0x4, 0x2, 3, (SpiritDef*)0x8014C1F0 },
    { 0x5, 0x0, 3, (SpiritDef*)0x8015AD50 },
    { 0x6, 0x0, 3, (SpiritDef*)0x801348C0 },
    { 0x7, 0x0, 4, (SpiritDef*)0x801419F0 },
    { 0x8, 0x0, 4, (SpiritDef*)0x8015DB70 },
    { 0x8, 0x1, 1, (SpiritDef*)0x8015DBA0 },
    { 0x9, 0x0, 6, (SpiritDef*)0x8015F1F0 },
    { 0xA, 0x0, 2, (SpiritDef*)0x80135DD0 },
    { 0xA, 0x1, 2, (SpiritDef*)0x80135DF0 },
    { 0xB, 0x1, 1, (SpiritDef*)0x8016DA10 },
    { 0xB, 0x2, 4, (SpiritDef*)0x8016DA20 },
    { 0xC, 0x0, 4, (SpiritDef*)0x80127990 },
    { 0x1A, 0x0, 6, (SpiritDef*)0x8016DAE0 },
    { 0x1A, 0x2, 1, (SpiritDef*)0x8016DB30 },
    { 0x1B, 0x0, 2, (SpiritDef*)0x8016EFF0 },
    { 0x1C, 0x0, 5, (SpiritDef*)0x8016A0D0 },
    { 0x1D, 0x0, 2, (SpiritDef*)0x80133AF0 },
    { 0x1E, 0x8, 1, (SpiritDef*)0x80152BD0 },
    { 0x1E, 0xF, 1, (SpiritDef*)0x80152BE0 },
    { 0x1F, 0x0, 4, (SpiritDef*)0x8014C410 },
    { 0x1F, 0x2, 1, (SpiritDef*)0x8014C440 },
    { 0x20, 0x0, 6, (SpiritDef*)0x8013D9C0 },
    { 0x21, 0x0, 3, (SpiritDef*)0x80143680 },
    { 0x21, 0x1, 1, (SpiritDef*)0x801436B0 },
    { 0xE, 0xF, 1, (SpiritDef*)0x801A3BD0 },
    { 0xE, 0xC, 1, (SpiritDef*)0x801A3BE0 },
    { 0x10, 0x15, 1, (SpiritDef*)0x80183190 },
    { 0x15, 0x0, 2, (SpiritDef*)0x801A6C80 },
    { 0x15, 0x6, 1, (SpiritDef*)0x801A6CA0 },
    { 0x16, 0x1, 1, (SpiritDef*)0x801832D0 },
    { 0x16, 0x17, 2, (SpiritDef*)0x801832E0 },
    { 0x17, 0x13, 1, (SpiritDef*)0x8018CC80 },
    { 0x17, 0x17, 1, (SpiritDef*)0x8018CC90 },
    { 0x18, 0x0, 4, (SpiritDef*)0x80166620 },
    { 0x18, 0x2, 2, (SpiritDef*)0x80166650 },
    { 0x19, 0x1, 1, (SpiritDef*)0x801717F0 },
    { 0x19, 0x4, 1, (SpiritDef*)0x80171800 },
    { 0x19, 0x9, 1, (SpiritDef*)0x80171810 },
};
Vtx spirit_sparkle_vtx[4] = {
    { 1, 1, 1, 0, 0x3C0, 0, 0, 0, 0, 0 },
    { -1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, -1, 1, 0, 0x3C0, 0x3C0, 0, 0, 0, 0 },
    { -1, -1, 1, 0, 0, 0x3C0, 0, 0, 0, 0 },
};
Gfx spirit_sparkle_dl[10] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFC629BFF, 0x1FFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0x0400103F, (u32)spirit_sparkle_vtx }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
u8 spirit_sparkle_tex[4][0x100] = {
#include "assets/spirit_sparkle_tex.inc.c"
};

void Spirit_ClearCollectedFlags(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        spirit_collected_flags[i] = 0;
    }
}

void Spirit_LoadForMap(void) {
    SpiritPlacement* entry;
    SpiritDef* def;
    SpiritObj* obj;
    u32 i;
    s32 id;

    id = map_id; entry = spirit_map_placements; for (i = 0; i < 0x2B; i++, entry++) {
        if (id == entry->mapId && map_subarea == entry->subarea) {
            break;
        }
    }
    if (i < 0x2B) {
        obj = spirit_objects;
        def = entry->defs;
        spirit_count = entry->count;
        i = spirit_count;
        while (i != 0) {
            obj->sparkleTimer = -1;
            obj->collected = Spirit_IsCollected(def->flagId);
            obj->x = def->x;
            obj->z = -def->z;
            Coll_ResolveFloorAndWalls(obj->x, 0.0f, obj->z, 0xA00, &spirit_coll);
            obj->y = spirit_coll.y;
            obj->sparkleAngle = 0.0f;
            obj->flagId = def->flagId;
            i--;
            def++;
            obj++;
        }
    } else {
        spirit_count = 0;
    }
}

SpiritObj* Spirit_FindInFront(Actor* arg0) {
    s32 n = spirit_count;
    SpiritObj* obj;
    f32 dx;
    f32 dz;
    SpiritObj* found = NULL;
    f32 dist;
    Vec2f v;

    obj = spirit_objects;
    while (n != 0) {
        if (obj->collected == 0) {
            dx = obj->x - arg0->x;
            dz = obj->z - arg0->z;
            if (dx * dx + dz * dz < 400.0f) {
                v.x = dx;
                v.y = dz;
                Math_RotateVec2(arg0->rot, &v);
                if (v.y >= 0.0f && v.x > -5.0 && v.x < 5.0) {
                    found = obj;
                    break;
                }
            }
        }
        n--;
        obj++;
    }
    return found;
}

void Spirit_SpawnSparkles(void) {
    static EffectSprite spirit_sparkle_template = {
        0x001E, 0, 0, Spirit_MoveSparkle, 2, 0x10, 0x10, 0, 0, { 0 }, (u8*)spirit_sparkle_tex, spirit_sparkle_dl,
        0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.3f, 0.0f, 0,
    };
    s32 n;
    SpiritObj* obj;
    s32 pad;
    Vec2f v;

    n = spirit_count;
    obj = spirit_objects;
    while (n != 0) {
        if (obj->collected == 0) {
            obj->sparkleTimer++;
            if (obj->sparkleTimer >= 0 && (obj->sparkleTimer & 1)) {
                v.x = 0.0f;
                v.y = 1.0f;
                Math_RotateVec2(obj->sparkleAngle, &v);
                spirit_sparkle_template.x = obj->x + v.x;
                spirit_sparkle_template.y = obj->y;
                spirit_sparkle_template.z = obj->z + v.y;
                spirit_sparkle_template.tex = spirit_sparkle_tex[obj->sparkleTimer >> 1];
                Effect_AllocateSprite(&spirit_sparkle_template);
                if (obj->sparkleTimer >= 6) {
                    obj->sparkleTimer = Math_Rand(30) - 60;
                    obj->sparkleAngle += 0.39269908169872414;
                }
            }
        }
        n--;
        obj++;
    }
}

ColorRGBA8 spirit_sparkle_colors[2] = { { 0x8C, 0x00, 0xFF, 0xDC }, { 0x8C, 0x00, 0xFF, 0x78 } };

void Spirit_MoveSparkle(EffectSprite* arg0) {
    f32 s;
    u8* c;

    s = sinf((f32)arg0->unk3C * 0.09817477042468103) * 0.1;
    arg0->unk3C += 4;
    c = (u8*)&spirit_sparkle_colors[arg0->life & 1];
    arg0->x += arg0->unk30 + s;
    arg0->y += arg0->unk34;
    arg0->z += arg0->unk38 + s;
    gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], c[3]);
}

u8 Spirit_IsCollected(u16 arg0) {
    return spirit_collected_flags[arg0 >> 3] & math_bit_masks[arg0 & 7];
}
