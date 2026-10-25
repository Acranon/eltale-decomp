#include "common.h"

typedef short NNScMsg;

typedef struct SCClient_s {
    struct SCClient_s *next;
    OSMesgQueue *msgQ;
} NNScClient;

typedef struct SCTask_s {
    struct SCTask_s *next;
    u32 state;
    u32 flags;
    void *framebuffer;
    OSTask list;
    OSMesgQueue *msgQ;
    OSMesg msg;
} NNScTask;

typedef struct {
    u8 unk0[0x678];
    u32 firstTime;
} NNSched;

/* one graphics frame: task + segment 2 data + display list */
typedef struct {
    /* 0x0000 */ u8 unk0[0x8A70]; /* matrices etc., segment 2 */
    /* 0x8A70 */ Gfx dl[(0xDA70 - 0x8A70) / sizeof(Gfx)];
    /* 0xDA70 */ s16 msg;
    /* 0xDA74 */ u16 *framebuffer;
} GfxFrameData; /* size 0xDA78 */

typedef struct {
    /* 0x0000 */ NNScTask task;
    /* 0x0058 */ GfxFrameData data;
} GfxFrame; /* size 0xDAD0 */

#define OS_SC_SWAPBUFFER 0x0040

void func_80000530(NNSched *sc, u8 numFields);
void func_8000062C(NNSched *sc);
OSMesgQueue *func_80000704(NNSched *sc);
void func_800007F4(NNSched *sc, NNScClient *c, OSMesgQueue *msgQ);
void func_80000F4C(void);
void func_80001084(void);
void func_800011B8(GfxFrame *arg0);
void func_80001944(void);
void func_8000205C(void);
void func_800023F4(void);
void func_8000275C(void);
void func_80002948(void);
void func_80002A8C(void);
void func_80002BDC(void);
void func_80003350(void);
void func_8000CEE0(void);
void func_80011A60(void);
void func_800134D0(void);
void func_80013BA0(void);
void func_80024F20(void);
void func_80028120(u8 *romStart, void *dest, u32 size);
void func_800285C4(void);
void func_80028FA8(NNSched *sc);
void func_80028FFC(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4);
void func_80029374(u8 *arg0, u8 *arg1, u8 *arg2);
void func_8002A4F0(void);
void func_8002A930(void);
void func_80035308(void);
void func_800357B0(void);
void func_80037B70(OSPri pri);
void func_801009EC(OSMesgQueue *arg0, OSMesgQueue *arg1);

extern u8 D_71920[];
extern u8 D_753F0[];
extern u8 D_D490C0[];
extern u8 D_D74AC0[];
extern u8 D_D86170[];
extern u8 D_DA4570[];
extern u8 D_DAB5F0[];
extern u8 D_E5BF60[];
extern u8 D_E5ED70[];
extern u8 D_E98330[];
extern u8 D_ECB7B0[];
extern u8 D_ECD470[];

extern u64 D_8004B980[]; /* rspboot text */
extern u64 D_8004BA50[]; /* gfx ucode text (= rspboot end) */
extern u64 D_80070260[]; /* gfx ucode data */
extern s32 D_8004DCA0;
extern OSViMode D_8006CDF0;
extern OSViMode D_8006D6B0;
extern u16 D_8007A170;
extern u16 D_8007A172;
extern u16 D_8007A178;
extern s32 D_8007A17C;
extern OSMesgQueue D_8007A1A8;
extern OSMesg D_8007A1C0;
extern u8 D_8007A1CC;
extern s8 D_8007A1CD;
extern void *D_8007A1D8;
extern NNSched D_8007A1E0;
extern OSMesgQueue D_8007A254;
extern OSMesgQueue *D_8007A860;
extern NNScClient D_8007A868;
extern OSMesgQueue D_8007A870;
extern OSMesg D_8007A888[];
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern s16 D_8007A9AC;
extern u16 D_8007A9AE;
extern s16 D_8007A9B0;
extern s16 D_8007AA0E;
extern u16 D_8007C282;
extern s32 D_800842BC;
extern u32 D_800842C4;
extern s32 D_800842C8;
extern s32 D_800842D0;
extern s32 D_800842DC;
extern s32 D_80084308;
extern s16 D_80084992;
extern f32 D_80085ECC;
extern s16 D_8008C152;
extern u16 D_8008C154;
extern s16 D_8008C156;
extern s16 D_8008C158[];
extern OSMesgQueue D_80092C90;
extern u8 D_80095AF0[];
extern u8 D_800C0000[];
extern u8 D_80100000[];
extern u64 D_80300000[];
extern u64 D_80300400[];
extern GfxFrame D_80301000[2];
extern u64 D_8031C5A0[];
extern u64 D_803245A0[];
extern u8 D_8039ADB0[];
extern u16 D_803B5000[];
extern u16 D_803DA800[];

