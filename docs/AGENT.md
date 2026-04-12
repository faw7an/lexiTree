# AGENT.md — English Parse Tree Compiler

**Current phase:** Phase 1

---

## 1. Project Identity

**What this is:** A C++17 command-line tool that accepts an English sentence or arithmetic expression and produces:
1. A labelled parse tree (rendered as ASCII art)
2. A symbol table listing every word with its POS tag, grammar role, and scope
3. A declaration of which parsing strategy was used (Top-Down or Bottom-Up)

**What this is NOT:**
- A full NLP pipeline (no semantics, no coreference, no ML)
- A general-purpose English grammar (handles a defined, finite CFG only)
- A web app, GUI, or interactive REPL (stdout only)

---

## 2. Non-Negotiable Rules

- **Never allocate raw `ParseNode*` outside of `std::unique_ptr`** — the tree owns all nodes via `unique_ptr`. If a parse attempt fails, the unique_ptr destructor cleans up automatically.
- **Never modify the token vector after lexing** — the parser reads from a `const std::vector<Token>&`. This prevents cursor/iterator invalidation bugs.
- **Always print the parsing strategy label before the tree** — output order: strategy → tree → symbol table.
- **Backtracking must save and restore the exact cursor value** — never assume a `parse_*()` call has no side effects on the cursor when it fails.
- **Grammar rules must match exactly the symbols defined in `pos_dict.h`** — a mismatch (e.g., matching "VERB" when your enum is `POS::V`) will silently fail every reduction.
- **The symbol table must be built post-parse** — do not build it during parsing (the tree may be discarded on backtrack). Always traverse the final accepted tree.

---

## 3. What NOT To Do

- **Do not use `dynamic_cast` or RTTI** — all node types are handled via the `NodeType` enum field and string label. Keep it simple.
- **Do not share ParseNode ownership across trees** — each parse attempt creates its own tree. Don't `std::move` a node into two different parents.
- **Do not add a POS tag for a word class you don't handle in grammar rules** — if you add `POS::INTERJECTION` to the dict, you must also handle it in the parser or it becomes a dead token that breaks parsing.
- **Do not hardcode display widths** — column widths in the symbol table must compute dynamically from the max length of each column's data.
- **Do not conflate `label` and `lexeme`** — internal nodes (NP, VP, S) have a `label` only. Leaf nodes have both a `label` (POS tag) and a `lexeme` (the actual word).
- **Do not try to parse sentences that don't fit the grammar silently** — always emit a clear error message: `"Error: Could not parse input as a valid sentence or expression."`.

---

## 4. Phase Task Checklists

### Phase 1 — Project Setup & POS Dictionary
**Goal:** Compilable skeleton + working POS tagger.

- [ ] Create directory structure: `include/`, `src/`, `tests/`, `tests/fixtures/`
- [ ] Write `CMakeLists.txt` with main executable and test target
- [ ] Define `POS` enum in `include/pos_dict.h`:
      `{ DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM, PROPER_N, UNKNOWN }`
- [ ] Implement `pos_dict.cpp`: populate `unordered_map<string, POS>` with at least 80 common English words (20 nouns, 20 verbs, 10 determiners, 10 adjectives, 10 adverbs, 10 prepositions)
- [ ] Implement suffix heuristic in `Lexer::assign_pos()`:
      `-ing` → V, `-ly` → ADV, `-ed` → V, `-tion/-ness/-ment` → N
- [ ] Write `Lexer::split_words()`: split on spaces + strip punctuation `.,:;!?`
- [ ] Write `Lexer::tokenize()`: calls `split_words()` then `assign_pos()` per word
- [ ] Implement `Token` struct with `word`, `tag`, `position`
- [ ] Write `tests/test_lexer.cpp` with at least 10 test cases
- [ ] Verify: `./english-parser "The dog runs"` prints token stream to stdout (temporary debug output)

**Phase 1 complete when:** `cmake --build . && ./run_tests` passes all lexer tests with zero failures.

---

### Phase 2 — Parse Tree Data Structure + Display
**Goal:** Build, traverse, and render the parse tree before any parsing logic.

- [ ] Define `NodeType` enum: `{ TERMINAL, NON_TERMINAL }`
- [ ] Implement `ParseNode` struct in `include/parse_tree.h`
- [ ] Implement `ParseNode::add_child(unique_ptr<ParseNode>)` in `src/parse_tree.cpp`
- [ ] Implement `Display::print_node()` — recursive, with prefix string:
      - If child is last: use `"└── "`; else use `"├── "`
      - Propagate `"│   "` vs `"    "` for deeper levels
- [ ] Implement `Display::print_tree(const ParseNode* root)` — calls `print_node(root, "", true)`
- [ ] Manually construct a test tree and call `print_tree()` on it (hardcoded, no parsing yet)
- [ ] Verify expected output for a 3-level tree:
```
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"
```
- [ ] Write `tests/test_display.cpp` that captures stdout and compares to expected string

