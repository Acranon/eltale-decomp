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
    """name -> (ROM offset, size in bytes without trailing nops), from the split asm."""
    out = {}
    for p in (ROOT / "asm").rglob("*.s"):
        name = None
        for ln in p.open(encoding="utf-8", errors="replace"):
            if ln.startswith("glabel "):
                name = ln.split()[1]
                out[name] = [None, 0]
                continue
            if ln.startswith(("endlabel", ".section", "dlabel", "jlabel")):
                name = None
                continue
            m = LINE.search(ln) if name else None
            if m:
                rec = out[name]
                if rec[0] is None:
                    rec[0] = int(m.group(1), 16)
                if m.group(3) != "00000000":
                    rec[1] = int(m.group(1), 16) + 4 - rec[0]
    return {k: (v[0], v[1]) for k, v in out.items() if v[0] is not None}


def non_matching_build() -> bool:
    ninja = ROOT / "build.ninja"
    return ninja.exists() and "-DNON_MATCHING" in ninja.read_text()


def active_source(path: Path) -> str:
    """The file's text without the #ifdef NON_MATCHING branch the current build leaves out,
    so a function whose C is under NON_MATCHING counts as C in a NON_MATCHING=1 build."""
    nm = non_matching_build()
    out, stack = [], []  # per open #if: (is it NON_MATCHING, is its current branch skipped)
    for ln in path.read_text(encoding="utf-8", errors="replace").splitlines():
        s = ln.strip()
        outer = bool(stack) and stack[-1][1]
        if s.startswith("#if"):
            is_nm = s.split()[:2] == ["#ifdef", "NON_MATCHING"]
            stack.append((is_nm, outer or (is_nm and not nm)))
        elif s.startswith("#else") and stack:
            is_nm = stack[-1][0]
            parent = len(stack) > 1 and stack[-2][1]
            stack[-1] = (is_nm, parent or (is_nm and nm))
        elif s.startswith("#endif") and stack:
            stack.pop()
        elif not outer:
            out.append(ln)
    return "\n".join(out)


def obj_path(src: Path) -> Path:
    return ROOT / "build" / src.with_suffix(".o")


def check(src: Path, funcs):
    src = src.resolve().relative_to(ROOT)
    obj = obj_path(src)
    r = subprocess.run(["ninja", str(obj.relative_to(ROOT))], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout[-3000:], r.stderr[-3000:])
        return False
    asm_included = set(re.findall(r'GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', active_source(ROOT / src)))
    ok = True
    with obj.open("rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        if text is None or text.data_size == 0:
            print("  (data-only file: no functions; ./build.sh checks its data)")
            return True
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
            rom, retail_size = funcs[name]
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
            # (retail_size comes from the function's own .s, without trailing nops)
            longer = retail_size > size
            # splat has no label for a function that follows another without padding (an
            # empty one, say), so its words sit in the previous .s: give it that address
            if longer and i + 1 < len(syms) and syms[i + 1][1] not in funcs:
                nxt_off = syms[i + 1][0]
                funcs[syms[i + 1][1]] = (rom + nxt_off - off, retail_size - (nxt_off - off))
                longer = False  # the rest is checked as that next function
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
