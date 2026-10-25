#!/usr/bin/env python3
"""Count functions in C against functions still in asm, by area."""
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LINE = re.compile(r'/\* ([0-9A-F]+) ([0-9A-F]+) ([0-9A-F]{8}) \*/')


def area(path):
    p = str(path)
    if "/libultra/" in p or "/libc/" in p:
        return "libultra"
    if "/ovl_" in p:
        return "overlays"
    return "game"


def main():
    still_asm = set()
    for c in (ROOT / "src").rglob("*.c"):
        still_asm.update(re.findall(r'GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', c.read_text(encoding="utf-8", errors="replace")))
    tot = defaultdict(lambda: [0, 0, 0, 0])  # funcs, bytes, done funcs, done bytes
    files = list((ROOT / "asm" / "nonmatchings").rglob("*.s")) + list((ROOT / "asm" / "matchings").rglob("*.s"))
    for s in files:
        text = s.read_text(encoding="utf-8", errors="replace")
        if "glabel" not in text:
            continue
        size = 4 * len(LINE.findall(text))
        a = area(str(s.relative_to(ROOT)))
        t = tot[a]
        t[0] += 1
        t[1] += size
        if s.stem not in still_asm:
            t[2] += 1
            t[3] += size
    allt = [sum(v[i] for v in tot.values()) for i in range(4)]
    for name, t in sorted(tot.items()) + [("total", allt)]:
        print(f"{name:9} {t[2]:4}/{t[0]:4} functions ({100 * t[2] / max(t[0], 1):5.1f}%)  "
              f"{t[3]:7}/{t[1]:7} bytes ({100 * t[3] / max(t[1], 1):5.1f}%)")


if __name__ == "__main__":
    main()
