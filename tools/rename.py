#!/usr/bin/env python3
"""Apply the name tables in names/*.tsv to the source tree.

    tools/rename.py            apply every table (already-applied rows are skipped)
    tools/rename.py --check    apply in a temporary worktree of HEAD, build it from
                               scratch, and report; the checkout is left untouched

A table row is:  old<TAB>new<TAB>evidence   (lines starting with # are comments)
  old       func_XXXXXXXX / func_XXXXXXXX_ovl_name / D_XXXXXXXX (_ovl_name)
  new       the name
  evidence  one line: why (the code, a caller, a string, a cited outside source)

Applying a row adds `new = 0xADDR; // type:func [segment:ovl_name]` to symbol_addrs.txt
(that is what makes splat use the name in asm/) and replaces `old` as a whole word in
src/, include/ (not include/ultra64), undefined_syms.txt and the src/nonmatching records
(renaming a record file with it).
"""
import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OLD_RE = re.compile(r'^(func|D)_([0-9A-F]{8})(?:_(ovl_\w+))?$')
IDENT = re.compile(r'^[A-Za-z_]\w*$')


def load_rows(root: Path):
    rows = []
    for f in sorted((root / "names").glob("*.tsv")):
        for n, ln in enumerate(f.read_text(encoding="utf-8").splitlines(), 1):
            if not ln.strip() or ln.startswith("#"):
                continue
            parts = ln.split("\t")
            if len(parts) < 3 or not parts[2].strip():
                sys.exit(f"{f.name}:{n}: need old<TAB>new<TAB>evidence")
            rows.append((f.name, n, parts[0].strip(), parts[1].strip()))
    return rows


def text_files(root: Path):
    for p in (root / "src").rglob("*"):
        if p.suffix in (".c", ".h", ".md") and p.is_file():
            yield p
    for p in (root / "include").rglob("*.h"):
        if "ultra64" not in p.parts:
            yield p
    yield root / "undefined_syms.txt"


def apply(root: Path) -> int:
    rows = load_rows(root)
    errors = []
    seen_old, seen_new = {}, {}
    for f, n, old, new in rows:
        where = f"{f}:{n}"
        if not OLD_RE.match(old):
            errors.append(f"{where}: '{old}' is not a func_/D_ name")
        if not IDENT.match(new) or OLD_RE.match(new):
            errors.append(f"{where}: '{new}' is not a usable name")
        if old in seen_old:
            errors.append(f"{where}: '{old}' is also named in {seen_old[old]}")
        if new in seen_new:
            errors.append(f"{where}: '{new}' is also used in {seen_new[new]}")
        seen_old[old], seen_new[new] = where, where
    if errors:
        sys.exit("\n".join(errors))

    sym_path = root / "symbol_addrs.txt"
    syms = sym_path.read_text(encoding="utf-8")
    defined = set(re.findall(r'^(\w+)\s*=', syms, re.M))
    files = {p: p.read_text(encoding="utf-8", errors="surrogateescape") for p in text_files(root)}
    every = "\n".join(files.values())
    todo = []
    for f, n, old, new in rows:
        if new in defined:
            continue  # applied earlier
        if new in re.findall(r'\b' + re.escape(new) + r'\b', every):
            sys.exit(f"{f}:{n}: '{new}' already exists in the source")
        todo.append((old, new))
    if not todo:
        print("rename: nothing to apply")
        return 0

    add = []
    for old, new in todo:
        kind, addr, seg = OLD_RE.match(old).groups()
        line = f"{new} = 0x{addr};"
        attrs = (["type:func"] if kind == "func" else []) + ([f"segment:{seg}"] if seg else [])
        if attrs:
            line += " // " + " ".join(attrs)
        add.append(line)
    if "// Game names (tools/rename.py from names/*.tsv)" not in syms:
        syms = syms.rstrip("\n") + "\n\n// Game names (tools/rename.py from names/*.tsv)\n"
    sym_path.write_text(syms + "\n".join(add) + "\n", encoding="utf-8")

    pat = re.compile(r'\b(' + "|".join(re.escape(o) for o, _ in todo) + r')\b')
    table = dict(todo)
    changed = 0
    for p, t in files.items():
        nt = pat.sub(lambda m: table[m.group(1)], t)
        if nt != t:
            p.write_text(nt, encoding="utf-8", errors="surrogateescape")
            changed += 1
    for p in list((root / "src" / "nonmatching").glob("*")):
        stem = p.name.split(".")[0]
        if stem in table:
            p.rename(p.with_name(table[stem] + p.name[len(stem):]))
    print(f"rename: applied {len(todo)} names, {changed} files changed")
    return len(todo)


def check():
    tmp = Path(tempfile.mkdtemp(prefix="rename_check_"))
    wt = tmp / "wt"
    subprocess.run(["git", "worktree", "add", "-q", "--detach", str(wt), "HEAD"], cwd=ROOT, check=True)
    try:
        for t in ("tools/ido_5.3", "tools/asm-processor", "tools/asm-differ", "tools/decomp-permuter",
                  "tools/m2c", "tools/ultralib", ".venv", "baserom.jp.z64"):
            if not (wt / t).exists():
                (wt / t).symlink_to((ROOT / t).resolve())
        apply(wt)
        r = subprocess.run(["bash", "-c", "./build.sh 2>&1 | tail -15"], cwd=wt, capture_output=True, text=True)
        print(r.stdout.strip())
        ok = "matches retail" in r.stdout
        if ok:
            r = subprocess.run(["bash", "-c", "NON_MATCHING=1 ./build.sh 2>&1 | tail -15"], cwd=wt,
                               capture_output=True, text=True)
            print(r.stdout.strip())
            ok = "built NON_MATCHING" in r.stdout
        print("rename --check:", "OK" if ok else "FAILED")
        return ok
    finally:
        subprocess.run(["git", "worktree", "remove", "--force", str(wt)], cwd=ROOT)
        shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    if a.check:
        sys.exit(0 if check() else 1)
    apply(ROOT)
