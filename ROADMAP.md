# ROADMAP — English Parse Tree Compiler

**Project:** C++ compiler for English sentences & arithmetic expressions  
**Output:** Parse tree (ASCII) + symbol table + parsing strategy label  
**Language:** C++17

---

## Phases Overview

| Phase | Name                        | Est. Time | Status      |
|-------|-----------------------------|-----------|-------------|
| 1     | Project Setup + POS Dict    | 1–2 days  | ⬜ Not started |
| 2     | Parse Tree + Display        | 1 day     | ⬜ Not started |
| 3     | Top-Down Parser             | 2–3 days  | ⬜ Not started |
| 4     | Bottom-Up Parser            | 2 days    | ⬜ Not started |
| 5     | Symbol Table                | 1 day     | ⬜ Not started |
| 6     | Expression Parser + main()  | 1–2 days  | ⬜ Not started |

**Total estimated time:** 8–11 days

---

## Phase 1 — Project Setup & POS Dictionary

**Goal:** Compilable project skeleton with a working lexer that correctly tags English words.

**In scope:**
- CMakeLists.txt (builds main executable + test binary)
- `POS` enum definition
- POS dictionary (80+ words minimum)
- Suffix heuristics for unknown words
- Lexer that splits and tags a sentence
- Unit tests for the lexer

**Out of scope:**
- Any parsing logic (no grammar rules yet)
- Parse tree data structures
- Display or output formatting

**Success criteria:**
- `cmake -B build && cmake --build build` succeeds with zero warnings
- `./build/run_tests` passes all lexer tests
- `Lexer("The quick brown fox").tokenize()` returns 4 tokens with correct tags: `[DET, ADJ, ADJ, N]`

**Key implementation notes:**
- Build the dictionary as a `static const unordered_map` in `pos_dict.cpp` — not rebuilt per Lexer instance
- Lowercase the input word before dictionary lookup so "The" and "the" both match
- The suffix rules must run only if the dictionary lookup misses — don't suffix-match known words

---

## Phase 2 — Parse Tree Data Structure & Display

**Goal:** A working ASCII tree renderer before any parsing exists.

**In scope:**
- `ParseNode` struct with `label`, `lexeme`, `type`, `children`
- `Display::print_tree()` — recursive ASCII renderer with `├──`, `└──`, `│` connectors
- Manual tree construction in a test to verify rendering

**Out of scope:**
- Any parser (trees are hand-built in tests for now)
- Symbol table

**Success criteria:**
- A manually constructed tree for "The dog runs" renders exactly as:
```
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"
```
- No missing `│` lines, no extra spaces, correct last-child detection

**Key implementation notes:**
- The rendering prefix must be built incrementally: pass `prefix` string into recursion, appending `"│   "` for non-last children and `"    "` for last children
- `is_last` is `true` when the current child is `children[children.size() - 1]`
- Terminal nodes print as `TAG: "word"`, non-terminals print as just `TAG`

---

## Phase 3 — Top-Down Parser (Recursive Descent)

**Goal:** Parse English sentences using recursive descent; produce correct labelled parse trees.

**In scope:**
- `TopDownParser` class
- Grammar rules for `S`, `NP`, `VP`, `PP` (per CFG in PROJECT_GUIDE.md)
- Backtracking via cursor save/restore
- Printing `"Parsing Strategy: Top-Down (Recursive Descent)"` before output
- Tests for 8 diverse sentences

**Out of scope:**
- Bottom-up parsing
- Expression parsing (numeric input)
- Symbol table
- `main.cpp` integration (can test via direct instantiation)

**Success criteria:**
- `parse("The dog runs")` → tree with `S → NP(DET, N) → VP(V)`
- `parse("The quick brown fox jumps over the lazy dog")` → full nested tree
- `parse("She loves him")` → `S → NP(PRON) → VP(V, NP(PRON))`
- `parse("jumps the the")` → `nullptr` (graceful failure)
- 8 test cases all pass

**Key implementation notes:**
- Try the longest rule first (e.g. `DET ADJ ADJ N` before `DET ADJ N`) to avoid partial matches
- Each `parse_*()` function must restore `cursor_` to its entry value on failure before returning `nullptr`
- `consume(POS tag)` should: check `current().tag == tag`, if yes create a TERMINAL node, advance cursor, return true; if no return false without advancing

---

## Phase 4 — Bottom-Up Parser (Shift-Reduce)

**Goal:** Alternate parsing mode producing the same tree structure via shift-reduce.