**Phase 2 complete when:** Hardcoded tree renders with correct ASCII connectors; no `│` lines misaligned.

---

### Phase 3 — Top-Down Parser (Recursive Descent)
**Goal:** Parse English sentences using recursive descent; produce correct parse trees.

- [ ] Implement `TopDownParser` class in `include/top_down_parser.h` + `src/top_down_parser.cpp`
- [ ] Implement `cursor_` management: `current()`, `peek(int)`, `at_end()`, `consume(POS)`
- [ ] Implement `parse_S()`:
      try `NP VP`, then `NP VP PP`; return first success or `nullptr`
- [ ] Implement `parse_NP()`:
      try rules in order: `DET ADJ ADJ N` → `DET ADJ N` → `DET N` → `PRON` → `N`
      use saved cursor + backtracking for each attempt
- [ ] Implement `parse_VP()`:
      try: `V NP PP` → `V NP` → `V PP` → `V ADV` → `V`
- [ ] Implement `parse_PP()`:
      expect `PREP` then `NP`; return `nullptr` if no PREP
- [ ] Wire `TopDownParser::parse()` to try `parse_S()` first, then expression parser
- [ ] Test with fixtures:
      - "The dog runs" → S(NP(DET,N), VP(V))
      - "The quick brown fox jumps over the lazy dog" → full tree
      - "She sees him" → S(NP(PRON), VP(V, NP(PRON)))
- [ ] Print `"Parsing strategy: Top-Down (Recursive Descent)"` before the tree
- [ ] Write `tests/test_top_down.cpp` with at least 8 sentence test cases

**Phase 3 complete when:** All 8 test sentences produce correct tree structures (verified by checking `tree->label`, `tree->children[0]->label`, etc. in tests).

---

### Phase 4 — Bottom-Up Parser (Shift-Reduce)
**Goal:** Alternate parsing mode; produces same parse tree structure via bottom-up strategy.

- [ ] Implement `StackItem` struct: holds `unique_ptr<ParseNode>` + `string symbol`
- [ ] Implement `BottomUpParser` class in `include/bottom_up_parser.h` + `src/bottom_up_parser.cpp`
- [ ] Implement `shift()`: create TERMINAL `ParseNode` for `tokens_[input_pos_]`, push to `stack_`, advance `input_pos_`
- [ ] Implement `stack_top_matches(vector<string> pattern)`: check if top N stack items' symbols match `pattern` (from bottom to top)
- [ ] Implement `reduce_NP()`: check patterns `{"DET","ADJ","N"}`, `{"DET","N"}`, `{"PRON"}`, `{"N"}`; pop + build NP node
- [ ] Implement `reduce_VP()`: check patterns `{"V","NP","PP"}`, `{"V","NP"}`, `{"V","PP"}`, `{"V","ADV"}`, `{"V"}`; pop + build VP node
- [ ] Implement `reduce_PP()`: check pattern `{"PREP","NP"}`; pop + build PP node
- [ ] Implement `reduce_S()`: check pattern `{"NP","VP"}`; pop + build S node
- [ ] Implement `try_reduce()`: call each reduce_*() in priority order (PP first, then NP, VP, S); return `true` if any succeeded
- [ ] Implement main `parse()` loop:
      ```
      while not (stack has one item with symbol "S" AND input exhausted):
          if try_reduce(): continue
          elif not at_end(): shift()
          else: return nullptr  // stuck — parse failure
      ```
- [ ] Implement safeguard: if loop runs > `tokens_.size() * 10` iterations, return `nullptr`
- [ ] Print `"Parsing strategy: Bottom-Up (Shift-Reduce)"` when `--bottom-up` flag is used
- [ ] Write `tests/test_bottom_up.cpp` — same 8 sentences as Phase 3

**Phase 4 complete when:** Bottom-up produces structurally identical trees to top-down for all 8 test sentences.

---

### Phase 5 — Symbol Table
**Goal:** Walk the final parse tree and populate the symbol table.

- [ ] Implement `SymbolEntry` struct: `index`, `lexeme`, `pos_tag`, `grammar_role`, `scope`
- [ ] Implement `SymbolTable::traverse(const ParseNode* node, const string& scope)`:
      - If node is TERMINAL: create `SymbolEntry`, infer `grammar_role` from parent's label + child position
      - If node is `PP`: recurse with `scope = "Prepositional"`
      - Otherwise recurse with current scope
- [ ] Implement `grammar_role` derivation logic:
      - `DET` child of `NP` → `"NP.determiner"`
      - `N` child of `NP` → `"NP.head"`
      - `ADJ` child of `NP` → `"NP.modifier"`
      - `V` child of `VP` → `"VP.head"`
      - `AUX` child of `VP` → `"VP.auxiliary"`
      - `PREP` child of `PP` → `"PP.head"`
      - fallback → `parent_label + "." + pos_tag`
- [ ] Implement `SymbolTable::print()`: render the table with aligned columns
- [ ] Write `tests/test_symbol_table.cpp`:
      - verify entry count matches number of words
      - verify verb entry has `grammar_role == "VP.head"`
      - verify determiner has correct scope

