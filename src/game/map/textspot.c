#include "game/map/textspot.h"

/*
 * Spirits: sets a collected flag. Text spots: fixed per-map points that show a message
 * read from ROM when the player faces them.
 * Original file: 14CF0.c (ROM 0x14CF0).
 */

/* Local view of Actor (game/actor/actor.h, h_actors) until H2. */
typedef struct Actor {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
} Actor;

extern u8 spirit_collected_flags[];
extern u8 math_bit_masks[];
extern s32 map_id;
extern s32 map_subarea;
TextSpotDef textspot_table[0x26] = {
    { 0x00, 3, 58.0f, -324.0f, -1.5707964f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 168.0f, -295.0f, 1.2217305f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, -384.0f, -146.0f, -2.3561945f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, -153.0f, -165.0f, 3.1415927f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 49.0f, -179.0f, 3.1415927f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 186.0f, -181.0f, 1.3962634f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 48.0f, 95.0f, -2.9146998f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 183.0f, -51.0f, 1.5707964f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x00, 3, 12.0f, 654.0f, 3.1415927f, 10.0f, 0, 0x0070, 0x0078 },
    { 0x02, 0, -1039.5f, 1459.5f, -1.2217305f, 10.0f, 0, 0x0090, 0x0098 },
    { 0x02, 0, -1010.0f, 1980.0f, 2.443461f, 10.0f, 0, 0x00D0, 0x00D8 },
    { 0x03, 0, -102.5f, -1557.5f, 0.2617994f, 10.0f, 0, 0x00F8, 0x0100 },
    { 0x03, 0, -582.0f, -720.0f, -1.7453293f, 10.0f, 0, 0x0120, 0x0128 },
    { 0x05, 0, 90.0f, -420.0f, -1.9198622f, 10.0f, 0, 0x01B8, 0x01C0 },
    { 0x05, 0, 285.0f, 1385.0f, 3.1415927f, 10.0f, 0, 0x0200, 0x0208 },
    { 0x05, 0, -555.0f, 885.0f, 3.1415927f, 10.0f, 0, 0x0230, 0x0238 },
    { 0x06, 0, 397.5f, 480.0f, 0.0f, 10.0f, 0, 0x0258, 0x0260 },
    { 0x06, 0, 10.0f, -532.0f, 0.0f, 10.0f, 0, 0x0280, 0x0288 },
    { 0x07, 0, 1285.0f, 1135.0f, -2.443461f, 10.0f, 0, 0x02B0, 0x02B8 },
    { 0x0B, 0, 475.0f, -104.0f, 0.0f, 10.0f, 0, 0x0358, 0x0360 },
    { 0x0B, 0, 186.0f, -168.0f, 0.17453292f, 10.0f, 0, 0x0358, 0x0360 },
    { 0x0B, 0, 117.0f, -63.0f, -2.7925267f, 10.0f, 0, 0x0358, 0x0360 },
    { 0x0B, 1, -1717.0f, -160.0f, -1.5707964f, 10.0f, 0, 0x0380, 0x0388 },
    { 0x0D, 11, 1.0f, 50.0f, -1.5707964f, 10.0f, 0, 0x0600, 0x0608 },
    { 0x0D, 15, -16.0f, -33.0f, 0.0f, 10.0f, 0, 0x0620, 0x0628 },
    { 0x0D, 15, 18.0f, -33.0f, 0.0f, 10.0f, 0, 0x0670, 0x0678 },
    { 0x0D, 15, 54.0f, -5.0f, 1.5707964f, 10.0f, 0, 0x06B0, 0x06B8 },
    { 0x0E, 9, -4.0f, -41.0f, 0.0f, 10.0f, 0, 0x07D0, 0x07D8 },
    { 0x0E, 9, 28.0f, 31.0f, 1.5707964f, 10.0f, 0, 0x0778, 0x0780 },
    { 0x0E, 9, -28.0f, 31.0f, -1.5707964f, 10.0f, 0, 0x0730, 0x0738 },
    { 0x15, 6, -38.0f, -12.0f, -1.5707964f, 10.0f, 0, 0x0AF8, 0x0B00 },
    { 0x15, 6, -38.0f, 12.0f, -1.5707964f, 10.0f, 0, 0x0AA8, 0x0AB0 },
    { 0x15, 6, -38.0f, 36.0f, -1.5707964f, 10.0f, 0, 0x0A60, 0x0A68 },
    { 0x1C, 0, -2902.5f, 432.5f, 2.3561945f, 10.0f, 2, 0x0C60, 0x0C68 },
    { 0x1F, 0, 42.0f, -524.0f, 0.5235988f, 10.0f, 0, 0x0CF8, 0x0D00 },
    { 0x1F, 0, -646.0f, 414.0f, 3.1415927f, 10.0f, 0, 0x0D20, 0x0D28 },
    { 0x1F, 0, -42.0f, -328.0f, 2.9670596f, 10.0f, 0, 0x0D48, 0x0D50 },
    { 0x21, 0, 858.5f, -438.0f, 0.0f, 10.0f, 0, 0x0D88, 0x0D90 },
};
s32 D_8004EB60 = 0x26; /* the entry count; nothing reads it */
/* This file's .bss, 80085AB0..80085B80, in address order (first declaration fixes
 * the order). Splat's D_80085AC8/D_80085ACC are TextSpot_LoadForMap's textspot_list[0].unk8
 * and &textspot_list[1]. */
