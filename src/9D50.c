#include "common.h"

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
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
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ f32 x;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 angle;
    /* 0x28 */ f32 unk28;
} NPCDef; /* size 0x2C */

typedef struct {
    /* 0x00 */ s16 state;
    /* 0x02 */ s16 timer;
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
    /* 0x24 */ u8 pad24[8];
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
    /* 0x0C */ u8 padC[0x20];
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
} Unk8007AA08;

void func_800131F0(f32, f32, f32, f32, f32, f32, f32);
void func_80020428(s32, NPCObj *, AnimEntry *, s32);
void func_8002099C(u16, NPCObj *, AnimEntry *);
extern Gfx *D_8007A184;
extern Unk8007AA08 D_8007AA08;
extern s32 D_8007ABA8;
extern NPCObj *D_8007ABB0[];

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ u8 *unkC;
} Unk80090458;

f32 func_800270D0(f32, f32);
s32 func_80024FF0(s32);
void func_80025094(s32);
s32 func_8000D398(s32);
void func_8000A0F8(NPC *, s32);
extern s32 D_8004DCA0;
extern u8 D_8004DD10[];
extern u8 D_8004DD18[];
extern s32 D_8007A174;
extern s32 D_80090454;
extern Unk80090458 D_80090458;

void func_80009764(s32);
void func_800097F8(NPCDef *, s32);
void func_80009A54(f32 *, f32 *, Unk80009988 *);
void func_8000A1D0(s32, u8 *);
void func_800107F0(f32, f32, f32, s32, CollOut *);
void func_800201A0(void *, s32, s32, s32, s32, s32);
u32 func_80026E90(s32);
void func_80028120(u32, void *, u32);
void func_80032D20(s32);
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
extern RomRange *D_8007AB70;
extern s16 D_8007AB74;
extern CollOut D_8007AB88;
extern s32 D_8007ABA4;
extern NPC D_8007ABF0[];
extern u8 D_8007B430[];
extern u8 D_8007B8E0[];
extern Unk8007C284 *D_8007C284;
extern Unk8007C288 *D_8007C288;
extern s32 D_800842C0;
extern u16 D_800842E8;

void func_80009150(void) {
    NPCList *list;

    D_8007ABA4 = 0;
    if (!(D_800842E8 & 1)) {
        func_80009764(D_8007C288->unk12);
        list = D_8007C284->npcs;
        if (list != NULL) {
            func_800097F8(list->defs, list->count);
        }
        D_8007AB74 = 0;
        if (D_8007A172 == 1) {
            func_8000A1D0(0, D_800568B8);
            func_80032D20(1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/9D50/func_800091E0.s")

void func_80009594(s32 arg0) {
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
            func_80020428(0, obj, &anims[obj->unk52], arg0);
            func_8002099C(obj->unk58, obj, &anims[obj->unk52]);
            func_800131F0(obj->x, obj->y, obj->z, obj->rx, obj->ry, obj->rz, 5.0f);
            *list++ = obj;
            D_8007ABA8++;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/9D50/func_80009764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/9D50/func_800097F8.s")

void func_80009988(f32 dx, f32 dz, Unk80009988 *obj) {
    func_80009A54(&dx, &dz, obj);
    obj->unk18 = dx;
    obj->unk20 = dz;
    obj->x += dx;
    obj->z += dz;
    D_8007AB88.x = 4.0f;
    func_800107F0(obj->x, obj->y, obj->z, 0xA01, &D_8007AB88);
    obj->x = D_8007AB88.x;
    obj->y = D_8007AB88.y;
    obj->z = D_8007AB88.z;
    obj->nx = D_8007AB88.nx;
    obj->ny = D_8007AB88.ny;
    obj->nz = D_8007AB88.nz;
}

#pragma GLOBAL_ASM("asm/nonmatchings/9D50/func_80009A54.s")

void func_80009DDC(s32 idx) {
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
        func_800201A0(&npc->x, 1, 1, 1, 1, 1);
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
            func_8000A0F8(npc, msg);
            if (found == 0) {
                func_80025094(npc->def->u6.b.unk7);
                D_8007AA08.unk8 |= 0x40;
            }
            break;
        case 5:
            if (func_8000D398(npc->def->u6.unk6) == 0) {
                msg = npc->def->unk8;
            } else {
                msg = npc->def->unkA;
                if (npc->def->u6.unk6 == 7) {
                    D_8004DCA0 |= 0x8080;
                    D_8007A174 = 0x16;
                }
            }
            func_8000A0F8(npc, msg);
            break;
        case 6:
            func_8000A0F8(npc, npc->def->unk8);
            D_80090458.unk0 = 2;
            D_80090458.unk8 = D_8004DD10;
            D_80090458.unkC = D_8004DD18;
            D_80090454 = -1;
            D_8004DCA0 |= 0x10;
            break;
        default:
            func_8000A0F8(npc, npc->def->unk8);
            break;
    }
}

void func_8000A040(s32 idx) {
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
        func_800201A0(&npc->x, 1, 1, 1, 1, 1);
    }
}

void func_8000A0F8(NPC *npc, s32 arg1) {
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

void func_8000A1D0(s32 arg0, u8 *arg1) {
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
