#include "common.h"

/*
 * NPCs (non-encounter areas): spawn from the area's def list, per-frame wander/turn update, draw,
 * collision, start/end of a talk and loading the message and speaker name into the text buffers.
 * Folder: src/game/npc/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0xA];
    /* 0x0E */ s16 unkE;
} Unk10;

typedef struct {
    /* 0x00 */ u16 area;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 flags;
    union {
        /* 0x06 */ u16 unk6;
        struct {
            /* 0x06 */ u8 unk6_hi;
            /* 0x07 */ u8 unk7;
        } b;
    } u6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ Unk10 *unk10;
    /* 0x14 */ u8 *name;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 x;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 angle;
    /* 0x28 */ f32 unk28;
} NPCDef; /* size 0x2C */

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 timer;
    /* 0x04 */ f32 homeX;
    /* 0x08 */ f32 homeZ;
    /* 0x0C */ f32 homeAngle;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 z;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 angle;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[0xC];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 nx;
    /* 0x44 */ f32 ny;
    /* 0x48 */ f32 nz;
    /* 0x4C */ u8 pad4C[0x28];
    /* 0x74 */ s16 unk74;
    /* 0x76 */ u8 pad76[0xA];
    /* 0x80 */ NPCDef *def;
} NPC; /* size 0x84 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
} CollOut;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 nx;
    /* 0x30 */ f32 ny;
    /* 0x34 */ f32 nz;
} Unk80009988;

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ NPCDef *defs;
} NPCList;

typedef struct {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ NPCList *npcs;
} Unk8007C284;

typedef struct {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u16 unk12;
} Unk8007C288;

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
} RomRange;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ f32 angle;
    /* 0x14 */ u8 pad14[0x10];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 rx;
    /* 0x30 */ f32 ry;
    /* 0x34 */ f32 rz;
    /* 0x38 */ u8 pad38[0x1A];
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u8 pad54[4];
    /* 0x58 */ u16 unk58;
} NPCObj;

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
} AnimEntry; /* size 0xC */

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ f32 x;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[0x18];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk8007C2A8;

f32 sqrtf(f32);
/* This file's .bss, 8007AB70..8007B900, in address order. D_8007AB80,
 * D_8007ABA0 and D_8007ABAC are unreferenced gaps. D_8007AC70 (each NPC's def
 * field, 3F50) and D_8007B7E2 are aliases in undefined_syms.txt. */
RomRange *npc_area_set_rom_range;
u16 npc_walking_count;
f32 npc_walk_step[2];
s32 D_8007AB80[2];
CollOut npc_move_coll;
s32 D_8007ABA0;
s32 npc_count;
s32 npc_drawn_count;
s32 D_8007ABAC;
NPCObj *npc_drawn_list[16];
NPC npc_slots[16];
u8 text_message_buf[0x4B0];
u8 text_speaker_name[0x20];

extern f32 D_8007AA20;
extern f32 D_8007AA28;
extern s32 mapobj_billboard_count;
extern Unk8007C2A8 *mapobj_billboard_list[];

void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
void Anim_DrawModel(s32, NPCObj *, AnimEntry *, s32);
void Anim_AdvanceFrame(s32, NPCObj *, AnimEntry *);
extern Gfx *gfx_dl_head;
extern Unk8007AA08 player_state;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ u8 *unkC;
} Unk80090458;

f32 Math_Atan2(f32, f32);
s32 Item_CountInInventory(u8);
void Item_AddToInventory(u8);
u8 Boss_IsDefeated(u32);
void Npc_LoadMessage(NPC *, s32);
extern s32 core_flags;
/* Message text that Npc_StartTalk hands to the text box. */
u8 npc_rest_choice_row0[8] = {
#include "assets/npc_rest_choice_row0.inc.c"
};
u8 npc_rest_choice_row1[8] = {
#include "assets/npc_rest_choice_row1.inc.c"
};
extern s32 core_transition_timer;
extern s32 text_last_choice_index;
extern Unk80090458 text_pending_choice_rows;

void func_80009764(s32);
void Npc_SpawnForArea(NPCDef *, s32);
void Npc_PushOutOfObjects(f32 *, f32 *, Unk80009988 *);
void Npc_SetMessage(s32, u8 *);
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

void Coll_ResolveFloorAndWalls(f32, f32, f32, u16, void *);
void Anim_SetCurrentAndNext(void *, s32, s32, s32, s32, u16);
u32 Math_Rand(u32);
void Dma_ReadRom();
void Text_OpenWindow(s32);
void func_8020C0D0(void);

