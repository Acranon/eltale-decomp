#!/usr/bin/env python3
"""Write undefined_syms_auto.txt / undefined_funcs_auto.txt from the split asm.

A symbol is undefined when the asm references it by an address-style name
(D_80123456, func_80100000, D_DA4570, D_80100000_ovl_title) but no label in
asm/ defines it, e.g. ROM addresses, fixed RAM addresses and overlay bss.
splat's own lists miss these, so configure.py runs this after splitting.
"""
import re
from pathlib import Path

LABEL = re.compile(r'^\s*(?:glabel|dlabel|jlabel|alabel)\s+(\w+)', re.M)
REF = re.compile(r'\b((?:D|func|jtbl|L)_([0-9A-F]{3,8})(?:_\w+)?)\b')


def main():
    defined = set()
    refs = {}
    for p in Path("asm").rglob("*.s"):
        text = p.read_text(encoding="utf-8", errors="replace")
        defined.update(LABEL.findall(text))
        for line in text.splitlines():
            if line.lstrip().startswith(("glabel", "dlabel", "jlabel", "alabel", ".size", "endlabel", "nonmatching")):
                continue
            for name, addr in REF.findall(line):
                if name.startswith("L_"):
                    continue
                refs[name] = int(addr, 16)
    for line in Path("symbol_addrs.txt").read_text().splitlines():
        m = re.match(r'\s*(\w+)\s*=', line)
        if m:
            defined.add(m.group(1))
    funcs, syms = [], []
    for name, addr in sorted(refs.items(), key=lambda kv: kv[1]):
        if name in defined:
            continue
        (funcs if name.startswith("func_") else syms).append(f"{name} = 0x{addr:X};\n")
    Path("undefined_funcs_auto.txt").write_text("".join(funcs))
    Path("undefined_syms_auto.txt").write_text("".join(syms))


if __name__ == "__main__":
    main()
