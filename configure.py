#!/usr/bin/env python3
"""Split the ROM with splat and write build.ninja."""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

import ninja_syntax
import splat
import splat.scripts.split as split

sys.path.insert(0, str(Path(__file__).parent / "tools"))
import extract_assets  # noqa: E402

ROOT = Path(__file__).parent.resolve()
YAML_FILE = "eltale.jp.yaml"
BASENAME = "eltale"
LD_PATH = f"{BASENAME}.ld"
ELF_PATH = f"build/{BASENAME}.elf"
ROM_PATH = f"build/{BASENAME}.z64"
MAP_PATH = f"build/{BASENAME}.map"
ASSETS_MANIFEST = "assets.yaml"
ASSETS_DIR = "build/assets"

IDO = "tools/ido_5.3/cc"
CROSS = "mips-linux-gnu-"
AS = f"{CROSS}as -EB -mtune=vr4300 -march=vr4300 -mabi=32"
INCLUDES = "-I. -Iinclude -Iinclude/ultra64 -Iinclude/ultra64/PR -Isrc -Ibuild"
DEFINES = "-D_LANGUAGE_C -DF3DEX_GBI -DNDEBUG -D_FINALROM -DBUILD_VERSION=VERSION_J"
WARNINGS = "-fullwarn -verbose -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -woff 649,838,712,516,624"
ASM_PROC = "python3 tools/asm-processor/build.py --input-enc=utf-8 --output-enc=euc-jp"

# Flags by path prefix; the first match wins. Per-file entries go first.
# Confirm each entry on a matched function before relying on it.
FLAGS = [
    ("src/libultra/io/contreaddata.c", "-mips2 -O2"),
    ("src/libultra/io/vimgr.c", "-mips2 -O2"),
    ("src/libultra/io/pimgr.c", "-mips2 -O2"),
    ("src/libultra/io/gbpakinit.c", "-mips2 -O2"),
    ("src/libultra/io/pfsinitpak.c", "-mips2 -O2"),
    ("src/libultra/io/motor.c", "-mips2 -O2"),
    ("src/libultra/io/pfssearchfile.c", "-mips2 -O2"),
    ("src/libultra/io/contramwrite.c", "-mips2 -O2"),
    ("src/libultra/io/crc.c", "-mips2 -O2"),
    ("src/libultra/io/pfschecker.c", "-mips2 -O2"),
    ("src/libultra/io/contpfs.c", "-mips2 -O2"),
    ("src/libultra/io/contramread.c", "-mips2 -O2"),
    ("src/libultra/io/pfsselectbank.c", "-mips2 -O2"),
    ("src/libultra/io/pfsnumfiles.c", "-mips2 -O2"),
    ("src/libultra/io/pfsrepairid.c", "-mips2 -O2"),
    ("src/libultra/io/pfsreadwritefile.c", "-mips2 -O2"),
    ("src/libultra/io/pfsdeletefile.c", "-mips2 -O2"),
    ("src/libultra/io/pfsallocatefile.c", "-mips2 -O2"),
    ("src/libultra/io/pfsfreeblocks.c", "-mips2 -O2"),
    ("src/libultra/io/pfsfilestate.c", "-mips2 -O2"),
    ("src/libultra/io/pfsgetstatus.c", "-mips2 -O2"),
    ("src/libultra/io/viswapcontext.c", "-mips2 -O2"),
    ("src/libultra/io/aisetfreq.c", "-mips2 -O2"),
    ("src/libultra/io/sirawdma.c", "-mips2 -O2"),
    ("src/libultra/audio/", "-mips2 -O3"),
    ("src/libultra/gu/", "-mips2 -O3"),
    ("src/libultra/io/", "-mips2 -O1"),
    ("src/libultra/os/", "-mips2 -O1"),
    ("src/libultra/", "-mips2 -O1"),
    ("src/libc/ll.c", "-mips3 -32 -O1"),
    # libultra is 2.0I-era (osInitialize is between ultralib's I and J): like
    # ultralib's VERSION <= I rules, -O1 except gu/audio/libc at -O3 (ll.c -O1).
    ("src/libc/", "-mips2 -O3"),
    ("src/ovl_DA4570/", "-mips2 -O2 -g3"),
    ("src/ovl_", "-mips2 -O2"),
    ("src/", "-mips2 -O2 -g3"),
]
# Files whose object needs the o32 ABI bit set after compiling (-mips3 -32).
SET_O32 = {"src/libc/ll.c"}


def flags_for(path: str) -> str:
    for prefix, flags in FLAGS:
        if path.startswith(prefix):
            return flags
    return "-mips2 -O2"


def clean():
    for p in (".splache", "build.ninja", LD_PATH):
        Path(p).unlink(missing_ok=True)
    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("build", ignore_errors=True)