Vec2f textspot_local_dir;
s32 D_80085AB8; /* unreferenced */
s32 textspot_count;
TextSpot textspot_list[16];
extern u8 D_D37700[];
extern u8 text_speaker_name[];
extern u8 text_message_buf[];
extern f32 D_8007AB3C;

f32 sqrtf(f32);
void Dma_ReadRom(u8*, void*, s32);

void Spirit_SetCollected(u16 arg0) {
    spirit_collected_flags[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}

void TextSpot_LoadForMap(void) {
    TextSpot* out = textspot_list;
    s32 i;

    textspot_count = 0;
    for (i = 0; i < 0x26; i++) {
        if (map_id == textspot_table[i].mapId && map_subarea == textspot_table[i].subarea) {
            out->entry = &textspot_table[i];
            out->unk8 = 0;
            out++;
            textspot_count++;
        }
    }
}

TextSpot* TextSpot_FindInFront(Actor* arg0) {
    s32 n = textspot_count;
    TextSpot* out = textspot_list;
    f32 dx;
    f32 dz;
    f32 angle;

    while (n != 0) {
        dx = arg0->x - out->entry->x;
        dz = arg0->z - out->entry->z;
        if (sqrtf(dx * dx + dz * dz) < out->entry->radius) {
            textspot_local_dir.x = -dx;
            textspot_local_dir.y = -dz;
            Math_RotateVec2(arg0->ry, &textspot_local_dir);
            angle = Math_Atan2(textspot_local_dir.x, textspot_local_dir.y);
            if (angle < 0.7853981633974483 && angle > -0.7853981633974483) {
                out->unk4 = arg0->ry - angle;
                if (out->entry->flags & 1) {
                    break;
                }
                textspot_local_dir.x = dx;
                textspot_local_dir.y = dz;
                Math_RotateVec2(-out->entry->angle, &textspot_local_dir);
                angle = Math_Atan2(textspot_local_dir.x, textspot_local_dir.y);
                if (angle < 0.7853981633974483 && angle > -0.7853981633974483) {
                    break;
                }
            }
        }
        n--;
        out++;
    }
    if (n == 0) {
        out = NULL;
    }
    return out;
}

void TextSpot_LoadMessage(TextSpot* arg0) {
    Dma_ReadRom(&D_D37700[arg0->entry->nameOffset], text_speaker_name, 0x20);
    Dma_ReadRom(&D_D37700[arg0->entry->textOffset], text_message_buf, 0x200);
    if (text_speaker_name[2] == 0xFF) {
        text_speaker_name[0] = 0xFF;
    }
    D_8007AB3C = arg0->unk4;
}
