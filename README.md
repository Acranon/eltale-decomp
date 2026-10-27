# Eltale Monsters decomp

A matching decompilation of **Eltale Monsters** (Japanese N64 release of Quest 64): C source
that compiles back to a byte-identical copy of the retail ROM.

- 874 of 896 functions match; the other 22 are written as equivalent C and documented in
  [src/nonmatching/](src/nonmatching/).
- Functions, data and struct fields are named from what the code does. The source is organised
  by subsystem under `src/game/` and `src/overlays/`, with one header per module.

This repository contains no game data. You need your own copy of the game to build it.

## Building

Linux or WSL. You need:

- Python 3, `ninja`, binutils for MIPS (`mips-linux-gnu-as`/`ld`; Debian/Ubuntu `binutils-mips-linux-gnu`)
- [IDO 5.3 static recomp](https://github.com/decompals/ido-static-recomp) in `tools/ido_5.3/`
- [asm-processor](https://github.com/simonlindholm/asm-processor) in `tools/asm-processor/`
- Python packages in `.venv`: `splat64`, `spimdisasm`, `rabbitizer`, `crunch64`, `n64img`,
  `ninja_syntax`, `PyYAML`

Then put your ROM at `baserom.jp.z64` (big-endian `.z64` byte order; SHA-1
`50ea6c3d4de4b68b3c9b77524d8177066b9f36e7`) and run:

    ./build.sh                    # split the ROM, build, and compare with retail
    NON_MATCHING=1 ./build.sh     # build the C of the 22 unmatched functions instead of their asm

Images, palettes and fonts are extracted from your ROM at build time (`assets.yaml`).

## License

[CC0 1.0](LICENSE): no rights reserved. This covers the contents of this repository only. Eltale
Monsters and its code and assets belong to their owners; nothing from the game is included. The
tools listed above keep their own licenses.
