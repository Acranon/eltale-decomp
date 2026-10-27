# Name tables (D3)

One `.tsv` per naming batch: `old<TAB>new<TAB>evidence`, `#` lines are comments.
`tools/rename.py` applies them (symbol_addrs.txt plus a whole-word replace across src/);
merge.sh runs it when work lands, so a batch commits only its table and its own module
edits. `tools/rename.py --check` builds HEAD with every table applied, in a temporary
worktree. The process and naming rules: `~/eltale-notes/D3_NAMING.md`.
