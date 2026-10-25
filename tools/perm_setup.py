#!/usr/bin/env python3
"""Set up a decomp-permuter run for one function, KF4 style.

    tools/perm_setup.py src/3F50.c func_800073E8 [--out DIR]
    tools/perm_run.sh DIR [jobs]          (default 2 jobs, nice 19)

The function must already be C in the file (a non-matching draft is fine; leave its
GLOBAL_ASM pragma out). This writes DIR (default ~/eltale-perm/<func>) with:
  base.c      the file, preprocessed, other GLOBAL_ASM pragmas dropped
  compile.sh  IDO with exactly this file's flags from configure.py
  target.o    the retail asm of the function, assembled
  settings.toml
To permute only part of the function, put  /* PERM_START */ ... /* PERM_END */
around the statements in the source first; they become PERM_RANDOMIZE( ... ).
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
import configure  # noqa: E402  (flags_for, IDO, INCLUDES, DEFINES, WARNINGS, AS)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--out")
    a = ap.parse_args()
    src = Path(a.src).resolve().relative_to(ROOT)
    out = Path(a.out) if a.out else Path.home() / "eltale-perm" / a.func
    out.mkdir(parents=True, exist_ok=True)

    asm = next((p for d in ("nonmatchings", "matchings")
                for p in (ROOT / "asm" / d).rglob(a.func + ".s")), None)
    if asm is None:
        sys.exit(f"no asm for {a.func} (run ./build.sh first)")

    text = (ROOT / src).read_text(encoding="utf-8")
    if re.search(r'GLOBAL_ASM\("[^"]*/' + re.escape(a.func) + r'\.s"\)', text):
        sys.exit(f"{a.func} is still a GLOBAL_ASM pragma in {src}; write a C draft first")
    text = re.sub(r'^#pragma GLOBAL_ASM\([^)]*\)\s*$', '', text, flags=re.M)
    text = text.replace("/* PERM_START */", "PERM_RANDOMIZE(").replace("/* PERM_END */", ")")
    (out / "src.c").write_text(text, encoding="utf-8")

    inc = " ".join(f"-I{ROOT / p[2:]}" for p in configure.INCLUDES.split())
    flags = configure.flags_for(str(src))
    cc = ROOT / configure.IDO
    pre = subprocess.run(f"cpp -P -nostdinc {inc} -I{(ROOT / src).parent} {configure.DEFINES} -D__sgi -D_MIPS_SZLONG=32 {out / 'src.c'}",
                         shell=True, capture_output=True, text=True)
    if pre.returncode:
        sys.exit("cpp failed:\n" + pre.stderr[-2000:])
    (out / "base.c").write_text(pre.stdout, encoding="utf-8")

    (out / "compile.sh").write_text(f"""#!/bin/bash
# permuter calls: compile.sh input.c -o output.o
{cc} -c -G 0 {configure.WARNINGS} {configure.DEFINES} {flags} -o "$3" "$1" 2>/dev/null
""")
    (out / "compile.sh").chmod(0o755)

    prelude = '.include "macro.inc"\n.set noat\n.set noreorder\n.set gp=64\n.section .text\n'
    (out / "target.s").write_text(prelude + asm.read_text(encoding="utf-8"))
    r = subprocess.run(f"{configure.AS} -I{ROOT / 'include'} -o {out / 'target.o'} {out / 'target.s'}",
                       shell=True, capture_output=True, text=True)
    if r.returncode:
        sys.exit("assembling the target failed:\n" + r.stderr[-2000:])
    (out / "settings.toml").write_text(f'func_name = "{a.func}"\ncompiler_type = "ido"\n')

    r = subprocess.run(["bash", str(out / "compile.sh"), str(out / "base.c"), "-o", str(out / "base.o")])
    print(f"{out}: flags {flags}; base compiles: {'yes' if r.returncode == 0 else 'NO'}")
    print(f"run: tools/perm_run.sh {out} [jobs]")


if __name__ == "__main__":
    main()