**Phase 5 complete when:** All symbol table tests pass; table renders with consistent column alignment.

---

### Phase 6 — Expression Parser + main() Integration
**Goal:** Handle arithmetic expressions; wire everything together with CLI flags.

- [ ] Implement `detect_input_type(const vector<Token>&)`: returns `InputType::SENTENCE` or `InputType::EXPRESSION`
      - EXPRESSION: first token is NUM, or any token is `+`, `-`, `*`, `/`
- [ ] Implement expression grammar using recursive descent in `TopDownParser`:
      - `parse_EXPR()` → `parse_TERM()` with `+`/`-` operators
      - `parse_TERM()` → `parse_FACTOR()` with `*`/`/` operators
      - `parse_FACTOR()` → NUM or `(` EXPR `)`
- [ ] Update `Lexer::split_words()` to handle operators and multi-digit numbers:
      - accumulate digit characters into one NUM token
      - emit `+`, `-`, `*`, `/`, `(`, `)` as their own tokens
- [ ] Implement `main.cpp`:
      - parse CLI args: `--bottom-up` flag, input string (remaining args joined)
      - call Lexer → Parser (top-down or bottom-up) → SymbolTable → Display
      - exit code `0` on success, `1` on parse failure
- [ ] Final output format for all runs:
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
========================================

Parse Tree:
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"

Symbol Table:
┌───────┬──────────┬─────────┬───────────────┬────────────┐
│ Index │ Lexeme   │ POS Tag │ Grammar Role  │ Scope      │
├───────┼──────────┼─────────┼───────────────┼────────────┤
│ 1     │ The      │ DET     │ NP.determiner │ Sentence   │
│ 2     │ dog      │ N       │ NP.head       │ Sentence   │
│ 3     │ runs     │ V       │ VP.head       │ Sentence   │
└───────┴──────────┴─────────┴───────────────┴────────────┘
```
- [ ] Write `tests/fixtures/sentences.txt` with 10 diverse test sentences
- [ ] Smoke test: run all 10 fixtures, confirm no crashes and output looks correct

**Phase 6 complete when:** `./english-parser "The dog runs"` produces the correct full output. `./english-parser --bottom-up "The dog runs"` produces the same tree with different strategy label. `./english-parser "3 + 4 * 2"` produces an expression parse tree.

---

## 5. Code Style Rules

- **Naming:** `snake_case` for variables/functions, `PascalCase` for classes/structs, `SCREAMING_SNAKE` for enum values (e.g. `POS::DET`)
- **Memory:** `std::unique_ptr` for all tree nodes; no raw `new` in parser code
- **Headers:** use `#pragma once`; no circular includes (parse_tree.h must not include lexer.h)
- **Error output:** use `std::cerr` for error messages, `std::cout` for program output
- **Comments:** every non-trivial function gets a one-line `//` doc comment above it explaining its contract

---

## 6. Debugging Decision Tree

| Symptom | Check First | Then Check |
|---------|-------------|------------|
| `parse()` returns nullptr | Print token stream: `for (auto& t : tokens) cout << t.word << ":" << pos_to_str(t.tag) << " ";` | Missing word in dict + no suffix heuristic match → tagged UNKNOWN |
| Infinite loop in bottom-up | `try_reduce()` returning true but not consuming stack items | Reduce function not popping stack before returning true |
| Wrong tree shape | Print cursor value before/after each `parse_*()` call | `consume()` not advancing cursor on match |
| Symbol table has wrong count | Check PP traversal: PP children are not being visited | `scope` param not passed correctly through recursion |
| ASCII tree has misaligned bars | `is_last` computed using `i < children.size() - 1` (off by one) | Use `i == children.size() - 1` |
| Build fails (linking error) | A `.cpp` file not listed in `CMakeLists.txt` | Missing `add_executable` source entry |

---

## 7. Reference Checklist (Before Demo)

- [ ] Top-down parse works for at least 5 diverse sentences
- [ ] Bottom-up parse works for at least 3 sentences
- [ ] Both modes produce structurally identical trees for the same input
- [ ] Symbol table shows correct grammar roles for nouns, verbs, determiners
- [ ] Arithmetic expression parses correctly with correct tree (`EXPR`, `TERM`, `FACTOR`)
- [ ] Unknown words are handled gracefully (not a crash, fallback to heuristic)
- [ ] Parse failure emits a clear error message, not a segfault
- [ ] Strategy label always appears in output

---

## 8. Not In Scope (Ever)

- **Semantic analysis** — no meaning extraction, no WordNet, no entity linking
- **Machine learning POS tagging** — no ML models; dictionary + heuristics only
- **Ambiguity resolution** — when two parses are valid, the first successful parse wins
- **Long-distance dependencies** — no wh-movement, no relative clauses beyond simple PP attachment
- **File input mode** — input is always a single command-line string or stdin line
- **Interactive mode / REPL** — one input → one output → exit