**In scope:**
- `BottomUpParser` class with `stack_`, `shift()`, `try_reduce()`
- Reduce functions for each non-terminal: `reduce_NP()`, `reduce_VP()`, `reduce_PP()`, `reduce_S()`
- Infinite-loop safeguard
- `--bottom-up` flag wired in (even if `main()` is minimal at this stage)
- Tests: same 8 sentences as Phase 3

**Out of scope:**
- Full `main()` integration (that's Phase 6)
- Expression parsing

**Success criteria:**
- `BottomUpParser("The dog runs").parse()` returns a tree structurally identical to the top-down result
- `reduce_NP()` correctly matches all 4 NP patterns
- Loop terminates on all 8 test sentences (no infinite loop)
- Parse failure returns `nullptr`, not a crash

**Key implementation notes:**
- Reduction priority matters: try PP before NP, NP before VP, VP before S — otherwise `PREP NP` may be reduced as bare NP
- `stack_top_matches(pattern)` must check from top of stack downward (i.e., pattern is listed left-to-right but the stack top is the rightmost element)
- When building the reduce node, children must be added in left-to-right order (pop stack in reverse, reverse again before adding children)

---

## Phase 5 — Symbol Table

**Goal:** Post-parse tree walk produces a complete, formatted symbol table.

**In scope:**
- `SymbolEntry` struct
- `SymbolTable::build(root)` — walks parse tree, creates entries for all terminals
- `grammar_role` derivation from parent–child relationships
- Scope propagation (`"Sentence"` at top level, `"Prepositional"` under PP)
- `SymbolTable::print()` — aligned column display
- Unit tests

**Out of scope:**
- Semantic roles (not subject/object — just grammar roles like NP.head, VP.head)
- Any modification of the parse tree

**Success criteria:**
- For "The dog runs": 3 entries — `The/DET/NP.determiner`, `dog/N/NP.head`, `runs/V/VP.head`
- For "jumps over the fence": PP children have scope `"Prepositional"`
- Column widths in the table adjust to longest value in each column (no hardcoded widths)

**Key implementation notes:**
- Build the symbol table by passing a `parent_label` down through the recursion — the terminal node itself doesn't know its parent without this
- For determining column widths, do two passes: first collect all entries, then compute `max(lexeme.size())` per column, then render

---

## Phase 6 — Expression Parser + main() Integration

**Goal:** Handle arithmetic expressions; full CLI integration; polished output.

**In scope:**
- `detect_input_type()` — sentence vs expression detection
- Expression grammar added to `TopDownParser`: `EXPR`, `TERM`, `FACTOR`
- Lexer updates: multi-digit numbers, operator tokens
- `main.cpp`: arg parsing, routing, full output pipeline
- Final output format with separators and headers
- Smoke tests against 10 fixture sentences

**Out of scope:**
- Expression evaluation (only parsing/tree, not computation)
- Interactive mode
- File input

**Success criteria:**
- `./english-parser "The dog runs"` → full correct output (strategy + tree + table)
- `./english-parser --bottom-up "The dog runs"` → same tree, different strategy label
- `./english-parser "3 + 4 * 2"` → expression tree showing operator precedence:
```
EXPR
├── TERM
│   └── FACTOR
│       └── NUM: "3"
├── OP: "+"
└── TERM
    ├── FACTOR
    │   └── NUM: "4"
    ├── OP: "*"
    └── FACTOR
        └── NUM: "2"
```
- Unknown/unparseable input prints: `"Error: Could not parse input."` to stderr
- Exit code is `0` on success, `1` on failure

**Key implementation notes:**
- `detect_input_type`: scan token list for any `NUM` token or operator character — if found, it's an expression
- Arithmetic lexer must accumulate digits: `while (isdigit(input[i])) token += input[i++]`
- Operator precedence is encoded in the grammar structure itself (TERM handles `*/`, EXPR handles `+-`) — do not implement an operator precedence table separately

---

## Not In Scope (Ever)

| Feature | Reason |
|---------|--------|
| ML/statistical POS tagger | Requires training data and an ML runtime; far out of scope for a compiler design course |
| Semantic role labeling | This is NLP beyond parsing — the project is about parse trees, not meaning |
| Relative clauses / subordinate clauses | "The man who runs" would require a more complex grammar; deliberately excluded to keep CFG manageable |
| Interactive REPL / `--watch` mode | One-shot input/output only; a loop would complicate error handling with no added learning value |
| Pretty HTML/graphical output | ASCII is sufficient and avoids a rendering dependency; if needed, add as an optional post-Phase-6 extension |
| Full English grammar coverage | The defined CFG handles the most common sentence structures; handling all of English grammar is an open research problem |
| Expression evaluation | Parse tree construction is the goal; evaluating the result is a separate concern (interpreter design) |
