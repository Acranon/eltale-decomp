#include "common.h"
#include "game/npc/npc.h"
#include "game/actor/anim.h"
#include "game/core/dma.h"
#include "game/core/main.h"
#include "game/enemy/boss.h"
#include "game/gfx/shadow.h"
#include "game/item/item.h"
#include "game/map/collision.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/player/player.h"
#include "game/text/text_window.h"
#include "game/ui/menu.h"

/*
 * NPCs (non-encounter areas): spawn from the area's def list, per-frame wander/turn update, draw,
 * collision, start/end of a talk and loading the message and speaker name into the text buffers.
 * Original file: 9D50.c (ROM 0x9D50).
 */

/* This file's .bss, 8007AB70..8007B900, in address order. D_8007AB80
 * and D_8007ABAC are unreferenced gaps (splat's D_8007ABA0 is npc_move_coll.flags). D_8007AC70 (each Npc's def
 * field, 3F50) and D_8007B7E2 are aliases in undefined_syms.txt. */
MenuRomRange *npc_area_set_rom_range;
u16 npc_walking_count;
Vec2f npc_walk_step;
s32 D_8007AB80[2];
CollResult npc_move_coll;
s32 npc_count;
s32 npc_drawn_count;
s32 D_8007ABAC;
Actor *npc_drawn_list[16];
Npc npc_slots[16];
u8 text_message_buf[0x4B0];
u8 text_speaker_name[0x20];

/* Npc_PushOutOfObjects reads player_state.actor.x/z through their labels (D_8007AA20.x,
 * D_8007AA28, player.h): retail addresses them as their own symbols. */

/* Message text that Npc_StartTalk hands to the text box. */
u8 npc_rest_choice_row0[8] = {
#include "assets/npc_rest_choice_row0.inc.c"
};
u8 npc_rest_choice_row1[8] = {
#include "assets/npc_rest_choice_row1.inc.c"
};

/* The overlay entry point and ROM symbols func_80009764 loads (no C module declares them). */
void func_8020C0D0(void);
extern u8 D_86F6F0[];
extern u8 D_871D10[];
extern u8 D_A70350[];
extern u8 D_A77F10[];
extern u8 D_D2E2F0[];
extern u8 D_802A0000[];
extern u8 D_8020E6F0[];

