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
(big-endian elements). configure.py adds a ninja edge that runs this tool; a file
is only rewritten when its contents change (ninja restat).

Usage: extract_assets.py <manifest> <rom> <outdir>
"""

import re
import sys
from pathlib import Path

import yaml

TYPES = {"u8": 1, "u16": 2, "u32": 4}
PER_LINE = {"u8": 16, "u16": 8, "u32": 4}
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


def render(data, typ):
    width = TYPES[typ]
    words = [int.from_bytes(data[i:i + width], "big") for i in range(0, len(data), width)]
    fmt = f"0x{{:0{width * 2}X}},"
    n = PER_LINE[typ]
    lines = [" ".join(fmt.format(w) for w in words[i:i + n]) for i in range(0, len(words), n)]
    return "\n".join(lines) + "\n"


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    manifest, rom_path, outdir = sys.argv[1:]
    rom = Path(rom_path).read_bytes()
    for e in load_manifest(manifest):
        if e["rom"] + e["size"] > len(rom):
            sys.exit(f"{manifest}: {e['name']} runs past the end of {rom_path}")
        text = render(rom[e["rom"]:e["rom"] + e["size"]], e["type"])
        out = output_path(outdir, e)
        if out.exists() and out.read_text() == text:
            continue
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text)


if __name__ == "__main__":
    main()
