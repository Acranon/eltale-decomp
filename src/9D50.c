#include "common.h"

/*
 * Town NPCs: spawn from the area's def list, per-frame wander/turn update, draw, collision,
 * start/end of a talk and loading the message and speaker name into the text buffers.
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
RomRange *D_8007AB70;
u16 D_8007AB74;
f32 D_8007AB78[2];
s32 D_8007AB80[2];
CollOut D_8007AB88;
s32 D_8007ABA0;
s32 D_8007ABA4;
s32 D_8007ABA8;
s32 D_8007ABAC;
NPCObj *D_8007ABB0[16];
NPC D_8007ABF0[16];
u8 D_8007B430[0x4B0];
u8 D_8007B8E0[0x20];

extern f32 D_8007AA20;
extern f32 D_8007AA28;
extern s32 D_8007C2A4;
extern Unk8007C2A8 *D_8007C2A8[];

void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
void Anim_DrawModel(s32, NPCObj *, AnimEntry *, s32);
void Anim_AdvanceFrame(s32, NPCObj *, AnimEntry *);
extern Gfx *D_8007A184;
extern Unk8007AA08 D_8007AA08;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ u8 *unkC;
} Unk80090458;

f32 func_800270D0(f32, f32);
s32 func_80024FF0(u8);
void func_80025094(u8);
u8 Boss_IsDefeated(u32);
void Npc_LoadMessage(NPC *, s32);
extern s32 D_8004DCA0;
/* Message text that Npc_StartTalk hands to the text box. */
u8 D_8004DD10[8] = {
#include "assets/D_8004DD10.inc.c"
};
u8 D_8004DD18[8] = {
#include "assets/D_8004DD18.inc.c"
};
extern s32 D_8007A174;
extern s32 D_80090454;
extern Unk80090458 D_80090458;

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
u32 func_80026E90(u32);
void func_80028120();
void Text_OpenWindow(s32);
void func_8020C0D0(void);

extern u8 D_86F6F0[];
extern u8 D_871D10[];
extern u8 D_A70350[];
extern u8 D_A77F10[];
extern u8 D_D2E2F0[];
extern u8 D_802A0000[];
extern u8 D_8020E6F0[];
extern RomRange D_80056880[];
extern u8 D_800568B8[];
extern u16 D_8007A172;
void func_800271B4(f32, f32 *);

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
extern Unk8007C284 *D_8007C284;
extern Unk8007C288 *D_8007C288;
extern s32 D_800842C0;
extern u16 D_800842E8;

