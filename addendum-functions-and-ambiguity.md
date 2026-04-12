# English Parser — Addendum: Numerical Functions & Ambiguity Detection

This is an addendum to `PROJECT_GUIDE.md`, `AGENT.md`, and `ROADMAP.md`.
Implement Phase 7 (Numerical Functions) and Phase 8 (Ambiguity Detection)
after Phase 6 is complete.

---

## Table of Contents
1. [How Numerical Functions Work](#1-how-numerical-functions-work)
2. [How Ambiguity Detection Works](#2-how-ambiguity-detection-works)
3. [Updated Data Structures](#3-updated-data-structures)
4. [Updated Grammar Rules](#4-updated-grammar-rules)
5. [Ambiguity: What to Show the User](#5-ambiguity-what-to-show-the-user)
6. [Debugging Notes](#6-debugging-notes)
7. [AGENT.md Additions — Phase 7 & 8 Checklists](#7-agentmd-additions)
8. [ROADMAP.md Additions — Phase 7 & 8](#8-roadmapmd-additions)

---

## 1. How Numerical Functions Work

### 1.1 What counts as a "numerical function"

A numerical function is a named operation applied to one or more numeric arguments:

| Function      | Arity | Example input           |
|---------------|-------|-------------------------|
| `sin`         | 1     | `sin(45)`               |
| `cos`         | 1     | `cos(90)`               |
| `tan`         | 1     | `tan(30)`               |
| `sqrt`        | 1     | `sqrt(16)`              |
| `log`         | 1     | `log(100)`              |
| `log2`        | 1     | `log2(8)`               |
| `abs`         | 1     | `abs(-5)`               |
| `floor`       | 1     | `floor(3.7)`            |
| `ceil`        | 1     | `ceil(3.2)`             |
| `pow`         | 2     | `pow(2, 8)`             |
| `max`         | 2+    | `max(3, 7, 12)`         |
| `min`         | 2+    | `min(3, 7, 12)`         |
| `mod`         | 2     | `mod(10, 3)`            |

Functions can be nested: `sqrt(pow(3, 2) + pow(4, 2))` — this must parse correctly because `EXPR` is reused inside the argument list.

### 1.2 Lexer Changes

Add `POS::FUNC` to the `POS` enum (or a separate `TokenType::FUNC`). In `pos_dict.cpp`, register all function names:

```cpp
// In the numeric token detection section of Lexer::tokenize():
static const std::unordered_set<std::string> MATH_FUNCS = {
    "sin","cos","tan","sqrt","log","log2","abs","floor","ceil",
    "pow","max","min","mod","exp","round"
};

// During tokenization, after reading an alphabetic run:
if (MATH_FUNCS.count(word_lower)) tag = POS::FUNC;
```

Also add tokens for `,` (COMMA) and for `(`, `)` (already needed for expressions). Update `Lexer::split_words()` to emit `(`, `)`, `,` as their own tokens.

### 1.3 Grammar Extension

Extend the expression grammar with function calls and argument lists:

```
EXPR     → TERM (('+' | '-') TERM)*

TERM     → FACTOR (('*' | '/') FACTOR)*

FACTOR   → NUM
          | '(' EXPR ')'
          | FUNC '(' ARGLIST ')'      ← NEW
          | '-' FACTOR                ← unary minus (NEW)

ARGLIST  → EXPR (',' EXPR)*           ← NEW
```

This naturally handles nesting because `ARGLIST` is defined in terms of `EXPR`, which loops back to `FACTOR`, which can again be a `FUNC` call.

### 1.4 Parse Tree Shape for Functions

```
Input: pow(2, 8)

EXPR
└── TERM
    └── FACTOR
        └── FUNC_CALL
            ├── FUNC: "pow"
            └── ARGLIST
                ├── EXPR
                │   └── TERM
                │       └── FACTOR
                │           └── NUM: "2"
                └── EXPR
                    └── TERM
                        └── FACTOR
                            └── NUM: "8"
```

```
Input: sqrt(pow(3, 2) + pow(4, 2))

EXPR
└── TERM
    └── FACTOR
        └── FUNC_CALL
            ├── FUNC: "sqrt"
            └── ARGLIST
                └── EXPR
                    ├── TERM
                    │   └── FACTOR
                    │       └── FUNC_CALL
                    │           ├── FUNC: "pow"
                    │           └── ARGLIST
                    │               ├── EXPR → NUM: "3"
                    │               └── EXPR → NUM: "2"
                    ├── OP: "+"
                    └── TERM
                        └── FACTOR
                            └── FUNC_CALL
                                ├── FUNC: "pow"
                                └── ARGLIST
                                    ├── EXPR → NUM: "4"
                                    └── EXPR → NUM: "2"
```

### 1.5 detect_input_type() Update

The existing check (any NUM or operator → EXPRESSION) must now also trigger on FUNC tokens:

```cpp
InputType detect_input_type(const std::vector<Token>& tokens) {
    for (auto& t : tokens) {
        if (t.tag == POS::NUM || t.tag == POS::FUNC ||
            t.word == "+" || t.word == "-" ||
            t.word == "*" || t.word == "/") {
            return InputType::EXPRESSION;
        }
    }
    return InputType::SENTENCE;
}
```

### 1.6 Symbol Table for Numerical Functions

Add a new grammar role `"FUNC_CALL.name"` for the function name token and `"FUNC_CALL.arg[N]"` for each argument:

```
┌───────┬──────────┬─────────┬──────────────────┬────────────┐
│ Index │ Lexeme   │ POS Tag │ Grammar Role     │ Scope      │
├───────┼──────────┼─────────┼──────────────────┼────────────┤
│ 1     │ pow      │ FUNC    │ FUNC_CALL.name   │ Expression │
│ 2     │ 2        │ NUM     │ FUNC_CALL.arg[0] │ Expression │
│ 3     │ 8        │ NUM     │ FUNC_CALL.arg[1] │ Expression │
└───────┴──────────┴─────────┴──────────────────┴────────────┘
```

---

## 2. How Ambiguity Detection Works

### 2.1 What ambiguity means in this context

A parse is **ambiguous** when two or more distinct parse trees can be produced from the same input under the same grammar. A parse is **unambiguous** when exactly one valid tree exists.

**English ambiguity types you must detect:**

| Type | Example | Ambiguity |
|------|---------|-----------|
| PP attachment | "I saw the man with the telescope" | Did I use the telescope, or does the man have it? |
| ADJ scope | "old men and women" | Are only the men old, or both men and women? |
| V/N ambiguity | "flies like an arrow" | Is "flies" a verb or "like" a verb? |
| Reduced relative | "The horse raced past the barn fell" | Garden-path; two possible tree structures |

**Expression ambiguity** does not occur in your grammar because operator precedence is encoded structurally (`TERM` handles `*/`, `EXPR` handles `+-`). If you see `3 + 4 * 2`, the grammar forces the correct tree. Mark all arithmetic and function expressions as **Unambiguous** automatically.

### 2.2 How to find all parses (exhaustive search)

Change the parser's return type from `unique_ptr<ParseNode>` to `vector<unique_ptr<ParseNode>>`. The parser no longer returns at the first success — it collects all successes.

**Top-down exhaustive parse:**

Each `parse_*()` function returns a `vector` of alternative subtrees instead of one:

```cpp
// Before (returns first match):
std::unique_ptr<ParseNode> parse_NP() {
    if (auto n = try_rule_DET_ADJ_N()) return n;
    if (auto n = try_rule_DET_N())     return n;
    ...
    return nullptr;
}

// After (returns ALL matches):
std::vector<AltResult> parse_NP_all(size_t cursor) {
    std::vector<AltResult> results;
    // try DET ADJ N
    auto [node1, end1] = try_rule_DET_ADJ_N(cursor);
    if (node1) results.push_back({std::move(node1), end1});
    // try DET N
    auto [node2, end2] = try_rule_DET_N(cursor);
    if (node2) results.push_back({std::move(node2), end2});
    // ... etc
    return results;
}
```

`AltResult` is a small struct: `{ unique_ptr<ParseNode> tree; size_t end_cursor; }`.

**PP attachment is the main source of ambiguity.** When parsing `VP`, both of these are valid:

```
"I saw the man with the telescope"

Tree A:                          Tree B:
S                                S
├── NP: "I"                      ├── NP: "I"
└── VP                           └── VP
    ├── V: "saw"                     ├── V: "saw"
    ├── NP: "the man"                └── NP
    └── PP: "with the telescope"         ├── DET: "the"
                                         ├── N: "man"
                                         └── PP: "with the telescope"
```

In Tree A, the PP attaches to the VP (I used the telescope).
In Tree B, the PP attaches to the NP inside the VP (the man has the telescope).

To produce both trees, `parse_VP_all()` must try both:
1. `V NP PP` (PP attaches to VP — Tree A)
2. `V NP` where NP is parsed by `parse_NP_all()` which itself can produce `DET N PP` (PP attaches to NP — Tree B)

### 2.3 Counting and Reporting

After collecting all parse trees, report the result:

```
count == 0  → Parse failure: "Error: Could not parse input."
count == 1  → "Verdict: UNAMBIGUOUS (1 valid parse)"
count >= 2  → "Verdict: AMBIGUOUS (N possible parses)"
```

When ambiguous, display **all trees** numbered:

```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: AMBIGUOUS (2 possible parses)
========================================

--- Parse Tree 1 of 2 ---
S
├── NP: "I"
└── VP
    ├── V: "saw"
    ├── NP
    │   ├── DET: "the"
    │   └── N: "man"
    └── PP
        ├── PREP: "with"
        └── NP
            ├── DET: "the"
            └── N: "telescope"

  Interpretation: "I used the telescope to see the man"

--- Parse Tree 2 of 2 ---
S
├── NP: "I"
└── VP
    ├── V: "saw"
    └── NP
        ├── DET: "the"
        ├── N: "man"
        └── PP
            ├── PREP: "with"
            └── NP
                ├── DET: "the"
                └── N: "telescope"

  Interpretation: "The man has the telescope"
```

The "Interpretation" line is a hardcoded string derived from which PP attachment rule fired — you don't need NLP to generate it; you detect the structure and pick from a small set of template strings.

### 2.4 Ambiguity Interpretation Template Strings

Derive the interpretation by inspecting the tree structure after parsing:

```cpp
std::string derive_interpretation(const ParseNode* root) {
    // Check: does VP have a PP child directly?
    auto* vp = find_child(root, "VP");
    if (!vp) return "";
    bool pp_in_vp = has_direct_child(vp, "PP");
    bool pp_in_np = false;
    auto* np = find_direct_child(vp, "NP");
    if (np) pp_in_np = has_direct_child(np, "PP");

    if (pp_in_vp)  return "Interpretation: The prepositional phrase modifies the verb (VP attachment)";
    if (pp_in_np)  return "Interpretation: The prepositional phrase modifies the object noun (NP attachment)";
    return "";
}
```

---

## 3. Updated Data Structures

### 3.1 POS Enum additions

```cpp
enum class POS {
    DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM,
    PROPER_N, FUNC,   // ← NEW: math function name
    COMMA, LPAREN, RPAREN,  // ← NEW: punctuation tokens
    UNKNOWN
};
```

### 3.2 AltResult struct (new)

```cpp
struct AltResult {
    std::unique_ptr<ParseNode> tree;
    size_t end_cursor;  // where this parse ended in the token stream
};
```

### 3.3 Parser return type change

```cpp
// Old (single parse):
class TopDownParser {
    std::unique_ptr<ParseNode> parse();
    ...
};

// New (all parses):
class TopDownParser {
    std::vector<std::unique_ptr<ParseNode>> parse_all();  // returns all trees
    std::unique_ptr<ParseNode> parse();                   // returns first, for compat
    ...
private:
    std::vector<AltResult> parse_S_all(size_t cursor);
    std::vector<AltResult> parse_NP_all(size_t cursor);
    std::vector<AltResult> parse_VP_all(size_t cursor);
    std::vector<AltResult> parse_PP_all(size_t cursor);
};
```

The original `parse()` calls `parse_all()` and returns `std::move(results[0].tree)` — backward compatible.

### 3.4 AmbiguityResult struct (new)

```cpp
struct AmbiguityResult {
    std::vector<std::unique_ptr<ParseNode>> trees;
    bool is_ambiguous() const { return trees.size() > 1; }
    bool failed()       const { return trees.empty(); }
};
```

### 3.5 FUNC_CALL node (new parse tree label)

Add `"FUNC_CALL"` and `"ARGLIST"` as valid non-terminal labels. No code change needed — these are just string values for `ParseNode::label`.

---

## 4. Updated Grammar Rules

### 4.1 Full expression grammar (replaces Phase 6 version)

```
EXPR      → TERM (('+' | '-') TERM)*

TERM      → FACTOR (('*' | '/') FACTOR)*

FACTOR    → NUM
           | '(' EXPR ')'
           | FUNC '(' ARGLIST ')'
           | '-' FACTOR

ARGLIST   → EXPR (',' EXPR)*
```

### 4.2 English grammar (extended for ambiguity collection)

```
S      → NP VP
       | NP VP PP          ← produces VP-level PP attachment (one of two trees)

NP     → DET N             ← plain NP
       | DET ADJ N
       | DET ADJ ADJ N
       | DET N PP          ← NP with embedded PP (produces NP-level PP attachment)
       | PRON
       | N

VP     → V
       | V NP              ← NP may itself contain a PP → ambiguity source
       | V NP PP           ← explicit VP-level PP
       | V PP
       | V ADV
       | AUX V
```

The key insight: **both `S → NP VP PP` and `NP → DET N PP` produce grammatically valid trees for the same input**. Your exhaustive parser will find both.

---

## 5. Ambiguity: What to Show the User

### Unambiguous sentence
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: UNAMBIGUOUS — exactly 1 valid parse
========================================

Parse Tree:
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"

Symbol Table:
...
```

### Ambiguous sentence
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: AMBIGUOUS — 2 possible parses detected
========================================

--- Parse 1 of 2 ---
[tree 1]
Interpretation: The prepositional phrase modifies the verb (VP attachment)

--- Parse 2 of 2 ---
[tree 2]
Interpretation: The prepositional phrase modifies the object noun (NP attachment)

Symbol Table (based on Parse 1):
...
Note: Symbol table roles differ between parses — shown for Parse 1 only.
```

### Failed parse
```
Error: Could not parse input as a valid sentence or expression.
Input: "foxes the over"
Tip: Check that the sentence follows Subject-Verb or Subject-Verb-Object order.
```

### Numerical function (always unambiguous)
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Input type: Arithmetic / Numerical Expression
 Verdict: UNAMBIGUOUS (operator precedence enforced by grammar)
========================================

Parse Tree:
EXPR
└── ...
```

---

## 6. Debugging Notes

| Symptom | Cause | Fix |
|---------|-------|-----|
| `parse_all()` returns only 1 tree for known ambiguous sentence | `parse_VP_all()` stops after first match | Each rule attempt must push to `results` independently, not early-return |
| Duplicate trees (same structure returned twice) | Two grammar rules produce identical trees for the same token span | After collecting all `AltResult`, deduplicate by comparing tree structure (label + children recursively) |
| `FUNC` token not recognized | Function name in input is uppercase; dict lookup case-sensitive | Lowercase before lookup in `assign_pos()` |
| `parse_ARGLIST()` fails on `pow(2, 8)` | Comma not tokenized as a separate token | Update `Lexer::split_words()` to emit `,` as its own COMMA token |
| Nested function parse fails | `parse_FACTOR()` doesn't recurse into `EXPR` for function args | `parse_ARGLIST()` calls `parse_EXPR_all()` — confirm it's not calling `parse_FACTOR_all()` directly |
| All sentences reported as ambiguous | `parse_NP_all()` always returns both `DET N` and `DET N PP` even when no PP exists | `parse_NP_all()` rule `DET N PP` must only add a result when `parse_PP_all()` returns non-empty |

---

## 7. AGENT.md Additions

Copy-paste the following two phase blocks into `AGENT.md` after Phase 6.

---

### Phase 7 — Numerical Functions
**Goal:** Parse named mathematical functions with arguments; produce correct nested trees.

- [ ] Add `POS::FUNC`, `POS::COMMA` to POS enum in `include/pos_dict.h`
- [ ] Add `MATH_FUNCS` unordered_set in `src/lexer.cpp`; tag function names as `POS::FUNC`
- [ ] Update `Lexer::split_words()` to emit `(`, `)`, `,` as single-character tokens
- [ ] Update `detect_input_type()` to return `EXPRESSION` when any token has `POS::FUNC`
- [ ] Implement `parse_FACTOR()` extension: handle `FUNC '(' ARGLIST ')'` case
- [ ] Implement `parse_ARGLIST()`: parse first `EXPR`, then loop consuming `COMMA EXPR` pairs
- [ ] Implement unary minus: `FACTOR → '-' FACTOR` (recursive, handles `abs(-5)`)
- [ ] Add `"FUNC_CALL"` and `"ARGLIST"` as valid non-terminal labels in the display renderer
- [ ] Add grammar roles to symbol table: `"FUNC_CALL.name"` and `"FUNC_CALL.arg[N]"` where N is 0-indexed
- [ ] Test with: `sin(45)`, `pow(2, 8)`, `sqrt(pow(3,2) + pow(4,2))`, `max(1, min(5, 3))`, `abs(-7)`
- [ ] Write `tests/test_functions.cpp` with at least 5 test cases including a nested call

**Phase 7 complete when:** `./english-parser "sqrt(pow(3,2) + pow(4,2))"` produces a correct nested tree and symbol table with `grammar_role == "FUNC_CALL.name"` for `sqrt` and `pow`.

---

### Phase 8 — Ambiguity Detection
**Goal:** Detect and report all valid parse trees for a given input; classify as Ambiguous or Unambiguous.

- [ ] Add `AltResult` struct to `include/parse_tree.h`
- [ ] Add `AmbiguityResult` struct to `include/parse_tree.h`
- [ ] Refactor `TopDownParser::parse_S()`, `parse_NP()`, `parse_VP()`, `parse_PP()` into `_all()` variants returning `vector<AltResult>`
- [ ] Keep original `parse()` as a wrapper calling `parse_all()[0]` — backward compatible with Phase 3–6 tests
- [ ] Add grammar rule `NP → DET N PP` to `parse_NP_all()` — this is the second source of PP attachment
- [ ] Add grammar rule `S → NP VP PP` to `parse_S_all()` — first source of PP attachment
- [ ] Implement deduplication: after collecting all trees, remove structurally identical ones (recursive label+children compare)
- [ ] Implement `derive_interpretation(const ParseNode*)` — template string based on PP attachment site
- [ ] Implement `Display::print_ambiguity_result(const AmbiguityResult&)`:
      - If `failed()`: print error message + tip
      - If `!is_ambiguous()`: print single tree with `"UNAMBIGUOUS"` header
      - If `is_ambiguous()`: print all trees numbered, each with interpretation line
- [ ] Mark all EXPRESSION inputs as UNAMBIGUOUS automatically (skip exhaustive search)
- [ ] Write `tests/test_ambiguity.cpp`:
      - `"The dog runs"` → unambiguous
      - `"I saw the man with the telescope"` → ambiguous (2 trees)
      - `"She ate the cake on the table"` → ambiguous (2 trees)
      - `"He runs"` → unambiguous
      - `"3 + 4 * 2"` → unambiguous (expression)
- [ ] Update `main.cpp` to use `parse_all()` and `AmbiguityResult` instead of single `parse()`

**Phase 8 complete when:** `./english-parser "I saw the man with the telescope"` outputs exactly 2 parse trees with correct interpretation labels and `AMBIGUOUS` verdict.

---

## 8. ROADMAP.md Additions

Copy-paste the following two phase blocks into `ROADMAP.md` after Phase 6.

---

### Phase 7 — Numerical Functions

**Goal:** Extend the expression grammar to handle named mathematical functions with one or more arguments, including nested calls.

**In scope:**
- `POS::FUNC` token type + function name dictionary
- `,` (COMMA) as a distinct token
- Grammar rules: `FACTOR → FUNC '(' ARGLIST ')'`, `ARGLIST → EXPR (',' EXPR)*`
- Unary minus: `FACTOR → '-' FACTOR`
- Symbol table roles: `FUNC_CALL.name`, `FUNC_CALL.arg[N]`
- Tests: 5+ cases including nested function calls

**Out of scope:**
- Evaluating the function (computing `sin(45)` — this is a parser, not a calculator)
- User-defined functions (only built-in names listed in `MATH_FUNCS`)
- Variable/symbol arguments (only numeric `EXPR` as args — no `x`, `y`)

**Success criteria:**
- `sqrt(pow(3,2) + pow(4,2))` produces a correct deeply-nested tree
- Symbol table shows `sqrt` as `FUNC_CALL.name`, `3` as `FUNC_CALL.arg[0]`, `2` as `FUNC_CALL.arg[1]` (inside inner `pow`)
- All Phase 3–6 tests still pass (no regression)

**Key implementation notes:**
- `parse_ARGLIST()` must stop on `)` — check that current token is not `)` before consuming COMMA
- Unary minus binds tighter than binary minus — it's in `FACTOR`, not `EXPR`
- `max(1, 2, 3)` (3 arguments) must work — `ARGLIST` loop handles variable arity

---

### Phase 8 — Ambiguity Detection

**Goal:** Run exhaustive parsing to find all valid parse trees; classify each input as Ambiguous or Unambiguous; display all trees with interpretation hints.

**In scope:**
- `_all()` variants of all parse functions returning `vector<AltResult>`
- Grammar extended with NP-level PP attachment (`NP → DET N PP`)
- Deduplication of structurally identical trees
- `derive_interpretation()` for PP attachment ambiguity
- `AmbiguityResult` struct and updated `Display` output
- Automatic UNAMBIGUOUS classification for all expression inputs
- 5 test cases for ambiguity detection

**Out of scope:**
- Detecting ambiguity types other than PP attachment (e.g. coordination scope, verb/noun homonymy)
- Ranking parses by likelihood (no probability model)
- Bottom-up exhaustive parsing (ambiguity detection applies to top-down mode only)
- Generating natural language explanations beyond the template strings

**Success criteria:**
- `"The dog runs"` → `UNAMBIGUOUS (1 parse)`
- `"I saw the man with the telescope"` → `AMBIGUOUS (2 parses)` with distinct trees
- `"3 + 4 * 2"` → `UNAMBIGUOUS` (expression, auto-classified)
- No duplicate trees reported for any input
- Original `parse()` (single result) still works — all Phase 3–6 tests pass

**Key implementation notes:**
- The deduplication step is essential — without it, some inputs produce 3–4 copies of the same tree from different rule orderings
- Structural comparison: two trees are identical if their labels match and all children are pairwise identical (recursive)
- The `_all()` refactor must pass the cursor by value into each alternative attempt, not by reference — otherwise one attempt's cursor advancement pollutes the next attempt
