#!/bin/bash
# Run decomp-permuter on a folder made by tools/perm_setup.py.
# Usage: tools/perm_run.sh DIR [jobs] [minutes]
# Defaults: 2 jobs at nice 19, 15 minutes, stop on a match. Keep it light: the machine
# is shared with the user's desktop. Results: DIR/output-<score>-<n>/ (0 = match).
D="$1"; J="${2:-2}"; M="${3:-15}"
[ -f "$D/base.c" ] || { echo "usage: perm_run.sh DIR [jobs] [minutes]"; exit 2; }
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
. "$ROOT/.venv/bin/activate"
cd "$ROOT/tools/decomp-permuter" || exit 1
timeout -s INT "${M}m" nice -n 19 python3 permuter.py -j "$J" --stop-on-zero "$D" 2>&1 | tr '\r' '\n' | grep -a -v '^$' | tail -5
ls -d "$D"/output-* 2>/dev/null | sed 's/.*output-\([0-9]*\)-.*/\1 &/' | sort -n | head -5 | cut -d' ' -f2-
