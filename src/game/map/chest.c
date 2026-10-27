#include "common.h"

/*
 * Chests: per-map placement, opened flags, the open interaction and animation, and the
 * item message text.
 * Original file: 140D0.c (ROM 0x140D0).
 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 scale;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ u8 unk64[0x8];
} Unk80085290; // size = 0x6C

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 ry;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
} Unk140D0Def; // size = 0x24

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x04 */ Unk140D0Def* defs;
} Unk140D0Group; // size = 0x8

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ Unk140D0Group* groups;
} Unk8004DF1C; // size = 0x8

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u16 unk18;
} Unk80085968; // size = 0x1C (Coll_ResolveFloorAndWalls's result)

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk80085958;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk80013808Arg;

typedef struct {
    u8 unk0[0xC];
} Unk8010FDC4;

/* This file's .bss, 80085290..800859B0, in address order (first declaration fixes the order). */
Unk80085290 chest_objects[16];
s32 chest_count;
Unk80085958 chest_local_offset;
u8 D_80085960[8]; /* unreferenced */
Unk80085968 chest_coll;
u8 chest_opened_flags[0x20];
u8 D_800859A8[8];

extern u8 math_bit_masks[];
extern s32 map_id;
extern s32 map_subarea;
extern Unk8010FDC4 D_8010FDC4[];
/* Message text around the name in Item_BuildMessage. */
u8 item_message_prefix[8] = {
#include "assets/item_message_prefix.inc.c"
};
u8 item_message_suffix[20] = {
#include "assets/item_message_suffix.inc.c"
};
/* Per-map placement groups (the group arrays are in the map overlays). */
Unk8004DF1C chest_map_placements[19] = {
    { 0x0D, (Unk140D0Group*) 0x80199140 },
    { 0x0E, (Unk140D0Group*) 0x801A3B44 },
    { 0x0F, (Unk140D0Group*) 0x801697A4 },
    { 0x11, (Unk140D0Group*) 0x8016AA24 },
    { 0x13, (Unk140D0Group*) 0x8015EB40 },
    { 0x15, (Unk140D0Group*) 0x801A6C18 },
    { 0x16, (Unk140D0Group*) 0x80183200 },
    { 0x17, (Unk140D0Group*) 0x8018CBAC },
    { 0x18, (Unk140D0Group*) 0x80166608 },
    { 0x19, (Unk140D0Group*) 0x80171794 },
    { 0x1A, (Unk140D0Group*) 0x8016D584 },
    { 0x1B, (Unk140D0Group*) 0x8016E9E4 },
    { 0x1C, (Unk140D0Group*) 0x80169D7C },
    { 0x1D, (Unk140D0Group*) 0x80133504 },
    { 0x1E, (Unk140D0Group*) 0x801527CC },
    { 0x1F, (Unk140D0Group*) 0x8014C030 },
    { 0x20, (Unk140D0Group*) 0x8013D5D4 },
    { 0x21, (Unk140D0Group*) 0x80143378 },
    { 0x09, (Unk140D0Group*) 0x8015F1E4 },
};
extern u8 text_message_buf[];
extern u8 text_speaker_name;
extern u8* D_803AB288[];

void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, Unk80085968*);
u8 Chest_IsOpened(u16);
void Chest_SetOpened(u16);
void Shadow_Queue(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale);
void Anim_SetCurrentAndNext(Unk80085290*, s32, s32, s32, s32, u16);
void Anim_DrawModel(s32, Unk80085290*, Unk8010FDC4*, s32);
void Anim_AdvanceFrame(u16, Unk80085290*, Unk8010FDC4*);
void Math_RotateVec2(f32, Unk80085958*);
void Sfx_Play(u8, s8, u8);

void Chest_ClearOpenedFlags(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        chest_opened_flags[i] = 0;
    }
}

void Chest_LoadForMap(void) {
    Unk8004DF1C* entry;
    Unk140D0Group* group;
    Unk140D0Def* def;
    Unk80085290* p;
    u32 i;
    s32 id;
    s32 mode;

    for (id = map_id, entry = chest_map_placements, i = 0; i < 19; i++, entry++) {
        if (id == entry->id) {
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
            p->rx = 0.0f;
            p->rz = 0.0f;
            p->ry = def->ry;
            Coll_ResolveFloorAndWalls(p->x, 0.0f, p->z, 0xA00, &chest_coll);
            p->y = chest_coll.unk4;
            p->unk2C = chest_coll.unkC;
            p->unk30 = chest_coll.unk10;
            p->unk34 = chest_coll.unk14;
            p->unk1C = def->unk14;
            p->unk18 = def->unk18;
            p->unk20 = def->unk1C;
            p->unk44 = def->unkC;
            p->unk4C = def->unk10;
            p->scale = 0.07f;
            p->unk62 = def->unk20;
            p->unk50 = def->unk21;
            p->unk60 = 0;
            if (Chest_IsOpened(p->unk62)) {
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

void Chest_UpdateAll(s32 arg0) {
    s32 n;
    Unk80085290* p;
    u16 t;

    n = chest_count;
    p = chest_objects;
    while (n != 0) {
        if (p->unk60 & 0x8000) {
            t = p->unk60 & ~0x8000;
            t--;
            if (!t) {
                p->unk60 = 0;
                Anim_SetCurrentAndNext(p, 3, 1, 3, 1, 1);
            } else {
                p->unk60 = t | 0x8000;
            }
        }
        Anim_DrawModel(0, p, &D_8010FDC4[p->unk52], arg0);
        Anim_AdvanceFrame(p->unk58, p, &D_8010FDC4[p->unk52]);
        Shadow_Queue(p->x, p->y, p->z, p->unk2C, p->unk30, p->unk34, 6.0f);
        n--;
        p++;
    }
}

Unk80085290* Chest_FindInFront(Unk80013808Arg* arg0) {
    s32 n = chest_count;
    Unk80085290* obj = chest_objects;
    f32 d;
    f32 dx;
    f32 dz;

    while (n != 0) {
        if (Chest_IsOpened(obj->unk62) == 0) {
            d = arg0->unk10 - obj->unk1C;
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
                    if (dx < obj->unk18 && dz < obj->unk20) {
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

void Chest_Open(Unk80085290* arg0) {
    Chest_SetOpened(arg0->unk62);
    arg0->unk60 = 0x805B;
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
    text_speaker_name = 0xFF;
}

u8 Chest_IsOpened(u16 arg0) {
    return chest_opened_flags[arg0 >> 3] & math_bit_masks[arg0 & 7];
}