extern u8 D_86F6F0[];
extern u8 D_871D10[];
extern u8 D_A70350[];
extern u8 D_A77F10[];
extern u8 D_D2E2F0[];
extern u8 D_802A0000[];
extern u8 D_8020E6F0[];
extern RomRange npc_area_set_rom_ranges[];
extern u8 npc_area_entry_message[];
extern u16 D_8007A172;
void Math_RotateVec2(f32, f32 *);

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 timer;
    /* 0x04 */ f32 homeX;
    /* 0x08 */ f32 homeZ;
    /* 0x0C */ f32 homeAngle;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ NPCObj obj;
    /* 0x70 */ u8 pad70[0x10];
    /* 0x80 */ NPCDef *def;
} NPC2; /* size 0x84 */
void Npc_Move(f32, f32, Unk80009988 *);
extern Unk8007C284 *map_area_def;
extern Unk8007C288 *map_subarea_def;
extern s32 map_subarea;
extern u16 map_subarea_flags;

void Npc_InitArea(void) {
    NPCList *list;

    npc_count = 0;
    if (!(map_subarea_flags & 1)) {
        func_80009764(map_subarea_def->unk12);
        list = map_area_def->npcs;
        if (list != NULL) {
            Npc_SpawnForArea(list->defs, list->count);
        }
        npc_walking_count = 0;
        if (D_8007A172 == 1) {
            Npc_SetMessage(0, npc_area_entry_message);
            Text_OpenWindow(1);
        }
    }
}

void Npc_UpdateAll(void) {
    NPC *npc;
    s32 i;
    NPCObj *obj;
    f32 dx;
    f32 dz;

    i = npc_count;
    npc = npc_slots;
    for (; i != 0; i--, npc++) {
        obj = (NPCObj *)&npc->x;
        switch (npc->state) {
            case 0:
                if (npc->def->unk4 == 2) {
                    if (--npc->timer == 0) {
                        if (npc_walking_count < 3) {
                            npc->state = 1;
                            npc->timer = (Math_Rand(2) + 1) * npc->def->unk10->unkE;
                            Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
                            dx = npc->homeX - obj->x;
                            dz = npc->homeZ - obj->z;
                            if (sqrtf(dx * dx + dz * dz) > 50.0) {
                                obj->angle = Math_Atan2(dx, dz);
                            } else {
                                obj->angle = (f32)Math_Rand(16) * 0.39269908169872414 - 1.5707963267948966;
                            }
                            npc_walking_count++;
                        } else {
                            npc->timer = (Math_Rand(2) + 1) * npc->def->unk10->unk2;
                        }
                    }
                }
                break;
            case 1:
                npc_walk_step[0] = 0.0f;
                npc_walk_step[1] = 0.4f;
                Math_RotateVec2(obj->angle, npc_walk_step);
                Npc_Move(npc_walk_step[0], npc_walk_step[1], (Unk80009988 *)obj);
                if (--npc->timer == 0) {
                    npc->state = 0;
                    npc->timer = npc->def->unk10->unk2;
                    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                    npc_walking_count--;
                }
                break;
            case 2:
                if (npc->timer != 0) {
                    npc->timer--;
                    obj->angle += npc->unk10 / 15.0f;
                    if (npc->timer == 0) {
                        Anim_SetCurrentAndNext(obj, npc->def->unk18, 1, npc->def->unk18, 1, 1);
                    }
                }
                break;
            case 3:
                npc->timer--;
                obj->angle -= npc->unk10 / 15.0f;
                if (npc->timer == 0) {
                    npc->state = 0;
                    npc->timer = npc->def->unk10->unk2;
                    obj->angle = npc->homeAngle;
                    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                }
                break;
        }
    }
}

