# Eltale Monsters decomp

A matching decompilation of **Eltale Monsters** (Japanese N64 release of Quest 64): C source
that compiles back to a byte-identical copy of the retail ROM.

- 874 of 896 functions match; the other 22 are written as equivalent C and documented in
  [src/nonmatching/](src/nonmatching/).
- Functions, data and struct fields are named from what the code does. The source is organised
  by subsystem under `src/game/` and `src/overlays/`, with one header per module.

This repository contains no game data. You need your own copy of the game to build it.

## Building

Linux or WSL (tested on Ubuntu 24.04):

    sudo apt install python3-venv ninja-build binutils-mips-linux-gnu git curl
    tools/setup.sh            # IDO 5.3 recomp, asm-processor, Python packages (.venv)
    tools/setup.sh --dev      # also asm-differ, m2c and decomp-permuter, for matching work

Then put your ROM at `baserom.jp.z64` (big-endian `.z64` byte order; SHA-1
`50ea6c3d4de4b68b3c9b77524d8177066b9f36e7`) and run:

    ./build.sh                    # split the ROM, build, and compare with retail
    NON_MATCHING=1 ./build.sh     # build the C of the 22 unmatched functions instead of their asm

Images, palettes and fonts are extracted from your ROM at build time (`assets.yaml`).

## License

[CC0 1.0](LICENSE): no rights reserved. This covers the contents of this repository only. Eltale
Monsters and its code and assets belong to their owners; nothing from the game is included. The
tools listed above keep their own licenses.
