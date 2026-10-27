#!/usr/bin/env python3
"""Bring the source in line with the name tables in names/*.tsv.

    tools/rename.py            sync the tree with every table
    tools/rename.py --check    sync a temporary worktree of HEAD, build it from scratch
                               (retail and NON_MATCHING), and report; the checkout is untouched

A table row is:  old<TAB>new<TAB>evidence   (lines starting with # are comments)
  old       func_XXXXXXXX / func_XXXXXXXX_ovl_name / D_XXXXXXXX (_ovl_name)
  new       the name
  evidence  one line: why (the code, a caller, a string, a cited outside source)

The tables are the truth. A sync compares them with the game section of symbol_addrs.txt
(what was applied before) and, for every symbol whose name differs, replaces the current
name with the wanted one as a whole word in src/, include/ (not include/ultra64),
undefined_syms.txt, assets.yaml and the src/nonmatching records (renaming record files too). So:
  - a new row names a func_/D_ symbol;
  - editing a row's `new` renames it again;
  - deleting a row (or commenting it out) turns the name back into func_/D_.
Then the game section of symbol_addrs.txt is rewritten from the tables (that is what makes
splat use the names in asm/).
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
SECTION = "// Game names (tools/rename.py from names/*.tsv)"
SYM_LINE = re.compile(r'^(\w+) = 0x([0-9A-Fa-f]{8});(?: // (.*))?$')


def load_rows(root: Path):
    rows = []
    for f in sorted((root / "names").glob("*.tsv")):
        for n, ln in enumerate(f.read_text(encoding="utf-8").splitlines(), 1):
            if not ln.strip() or ln.startswith("#"):
                continue
            parts = ln.split("\t")
            if len(parts) < 3 or not parts[2].strip():
                sys.exit(f"{f.name}:{n}: need old<TAB>new<TAB>evidence")
            rows.append((f"{f.name}:{n}", parts[0].strip(), parts[1].strip()))
    return rows


def text_files(root: Path):
    for p in (root / "src").rglob("*"):
        if p.suffix in (".c", ".h", ".md") and p.is_file():
            yield p
    for p in (root / "include").rglob("*.h"):
        if "ultra64" not in p.parts:
            yield p
    yield root / "undefined_syms.txt"
    yield root / "assets.yaml"


def sym_line(old: str, new: str) -> str:
    kind, addr, seg = OLD_RE.match(old).groups()
    attrs = (["type:func"] if kind == "func" else []) + ([f"segment:{seg}"] if seg else [])
    return f"{new} = 0x{addr};" + (" // " + " ".join(attrs) if attrs else "")


def applied(section: str):
    """old (func_/D_ form) -> name, from the game section of symbol_addrs.txt."""
    out = {}
    for ln in section.splitlines():
        m = SYM_LINE.match(ln.strip())
        if not m:
            continue
        name, addr, attrs = m.group(1), m.group(2).upper(), (m.group(3) or "").split()
        kind = "func" if "type:func" in attrs else "D"
        seg = next((a.split(":", 1)[1] for a in attrs if a.startswith("segment:")), None)
        out[f"{kind}_{addr}" + (f"_{seg}" if seg else "")] = name
    return out


def apply(root: Path) -> int:
    rows = load_rows(root)
    errors, want, seen_new = [], {}, {}
    for where, old, new in rows:
        if not OLD_RE.match(old):
            errors.append(f"{where}: '{old}' is not a func_/D_ name")
        if not IDENT.match(new) or OLD_RE.match(new):
            errors.append(f"{where}: '{new}' is not a usable name")
        if old in want:
            errors.append(f"{where}: '{old}' is named twice")
        if new in seen_new:
            errors.append(f"{where}: '{new}' is also used in {seen_new[new]}")
        want[old], seen_new[new] = new, where
    if errors:
        sys.exit("\n".join(errors))

    sym_path = root / "symbol_addrs.txt"
    syms = sym_path.read_text(encoding="utf-8")
    head, _, section = syms.partition(SECTION)
    have = applied(section)

    table = {}  # current name in the source -> wanted name
    for old in set(want) | set(have):
        cur, new = have.get(old, old), want.get(old, old)
        if cur != new:
            table[cur] = new
    files = {p: p.read_text(encoding="utf-8", errors="surrogateescape") for p in text_files(root)}

    if table:
        every = "\n".join(files.values())
        moving = set(table)
        for cur, new in table.items():
            if new not in moving and re.search(r'\b' + re.escape(new) + r'\b', every):
                sys.exit(f"rename: '{new}' (for '{cur}') already exists in the source")
        pat = re.compile(r'\b(' + "|".join(re.escape(c) for c in sorted(table, key=len, reverse=True)) + r')\b')
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

    lines = [sym_line(old, new) for old, new in want.items()]
    order = {old: i for i, (_, old, _) in enumerate(rows)}
    lines = [sym_line(old, want[old]) for old in sorted(want, key=order.get)]
    new_syms = head.rstrip("\n") + "\n\n" + SECTION + "\n" + "\n".join(lines) + "\n"
    if new_syms != syms:
        sym_path.write_text(new_syms, encoding="utf-8")
    if not table:
        print("rename: nothing to apply")
        return 0
    named = sum(1 for c, n in table.items() if not OLD_RE.match(n) and OLD_RE.match(c))
    reverted = sum(1 for n in table.values() if OLD_RE.match(n))
    print(f"rename: {named} named, {len(table) - named - reverted} renamed, {reverted} reverted to func_/D_; "
          f"{changed} files changed")
    return len(table)


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