def write_permuter_settings():
    with open("permuter_settings.toml", "w") as f:
        f.write(f'''compiler_command = "{IDO} -c -G 0 {WARNINGS} {INCLUDES} {DEFINES} -mips2 -O2 -g3"
assembler_command = "{AS}"
compiler_type = "ido"

[preserve_macros]

[decompme.compilers]
"{IDO}" = "ido5.3"
''')


def write_ninja(linker_entries):
    ninja = ninja_syntax.Writer(open(ROOT / "build.ninja", "w"), width=9999)
    dep = f"cpp -w {INCLUDES} {DEFINES} -nostdinc -MD -MF $out.d $in -o /dev/null"
    ninja.rule("as", description="as $in",
               command=f"cpp {INCLUDES} -nostdinc -P $in -o - | {AS} -no-pad-sections -Iinclude -o $out")
    ninja.rule("bin", description="bin $in",
               command=f"{CROSS}ld -r -b binary $in -o $out")
    # asm-processor only takes -O0..-O2. An -O3 file that still has GLOBAL_ASM is
    # built at -O2 (its asm doesn't care); once it is all C it is built at -O3.
    ninja.rule("cc", description="cc $in", depfile="$out.d", deps="gcc",
               command=f"if echo \"$flags\" | grep -q O3 && ! grep -q GLOBAL_ASM $in; then "
                       f"{IDO} -c -G 0 {WARNINGS} {INCLUDES} {DEFINES} $flags -o $out $in; else "
                       f"{ASM_PROC} {IDO} -- {AS} -- -c -G 0 {WARNINGS} {INCLUDES} {DEFINES} $$(echo \"$flags\" | sed s/-O3/-O2/) -o $out $in; fi "
                       f"&& if [ -n \"$o32\" ]; then python3 tools/set_o32abi_bit.py $out; fi && {dep}")
    ninja.rule("ld", description="link $out",
               command=f"{CROSS}ld -T {LD_PATH} -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -T undefined_syms.txt -Map {MAP_PATH} --no-check-sections -o $out")
    ninja.rule("z64", description="z64 $out", command=f"{CROSS}objcopy $in $out -O binary")
    ninja.rule("sha1", description="check $in", command="sha1sum -c checksum.sha1 && touch $out")

    # ROM assets (assets.yaml): build/assets/<name>.inc.c, included by C files.
    # Every cc edge waits for them (order-only); the depfile then tracks which
    # object includes which, and restat skips recompiles when nothing changed.
    ninja.rule("assets", description="extract assets", restat=True,
               command=f"python3 tools/extract_assets.py $in {ASSETS_DIR}")
    asset_outs = [str(extract_assets.output_path(ASSETS_DIR, e))
                  for e in extract_assets.load_manifest(ASSETS_MANIFEST)]
    if asset_outs:
        ninja.build(asset_outs, "assets", [ASSETS_MANIFEST, "baserom.jp.z64"],
                    implicit=["tools/extract_assets.py"])
    ninja.build("assets", "phony", asset_outs)

    objects = []
    for entry in linker_entries:
        seg = entry.segment
        if entry.object_path is None:
            continue
        # A .data/.bss entry is linked from its C file's object, which the c entry builds.
        # Without a c entry it is a data-only C file (no text, e.g. libultra's vitbl.c):
        # build it here, once.
        data_only = seg.type[0] == "." and seg.sibling is None and not seg.siblings
        if seg.type[0] == "." and not data_only:
            continue
        obj = str(entry.object_path)
        srcs = [str(s) for s in entry.src_paths]
        if obj in objects:
            continue
        objects.append(obj)
        if data_only or isinstance(seg, splat.segtypes.common.c.CommonSegC):
            src = srcs[0]
            ninja.build(obj, "cc", srcs, order_only=["assets"],
                        variables={"flags": flags_for(src), "o32": "1" if src in SET_O32 else ""})
        elif isinstance(seg, (splat.segtypes.common.asm.CommonSegAsm, splat.segtypes.common.data.CommonSegData)) \
                or seg.type in ("hasm", "header", "asm", "data", "rodata", "bss"):
            ninja.build(obj, "as", srcs)
        elif isinstance(seg, splat.segtypes.common.bin.CommonSegBin):
            ninja.build(obj, "as", srcs)
        else:
            ninja.build(obj, "as", srcs)

    ninja.build(ELF_PATH, "ld", LD_PATH, implicit=objects)
    ninja.build(ROM_PATH, "z64", ELF_PATH)
    ninja.build("build/ok", "sha1", ROM_PATH, implicit=["checksum.sha1"])
    ninja.default(ROM_PATH)


if __name__ == "__main__":
    ap = argparse.ArgumentParser(description="Configure the project")
    ap.add_argument("-c", "--clean", action="store_true", help="remove split and build output first")
    args = ap.parse_args()
    if args.clean:
        clean()
    split.main([Path(YAML_FILE)], modes=["all"], verbose=False)
    subprocess.run([sys.executable, "tools/undefined_syms.py"], check=True)
    write_ninja(split.linker_writer.entries)
    write_permuter_settings()
