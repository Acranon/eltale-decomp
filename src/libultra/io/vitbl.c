#include "PR/os.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"
#ifndef VI_CTRL_ANTIALIAS_MODE_0 /* not in our rcp.h: ultralib J values */
#define VI_CTRL_ANTIALIAS_MODE_0 0x00000
#define VI_CTRL_ANTIALIAS_MODE_1 0x00100
#define VI_CTRL_ANTIALIAS_MODE_2 0x00200
#define VI_CTRL_ANTIALIAS_MODE_3 0x00300
#define VI_CTRL_PIXEL_ADV_3 0x03000
#endif

/* osViModeTable (J, 56 modes): .data 8006CD50..8006DED0, a data-only file.
 * Our os_vi.h predates the FPAL modes; ultralib J numbers them 42..55. */
#ifndef OS_VI_FPAL_LPN1
#define OS_VI_FPAL_LPN1 42
#define OS_VI_FPAL_LPF1 43
#define OS_VI_FPAL_LAN1 44
#define OS_VI_FPAL_LAF1 45
#define OS_VI_FPAL_LPN2 46
#define OS_VI_FPAL_LPF2 47
#define OS_VI_FPAL_LAN2 48
#define OS_VI_FPAL_LAF2 49
#define OS_VI_FPAL_HPN1 50
#define OS_VI_FPAL_HPF1 51
#define OS_VI_FPAL_HAN1 52
#define OS_VI_FPAL_HAF1 53
#define OS_VI_FPAL_HPN2 54
#define OS_VI_FPAL_HPF2 55
#endif

OSViMode osViModeTable[] = {
    { OS_VI_NTSC_LPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(525),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(525),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(57, 34, 5, 62),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3093, 0),                                     // hSync
          LEAP(3093, 3093),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(525),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LAN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_0 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(525),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_LAF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(57, 34, 5, 62),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3093, 0),                                     // hSync
          LEAP(3093, 3093),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),                                        // width
          BURST(57, 34, 5, 62),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3093, 0),                                     // hSync
          LEAP(3093, 3093),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),                                         // width
          BURST(57, 34, 5, 62),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3093, 0),                                     // hSync
          LEAP(3093, 3093),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(5120),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_NTSC_HPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(57, 34, 5, 62),    // burst
          VSYNC(524),              // vSync
          HSYNC(3093, 0),          // hSync
          LEAP(3093, 3093),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(5120),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_PAL_LPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_PAL_LPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0.25),      // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),          // origin
            SCALE(1, 0.75),       // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_LAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_PAL_LAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0.25),      // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),          // origin
            SCALE(1, 0.75),       // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_LPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_PAL_LPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0.25),      // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),         // origin
            SCALE(1, 0.75),       // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_LAN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_0 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(95, 569),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_PAL_LAF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0.25),      // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),         // origin
            SCALE(1, 0.75),       // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(1, 0),          // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),                                        // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(1, 0),          // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),        // origin
            SCALE(1, 0),         // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(5120),         // origin
            SCALE(1, 0),          // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_PAL_HPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(93, 567),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(5120),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(95, 569),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_MPAL_LPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(525),              // vSync
          HSYNC(3089, 4),          // hSync
          LEAP(3097, 3098),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(525),              // vSync
          HSYNC(3089, 4),          // hSync
          LEAP(3097, 3098),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(57, 30, 5, 70),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3088, 0),                                     // hSync
          LEAP(3100, 3100),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),        // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(640),        // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(525),              // vSync
          HSYNC(3089, 4),          // hSync
          LEAP(3097, 3098),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LAN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_0 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(525),              // vSync
          HSYNC(3089, 4),          // hSync
          LEAP(3097, 3098),        // leap
          HSTART(108, 748),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_LAF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(57, 30, 5, 70),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3088, 0),                                     // hSync
          LEAP(3100, 3100),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0.25),     // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(1280),       // origin
            SCALE(1, 0.75),     // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),                                        // width
          BURST(57, 30, 5, 70),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3088, 0),                                     // hSync
          LEAP(3100, 3100),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),                                         // width
          BURST(57, 30, 5, 70),                               // burst
          VSYNC(524),                                         // vSync
          HSYNC(3088, 0),                                     // hSync
          LEAP(3100, 3100),                                   // leap
          HSTART(108, 748),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            //[0]
            ORIGIN(1280),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            //[1]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),       // origin
            SCALE(1, 0),        // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(5120),       // origin
            SCALE(1, 0),        // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
    { OS_VI_MPAL_HPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(57, 30, 5, 70),    // burst
          VSYNC(524),              // vSync
          HSYNC(3088, 0),          // hSync
          LEAP(3100, 3100),        // leap
          HSTART(108, 748),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(35, 509),    // vStart
            BURST(2, 2, 11, 0), // vBurst
            VINTR(2),           // vIntr
        },
        {
            // [1]
            ORIGIN(5120),       // origin
            SCALE(0.5, 0.5),    // yScale
            HSTART(37, 511),    // vStart
            BURST(4, 2, 14, 0), // vBurst
            VINTR(2),           // vIntr
        } } },
#if BUILD_VERSION >= VERSION_J
    { OS_VI_FPAL_LPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_FPAL_LPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0.25),      // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),          // origin
            SCALE(1, 0.75),       // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_LAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),         // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_FPAL_LAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(640),         // origin
            SCALE(1, 0.25),      // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(640),          // origin
            SCALE(1, 0.75),       // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_LPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_FPAL_LPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0.25),      // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),         // origin
            SCALE(1, 0.75),       // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_LAN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_0 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(625),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(2, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(47, 617),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        } } },
    { OS_VI_FPAL_LAF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(320),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(2, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0.25),      // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(1280),         // origin
            SCALE(1, 0.75),       // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HPN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(1, 0),          // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HPF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HAN1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),                                        // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(1, 0),         // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(1, 0),          // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HAF1, // type
      {
          // comRegs
          VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON |
              VI_CTRL_ANTIALIAS_MODE_0 | VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),                                         // width
          BURST(58, 30, 4, 69),                               // burst
          VSYNC(624),                                         // vSync
          HSYNC(3177, 23),                                    // hSync
          LEAP(3183, 3181),                                   // leap
          HSTART(128, 768),                                   // hStart
          SCALE(1, 0),                                        // xScale
          VCURRENT(0),                                        // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(1280),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(2560),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HPN2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(1280),             // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),        // origin
            SCALE(1, 0),         // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(5120),         // origin
            SCALE(1, 0),          // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
    { OS_VI_FPAL_HPF2, // type
      {
          // comRegs
          VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 |
              VI_CTRL_PIXEL_ADV_3, // ctrl
          WIDTH(640),              // width
          BURST(58, 30, 4, 69),    // burst
          VSYNC(624),              // vSync
          HSYNC(3177, 23),         // hSync
          LEAP(3183, 3181),        // leap
          HSTART(128, 768),        // hStart
          SCALE(1, 0),             // xScale
          VCURRENT(0),             // vCurrent
      },
      { // fldRegs
        {
            // [0]
            ORIGIN(2560),        // origin
            SCALE(0.5, 0.5),     // yScale
            HSTART(45, 615),     // vStart
            BURST(107, 2, 9, 0), // vBurst
            VINTR(2),            // vIntr
        },
        {
            // [1]
            ORIGIN(5120),         // origin
            SCALE(0.5, 0.5),      // yScale
            HSTART(47, 617),      // vStart
            BURST(105, 2, 13, 0), // vBurst
            VINTR(2),             // vIntr
        } } },
#endif
};
