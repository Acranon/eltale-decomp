#include "common.h"
#include "game/enemy/boss.h"

/*
 * Bosses (8, one per map/sub-area in D_803AB3D0): defeated bits, the boss standing on
 * the field map (load, draw, proximity trigger, encounter start), its battle record
 * init, and the defeat handling (stat reward, or boss 7's exit to the ending).
 * Original file: DAE0.c (ROM 0xDAE0).
 */

/* local copy of game/map/collision.h's CollResult until H2 */
typedef struct CollResult {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk803AB3D0; /* size 0x18 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
} RomRange;

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
} Unk8007A9D0;

f32 sqrtf(f32);
void Dma_ReadRom();
void Anim_DrawModel(s32, Actor *, void *, struct GfxFrameData *);
void Anim_AdvanceFrame(s32, Actor *, void *);
void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
void Anim_SetCurrentAndNext(Actor *, s32, s32, s32, s32, u16);
void Coll_ResolveFloorAndWalls(f32, f32, f32, u16, CollResult *);

/* This file's .bss, 8007C0B0..8007C280, in address order (first declared in boss.h).
 * D_8007C0CC, D_8007C144 and D_8007C278 are unreferenced gaps. Splat's labels inside
 * boss_field_record (D_8007C174..D_8007C1D8, its actor) are aliases in undefined_syms.txt. */
CollResult boss_spawn_coll;
s32 D_8007C0CC;
Actor boss_camera_target;
u8 boss_defeated_bits[4];
s32 boss_field_index;
s32 D_8007C144;
Enemy boss_field_record;
s32 D_8007C278[2];

extern u8 math_bit_masks[];
extern Gfx *gfx_dl_head;
extern Unk8007AA08 player_state;
extern u8 D_802A7BC0[];
extern RomRange D_803AB390[];
extern Unk803AB3D0 D_803AB3D0[];
extern f32 D_803AB48C[];
extern EnemyDef D_803AB820[];
extern EnemyDef D_803AB9A8;
extern u8 *D_803ABA58[];
extern s32 map_id;
extern s32 map_subarea;
extern u8 text_speaker_name[];
extern u8 text_message_buf[];
extern u8 *D_803AC418[];
extern u8 *D_803AC438[];
extern u8 D_803AC328[];
extern EnemyDef D_803AB4B0[];
extern s32 core_flags;
extern s16 D_8007A172;
extern s32 core_transition_timer;
extern s16 fade_transition_style;
extern s16 core_fade_out_time;
u16 boss_reward_max_hp[8] = { 10, 10, 15, 20, 20, 25, 25, 0 };
u16 boss_reward_max_mp[8] = { 5, 5, 5, 10, 10, 15, 15, 0 };
extern Unk8007A9D0 player_stats;
void Camera_SetTargetView(EnemyDef *, Actor *);
void Text_OpenWindow(s32);

void Boss_ClearDefeated(void) {
    boss_defeated_bits[0] = 0;
}

void Boss_LoadForArea(void) {
    s32 start;
    s32 end;
    s32 i;
    s32 size;
    Unk803AB3D0 *p;

    boss_field_index = 0;
    for (i = 0; i < 8; i++) {
        p = &D_803AB3D0[i];
        if (map_id == p->unk0 && map_subarea == p->unk2) {
            if (Boss_IsDefeated(i) == 0) {
                start = D_803AB390[p->unk4].start;
                end = D_803AB390[p->unk4].end;
                size = end - start;
                Dma_ReadRom(start, D_802A7BC0, size);
                Boss_Spawn(i, p->unkC, p->unk10, p->unk14, &boss_field_record);
                boss_field_index = i + 1;
            }
            return;
        }
    }
}

void Boss_Draw(struct GfxFrameData *arg0) {
    Enemy *p = &boss_field_record;
    s32 pad;
    u8 *temp;

    if (boss_field_index != 0) {
        temp = D_803ABA58[boss_field_record.actor.unk50];
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
        Anim_DrawModel(1, &p->actor, temp + boss_field_record.actor.unk52 * 0xC, arg0);
        Anim_AdvanceFrame(p->actor.unk58, &p->actor, temp + p->actor.unk52 * 0xC);
        if (p->actor.unk64->unk0 != 2) {
            Shadow_Queue(p->actor.x, p->actor.y, p->actor.z, p->actor.nx, p->actor.ny, p->actor.nz,
                          p->actor.unk28 * p->actor.scale);
        }
    }
}

s32 Boss_CheckPlayerNear(void) {
    s32 ret = 0;
    f32 dx;
    f32 dz;

    if (boss_field_index != 0) {
        dx = boss_field_record.actor.x - player_state.x;
        dz = boss_field_record.actor.z - player_state.z;
        if (sqrtf(dx * dx + dz * dz) < D_803AB48C[boss_field_index]) {
            ret = boss_field_index;
        }
    }
    return ret;
}

void Boss_Spawn(s32 arg0, f32 arg1, f32 arg2, f32 arg3, Enemy *arg4) {
    EnemyDef *s2 = &D_803AB820[arg0];
    Actor *s1 = &arg4->actor;
    s16 flags;

    arg4->actor.unk50 = s2->unk2;
    Anim_SetCurrentAndNext(s1, 0, 1, 0, 1, 1);
    s1->scale = s2->unk20;
    s1->unk28 = s2->unk18;
    s1->unk64 = (ActorStats *)s2;
    s1->unk68 = &arg4->battle;
    arg4->unk28 = s2;
    arg4->unkA = s2->unk6;
    arg4->unkC = s2->unk6;
    arg4->type = 0;
    arg4->flags = 0;
    arg4->unk10 = sqrtf((u32)s2->unkC) * 3.846 + 17.838;
    arg4->battle.unk0 = 0;
    arg4->battle.unk84 = arg4->unk28->unk2A;
    arg4->battle.unk86 = ((EnemyDef *)s1->unk64)->unkC;
    arg4->battle.unk88 = ((EnemyDef *)s1->unk64)->unkE;
    arg4->battle.unk90 = 1.0f;
    Coll_ResolveFloorAndWalls(arg1, 0.0f, arg2, 0xA00, &boss_spawn_coll);
    s1->x = boss_spawn_coll.x;
    s1->y = boss_spawn_coll.y;
    s1->z = boss_spawn_coll.z;
    if (arg0 == 7) {
        arg4->flags |= 4;
        s1->y -= 30.0;
    }
    s1->rot = arg3;
    s1->nx = boss_spawn_coll.nx;
    s1->ny = boss_spawn_coll.ny;
    s1->nz = boss_spawn_coll.nz;
    s1->unk5E = 1;
    s1->unk60 = 0;
    if (s2 == &D_803AB9A8) {
        s1->unk5E |= 4;
    }
}

u8 Boss_IsDefeated(u32 arg0) {
    return boss_defeated_bits[arg0 >> 3] & math_bit_masks[arg0 & 7];
}

void Boss_SetDefeated(u16 arg0) {
    boss_defeated_bits[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}

void Boss_BeginEncounter(s32 arg0) {
    u8 *src;
    u8 *dst;
    s32 i;

    src = D_803AC418[arg0];
    dst = text_speaker_name;
    for (i = 0x20; i != 0; i--) {
        *dst++ = *src++;
    }
    src = D_803AC438[arg0];
    dst = text_message_buf;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *src++;
    }
    boss_camera_target = boss_field_record.actor;
    if (arg0 == 7) {
        boss_camera_target.x = -31.0f;
        boss_camera_target.y = 139.0f;
        boss_camera_target.z = -328.0f;
    }
    Camera_SetTargetView(&D_803AB4B0[arg0], &boss_camera_target);
}

void Boss_HandleDefeat(s32 arg0) {
    u8 *src;
    u8 *dst;
    s32 i;

    if (arg0 == 7) {
        src = D_803AC418[arg0];
        dst = text_speaker_name;
        for (i = 0x20; i != 0; i--) {
            *dst++ = *src++;
        }
        src = D_803AC328;
        dst = text_message_buf;
        for (i = 0x4B0; i != 0; i--) {
            *dst++ = *src++;
        }
        Text_OpenWindow(1);
        player_state.unk8 |= 0x10;
        core_flags |= 0x80;
        core_transition_timer = 0x40;
        fade_transition_style = 3;
        core_fade_out_time = 0x3E;
        D_8007A172 = 4;
    } else {
        player_stats.unk6 += boss_reward_max_hp[arg0];
        if (player_stats.unk6 > 500) {
            player_stats.unk6 = 500;
        }
        player_stats.unk4 = player_stats.unk6;
        player_stats.unkA += boss_reward_max_mp[arg0];
        if (player_stats.unkA > 500) {
            player_stats.unkA = 500;
        }
        player_stats.unk8 = player_stats.unkA;
    }
}
