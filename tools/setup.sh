#!/bin/bash
# Fetch the build tools into tools/ and the Python packages into .venv.
# Needs (Debian/Ubuntu): sudo apt install python3-venv ninja-build binutils-mips-linux-gnu git curl
# --dev also fetches the matching tools (asm-differ, m2c, decomp-permuter).
set -e
cd "$(dirname "$0")/.."

IDO_URL=https://github.com/decompals/ido-static-recomp/releases/download/v1.2/ido-5.3-recomp-linux.tar.gz

for t in python3 ninja mips-linux-gnu-as mips-linux-gnu-ld git curl; do
    command -v $t >/dev/null || { echo "missing: $t (see the top of tools/setup.sh)"; exit 1; }
done

# fetch <dir> <repo> <commit>: clone at a fixed commit, the one the ROM was matched with
fetch() {
    [ -d "tools/$1" ] && return
    git clone -q "$2" "tools/$1"
    git -C "tools/$1" checkout -q "$3"
}

if [ ! -x tools/ido_5.3/cc ]; then
    mkdir -p tools/ido_5.3
    curl -sSL "$IDO_URL" | tar -xz -C tools/ido_5.3
fi
fetch asm-processor https://github.com/simonlindholm/asm-processor.git f3b2f85
if [ "$1" = "--dev" ]; then
    fetch asm-differ https://github.com/simonlindholm/asm-differ.git 0dd09af
    fetch m2c https://github.com/matt-kempster/m2c.git c632946
    fetch decomp-permuter https://github.com/simonlindholm/decomp-permuter.git 8556c81
fi

[ -d .venv ] || python3 -m venv .venv
.venv/bin/pip install -q -r requirements.txt

echo "Done. Put your ROM at baserom.jp.z64 and run ./build.sh"