void Npc_DrawAll(s32 arg0) {
    NPC *npc;
    s32 i;
    NPCObj **list;
    NPCObj *obj;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 filter;
    AnimEntry *anims;

    npc_drawn_count = 0;
    i = npc_count;
    npc = npc_slots;
    list = npc_drawn_list;
    for (; i != 0; i--, npc++) {
        dx = npc->x - player_state.x;
        obj = (NPCObj *)&npc->x;
        dz = npc->z - player_state.z;
        dist = dx * dx + dz * dz;
        if (dist < 90000.0f) {
            filter = (dist < 20000.0f) ? G_TF_BILERP : G_TF_POINT;
            gDPSetTextureFilter(gfx_dl_head++, filter);
            anims = (AnimEntry *)npc->def->unk10;
            Anim_DrawModel(0, obj, &anims[obj->unk52], arg0);
            Anim_AdvanceFrame(obj->unk58, obj, &anims[obj->unk52]);
            Shadow_Queue(obj->x, obj->y, obj->z, obj->rx, obj->ry, obj->rz, 5.0f);
            *list++ = obj;
            npc_drawn_count++;
        }
    }
}

void func_80009764(s32 arg0) {
    u32 start;
    u32 end;

    npc_area_set_rom_range = &npc_area_set_rom_ranges[arg0];
    Dma_ReadRom(D_86F6F0, func_8020C0D0, D_871D10 - D_86F6F0);
    Dma_ReadRom(D_A70350, D_802A0000, D_A77F10 - D_A70350);
    start = npc_area_set_rom_range->start;
    end = npc_area_set_rom_range->end;
    Dma_ReadRom(start, D_8020E6F0, end - start);
}

void Npc_SpawnForArea(NPCDef *def, s32 n) {
    NPC *npc = npc_slots;
    CollResult out;

    for (; n != 0; n--, def++) {
        if (map_subarea == def->area) {
            npc->state = 0;
            npc->timer = 1;
            npc->def = def;
            npc->x = def->x;
            npc->z = def->z;
            npc->angle = def->angle;
            npc->unk20 = 0.0f;
            npc->unk28 = 0.0f;
            npc->unk38 = def->unk28;
            npc->unk3C = 50.0f;
            Coll_ResolveFloorAndWalls(npc->x, npc->y, npc->z, 0xA00, &out);
            npc->y = out.y;
            npc->nx = out.nx;
            npc->ny = out.ny;
            npc->nz = out.nz;
            Anim_SetCurrentAndNext(&npc->x, 0, 1, 0, 1, 1);
            npc->homeX = def->x;
            npc->homeZ = def->z;
            npc->homeAngle = def->angle;
            if (def->flags & 1) {
                npc->unk74 = 0x1000;
            } else {
                npc->unk74 = 0;
            }
            npc++;
            npc_count++;
        }
    }
}

void Npc_Move(f32 dx, f32 dz, Unk80009988 *obj) {
    Npc_PushOutOfObjects(&dx, &dz, obj);
    obj->unk18 = dx;
    obj->unk20 = dz;
    obj->x += dx;
    obj->z += dz;
    npc_move_coll.x = 4.0f;
    Coll_ResolveFloorAndWalls(obj->x, obj->y, obj->z, 0xA01, &npc_move_coll);
    obj->x = npc_move_coll.x;
    obj->y = npc_move_coll.y;
    obj->z = npc_move_coll.z;
    obj->nx = npc_move_coll.nx;
    obj->ny = npc_move_coll.ny;
    obj->nz = npc_move_coll.nz;
}

void Npc_PushOutOfObjects(f32 *dx, f32 *dz, Unk80009988 *obj) {
    f32 nx;
    f32 nz;
    f32 ddx;
    f32 ddz;
    f32 r;
    f32 d;
    s32 hit;
    f32 radius;
    s32 i;
    NPCObj **list;
    NPCObj *other;
    Unk8007C2A8 **list2;
    Unk8007C2A8 *other2;

    nx = *dx + obj->x;
    nz = *dz + obj->z;
    radius = obj->unk28 * obj->unk24;
    hit = 0;
    ddx = nx - player_state.x;
    ddz = nz - player_state.z;
    r = player_state.unk40 * player_state.unk3C + radius;
    if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
        d = sqrtf(ddx * ddx + ddz * ddz);
        if (d < r) {
            d = r / d;
            hit = 1;
            ddx *= d;
            ddz *= d;
            *dx = D_8007AA20 + ddx - obj->x;
            *dz = D_8007AA28 + ddz - obj->z;
        }
    }
    i = npc_drawn_count;
    if (i != 0) {
        for (list = npc_drawn_list; !hit && i != 0; i--) {
            other = *list++;
            if ((void *)other != (void *)obj) {
                ddx = nx - other->x;
                ddz = nz - other->z;
                r = other->unk28 * other->unk24 + radius;
                if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                    d = sqrtf(ddx * ddx + ddz * ddz);
                    if (d < r) {
                        d = r / d;
                        hit = 1;
                        ddx *= d;
                        ddz *= d;
                        *dx = other->x + ddx - obj->x;
                        *dz = other->z + ddz - obj->z;
                    }
                }
            }
        }
    }
    i = mapobj_billboard_count;
    if (i != 0) {
        for (list2 = mapobj_billboard_list; !hit && i != 0; i--) {
            other2 = *list2++;
            ddx = nx - other2->x;
            ddz = nz - other2->z;
            r = radius + other2->unk10 * 2.0;
            if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                d = sqrtf(ddx * ddx + ddz * ddz);
                if (d < r) {
                    d = r / d;
                    hit = 1;
                    ddx *= d;
                    ddz *= d;
                    *dx = other2->x + ddx - obj->x;
                    *dz = other2->z + ddz - obj->z;
                }
            }
        }
    }
}

