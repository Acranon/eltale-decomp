/* Unmatched research draft for func_801009EC_ovl_DA4570. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/09ec-focus/func_801009EC_37words.c
 * Snapshot SHA-256: 4fa8eb94d8c2de18d3561e6db9e6b2b7eea5cd84060452501c3f6f684b27b82e
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_801009EC_ovl_DA4570(OSMesgQueue* mq, OSMesgQueue* arg1) {
    OSContPad pads[4];
    u32* p;
    u16 btn;
    s16 dir;
    s16 unused3;
    u16 repeat;
    u16 blink;
    u16 unused4;
    u32 timer;
    OSPfs pfs;
    OSPfs pfs2;
    s32 count;
    s32 maxFiles;
    s32 ret;
    s32 ret2;
    s32 ret3;
    s32 sub;
    s32 i;
    u16 held;
    u16 cur;
    UnkStruct_80107080* file;

    D_801072E4_ovl_DA4570 = mq;
    D_801072E8_ovl_DA4570 = arg1;
    if (D_80092E98 == 0) {
        return 0;
    }
    osContStartReadData(mq);
    osRecvMesg(mq, &D_801072EC_ovl_DA4570, 1);
    osContGetReadData(pads);
    if (!(D_80092EA0[D_80092C80].status & 1)) {
        return 0;
    }
    ret = func_8003D0F0(mq, &pfs, D_80092C80);
    if (ret == 10) {
        ret2 = func_8003D554(mq, &pfs2, D_80092C80);
    } else {
        ret2 = 11;
    }
    if ((ret == 10) && (ret2 == 11)) {
        ret3 = func_8003D6B0(mq, &pfs2, D_80092C80);
    } else {
        ret3 = 11;
    }
    if ((ret != 0) && (ret != 10)) {
        return 0;
    }
    if (ret2 == 0) {
        return 0;
    }
    if (ret3 == 0) {
        return 0;
    }
    if (ret == 0) {
        D_801072C8_ovl_DA4570 = 0;
    } else {
        D_801072C8_ovl_DA4570 = 5;
    }
    if (!(pads[D_80092C80].button & 0x1000) && (D_801072C8_ovl_DA4570 != 5)) {
        return 2;
    }
    for (p = (u32*) 0x80200000; p != (u32*) 0x8024B000; p++) {
        *p = 0;
    }
    osViBlack(0);
    D_801072DC_ovl_DA4570 = 1;
    func_8010055C_ovl_DA4570();
    D_80107280_ovl_DA4570 = 0x62;
    repeat = 0;
    held = 0;
    btn = 0x400;
    blink = 0;
    sub = 0;

    while (TRUE) {
        ret2 = D_801072CA_ovl_DA4570 + D_801072CE_ovl_DA4570;
        switch (D_801072C8_ovl_DA4570) {
            case 0:
                if (sub == 0) {
                    count = 0;
                    if (1) {}
                    ret = func_8003EDC0(&pfs, &maxFiles, &count);
                    if (ret == 0) {
                        for (i = 0; i < 16; i++) {
                            D_80107288_ovl_DA4570[i] = osPfsFileState(&pfs, i, (OSPfsState*)(D_80107080_ovl_DA4570 + i));
                        }
                        ret = osPfsFreeBlocks(&pfs, &D_801072D8_ovl_DA4570);
                    }
                    switch (ret) {
                        case 0:
                            D_801072D4_ovl_DA4570 = 1;
                            D_801072C8_ovl_DA4570 = 1;
                            D_801072D8_ovl_DA4570 >>= 8;
                            break;
                        case 1:
                            D_801072C8_ovl_DA4570 = 8;
                            break;
                        case 2:
                            sub = 1;
                            break;
                        case 10:
                            D_801072C8_ovl_DA4570 = 5;
                            break;
                        default:
                            return 0;
                    }
                }
                if (sub != 0) {
                    ret = func_8003D0F0(mq, &pfs, D_80092C80);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                    } else if (ret == 2) {
                        D_801072C8_ovl_DA4570 = 0;
                    } else if (ret == 10) {
                        D_801072C8_ovl_DA4570 = 5;
                    } else {
                        return 0;
                    }
                }
                D_801072CC_ovl_DA4570 = D_801072CA_ovl_DA4570 = D_801072CF_ovl_DA4570 = D_801072CE_ovl_DA4570 = 0;
                sub = 0;
                break;
            case 1:
                if (sub == 0) {
                    sub++;
                    D_801072D2_ovl_DA4570 = 0x36;
                    if (count == 0) {
                        D_801072D4_ovl_DA4570 = 1;
                    }
                    D_801072D0_ovl_DA4570 = (D_801072D4_ovl_DA4570 != 0) ? 0xBA : 0x4C;
                    func_80100944_ovl_DA4570();
                    func_8010089C_ovl_DA4570();
                } else if ((D_801072D4_ovl_DA4570 == 0) && (btn & 0x8000)) {
                    D_801072C8_ovl_DA4570 = 2;
                    sub = 0;
                } else if (btn & 0xC000) {
                    return 3;
                } else if ((count != 0) && (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0)))) {
                    if (btn & 2) {
                        D_801072D4_ovl_DA4570 = 0;
                        D_801072D0_ovl_DA4570 = 0x4C;
                    } else {
                        D_801072D4_ovl_DA4570 = 1;
                        D_801072D0_ovl_DA4570 = 0xBA;
                    }
                    func_80100944_ovl_DA4570();
                    func_8010089C_ovl_DA4570();
                }
                break;
            case 2:
                if (sub == 0) {
                    D_801072D0_ovl_DA4570 = 0x26;
                    D_801072D2_ovl_DA4570 = (D_801072CA_ovl_DA4570 * 13) + 0x58;
                    func_80100944_ovl_DA4570();
                    func_8010089C_ovl_DA4570();
                    sub++;
                } else if (btn & 0x4000) {
                    D_801072C8_ovl_DA4570 = 1;
                    sub = 0;
                    D_801072D4_ovl_DA4570 = 0;
                } else if (btn & 0x8000) {
                    if (D_80107288_ovl_DA4570[ret2] == 0) {
                        D_801072C8_ovl_DA4570 = 4;
                        sub = 0;
                        D_801072D4_ovl_DA4570 = 1;
                    }
                } else {
                    if (held & 4) {
                        if (D_801072CA_ovl_DA4570 >= 5) {
                            if (D_801072CE_ovl_DA4570 < 10) {
                                D_801072CE_ovl_DA4570++;
                            }
                            D_801072CA_ovl_DA4570 = 5;
                        } else {
                            D_801072CA_ovl_DA4570++;
                        }
                    }
                    if (held & 8) {
                        if (D_801072CA_ovl_DA4570 == 0) {
                            if (D_801072CE_ovl_DA4570 != 0) {
                                D_801072CE_ovl_DA4570--;
                            }
                        } else {
                            D_801072CA_ovl_DA4570--;
                        }
                    }
                    if ((D_801072CA_ovl_DA4570 != D_801072CC_ovl_DA4570) || (D_801072CE_ovl_DA4570 != D_801072CF_ovl_DA4570)) {
                        D_801072CC_ovl_DA4570 = D_801072CA_ovl_DA4570;
                        D_801072CF_ovl_DA4570 = D_801072CE_ovl_DA4570;
                        func_80100944_ovl_DA4570();
                        D_801072D0_ovl_DA4570 = 0x26;
                        D_801072D2_ovl_DA4570 = (D_801072CA_ovl_DA4570 * 13) + 0x58;
                        func_8010089C_ovl_DA4570();
                    }
                }
                break;
            case 3:
                if (sub == 0) {
                    D_801072D2_ovl_DA4570 = 0xA2;
                    sub++;
                    D_801072D0_ovl_DA4570 = (D_801072D4_ovl_DA4570 != 0) ? 0xA6 : 0x60;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_80105408_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                }
                if ((D_801072D4_ovl_DA4570 == 0) && (btn & 0x8000)) {
                    sub = 0; file = &D_80107080_ovl_DA4570[ret2]; ret = osPfsDeleteFile(&pfs, file->unk8, file->unk4, file->name, &file->unkA);
                    if (ret != 0) {
                        if (ret == 1) {
                            D_801072C8_ovl_DA4570 = 8;
                        } else {
                            D_801072C8_ovl_DA4570 = 7;
                        }
                    } else {
                        count--; D_80107288_ovl_DA4570[ret2] = -1; D_801072D8_ovl_DA4570 += (u8) ((D_80107080_ovl_DA4570[ret2].unk0 + 0xFF) >> 8); if (count != 0) {
                            D_801072C8_ovl_DA4570 = 2;
                        } else {
                            D_801072C8_ovl_DA4570 = 1;
                        }
                    }
                } else if (btn & 0xC000) {
                    D_801072C8_ovl_DA4570 = 4;
                    sub = 0;
                    D_801072D4_ovl_DA4570 = 0;
                } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                    if (btn & 2) {
                        D_801072D4_ovl_DA4570 = 0;
                        D_801072D0_ovl_DA4570 = 0x60;
                    } else {
                        D_801072D4_ovl_DA4570 = 1;
                        D_801072D0_ovl_DA4570 = 0xA6;
                    }
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_80105408_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                }
                break;
            case 4:
                if (sub == 0) {
                    D_801072D2_ovl_DA4570 = 0xC0;
                    sub++;
                    D_801072D0_ovl_DA4570 = (D_801072D4_ovl_DA4570 != 0) ? 0x9C : 0x59;
                    func_80100944_ovl_DA4570();
                    func_8010089C_ovl_DA4570();
                } else if ((D_801072D4_ovl_DA4570 == 0) && (btn & 0x8000)) {
                    D_801072C8_ovl_DA4570 = 3;
                    sub = 0;
                    D_801072D4_ovl_DA4570 = 1;
                } else if (btn & 0xC000) {
                    D_801072C8_ovl_DA4570 = 2;
                    sub = 0;
                } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                    if (btn & 2) {
                        D_801072D4_ovl_DA4570 = 0;
                        D_801072D0_ovl_DA4570 = 0x59;
                    } else {
                        D_801072D4_ovl_DA4570 = 1;
                        D_801072D0_ovl_DA4570 = 0x9C;
                    }
                    func_80100944_ovl_DA4570();
                    func_8010089C_ovl_DA4570();
                }
                break;
            case 5:
                if (sub == 0) {
                    count = D_801072D8_ovl_DA4570 = 0; sub++;
                    for (i = 0; i < 16; i++) {
                        D_80107288_ovl_DA4570[i] = -1;
                    }
                    if (D_801072D4_ovl_DA4570 != 0) {
                        D_801072D0_ovl_DA4570 = 0xA6;
                    } else {
                        D_801072D0_ovl_DA4570 = 0x60;
                    }
                    D_801072D2_ovl_DA4570 = 0xA2;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_801054E8_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                } else if (sub == 1) {
                    if (btn & 0x8000) {
                        sub++;
                        if (D_801072D4_ovl_DA4570 == 0) {
                            timer = 0;
                            blink = 0;
                        } else {
                            D_801072C8_ovl_DA4570 = 9;
                            sub = 0;
                            D_801072D4_ovl_DA4570 = 0;
                        }
                    } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                        if (btn & 2) {
                            D_801072D4_ovl_DA4570 = 0;
                            D_801072D0_ovl_DA4570 = 0x60;
                        } else {
                            D_801072D4_ovl_DA4570 = 1;
                            D_801072D0_ovl_DA4570 = 0xA6;
                        }
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_801054E8_ovl_DA4570);
                        func_8010089C_ovl_DA4570();
                    }
                    break;
                } else {
                    timer++;
                    if (blink == 0) {
                        D_801072D0_ovl_DA4570 = (D_801072D4_ovl_DA4570 != 0) ? 0xA6 : 0x60;
                        D_801072D2_ovl_DA4570 = 0xA2;
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_801054E8_ovl_DA4570);
                        if (D_80105660_ovl_DA4570 & 1) {
                            func_8010089C_ovl_DA4570();
                        }
                    }
                    ret = osPfsRepairId(&pfs);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 6;
                        sub = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                        sub = 0;
                    } else if (timer >= 181) {
                        D_801072C8_ovl_DA4570 = 10;
                        sub = 0;
                    }
                }
                break;
            case 6:
                if (sub == 0) {
                    sub++;
                    timer = 0;
                    blink = 0;
                } else {
                    timer++;
                    if (blink == 0) {
                        D_801072D0_ovl_DA4570 = (D_801072D4_ovl_DA4570 != 0) ? 0xA6 : 0x60;
                        D_801072D2_ovl_DA4570 = 0xA2;
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_801054E8_ovl_DA4570);
                        if (D_80105660_ovl_DA4570 & 1) {
                            func_8010089C_ovl_DA4570();
                        }
                    }
                    ret = func_8003D0F0(mq, &pfs, D_80092C80);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 0;
                        sub = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                        sub = 0;
                    } else if (timer >= 181) {
                        D_801072C8_ovl_DA4570 = 10;
                        sub = 0;
                    }
                }
                break;
            case 7:
                if (sub == 0) {
                    D_801072D0_ovl_DA4570 = 0x88;
                    sub++;
                    D_801072D2_ovl_DA4570 = 0xA2;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_801054B0_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                } else if (sub == 1) {
                    if (btn & 0x8000) {
                        sub++;
                    }
                } else {
                    ret = func_8003D0F0(mq, &pfs, D_80092C80);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 0;
                        sub = 0;
                    } else if (ret == 10) {
                        D_801072C8_ovl_DA4570 = 5;
                        sub = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                        sub = 0;
                    }
                }
                break;
            case 8:
                if (sub == 0) {
                    count = D_801072D8_ovl_DA4570 = 0; sub++;
                    for (i = 0; i < 16; i++) {
                        D_80107288_ovl_DA4570[i] = -1;
                    }
                    if (D_801072D4_ovl_DA4570 != 0) {
                        D_801072D0_ovl_DA4570 = 0xA6;
                    } else {
                        D_801072D0_ovl_DA4570 = 0x60;
                    }
                    D_801072D2_ovl_DA4570 = 0xA2;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_80105448_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                } else if (sub == 1) {
                    if (btn & 0x8000) {
                        sub++;
                        timer = 0;
                    } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                        if (btn & 2) {
                            D_801072D4_ovl_DA4570 = 0;
                            D_801072D0_ovl_DA4570 = 0x60;
                        } else {
                            D_801072D4_ovl_DA4570 = 1;
                            D_801072D0_ovl_DA4570 = 0xA6;
                        }
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_80105448_ovl_DA4570);
                        func_8010089C_ovl_DA4570();
                    }
                } else if (sub == 2) {
                    if (D_801072D4_ovl_DA4570 == 0) {
                        if (blink == 0) {
                            func_80100944_ovl_DA4570();
                            func_801008F0_ovl_DA4570(D_80105448_ovl_DA4570);
                            if (D_80105660_ovl_DA4570 & 1) {
                                func_8010089C_ovl_DA4570();
                            }
                        }
                        ret = func_8003D0F0(mq, &pfs, D_80092C80);
                        if (ret == 0) {
                            D_801072C8_ovl_DA4570 = 0;
                            sub = 0;
                        } else if (ret == 10) {
                            D_801072C8_ovl_DA4570 = 5;
                            sub = 0;
                        }
                        if (++timer >= 181) {
                            sub = 0;
                        }
                    } else {
                        return 3;
                    }
                }
                break;
            case 9:
                if (sub == 0) {
                    sub++;
                    if (D_801072D4_ovl_DA4570 != 0) {
                        D_801072D0_ovl_DA4570 = 0xA6;
                    } else {
                        D_801072D0_ovl_DA4570 = 0x60;
                    }
                    D_801072D2_ovl_DA4570 = 0xA2;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_80105578_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                } else if (sub == 1) {
                    if (btn & 0x8000) {
                        sub++;
                    } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                        if (btn & 2) {
                            D_801072D4_ovl_DA4570 = 0;
                            D_801072D0_ovl_DA4570 = 0x60;
                        } else {
                            D_801072D4_ovl_DA4570 = 1;
                            D_801072D0_ovl_DA4570 = 0xA6;
                        }
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_80105578_ovl_DA4570);
                        func_8010089C_ovl_DA4570();
                    }
                } else if (D_801072D4_ovl_DA4570 == 0) {
                    ret = func_8003D0F0(mq, &pfs, D_80092C80);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 0;
                        sub = 0;
                    } else if (ret == 10) {
                        D_801072C8_ovl_DA4570 = 5;
                        sub = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                        sub = 0;
                    }
                } else {
                    return 3;
                }
                break;
            case 10:
                if (sub == 0) {
                    sub++;
                    if (D_801072D4_ovl_DA4570 != 0) {
                        D_801072D0_ovl_DA4570 = 0xA6;
                    } else {
                        D_801072D0_ovl_DA4570 = 0x60;
                    }
                    D_801072D2_ovl_DA4570 = 0xA2;
                    func_80100944_ovl_DA4570();
                    func_801008F0_ovl_DA4570(D_80105608_ovl_DA4570);
                    func_8010089C_ovl_DA4570();
                } else if (sub == 1) {
                    if (btn & 0x8000) {
                        sub++;
                    } else if (((btn & 2) && (D_801072D4_ovl_DA4570 != 0)) || ((btn & 1) && (D_801072D4_ovl_DA4570 == 0))) {
                        if (btn & 2) {
                            D_801072D4_ovl_DA4570 = 0;
                            D_801072D0_ovl_DA4570 = 0x60;
                        } else {
                            D_801072D4_ovl_DA4570 = 1;
                            D_801072D0_ovl_DA4570 = 0xA6;
                        }
                        func_80100944_ovl_DA4570();
                        func_801008F0_ovl_DA4570(D_80105608_ovl_DA4570);
                        func_8010089C_ovl_DA4570();
                    }
                } else if (D_801072D4_ovl_DA4570 == 0) {
                    ret = func_8003D0F0(mq, &pfs, D_80092C80);
                    if (ret == 0) {
                        D_801072C8_ovl_DA4570 = 0;
                        sub = 0;
                    } else if (ret == 10) {
                        D_801072C8_ovl_DA4570 = 5;
                        sub = 0;
                    } else if (ret == 1) {
                        D_801072C8_ovl_DA4570 = 8;
                        sub = 0;
                    }
                } else {
                    return 3;
                }
                break;
        }
        if ((D_801072C8_ovl_DA4570 != 0) && (D_801072C8_ovl_DA4570 < 5)) {
            osContStartQuery(mq);
            osRecvMesg(mq, &D_801072EC_ovl_DA4570, 1);
            osContGetQuery(D_80092EA0);
            if (D_80092EA0[D_80092C80].status & 2) {
                D_801072C8_ovl_DA4570 = 8;
                sub = 0;
            }
        }
        blink++;
        if (blink >= 20) {
            blink = 0;
        }
        osContStartReadData(mq);
        func_8010055C_ovl_DA4570();
        osRecvMesg(mq, &D_801072EC_ovl_DA4570, 1);
        unused3 = pads[D_80092C80].stick_y;
        dir = (((unused3 < 33) ^ 1) << 3) | ((pads[D_80092C80].stick_x < 33) ^ 1); dir |= ((unused3 < -32) << 2); dir |= ((pads[D_80092C80].stick_x < -32) << 1);
        btn = pads[D_80092C80].button | dir;
        osContGetReadData(pads);
        unused3 = pads[D_80092C80].stick_y;
        dir = (((unused3 < 33) ^ 1) << 3) | ((pads[D_80092C80].stick_x < 33) ^ 1); dir |= ((unused3 < -32) << 2); dir |= ((pads[D_80092C80].stick_x < -32) << 1);
        cur = pads[D_80092C80].button | dir;
        held = cur & btn;
        if (held) {
            repeat++;
            if (((repeat >> 5) == 0) || (repeat & 7)) {
                held = 0;
            }
        } else {
            repeat = 0;
        }
        btn = cur & (cur ^ btn);
        if (btn) {
            held = btn;
            repeat = 0;
        }
    }
}
