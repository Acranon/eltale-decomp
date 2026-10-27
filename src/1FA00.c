#include "common.h"

/*
 * Battle setup, encounter placement, turn order, camera transition, and completion.
 * Folder: src/game/battle/
 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ char unk8[0x18 - 0x8];
} Struct_8001FD44;

typedef struct {
    /* 0x00 */ Struct_8001FD44* unk0;
    /* 0x04 */ s32 unk4;
} Struct_8007C284_30;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} Struct_8001FE08;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Struct_8001FF10_C;

typedef struct {
    /* 0x00 */ Struct_8001FF10_C* unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
} Struct_8001FF10_8;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} Struct_8001FF10_Pos;

typedef struct {
    /* 0x00 */ Struct_8001FF10_Pos** unk0;
    /* 0x04 */ Struct_8001FF10_8* unk4;
    /* 0x08 */ Struct_8001FE08* unk8;
    /* 0x0C */ s32 unkC;
} Struct_8007C284_34;

typedef struct {
    char unk0[0x30];
    Struct_8007C284_30* unk30;
    Struct_8007C284_34* unk34;
} Struct_8007C284;

extern Struct_8007C284* D_8007C284;

/* This file's .bss, 8008BE40..8008BFC0, in address order (first declaration fixes the order). */
Struct_8001FF10_Pos D_8008BE40;
u16 D_8008BE4C;
u16 D_8008BE4E;
u16 D_8008BE50;
u16 D_8008BE52;
u16 D_8008BE54;
s16 D_8008BE56;
u16 D_8008BE58;
u16 D_8008BE5A;
f32 D_8008BE5C;
f32 D_8008BE60;
f32 D_8008BE64;
f32 D_8008BE68;
f32 D_8008BE6C;
u8 D_8008BE70[0x100]; /* unreferenced */
void* D_8008BF70[8];
u32 D_8008BF90;
s16 D_8008BF94;
u16 D_8008BF96;
Struct_8007C284_30* D_8008BF98;
Struct_8007C284_34* D_8008BF9C;
void* D_8008BFA0;
void* D_8008BFA4;
s32 D_8008BFA8;
f32 D_8008BFAC;
u16 D_8008BFB0;
extern s32 D_800842C0;
extern u16 D_800842E8;

u32 Math_Rand(u32);

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x000 */ char unk0[0xA];
    /* 0x00A */ u16 unkA;
    /* 0x00C */ char unkC[0x10 - 0xC];
    /* 0x010 */ f32 unk10;
    /* 0x014 */ char unk14[0x28 - 0x14];
    /* 0x028 */ struct Struct_Stats* unk28;
    /* 0x02C */ char unk2C[0x7C - 0x2C];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ char unk7E[0x130 - 0x7E];
} Struct_8007B908;

extern Struct_8007B908 D_8007B908[];
extern u16 D_8007C050[];

void Magic_TickActorStatuses(Vec3f*);
void Effect_FadeRing(u16, f32, f32, f32);


extern f32 D_8004F2A0[];
extern s32 D_8007B900;
extern Struct_8007B908 D_8007B908[];
extern void* D_8007C048;
extern void* D_8007C04C;
extern s32 D_8007C140;
extern f32 D_8007C174;
extern f32 D_8007C178;
extern f32 D_8007C17C;
extern f32 D_8007C184;
extern u8 D_803ABA58[];
extern u8 D_803AC3F8[];

void Player_InitBattle(void);
void Enemy_SortTurnOrder(void);
void Enemy_ClearAttackScript(void);
void Boss_Spawn(s32, f32, f32, f32, Struct_8007B908*);
s16 Effect_CreateTerrainRing(u16, f32, f32, f32, f32);
void Hud_ResetPopups(void);
void Bgm_Play(s8);

void Battle_ResetState(void) {
    D_8008BE52 &= 0x8000;
    D_8008BFAC = 0.0f;
    D_8008BFB0 = 0;
    if (D_800842E8 & 1) {
        if (D_8007C284->unk30 != NULL) {
            D_8008BF98 = &D_8007C284->unk30[D_800842C0];
            D_8008BF9C = &D_8007C284->unk34[D_800842C0];
            return;
        }
        D_8008BF98 = NULL;
        D_8008BF9C = NULL;
    }
}

typedef struct Struct_Stats {
    /* 0x00 */ char unk0[0xC];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ char unkE[0x34 - 0xE];
    /* 0x34 */ u8 unk34;
} Struct_Stats;

typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ char unk10[0x14 - 0x10];
    /* 0x14 */ Struct_Stats* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Struct_8007AA08;

extern Struct_8007AA08 D_8007AA08;
extern f32 D_8007A9A8;
extern u16 D_8007AA80;
Struct_8001FD44* Battle_FindEncounterRegion(f32 x, f32 y, Struct_8007C284_30* list);
Struct_8001FE08* Battle_ChooseNearbyEncounterPoint(f32 x, f32 y);
void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16* list);
f32 Math_Atan2(f32, f32);

void Battle_TryStartRandomEncounter(void) {
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 ang;
    Struct_8001FD44* area;
    Struct_8001FE08* pt;

    if (!(D_8008BE52 & 1) && !(D_8008BE52 & 0x8000) && !(D_8007AA80 & 1) && (D_8007A9A8 != 0.0f)) {
        D_8008BFAC += D_8007A9A8;
        if (D_8008BFAC >= 50.0) {
            D_8008BFB0 += 50;
            if (Math_Rand(2000) < D_8008BFB0) {
                x = D_8007AA08.unk18;
                y = D_8007AA08.unk20;
                pt = Battle_ChooseNearbyEncounterPoint(x, y);
                if (pt != NULL) {
                    area = Battle_FindEncounterRegion(x, y, D_8008BF98);
                    if (area != NULL) {
                        D_8008BFB0 = 0;
                        dx = x - pt->unk0;
                        dy = y - pt->unk2;
                        ang = Math_Atan2(dx, dy);
                        Battle_SpawnEncounterGroup(pt->unk0, pt->unk2, ang, (u16*)area->unk8);
                        D_8008BE5C = pt->unk0;
                        D_8008BE60 = pt->unk2;
                        D_8008BE52 = 0x205;
                        D_8008BE56 = 0;
                        D_8008BE54 = 20;
                        if (D_8007AA08.unk14->unkC < D_8007B908[D_8007C050[0]].unk28->unkC) {
                            D_8008BE58 = 0;
                            D_8008BE52 |= 2;
                        } else {
                            D_8008BE58 = D_8008BE5A - 1;
                        }
                        Player_InitBattle();
                        Hud_ResetPopups();
                        D_8008BE6C = 100.0f;
                        D_8008BF94 = Effect_CreateTerrainRing(0, D_8008BE5C, D_8007AA08.unk1C, D_8008BE60, D_8008BE6C * 1.04);
                        D_8008BE4C = 0;
                        D_8008BE4E = 1;
                        D_8008BE50 = Math_Rand(D_8007B900);
                        Bgm_Play(13);
                    }
                }
            }
            D_8008BFAC = 0.0f;
        }
    }
}

void Battle_StartBossEncounter(void) {
    s32 v;

    if (D_8007C140 == 7) {
        D_8008BE5C = 0.0f;
        D_8008BE60 = 0.0f;
    } else {
        D_8008BE5C = D_8007C174;
        D_8008BE60 = D_8007C17C;
    }
    D_8008BE52 = 0x305;
    D_8008BE56 = 0;
    D_8008BE54 = 0;
    D_8008BFA0 = D_8007C048;
    D_8008BFA4 = D_8007C04C;
    D_8008BFA8 = D_8007C140;
    D_8007C048 = D_803ABA58;
    D_8007C04C = D_803AC3F8;
    Boss_Spawn(D_8007C140 - 1, D_8008BE5C, D_8008BE60, D_8007C184, D_8007B908);
    Enemy_ClearAttackScript();
    D_8007C140 = 0;
    D_8008BE5A = D_8007B900 = 1;
    Enemy_SortTurnOrder();
    D_8008BF90 = 1;
    D_8008BF70[0] = D_8007B908[0].unk2C;
    D_8008BE4C = 1;
    D_8008BE4E = 1;
    D_8008BE50 = 0;
    D_8008BE58 = D_8008BE5A - 1;
    if (D_8008BFA8 != 8) {
        v = 0;
    } else {
        v = 0x29;
    }
    Bgm_Play(v);
    Player_InitBattle();
    Hud_ResetPopups();
    D_8008BE6C = D_8004F2A0[D_8008BFA8 - 1];
    D_8008BF94 = Effect_CreateTerrainRing(0, D_8008BE5C, D_8007C178, D_8008BE60, D_8008BE6C * 1.04);
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x2C - 0x18];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ char unk30[0x3C - 0x30];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ char unk50[0x58 - 0x50];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ char unk60[0x70 - 0x60];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ char unk74[0x80 - 0x74];
    /* 0x80 */ void* unk80;
} Struct_80085E48;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Struct_8004F0B0;