void Npc_StartTalk(s32 idx) {
    s32 pad;
    s32 found;
    NPC *npc = &npc_slots[idx];
    f32 angle;
    f32 dx;
    f32 dz;
    s32 msg;

    npc->state = 2;
    if (npc->def->flags & 2) {
        npc->timer = 0;
    } else {
        npc->timer = 15;
        dx = player_state.x - npc->x;
        dz = player_state.z - npc->z;
        angle = Math_Atan2(dx, dz) - npc->angle;
        if (angle < -3.141592653589793) {
            angle += 6.283185307179586;
        }
        if (angle > 3.141592653589793) {
            angle -= 6.283185307179586;
        }
        npc->unk10 = angle;
        npc->timer = 15;
        Anim_SetCurrentAndNext(&npc->x, 1, 1, 1, 1, 1);
    }
    switch (npc->def->unk2) {
        case 2:
            if (Item_CountInInventory(npc->def->u6.b.unk7) == 0) {
                found = 0;
                msg = npc->def->unk8;
            } else {
                found = 1;
                msg = npc->def->unkA;
            }
            Npc_LoadMessage(npc, msg);
            if (found == 0) {
                Item_AddToInventory(npc->def->u6.b.unk7);
                player_state.unk8 |= 0x40;
            }
            break;
        case 5:
            if (Boss_IsDefeated(npc->def->u6.unk6) == 0) {
                msg = npc->def->unk8;
            } else {
                msg = npc->def->unkA;
                if (npc->def->u6.unk6 == 7) {
                    core_flags |= 0x8080;
                    core_transition_timer = 0x16;
                }
            }
            Npc_LoadMessage(npc, msg);
            break;
        case 6:
            Npc_LoadMessage(npc, npc->def->unk8);
            text_pending_choice_rows.unk0 = 2;
            text_pending_choice_rows.unk8 = npc_rest_choice_row0;
            text_pending_choice_rows.unkC = npc_rest_choice_row1;
            text_last_choice_index = -1;
            core_flags |= 0x10;
            break;
        default:
            Npc_LoadMessage(npc, npc->def->unk8);
            break;
    }
}

void Npc_EndTalk(s32 idx) {
    NPC *npc = &npc_slots[idx];

    if (npc->def->unk4 == 2) {
        npc->state = 0;
        npc->timer = Math_Rand(30) + 30;
    } else if (npc->def->flags & 2) {
        npc->state = 0;
        npc->timer = npc->def->unk10->unk2;
    } else {
        npc->state = 3;
        npc->timer = 15;
        Anim_SetCurrentAndNext(&npc->x, 1, 1, 1, 1, 1);
    }
}

void Npc_LoadMessage(NPC *npc, s32 arg1) {
    s32 i;

    Dma_ReadRom(arg1 + (u32)D_D2E2F0, text_message_buf, 0x4B0);
    if (npc->def->name != NULL) {
        for (i = 0; i != 0x20; i++) {
            text_speaker_name[i] = npc->def->name[i];
        }
    } else {
        text_speaker_name[0] = 0xFF;
    }
}

void Npc_SetMessage(s32 arg0, u8 *arg1) {
    s32 i;
    u8 *dst;
    NPC *npc;

    dst = text_message_buf;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *arg1++;
    }
    npc = &npc_slots[arg0];
    if (npc->def->name != NULL) {
        for (i = 0; i != 0x20; i++) {
            text_speaker_name[i] = npc->def->name[i];
        }
    } else {
        text_speaker_name[0] = 0xFF;
    }
}