void Npc_InitArea(void) {
    NpcList *list;

    npc_count = 0;
    if (!(map_subarea_flags & 1)) {
        func_80009764(map_subarea_def->areaSetIndex);
        list = map_area_def->npcList;
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
    Npc *npc;
    s32 i;
    Actor *obj;
    f32 dx;
    f32 dz;

    i = npc_count;
    npc = npc_slots;
    for (; i != 0; i--, npc++) {
        obj = &npc->actor;
        switch (npc->state) {
            case 0:
                if (npc->def->movement_kind == 2) {
                    if (--npc->timer == 0) {
                        if (npc_walking_count < 3) {
                            npc->state = 1;
                            npc->timer = (Math_Rand(2) + 1) * (npc->def->anim_sets + 1)->length;
                            Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
                            dx = npc->homeX - obj->x;
                            dz = npc->homeZ - obj->z;
                            if (sqrtf(dx * dx + dz * dz) > 50.0) {
                                obj->rot = Math_Atan2(dx, dz);
                            } else {
                                obj->rot = (f32)Math_Rand(16) * 0.39269908169872414 - 1.5707963267948966;
                            }
                            npc_walking_count++;
                        } else {
                            npc->timer = (Math_Rand(2) + 1) * npc->def->anim_sets->length;
                        }
                    }
                }
                break;
            case 1:
                npc_walk_step.x = 0.0f;
                npc_walk_step.y = 0.4f;
                Math_RotateVec2(obj->rot, &npc_walk_step);
                Npc_Move(npc_walk_step.x, npc_walk_step.y, obj);
                if (--npc->timer == 0) {
                    npc->state = 0;
                    npc->timer = npc->def->anim_sets->length;
                    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                    npc_walking_count--;
                }
                break;
            case 2:
                if (npc->timer != 0) {
                    npc->timer--;
                    obj->rot += npc->turn_delta / 15.0f;
                    if (npc->timer == 0) {
                        Anim_SetCurrentAndNext(obj, npc->def->talk_anim_index, 1, npc->def->talk_anim_index, 1, 1);
                    }
                }
                break;
            case 3:
                npc->timer--;
                obj->rot -= npc->turn_delta / 15.0f;
                if (npc->timer == 0) {
                    npc->state = 0;
                    npc->timer = npc->def->anim_sets->length;
                    obj->rot = npc->homeAngle;
                    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                }
                break;
        }
    }
}

void Npc_DrawAll(struct GfxFrameData *arg0) {
    Npc *npc;
    s32 i;
    Actor **list;
    Actor *obj;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 filter;
    AnimSet *anims;

    npc_drawn_count = 0;
    i = npc_count;
    npc = npc_slots;
    list = npc_drawn_list;
    for (; i != 0; i--, npc++) {
        dx = npc->actor.x - player_state.actor.x;
        obj = &npc->actor;
        dz = npc->actor.z - player_state.actor.z;
        dist = dx * dx + dz * dz;
        if (dist < 90000.0f) {
            filter = (dist < 20000.0f) ? G_TF_BILERP : G_TF_POINT;
            gDPSetTextureFilter(gfx_dl_head++, filter);
            anims = npc->def->anim_sets;
            Anim_DrawModel(0, obj, &anims[obj->animIndex], arg0);
            Anim_AdvanceFrame(obj->animStep, obj, &anims[obj->animIndex]);
            Shadow_Queue(obj->x, obj->y, obj->z, obj->nx, obj->ny, obj->nz, 5.0f);
            *list++ = obj;
            npc_drawn_count++;
        }
    }
}

void func_80009764(s32 arg0) {
    u8 *start;
    u8 *end;

    npc_area_set_rom_range = &npc_area_set_rom_ranges[arg0];
    Dma_ReadRom(D_86F6F0, func_8020C0D0, D_871D10 - D_86F6F0);
    Dma_ReadRom(D_A70350, D_802A0000, D_A77F10 - D_A70350);
    start = npc_area_set_rom_range->start;
    end = npc_area_set_rom_range->end;
    Dma_ReadRom(start, D_8020E6F0, end - start);
}

void Npc_SpawnForArea(NpcDef *def, s32 n) {
    Npc *npc = npc_slots;
    CollResult out;

    for (; n != 0; n--, def++) {
        if (map_subarea == def->area) {
            npc->state = 0;
            npc->timer = 1;
            npc->def = def;
            npc->actor.x = def->x;
            npc->actor.z = def->z;
            npc->actor.rot = def->angle;
            npc->actor.rotX = 0.0f;
            npc->actor.rotZ = 0.0f;
            npc->actor.scale = def->scale;
            npc->actor.collisionRadius = 50.0f;
            Coll_ResolveFloorAndWalls(npc->actor.x, npc->actor.y, npc->actor.z, 0xA00, &out);
            npc->actor.y = out.y;
            npc->actor.nx = out.nx;
            npc->actor.ny = out.ny;
            npc->actor.nz = out.nz;
            Anim_SetCurrentAndNext(&npc->actor, 0, 1, 0, 1, 1);
            npc->homeX = def->x;
            npc->homeZ = def->z;
            npc->homeAngle = def->angle;
            if (def->flags & 1) {
                npc->actor.animFlags = 0x1000;
            } else {
                npc->actor.animFlags = 0;
            }
            npc++;
            npc_count++;
        }
    }
}

void Npc_Move(f32 dx, f32 dz, Actor *obj) {
    Npc_PushOutOfObjects(&dx, &dz, obj);
    obj->vx = dx;
    obj->vz = dz;
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

void Npc_PushOutOfObjects(f32 *dx, f32 *dz, Actor *obj) {
    f32 nx;
    f32 nz;
    f32 ddx;
    f32 ddz;
    f32 r;
    f32 d;
    s32 hit;
    f32 radius;
    s32 i;
    Actor **list;
    Actor *other;
    MapObj **list2;
    MapObj *other2;

    nx = *dx + obj->x;
    nz = *dz + obj->z;
    radius = obj->collisionRadius * obj->scale;
    hit = 0;
    ddx = nx - player_state.actor.x;
    ddz = nz - player_state.actor.z;
    r = player_state.actor.collisionRadius * player_state.actor.scale + radius;
    if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
        d = sqrtf(ddx * ddx + ddz * ddz);
        if (d < r) {
            d = r / d;
            hit = 1;
            ddx *= d;
            ddz *= d;
            *dx = D_8007AA20.x + ddx - obj->x;
            *dz = D_8007AA28 + ddz - obj->z;
        }
    }
    i = npc_drawn_count;
    if (i != 0) {
        for (list = npc_drawn_list; !hit && i != 0; i--) {
            other = *list++;
            if (other != obj) {
                ddx = nx - other->x;
                ddz = nz - other->z;
                r = other->collisionRadius * other->scale + radius;
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
            r = radius + other2->scale * 2.0;
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
    Npc *npc = &npc_slots[idx];
    f32 angle;
    f32 dx;
    f32 dz;
    s32 msg;

    npc->state = 2;
    if (npc->def->flags & 2) {
        npc->timer = 0;
    } else {
        npc->timer = 15;
        dx = player_state.actor.x - npc->actor.x;
        dz = player_state.actor.z - npc->actor.z;
        angle = Math_Atan2(dx, dz) - npc->actor.rot;
        if (angle < -3.141592653589793) {
            angle += 6.283185307179586;
        }
        if (angle > 3.141592653589793) {
            angle -= 6.283185307179586;
        }
        npc->turn_delta = angle;
        npc->timer = 15;
        Anim_SetCurrentAndNext(&npc->actor, 1, 1, 1, 1, 1);
    }
    switch (npc->def->talk_kind) {
        case 2:
            if (Item_CountInInventory(npc->def->u6.b.item_id) == 0) {
                found = 0;
                msg = npc->def->message_offset;
            } else {
                found = 1;
                msg = npc->def->alternate_message_offset;
            }
            Npc_LoadMessage(npc, msg);
            if (found == 0) {
                Item_AddToInventory(npc->def->u6.b.item_id);
                player_state.flags |= 0x40;
            }
            break;
        case 5:
            if (Boss_IsDefeated(npc->def->u6.boss_index) == 0) {
                msg = npc->def->message_offset;
            } else {
                msg = npc->def->alternate_message_offset;
                if (npc->def->u6.boss_index == 7) {
                    core_flags |= 0x8080;
                    core_transition_timer = 0x16;
                }
            }
            Npc_LoadMessage(npc, msg);
            break;
        case 6:
            Npc_LoadMessage(npc, npc->def->message_offset);
            text_pending_choice_rows.n = 2;
            text_pending_choice_rows.rows[0] = npc_rest_choice_row0;
            text_pending_choice_rows.rows[1] = npc_rest_choice_row1;
            text_last_choice_index = -1;
            core_flags |= 0x10;
            break;
        default:
            Npc_LoadMessage(npc, npc->def->message_offset);
            break;
    }
}

void Npc_EndTalk(s32 idx) {
    Npc *npc = &npc_slots[idx];

    if (npc->def->movement_kind == 2) {
        npc->state = 0;
        npc->timer = Math_Rand(30) + 30;
    } else if (npc->def->flags & 2) {
        npc->state = 0;
        npc->timer = npc->def->anim_sets->length;
    } else {
        npc->state = 3;
        npc->timer = 15;
        Anim_SetCurrentAndNext(&npc->actor, 1, 1, 1, 1, 1);
    }
}

void Npc_LoadMessage(Npc *npc, s32 arg1) {
    s32 i;

    Dma_ReadRom(&D_D2E2F0[arg1], text_message_buf, 0x4B0);
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
    Npc *npc;

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
