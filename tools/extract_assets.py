#!/usr/bin/env python3
"""Write C initializers for ROM assets listed in assets.yaml.

The repo holds no ROM content. Asset bytes (pixels, palettes, fonts, sound, text)
come from the user's baserom at build time: for each manifest entry this writes
build/assets/<name>.inc.c, a comma-separated initializer that C includes:

    u8 D_8010568C_ovl_DA4570[0x1980] = {
    #include "assets/D_8010568C_ovl_DA4570.inc.c"
    };

Manifest entry (assets.yaml):

    - { name: D_8010568C_ovl_DA4570, rom: 0xDA9BFC, size: 0x1980, type: u8 }

name: output name (the C symbol), rom: ROM offset, size: bytes, type: u8/u16/u32
(big-endian elements) or f32 (big-endian IEEE singles, written as float
literals checked to convert back to the same bits). configure.py adds a ninja edge
that runs this tool; a file is only rewritten when its contents change (ninja restat).

Usage: extract_assets.py <manifest> <rom> <outdir>
"""

import math
import re
import struct
import sys
from pathlib import Path

import yaml

TYPES = {"u8": 1, "u16": 2, "u32": 4, "f32": 4}
PER_LINE = {"u8": 16, "u16": 8, "u32": 4, "f32": 4}
NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def load_manifest(path):
    """Return the manifest's entries as dicts (name, rom, size, type), checked."""
    entries = yaml.safe_load(Path(path).read_text()) or []
    seen = set()
    for e in entries:
        for key in ("name", "rom", "size", "type"):
            if key not in e:
                sys.exit(f"{path}: entry {e} lacks '{key}'")
        if not NAME_RE.match(e["name"]):
            sys.exit(f"{path}: bad asset name {e['name']!r}")
        if e["name"] in seen:
            sys.exit(f"{path}: duplicate asset {e['name']}")
        seen.add(e["name"])
        if e["type"] not in TYPES:
            sys.exit(f"{path}: {e['name']}: type must be one of {', '.join(TYPES)}")
        width = TYPES[e["type"]]
        if e["size"] <= 0 or e["size"] % width or e["rom"] % width:
            sys.exit(f"{path}: {e['name']}: rom/size must be positive multiples of {width}")
    return entries


def output_path(outdir, entry):
    return Path(outdir) / f"{entry['name']}.inc.c"


def f32_literal(word):
    """A C float literal for the 32-bit pattern `word` that converts back to it exactly."""
    raw = word.to_bytes(4, "big")
    value = struct.unpack(">f", raw)[0]
    if not math.isfinite(value):
        raise ValueError(f"0x{word:08X} is not a finite float")
    text = f"{value:.9g}"
    if not any(c in text for c in ".e"):
        text += ".0"
    # 9 significant digits always identify a single; check it anyway.
    if struct.pack(">f", float(text)) != raw:
        raise ValueError(f"0x{word:08X}: {text} does not round-trip")
    return text + "f"


def render(data, typ):
    width = TYPES[typ]
    words = [int.from_bytes(data[i:i + width], "big") for i in range(0, len(data), width)]
    if typ == "f32":
        items = [f32_literal(w) + "," for w in words]
    else:
        fmt = f"0x{{:0{width * 2}X}},"
        items = [fmt.format(w) for w in words]
    n = PER_LINE[typ]
    lines = [" ".join(items[i:i + n]) for i in range(0, len(items), n)]
    return "\n".join(lines) + "\n"


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    manifest, rom_path, outdir = sys.argv[1:]
    rom = Path(rom_path).read_bytes()
    for e in load_manifest(manifest):
        if e["rom"] + e["size"] > len(rom):
            sys.exit(f"{manifest}: {e['name']} runs past the end of {rom_path}")
        try:
            text = render(rom[e["rom"]:e["rom"] + e["size"]], e["type"])
        except ValueError as err:
            sys.exit(f"{manifest}: {e['name']}: {err}")
        out = output_path(outdir, e)
        if out.exists() and out.read_text() == text:
            continue
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text)


if __name__ == "__main__":
    main()