extern Struct_80085E48 D_80085E48;
extern Struct_8004F0B0 D_8004F0B0[];
extern f32 D_80085F78;
extern f32 D_80085F84;
extern s32 D_80085F60;
extern s32 D_800842BC;
void Math_RotateVec2(f32, Struct_8001FF10_Pos*);
void Camera_SetPreset(s32);

typedef struct Actor {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x24 - 0xC];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x60 - 0x28];
    /* 0x60 */ u16 unk60;
    /* 0x64 */ struct { char unk0[0x18]; f32 unk18; f32 unk1C; }* unk64;
    /* 0x68 */ struct { char unk0[0x90]; f32 unk90; }* unk68;
} Actor;

extern Actor D_8007AA20;

void Battle_UpdateTurnCamera(void) {
    f32 dx;
    f32 dz;
    f32 ang;
    Actor* a;

    switch (D_8008BE4C) {
        case 0:
            a = (Actor*)D_8007B908[D_8008BE50].unk2C;
            dx = a->unk0 - D_8007AA08.unk18;
            dz = a->unk8 - D_8007AA08.unk20;
            ang = Math_Atan2(dx, dz);
            if (Math_Rand(100) > 50) {
                ang += 3.141592653589793;
                if (ang < -3.141592653589793) {
                    ang += 6.283185307179586;
                } else if (ang > 3.141592653589793) {
                    ang -= 6.283185307179586;
                }
            }
            ang += 0.39269908169872414;
            if (ang < -3.141592653589793) {
                ang += 6.283185307179586;
            } else if (ang > 3.141592653589793) {
                ang -= 6.283185307179586;
            }
            D_8008BE40.unk0 = 0.0f;
            if (a->unk64->unk1C < a->unk64->unk18) {
                D_8008BE40.unk4 = a->unk64->unk18 * a->unk24 * 2.0 + 15.0;
            } else {
                D_8008BE40.unk4 = a->unk64->unk1C * a->unk24 * 2.0 + 15.0;
            }
            D_80085E48.unk4C = D_8008BE40.unk4 * 1.5;
            Math_RotateVec2(ang, &D_8008BE40);
            D_80085E48.unkC = a->unk0 + D_8008BE40.unk0;
            D_80085E48.unk14 = a->unk8 + D_8008BE40.unk4;
            D_80085E48.unk10 = a->unk4 + 15.0;
            if (D_80085E48.unk10 < D_8007AA08.unk1C) {
                D_80085E48.unk10 = D_8007AA08.unk1C;
            }
            D_80085E48.unk48 = 0.0f;
            D_80085E48.unk0 = 0;
            D_80085E48.unk3C = 0.0f;
            D_80085E48.unk44 = D_80085E48.unk48;
            D_80085E48.unk40 = D_80085E48.unk44;
            D_80085E48.unk58 = 15.0f;
            D_80085E48.unk80 = a;
            D_80085E48.unk70 = 0.01f;
            D_80085F78 = D_80085E48.unk2C;
            D_8008BE4C++;
            D_8008BE4E = 60;
            break;
        case 1:
            if (--D_8008BE4E == 0) {
                D_8008BE52 &= ~0x200;
                Camera_SetPreset(D_80085F60);
                dx = D_8008BE5C - D_8007AA08.unk18;
                dz = D_8008BE60 - D_8007AA08.unk20;
                ang = Math_Atan2(dx, dz) + 3.141592653589793;
                if (ang > 3.141592653589793) {
                    ang -= 6.283185307179586;
                } else if (ang < -3.141592653589793) {
                    ang += 6.283185307179586;
                }
                D_8008BE40.unk0 = 0.0f;
                D_8008BE40.unk4 = 50.0f;
                Math_RotateVec2(ang, &D_8008BE40);
                D_80085E48.unk0 = 4;
                D_80085E48.unk8 |= 0x10;
                D_80085E48.unkC = D_8007AA08.unk18 + D_8008BE40.unk0;
                D_80085E48.unk48 = 0.0f;
                D_80085E48.unk10 = D_8007AA08.unk1C + 30.0;
                D_80085E48.unk14 = D_8007AA08.unk20 + D_8008BE40.unk4;
                D_80085E48.unk44 = D_80085E48.unk48;
                D_80085E48.unk3C = 0.0f;
                D_80085E48.unk40 = D_80085E48.unk44;
                if ((D_8008BE52 & 0x100) && D_8008BFA8 == 8) {
                    D_80085E48.unk58 = 50.0f;
                    D_80085E48.unk5C = 28.0f;
                    D_80085E48.unk4C = 180.0f;
                } else {
                    D_80085E48.unk58 += D_8004F0B0[D_800842BC].unk0;
                    D_80085E48.unk4C += D_8004F0B0[D_800842BC].unk4;
                }
                D_80085E48.unk80 = &D_8007AA20;
                D_80085E48.unk70 = 0.02f;
                D_80085F84 = 0.0f;
            }
            break;
    }
}