void func_80000C70(void *arg0) {
    func_80037B70(0xFE);
    osCreateMesgQueue(&D_8007A1A8, &D_8007A1C0, 1);
    func_800285C4();
    /* the ROM end symbols don't exist yet: ends are written start + size */
    func_80028FFC(D_E5BF60, D_E5BF60 + 0x2E10, D_E98330, D_E98330 + 0x33480, D_E5ED70);
    func_80029374(D_ECB7B0, D_ECB7B0 + 0x1CC0, D_ECD470);
    func_80000530(&D_8007A1E0, 1);
    func_800357B0();
    if (osTvType == OS_TV_NTSC) {
        osViSetMode(&D_8006CDF0);
    } else {
        osViSetMode(&D_8006D6B0);
    }
    osViBlack(1);
    func_80028120(D_DA4570, D_80100000, D_DAB5F0 - D_DA4570);
    func_80035308();
    func_801009EC(&D_80092C90, &D_8007A254);
    osViBlack(1);
    osViSetSpecialFeatures(0x5A);
    func_8000062C(&D_8007A1E0);
    func_80028FA8(&D_8007A1E0);
    osCreateMesgQueue(&D_8007A870, D_8007A888, 8);
    func_800007F4(&D_8007A1E0, &D_8007A868, &D_8007A870);
    D_8007A860 = func_80000704(&D_8007A1E0);
    func_80001084();

    while (1) {
        func_8000CEE0();
        func_800134D0();
        func_80013BA0();
        func_80003350();
        func_80024F20();
        func_80011A60();
        func_80035308();
        func_8002A4F0();
        func_80000F4C();
        func_8002A930();
    loop:
        D_8004DCA0 &= ~3;
        if (D_8007A170 == 0) {
            D_8007A170 = 1;
        }
        switch (D_8007A170) {
            case 1:
                func_80001944();
                break;
            case 6:
                func_8000205C();
                break;
            case 7:
                func_800023F4();
                break;
            case 2:
                func_8000275C();
                break;
            case 3:
                func_80002948();
                break;
            case 4:
                func_80002A8C();
                break;
            case 5:
                func_80002BDC();
                break;
        }
        if (!(D_8004DCA0 & 0x8000)) {
            goto loop;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80000F4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80001084.s")

void func_800011B8(GfxFrame *arg0) {
    arg0->task.list.t.type = M_GFXTASK;
    arg0->task.list.t.flags = 0;
    arg0->task.list.t.ucode_boot = D_8004B980;
    arg0->task.list.t.ucode_boot_size = (u32)&D_8004B980[0xD0 / 8] - (u32)D_8004B980;
    arg0->task.list.t.ucode = D_8004BA50;
    arg0->task.list.t.ucode_data = D_80070260;
    arg0->task.list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    arg0->task.list.t.dram_stack = D_80300000;
    arg0->task.list.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    arg0->task.list.t.output_buff = D_8031C5A0;
    arg0->task.list.t.output_buff_size = D_803245A0;
    arg0->task.list.t.yield_data_ptr = D_80300400;
    arg0->task.list.t.yield_data_size = OS_YIELD_DATA_SIZE;
    arg0->task.next = NULL;
    arg0->task.flags = OS_SC_SWAPBUFFER;
    arg0->task.msgQ = &D_8007A870;
    arg0->task.msg = &arg0->data.msg;
    arg0->task.framebuffer = arg0->data.framebuffer;
}

extern Gfx *D_8007A184;
extern s32 D_8007A188;
extern s32 D_8007A18C;
extern u32 D_8007A190;
extern s32 D_8007A1C8;
extern s32 D_8007A1D4;
extern s32 D_8007AB60;
extern u16 D_8007C280;
extern s32 D_8004DCA4;
extern s8 D_8006CC80;
extern u8 D_1000010[];
extern u8 D_2000000[];
extern u16 D_802DA800[];

void func_8000464C(void *arg0);
void func_80009594(void *arg0);
void func_8000A3E4(void *arg0);
void func_8000CFD8(void *arg0);
void func_8000DE54(void *arg0);
void func_8000E81C(void *arg0);
void func_8000F34C(void *arg0);
void func_800124E8(void);
void func_80012B88(s32 arg0);
void func_80013264(void *arg0);
void func_800136B8(void *arg0);
void func_80013E4C(void);
void func_80014994(void *arg0);
void func_8001A658(void *arg0);
void func_8001DA3C(void *arg0);
void func_80020B78(void *arg0);
void func_80025318(void);
void func_80026774(void *arg0);
void func_8002A984(void *arg0);
void func_8002FA00(s32 arg0);
void func_80033050(void);
void func_80036664(void);
s32 func_8020C11C(void);
s32 func_8020C15C(void);
s32 func_8020C16C(void);

void func_80001278(GfxFrame *arg0) {
    s32 count;
    s32 one = 1;
    GfxFrameData *sub;

    D_8007A184 = arg0->data.dl;

    gSPSegment(D_8007A184++, 0x00, 0x00000000);
    gSPSegment(D_8007A184++, 0x01, osVirtualToPhysical(D_8007A1D8));
    gSPSegment(D_8007A184++, 0x02, osVirtualToPhysical(sub = &arg0->data));
    gSPDisplayList(D_8007A184++, D_1000010);
    gDPSetDepthImage(D_8007A184++, osVirtualToPhysical(D_802DA800));
    gDPPipeSync(D_8007A184++);
    gDPSetCycleType(D_8007A184++, G_CYC_FILL);
    gDPSetColorImage(D_8007A184++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_802DA800));
    gDPSetFillColor(D_8007A184++, 0xFFFCFFFC);
    gDPFillRectangle(D_8007A184++, 8, 8, 311, 231);
    gDPPipeSync(D_8007A184++);
    gDPSetColorImage(D_8007A184++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(arg0->data.framebuffer));

    if (D_8007A170 == 1 || D_8007A170 == 6 || D_8007A170 == 7) {
        gDPSetFillColor(D_8007A184++, (GPACK_RGBA5551(D_8007A188, D_8007A18C, D_8007A190, 1) << 16) |
                                          GPACK_RGBA5551(D_8007A188, D_8007A18C, D_8007A190, 1));
        gDPFillRectangle(D_8007A184++, 8, 8, 311, 231);
    } else {
        gDPSetFillColor(D_8007A184++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(D_8007A184++, 8, 8, 311, 231);
    }
    gDPPipeSync(D_8007A184++);
    gDPSetCycleType(D_8007A184++, G_CYC_2CYCLE);

    if (D_8007A170 == 1 || D_8007A170 == 6 || D_8007A170 == 7) {
        func_80014994(sub);
        func_800124E8();
        if (D_8007C280 & 4) {
            func_80012B88(D_8007A1C8);
            func_8000F34C(sub);
        }
        func_80012B88(D_8007A1C8);
        func_8000DE54(sub);
        if (!(D_8004DCA0 & 0x10000)) {
            func_8000464C(sub);
        }
        func_80009594(sub);
        func_800136B8(sub);
        func_8000E81C(sub);
        func_8000A3E4(sub);
        func_8000CFD8(sub);
        func_80013E4C();
        func_80012B88(D_8007AB60);
        func_80013264(sub);
        func_8001DA3C(sub);
        func_8001A658(sub);
        func_80026774(sub);
        if (D_8004DCA0 & 2) {
            func_80033050();
        }
        if (!(D_8004DCA0 & 0x4000) && (D_8007A172 != 4)) {
            func_80020B78(sub);
        }
        if (D_8004DCA0 & 1) {
            func_80025318();
        }
        if (D_8007A170 == 7) {
            func_80036664();
        }
    } else if (D_8007A170 == 2) {
        func_8002A984(sub);
    } else if (D_8007A170 == 3) {
        switch (func_8020C11C()) {
            case 0:
                switch (D_8007A1CC & 0xF0) {
                    case 0x10:
                        D_8007A170 = 1;
                        D_8004DCA0 &= ~0x400;
                        break;
                    case 0x20:
                        D_8004DCA0 |= 0x400;
                        func_8002FA00(0);
                        break;
                    case 0x30:
                        D_8004DCA0 |= 0x400;
                        func_8002FA00(8);
                        break;
                    default:
                        D_8007A170 = 1;
                        break;
                }
                break;
            case 1:
                D_8007A170 = 4;
                break;
        }
    } else if (D_8007A170 == 4) {
        switch (func_8020C16C()) {
            case 0:
                D_8006CC80 = 0;
                D_8007A170 = 3;
                break;
            case 1:
                D_8006CC80 = one;
                D_8007A170 = 3;
                break;
            default:
                D_8006CC80 = 0;
        }
    } else if (D_8007A170 == 5) {
        count = func_8020C15C();
        func_80026774(sub);
        if (count == 0) {
            D_8007A170 = 7;
        }
    }
    gDPFullSync(D_8007A184++);
    gSPEndDisplayList(D_8007A184++);
    osWritebackDCache(D_2000000, 0xDA70);

    count = D_8007A184 - arg0->data.dl;
    if (D_8007A1D4 < count) {
        D_8007A1D4 = count;
    }
    D_8004DCA4 = count;

    arg0->task.list.t.data_ptr = (u64 *)sub->dl;
    arg0->task.list.t.data_size = (D_8007A184 - sub->dl) * sizeof(Gfx);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80001944.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_8000205C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_800023F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_8000275C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80002948.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80002A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1870/func_80002BDC.s")

void func_800269B8(s32 arg0, s32 arg1, void *arg2);

extern u8 D_8004F5A0[];
extern u8 D_8004F5DC[];
extern u8 D_8004F5E0[];
extern u8 D_8004F61C[];
extern u8 D_8004F620[];
extern u8 D_8004F69C[];
extern u8 D_8004F6C0[];
extern u8 D_8004F73C[];
extern u8 D_8008CA58[];
extern u8 D_8008CE54[];

void func_80002D44(s16 arg0) {
    OSMesg msg = NULL;

    do {
        osRecvMesg(&D_8007A870, &msg, OS_MESG_BLOCK);
    } while (arg0 != *(s16 *)msg);
}

void func_80002DB0(void) {
    switch (D_8007A178) {
        case 0:
            func_800269B8(0x10, 4, D_8004F5DC);
            break;
        case 1:
            func_800269B8(0x10, 4, D_8004F61C);
            break;
        case 2:
            func_800269B8(0x20, 4, D_8004F69C);
            break;
        case 3:
            func_800269B8(0x20, 4, D_8004F73C);
            break;
        case 4:
            func_800269B8(0x100, 4, D_8008CE54);
            break;
    }
}

void func_80002E74(void) {
    switch (D_8007A178) {
        case 0:
            func_800269B8(0xF, 2, D_8004F5A0);
            break;
        case 1:
            func_800269B8(0xF, 2, D_8004F5E0);
            break;
        case 2:
            func_800269B8(0x1F, 2, D_8004F620);
            break;
        case 3:
            func_800269B8(0x1F, 2, D_8004F6C0);
            break;
        case 4:
            func_800269B8(0xFF, 2, D_8008CA58);
            break;
    }
}