void Npc_InitArea(void) {
    NPCList *list;

    D_8007ABA4 = 0;
    if (!(D_800842E8 & 1)) {
        func_80009764(D_8007C288->unk12);
        list = D_8007C284->npcs;
        if (list != NULL) {
            Npc_SpawnForArea(list->defs, list->count);
        }
        D_8007AB74 = 0;
        if (D_8007A172 == 1) {
            Npc_SetMessage(0, D_800568B8);
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

    i = D_8007ABA4;
    npc = D_8007ABF0;
    for (; i != 0; i--, npc++) {
        obj = (NPCObj *)&npc->x;
        switch (npc->state) {
            case 0:
                if (npc->def->unk4 == 2) {
                    if (--npc->timer == 0) {
                        if (D_8007AB74 < 3) {
                            npc->state = 1;
                            npc->timer = (func_80026E90(2) + 1) * npc->def->unk10->unkE;
                            Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
                            dx = npc->homeX - obj->x;
                            dz = npc->homeZ - obj->z;
                            if (sqrtf(dx * dx + dz * dz) > 50.0) {
                                obj->angle = func_800270D0(dx, dz);
                            } else {
                                obj->angle = (f32)func_80026E90(16) * 0.39269908169872414 - 1.5707963267948966;
                            }
                            D_8007AB74++;
                        } else {
                            npc->timer = (func_80026E90(2) + 1) * npc->def->unk10->unk2;
                        }
                    }
                }
                break;
            case 1:
                D_8007AB78[0] = 0.0f;
                D_8007AB78[1] = 0.4f;
                func_800271B4(obj->angle, D_8007AB78);
                Npc_Move(D_8007AB78[0], D_8007AB78[1], (Unk80009988 *)obj);
                if (--npc->timer == 0) {
                    npc->state = 0;
                    npc->timer = npc->def->unk10->unk2;
                    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                    D_8007AB74--;
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

    D_8007ABA8 = 0;
    i = D_8007ABA4;
    npc = D_8007ABF0;
    list = D_8007ABB0;
    for (; i != 0; i--, npc++) {
        dx = npc->x - D_8007AA08.x;
        obj = (NPCObj *)&npc->x;
        dz = npc->z - D_8007AA08.z;
        dist = dx * dx + dz * dz;
        if (dist < 90000.0f) {
            filter = (dist < 20000.0f) ? G_TF_BILERP : G_TF_POINT;
            gDPSetTextureFilter(D_8007A184++, filter);
            anims = (AnimEntry *)npc->def->unk10;
            Anim_DrawModel(0, obj, &anims[obj->unk52], arg0);
            Anim_AdvanceFrame(obj->unk58, obj, &anims[obj->unk52]);
            Shadow_Queue(obj->x, obj->y, obj->z, obj->rx, obj->ry, obj->rz, 5.0f);
            *list++ = obj;
            D_8007ABA8++;
        }
    }
}

void func_80009764(s32 arg0) {
    u32 start;
    u32 end;

    D_8007AB70 = &D_80056880[arg0];
    func_80028120(D_86F6F0, func_8020C0D0, D_871D10 - D_86F6F0);
    func_80028120(D_A70350, D_802A0000, D_A77F10 - D_A70350);
    start = D_8007AB70->start;
    end = D_8007AB70->end;
    func_80028120(start, D_8020E6F0, end - start);
}

void Npc_SpawnForArea(NPCDef *def, s32 n) {
    NPC *npc = D_8007ABF0;
    CollResult out;

    for (; n != 0; n--, def++) {
        if (D_800842C0 == def->area) {
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
            D_8007ABA4++;
        }
    }
}

void Npc_Move(f32 dx, f32 dz, Unk80009988 *obj) {
    Npc_PushOutOfObjects(&dx, &dz, obj);
    obj->unk18 = dx;
    obj->unk20 = dz;
    obj->x += dx;
    obj->z += dz;
    D_8007AB88.x = 4.0f;
    Coll_ResolveFloorAndWalls(obj->x, obj->y, obj->z, 0xA01, &D_8007AB88);
    obj->x = D_8007AB88.x;
    obj->y = D_8007AB88.y;
    obj->z = D_8007AB88.z;
    obj->nx = D_8007AB88.nx;
    obj->ny = D_8007AB88.ny;
    obj->nz = D_8007AB88.nz;
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
    ddx = nx - D_8007AA08.x;
    ddz = nz - D_8007AA08.z;
    r = D_8007AA08.unk40 * D_8007AA08.unk3C + radius;
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
    i = D_8007ABA8;
    if (i != 0) {
        for (list = D_8007ABB0; !hit && i != 0; i--) {
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
    i = D_8007C2A4;
    if (i != 0) {
        for (list2 = D_8007C2A8; !hit && i != 0; i--) {
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
    NPC *npc = &D_8007ABF0[idx];
    f32 angle;
    f32 dx;
    f32 dz;
    s32 msg;

    npc->state = 2;
    if (npc->def->flags & 2) {
        npc->timer = 0;
    } else {
        npc->timer = 15;
        dx = D_8007AA08.x - npc->x;
        dz = D_8007AA08.z - npc->z;
        angle = func_800270D0(dx, dz) - npc->angle;
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
            if (func_80024FF0(npc->def->u6.b.unk7) == 0) {
                found = 0;
                msg = npc->def->unk8;
            } else {
                found = 1;
                msg = npc->def->unkA;
            }
            Npc_LoadMessage(npc, msg);
            if (found == 0) {
                func_80025094(npc->def->u6.b.unk7);
                D_8007AA08.unk8 |= 0x40;
            }
            break;
        case 5:
            if (Boss_IsDefeated(npc->def->u6.unk6) == 0) {
                msg = npc->def->unk8;
            } else {
                msg = npc->def->unkA;
                if (npc->def->u6.unk6 == 7) {
                    D_8004DCA0 |= 0x8080;
                    D_8007A174 = 0x16;
                }
            }
            Npc_LoadMessage(npc, msg);
            break;
        case 6:
            Npc_LoadMessage(npc, npc->def->unk8);
            D_80090458.unk0 = 2;
            D_80090458.unk8 = D_8004DD10;
            D_80090458.unkC = D_8004DD18;
            D_80090454 = -1;
            D_8004DCA0 |= 0x10;
            break;
        default:
            Npc_LoadMessage(npc, npc->def->unk8);
            break;
    }
}

void Npc_EndTalk(s32 idx) {
    NPC *npc = &D_8007ABF0[idx];

    if (npc->def->unk4 == 2) {
        npc->state = 0;
        npc->timer = func_80026E90(30) + 30;
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

    func_80028120(arg1 + (u32)D_D2E2F0, D_8007B430, 0x4B0);
    if (npc->def->name != NULL) {
        for (i = 0; i != 0x20; i++) {
            D_8007B8E0[i] = npc->def->name[i];
        }
    } else {
        D_8007B8E0[0] = 0xFF;
    }
}

void Npc_SetMessage(s32 arg0, u8 *arg1) {
    s32 i;
    u8 *dst;
    NPC *npc;

    dst = D_8007B430;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *arg1++;
    }
    npc = &D_8007ABF0[arg0];
    if (npc->def->name != NULL) {
        for (i = 0; i != 0x20; i++) {
            D_8007B8E0[i] = npc->def->name[i];
        }
    } else {
        D_8007B8E0[0] = 0xFF;
    }
}