extern Actor D_8007AA20;
extern s32 D_8007A9BC;
extern s32 D_80085F60;
extern s32 D_800842BC;
extern s16 D_8008C162;

void Boss_SetDefeated(u16);
void Boss_GiveDefeatReward(s32);
void Enemy_RemoveAll(void);
void Camera_SetPresetDelayedTurn(s32);
void Enemy_StartTurn(void);
s32 func_800200F8(void);
void Bgm_PlayDelayed(s32, s32);
void Bgm_PlayForMap(s32, s32, s32);

void Battle_UpdateTurnTransition(void) {
    s32 done;
    f32 f;
    Actor* a;

    if (D_8008BE52 & 4) {
        if (D_8008BE54 != 0) {
            D_8008BE54--;
            return;
        }
        if (D_8008BE52 & 2) {
            a = (Actor*)D_8007B908[D_8007C050[D_8008BE58]].unk2C;
        } else {
            a = &D_8007AA20;
        }
        if (!(a->unk60 & 1)) {
            done = 0;
            if (D_8007B900 == 0 || (D_8008BE52 & 0x400)) {
                D_8008BE52 |= 8;
                done = 1;
                if (D_8008BE52 & 0x100) {
                    Boss_SetDefeated(D_8008BFA8 - 1);
                    Boss_GiveDefeatReward(D_8008BFA8 - 1);
                    D_8007C048 = D_8008BFA0;
                    D_8007C04C = D_8008BFA4;
                }
                D_8007A9BC = func_800200F8();
            } else if (D_8008BE52 & 0x10) {
                done = 1;
            } else if (!(D_8008BE52 & 0x100) && (D_8007AA08.unk8 & 0x20)) {
                D_8008BE52 |= 0x10;
                done = 1;
            }
            if (done) {
                D_8008BE52 &= ~1;
                D_8008C162 = 0;
                Effect_FadeRing(D_8008BF94, D_8007AA08.unk18, D_8007AA08.unk1C, D_8007AA08.unk20);
                Enemy_RemoveAll();
                Camera_SetPresetDelayedTurn(D_80085F60);
                if (D_8008BE52 & 0x100) {
                    D_8008BE52 &= ~0x100;
                }
                if (D_8008BE52 & 0x10) {
                    Bgm_PlayForMap(D_800842BC, D_800842C0, 0);
                } else {
                    Bgm_PlayDelayed(0x2B, 8);
                }
                return;
            }
            D_8008BE52 &= ~4;
            if (D_8008BE52 & 2) {
                Enemy_StartTurn();
            }
            D_8008BE64 = a->unk0;
            D_8008BE68 = a->unk8;
            if (D_8008BE52 & 2) {
                f = D_8007B908[D_8007C050[D_8008BE58]].unk10;
            } else {
                f = D_8007AA08.unkC;
            }
            if (D_8008BE52 & 2) {
                a = (Actor*)D_8007B908[D_8007C050[D_8008BE58]].unk2C;
            } else {
                a = &D_8007AA20;
            }
            f *= a->unk68->unk90;
            f += a->unk64->unk18 * a->unk24;
            D_8008BF96 = Effect_CreateTerrainRing((D_8008BE52 & 2) ? 1 : 2, D_8008BE64, a->unk4, D_8008BE68, f * 1.04);
        }
    }
}

void Battle_EndTurn(Vec3f* arg0) {
    s32 n;
    s32 max; s32 id;
    Struct_8007B908* e;

    Magic_TickActorStatuses(arg0);
    if (D_8008BE52 & 1) {
        if (!(D_8008BE52 & 2)) {
            n = D_8008BE5A;
            while (n != 0) {
                D_8008BE58++;
                max = D_8008BE5A;
                if (D_8008BE58 >= max) {
                    D_8008BE58 = 0;
                }
                e = &D_8007B908[id = D_8007C050[D_8008BE58]];
                if (e->unkA != 0 && e->unk7C != -1) {
                    break;
                }
                n--;
            }
            if (n == 0) {
                D_8008BE52 |= 0x400;
            }
            D_8008BE54 = 0x14;
        } else {
            D_8008BE54 = 0;
        }
        Effect_FadeRing(D_8008BF96, arg0->x, arg0->y, arg0->z);
        D_8008BE52 ^= 2;
        D_8008BE52 |= 4;
    }
}

