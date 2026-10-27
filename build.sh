#!/bin/bash
# Split the ROM, build it, and check it against retail.
# From scratch: rm -rf asm build && ./build.sh
# NON_MATCHING=1 ./build.sh builds the C drafts of unmatched functions (src/nonmatching/)
# instead of their asm; that ROM is not compared with retail.
set -e
cd "$(dirname "$0")"
[ -f baserom.jp.z64 ] || { echo "baserom.jp.z64 missing (Eltale Monsters (J), z64 byte order)"; exit 1; }
. .venv/bin/activate
[ -d asm ] || rm -f .splache
NM=""; [ -n "$NON_MATCHING" ] && NM="--non-matching"
# switching between the two modes needs a reconfigure
HAVE=""; grep -q DNON_MATCHING build.ninja 2>/dev/null && HAVE="--non-matching"
[ "$HAVE" = "$NM" ] || rm -f build.ninja
if [ ! -f build.ninja ] || [ ! -d asm ] || [ eltale.jp.yaml -nt build.ninja ] || [ symbol_addrs.txt -nt build.ninja ] || [ assets.yaml -nt build.ninja ]; then
    python3 configure.py $NM
fi
ninja "$@"
if [ -n "$NM" ]; then
    echo "build/eltale.z64: built NON_MATCHING (not compared with retail)"
    exit 0
fi
if cmp -s build/eltale.z64 baserom.jp.z64; then
    echo "build/eltale.z64: OK (matches retail)"
else
    echo "build/eltale.z64: MISMATCH"
    python3 tools/first_diff.py 2>/dev/null || true
    exit 1
fi
