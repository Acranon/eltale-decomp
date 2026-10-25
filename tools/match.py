#!/usr/bin/env python3
"""Check the C functions of one or more source files against the retail ROM.

    tools/match.py diff src/1870.c [src/...]   compile, then compare every C function
    tools/match.py func func_80001234          show one function's diff (asm-differ)

The compare works on the compiled object, so it doesn't need a link and it isn't
thrown off by other functions that don't match yet. Relocated fields (jal targets,
%hi/%lo halves) are masked using the object's relocations, so a wrong symbol in
those fields isn't caught here; the full build (./build.sh) catches it, and data
placement too.
"""
import re
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parent.parent
ROM = (ROOT / "baserom.jp.z64").read_bytes()
LINE = re.compile(r'/\* ([0-9A-F]+) ([0-9A-F]+) ([0-9A-F]{8}) \*/')

R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 4, 5, 6


def retail_funcs():
    """name -> ROM offset, from the split asm."""
    out = {}
    for p in (ROOT / "asm").rglob("*.s"):
        name = None
        for ln in p.open(encoding="utf-8", errors="replace"):
            if ln.startswith("glabel "):
                name = ln.split()[1]
                continue
            if name:
                m = LINE.search(ln)
                if m:
                    out[name] = int(m.group(1), 16)
                    name = None
    return out


def obj_path(src: Path) -> Path:
    return ROOT / "build" / src.with_suffix(".o")


def check(src: Path, funcs):
    src = src.resolve().relative_to(ROOT)
    obj = obj_path(src)
    r = subprocess.run(["ninja", str(obj.relative_to(ROOT))], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout[-3000:], r.stderr[-3000:])
        return False
    asm_included = set(re.findall(r'GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', (ROOT / src).read_text(encoding="utf-8", errors="replace")))
    ok = True
    with obj.open("rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        data = text.data()
        masks = {}
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name in (".rel.text", ".rela.text"):
                for rel in sec.iter_relocations():
                    t = rel["r_info_type"]
                    masks[rel["r_offset"]] = 0x03FFFFFF if t == R_MIPS_26 else 0xFFFF if t in (R_MIPS_HI16, R_MIPS_LO16) else 0
        symtab = elf.get_section_by_name(".symtab")
        syms = sorted((s["st_value"], s.name, s["st_size"]) for s in symtab.iter_symbols()
                      if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == elf.get_section_index(".text"))
        n_c = 0
        for i, (off, name, size) in enumerate(syms):
            if name in asm_included:
                continue
            n_c += 1
            end = syms[i + 1][0] if i + 1 < len(syms) else len(data)
            if size == 0:
                size = end - off
            if name not in funcs:
                print(f"  {name}: no retail address (renamed? add it to symbol_addrs.txt)")
                ok = False
                continue
            rom = funcs[name]
            ndiff = 0
            first = None
            for k in range(0, size, 4):
                a = int.from_bytes(data[off + k:off + k + 4], "big")
                b = int.from_bytes(ROM[rom + k:rom + k + 4], "big")
                m = ~masks.get(off + k, 0) & 0xFFFFFFFF
                if (a & m) != (b & m):
                    ndiff += 1
                    if first is None:
                        first = k
            # the retail function must not be longer either
            nxt = sorted(v for v in funcs.values() if v > rom)
            retail_size = (nxt[0] - rom) if nxt else size
            tail = ROM[rom + size:rom + retail_size]
            longer = any(tail[j:j + 4] != b"\0\0\0\0" for j in range(0, len(tail), 4))
            if ndiff == 0 and not longer:
                print(f"  {name}: OK")
            else:
                ok = False
                why = f"{ndiff} words differ, first at +0x{first:X}" if ndiff else ""
                if longer:
                    why += (", " if why else "") + f"retail is longer (0x{retail_size:X} vs 0x{size:X})"
                print(f"  {name}: DIFF ({why})")
        if n_c == 0:
            print("  (no C functions)")
    return ok


def main():
    if len(sys.argv) < 3 or sys.argv[1] not in ("diff", "func"):
        print(__doc__)
        sys.exit(2)
    if sys.argv[1] == "func":
        sys.exit(subprocess.call([sys.executable, "tools/asm-differ/diff.py", "-m", sys.argv[2]] + sys.argv[3:], cwd=ROOT))
    funcs = retail_funcs()
    ok = True
    for s in sys.argv[2:]:
        print(s)
        ok &= check(Path(s), funcs)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