Struct_8001FD44* Battle_FindEncounterRegion(f32 x, f32 y, Struct_8007C284_30* list) {
    Struct_8001FD44* r = NULL;
    s32 n;

    if (list != NULL) {
        n = list->unk4;
        r = list->unk0;
        while (n != 0) {
            if (r->unk0 <= x && r->unk2 <= y && x - r->unk0 <= r->unk4 && y - r->unk2 <= r->unk6) {
                break;
            }
            n--;
            r++;
        }
        if (n == 0) {
            r = NULL;
        }
    }
    return r;
}

Struct_8001FE08* Battle_ChooseNearbyEncounterPoint(f32 x, f32 y) {
    s32 n;
    Struct_8001FE08* p;
    s32 cnt;
    f32 dx;
    f32 dy;
    f32 d;
    Struct_8001FE08* cands[6];

    n = 0;

    if (D_8008BF9C != NULL) {
        cnt = D_8008BF9C->unkC;
        p = D_8008BF9C->unk8;
        while (n < 6 && cnt != 0) {
            cnt--;
            dx = p->unk0 - x;
            dy = p->unk2 - y;
            d = dx * dx + dy * dy;
            if (d >= 2500.0f && d <= 8100.0f) {
                cands[n++] = p;
            }
            p++;
        }
        if (n == 0) {
            p = NULL;
        } else {
            p = cands[Math_Rand(n)];
        }
    } else {
        p = NULL;
    }
    return p;
}

void Math_RotateVec2(f32, Struct_8001FF10_Pos*);
void Enemy_Spawn(s32, f32, f32, f32, void*, Struct_8007B908*);

void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16* list) {
    Struct_8001FF10_8* e;
    s32 n;
    Struct_8001FF10_C* p;
    Struct_8001FF10_Pos* pos;
    Struct_8007B908* actor;
    s32 (*o)[2];
    s32 cnt;
    s32 out[8][2];

    cnt = Math_Rand(*list++);
    e = &D_8008BF9C->unk4[list[cnt]];
    pos = &(*D_8008BF9C->unk0)[e->unk6];
    n = e->unk4;
    p = e->unk0;
    actor = D_8007B908;
    o = out;
    D_8008BF90 = 0;
    while (n != 0) {
        cnt = p->unk4;
        if (p->unk8 != 0) {
            cnt += Math_Rand(p->unk8 + 1);
        }
        (*o)[0] = p->unk0;
        (*o)[1] = cnt;
        o++;
        D_8007B900 += cnt;
        D_8008BF70[D_8008BF90++] = &actor->unk2C;
        while (cnt != 0) {
            D_8008BE40.unk0 = pos->unk0;
            D_8008BE40.unk4 = pos->unk4;
            Math_RotateVec2(z, &D_8008BE40);
            Enemy_Spawn(p->unk0, x + D_8008BE40.unk0, y + D_8008BE40.unk4, z, &actor->unk2C, actor);
            cnt--;
            actor++;
            pos++;
        }
        n--;
        p++;
    }
    Enemy_SortTurnOrder();
    D_8008BE5A = D_8007B900;
}

void func_800200F0(void) {
}

s32 func_800200F8(void) {
    s32 r;

    if (D_8007AA08.unk8 & 0x2000) {
        r = 3;
    } else {
        r = 4;
    }
    if ((D_8008BE52 & 0x100) || Math_Rand(r) == 0) {
        r = D_8007B908[Math_Rand(D_8008BE5A)].unk28->unk34;
    } else {
        r = 0xFF;
    }
    return r;
}

void func_8002018C(void) {
}

/* .data 8004F0B0..8004F2C0 */
Struct_8004F0B0 D_8004F0B0[36] = {
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
};
/* Two message strings that nothing references by address. */
u8 D_8004F260[0x24] = {
#include "assets/D_8004F260.inc.c"
};
u8 D_8004F284[0x1C] = {
#include "assets/D_8004F284.inc.c"
};
f32 D_8004F2A0[8] = { 85.0f, 140.0f, 100.0f, 150.0f, 150.0f, 100.0f, 100.0f, 190.0f };
