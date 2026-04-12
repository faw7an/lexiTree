# English Parse Tree Compiler — Project Guide

**Language:** C++17  
**Domain:** Compiler Design · Natural Language Processing · Formal Grammar  
**Scope:** Takes an English sentence or arithmetic expression, produces an annotated parse tree (ASCII + structured), a symbol table, and identifies the parsing strategy used (top-down or bottom-up).

---

## Table of Contents
1. [How an English Compiler Works](#1-how-an-english-compiler-works)
2. [Project Structure](#2-project-structure)
3. [Recommended Libraries](#3-recommended-libraries)
4. [Testing Strategy](#4-testing-strategy)
5. [Debugging Decision Tree](#5-debugging-decision-tree)

---

## 1. How an English Compiler Works

### 1.1 Pipeline Overview

A traditional compiler has three front-end stages. This project maps those same stages onto natural language:

```
INPUT (English string)
        │
        ▼
┌───────────────┐
│  LEXER        │  Splits text into tokens (words + punctuation)
│  (Tokenizer)  │  Tags each word with a Part-of-Speech (POS)
└───────┬───────┘
        │  Token stream: [(word, POS), ...]
        ▼
┌───────────────┐
│  PARSER       │  Applies CFG grammar rules
│               │  Builds the parse tree
│               │  Top-Down OR Bottom-Up mode
└───────┬───────┘
        │  ParseTree*
        ▼
┌───────────────┐
│  SYMBOL TABLE │  Extracts nouns, verbs, adjectives into
│  BUILDER      │  a structured lookup table
└───────┬───────┘
        │
        ▼
┌───────────────┐
│  DISPLAY      │  Renders ASCII tree + symbol table to stdout
└───────────────┘
```

### 1.2 Lexical Analysis (Tokenization + POS Tagging)

The lexer does two jobs in one pass:

**Tokenization** — split the input string into words. Handle punctuation by stripping or isolating it.

```
"The quick brown fox jumps over the lazy dog."
→ ["The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"]
```

**POS Tagging** — assign each word a grammatical category. You can implement a simplified rule-based tagger using a dictionary:

| Tag  | Category      | Examples                          |
|------|---------------|-----------------------------------|
| DET  | Determiner    | the, a, an, this, that            |
| N    | Noun          | fox, dog, cat, man, city          |
| V    | Verb          | runs, jumps, eats, is, sees       |
| ADJ  | Adjective     | quick, brown, lazy, tall, happy   |
| ADV  | Adverb        | quickly, slowly, very, soon       |
| PREP | Preposition   | over, under, in, on, at, by, to   |
| PRON | Pronoun       | he, she, it, they, I, you         |
| CONJ | Conjunction   | and, or, but, because, although   |
| AUX  | Auxiliary     | is, was, were, has, have, can     |
| NUM  | Number        | one, two, 42, 3.14                |

Your dictionary is a `std::unordered_map<std::string, POS>`. For unknown words, apply suffix heuristics:
- ends in `-ing` → V (gerund) or ADJ (participial)
- ends in `-ly` → ADV
- ends in `-ed` → V (past tense)
- ends in `-tion`, `-ness`, `-ment` → N
- starts uppercase mid-sentence → PROPER_N

### 1.3 Context-Free Grammar (CFG) for English

Your grammar defines legal sentence structures. This is the ruleset your parser enforces.

**Sentence Grammar:**
```
S   → NP VP
    | NP VP PP

NP  → DET N
    | DET ADJ N
    | DET ADJ ADJ N
    | PRON
    | N
    | PROPER_N

VP  → V
    | AUX V
    | V NP
    | V NP PP
    | V PP
    | V ADV

PP  → PREP NP

ADJ_LIST → ADJ
         | ADJ ADJ_LIST
```

**Expression Grammar (for arithmetic input):**
```
EXPR   → TERM (('+' | '-') TERM)*
TERM   → FACTOR (('*' | '/') FACTOR)*
FACTOR → NUM
       | '(' EXPR ')'
```

> The parser detects whether the input is an English sentence or an arithmetic expression by checking the first token. If it's a number or if the string contains operators (`+`, `-`, `*`, `/`), route to the expression parser; otherwise, route to the sentence parser.

### 1.4 Parse Tree

The parse tree is the central data structure. Each node has:
- A **label** (the grammar symbol: `S`, `NP`, `VP`, `V`, `N`, etc.)
- A **value** (for leaf nodes: the actual word)
- A list of **children**

```cpp
struct ParseNode {
    std::string label;    // "NP", "VP", "V", "the", etc.
    std::string value;    // only set for terminals (leaves)
    bool is_terminal;
    std::vector<std::unique_ptr<ParseNode>> children;
};
```

**ASCII Tree Display** — render the tree to stdout using indentation + connectors:

```
S
├── NP
│   ├── DET: "The"
│   └── N:   "fox"
└── VP
    ├── V:   "jumps"
    └── PP
        ├── PREP: "over"
        └── NP
            ├── DET: "the"
            └── N:   "fence"
```

The rendering algorithm: recursively walk the tree; for each child, print the right prefix (`├──` for non-last children, `└──` for the last child). Thread the vertical bar `│` down through siblings.

### 1.5 Top-Down Parsing (Recursive Descent)

**Strategy:** Start from the start symbol `S`, try to predict which rule to apply based on the next token (lookahead), and recurse down.

```
parseS()  →  calls parseNP(), parseVP()
parseNP() →  looks at current token:
               if DET → apply "DET N" or "DET ADJ N"
               if PRON → apply "PRON"
               else    → try bare N
parseVP() →  looks at current token:
               if V → try V, V NP, V NP PP, V PP, V ADV
```

**Key implementation notes:**
- Maintain a **cursor** (index into token array). Each `parse*()` function advances the cursor as it consumes tokens.
- Use **backtracking** when multiple rules could apply: save cursor position, try a rule, if it fails restore cursor and try the next.
- This is **LL(1)** parsing — one token of lookahead. Most English sentences are unambiguous at this level.
- Return `nullptr` on failure, a valid `ParseNode*` on success.

**When to use:** This is the default mode. Label your output with `"Parsing strategy: Top-Down (Recursive Descent)"`.

### 1.6 Bottom-Up Parsing (Shift-Reduce)

**Strategy:** Start with individual tokens, apply grammar rules in reverse to reduce groups of tokens into non-terminals, working up to `S`.

Two operations on a **stack**:
- **SHIFT** — push the next input token onto the stack
- **REDUCE** — pop the top N items from the stack that match the RHS of a rule, push the LHS

```
Input: "The fox jumps"
Stack: []

SHIFT "The"  → Stack: [The/DET]
SHIFT "fox"  → Stack: [The/DET, fox/N]
REDUCE NP → DET N  → Stack: [NP]
SHIFT "jumps" → Stack: [NP, jumps/V]
REDUCE VP → V  → Stack: [NP, VP]
REDUCE S → NP VP  → Stack: [S]  ✓ ACCEPT
```

**Key implementation notes:**
- Implement the stack as `std::vector<StackItem>` where each `StackItem` holds a `ParseNode*` plus its grammar symbol.
- The parser table (what to shift vs reduce) can be a simple hand-coded priority: always try to reduce before shifting if a valid reduction exists.
- This is an **LR(0)** style parser — simpler than full LR(1) but sufficient for the grammar defined above.
- When you successfully reduce, build the `ParseNode`: create a new non-terminal node, attach the popped nodes as children.
- Label your output with `"Parsing strategy: Bottom-Up (Shift-Reduce)"`.

**When to use:** Offer this as a `--bottom-up` flag. Or switch automatically when the input is an arithmetic expression.

### 1.7 Symbol Table

The symbol table records all meaningful words found in the input. It is built from the completed parse tree (not during parsing — post-pass).

```
┌──────────────────────────────────────────────────────────────────┐
│                        SYMBOL TABLE                              │
├────────┬──────────┬──────────┬────────────────┬─────────────────┤
│ Index  │ Lexeme   │ POS Tag  │ Grammar Role   │ Scope           │
├────────┼──────────┼──────────┼────────────────┼─────────────────┤
│ 1      │ The      │ DET      │ NP.determiner  │ Sentence        │
│ 2      │ fox      │ N        │ NP.head        │ Sentence        │
│ 3      │ jumps    │ V        │ VP.head        │ Sentence        │
│ 4      │ over     │ PREP     │ PP.head        │ Prepositional   │
│ 5      │ the      │ DET      │ NP.determiner  │ Prepositional   │
│ 6      │ fence    │ N        │ NP.head        │ Prepositional   │
└────────┴──────────┴──────────┴────────────────┴─────────────────┘
```

Implement as `std::vector<SymbolEntry>` where each entry has: index, lexeme, pos_tag, grammar_role, scope.

The "Grammar Role" is derived by traversing the parse tree and noting which node each terminal falls under. For example, a noun that is the direct child of `NP` has role `NP.head`; a verb that is the direct child of `VP` has role `VP.head`.

### 1.8 Runtime Flow

```
User Input
    │
    ▼
main()
    │── detect_input_type() ──► "sentence" or "expression"
    │
    ├── [sentence] ──► Lexer::tokenize(input)
    │                     │
    │                     ▼ token stream
    │               Parser::parse_top_down()  OR  Parser::parse_bottom_up()
    │                     │
    │                     ▼ ParseTree root
    │               SymbolTableBuilder::build(root)
    │                     │
    │                     ▼ SymbolTable
    │               Display::print_tree(root)
    │               Display::print_symbol_table(table)
    │               Display::print_strategy("Top-Down" | "Bottom-Up")
    │
    └── [expression] ──► same flow, expression grammar
```

---

## 2. Project Structure

```
english-parser/
├── CMakeLists.txt           # Build config
├── README.md
├── AGENT.md
├── ROADMAP.md
│
├── include/
│   ├── lexer.h              # Tokenizer + POS tagger declarations
│   ├── parser.h             # Base Parser class
│   ├── top_down_parser.h    # Recursive descent parser
│   ├── bottom_up_parser.h   # Shift-reduce parser
│   ├── parse_tree.h         # ParseNode + ParseTree structs
│   ├── symbol_table.h       # SymbolEntry + SymbolTable
│   ├── display.h            # ASCII tree + table rendering
│   └── pos_dict.h           # POS dictionary + heuristics
│
├── src/
│   ├── main.cpp             # Entry point, argument handling
│   ├── lexer.cpp            # Tokenizer implementation
│   ├── pos_dict.cpp         # Dictionary data + suffix rules
│   ├── top_down_parser.cpp  # Recursive descent parse*() functions
│   ├── bottom_up_parser.cpp # Shift-reduce stack machine
│   ├── parse_tree.cpp       # Node construction, tree traversal
│   ├── symbol_table.cpp     # Post-parse tree walk, table building
│   └── display.cpp          # Rendering logic
│
└── tests/
    ├── test_lexer.cpp        # POS tagging unit tests
    ├── test_top_down.cpp     # Parse tree correctness for known sentences
    ├── test_bottom_up.cpp    # Shift-reduce correctness
    ├── test_symbol_table.cpp # Symbol table extraction
    └── fixtures/
        ├── sentences.txt     # Sample inputs (one per line)
        └── expected/         # Expected tree output (for diff testing)
```

### Module Mini-Specs

**`lexer.h / lexer.cpp`**
```cpp
struct Token {
    std::string word;
    POS         tag;
    int         position;   // 0-indexed position in input
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();       // main entry point
private:
    std::vector<std::string> split_words(const std::string& s);
    POS assign_pos(const std::string& word);
};
```

**`parse_tree.h`**
```cpp
enum class NodeType { TERMINAL, NON_TERMINAL };

struct ParseNode {
    std::string label;                              // "NP", "VP", "N", etc.
    std::string lexeme;                             // only for terminals
    NodeType    type;
    std::vector<std::unique_ptr<ParseNode>> children;

    void add_child(std::unique_ptr<ParseNode> child);
    bool is_leaf() const { return type == NodeType::TERMINAL; }
};
```

**`top_down_parser.h`**
```cpp
class TopDownParser {
public:
    explicit TopDownParser(std::vector<Token> tokens);
    std::unique_ptr<ParseNode> parse();    // returns root or nullptr on failure

private:
    std::vector<Token>  tokens_;
    size_t              cursor_;

    std::unique_ptr<ParseNode> parse_S();
    std::unique_ptr<ParseNode> parse_NP();
    std::unique_ptr<ParseNode> parse_VP();
    std::unique_ptr<ParseNode> parse_PP();
    std::unique_ptr<ParseNode> parse_ADJ_list();

    Token& current();
    Token& peek(int offset = 0);
    bool   consume(POS expected, ParseNode* parent);
    bool   at_end() const;
};
```

**`bottom_up_parser.h`**
```cpp
struct StackItem {
    std::unique_ptr<ParseNode> node;
    std::string symbol;   // the grammar symbol this node represents
};

class BottomUpParser {
public:
    explicit BottomUpParser(std::vector<Token> tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token>    tokens_;
    size_t                input_pos_;
    std::vector<StackItem> stack_;

    void   shift();
    bool   try_reduce();
    bool   reduce_NP();
    bool   reduce_VP();
    bool   reduce_PP();
    bool   reduce_S();
    bool   stack_top_matches(std::vector<std::string> pattern);
};
```

**`symbol_table.h`**
```cpp
struct SymbolEntry {
    int         index;
    std::string lexeme;
    std::string pos_tag;        // "N", "V", "DET", etc.
    std::string grammar_role;   // "NP.head", "VP.head", etc.
    std::string scope;          // "Sentence", "Prepositional", etc.
};

class SymbolTable {
public:
    void build(const ParseNode* root);
    void print() const;
    const std::vector<SymbolEntry>& entries() const;

private:
    std::vector<SymbolEntry> entries_;
    int counter_ = 1;
    void traverse(const ParseNode* node, const std::string& scope);
};
```

**`display.h`**
```cpp
class Display {
public:
    static void print_tree(const ParseNode* root);
    static void print_symbol_table(const SymbolTable& table);
    static void print_strategy(const std::string& name);

private:
    static void print_node(const ParseNode* node,
                           const std::string& prefix,
                           bool is_last);
};
```

---

## 3. Recommended Libraries

This project is intentionally self-contained. No heavy NLP frameworks are needed. All dependencies should be available via your system package manager or CMake FetchContent.

| Library      | Version  | Purpose                          | Install              |
|--------------|----------|----------------------------------|----------------------|
| Google Test  | 1.14.0   | Unit testing framework           | CMake FetchContent   |
| tabulate     | 1.5      | Pretty table printing (optional) | CMake FetchContent   |

> For the symbol table display, you can use `tabulate` (header-only C++ library) for clean aligned columns, or implement your own printf-based column padding — the latter is simpler for a university project.

**CMake FetchContent for GoogleTest:**
```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
```

**CMakeLists.txt skeleton:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(EnglishParser CXX)
set(CMAKE_CXX_STANDARD 17)

# Main executable
add_executable(english-parser
    src/main.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    src/top_down_parser.cpp
    src/bottom_up_parser.cpp
    src/parse_tree.cpp
    src/symbol_table.cpp
    src/display.cpp
)
target_include_directories(english-parser PRIVATE include)

# Tests
enable_testing()
# ... FetchContent GoogleTest ...
add_executable(run_tests
    tests/test_lexer.cpp
    tests/test_top_down.cpp
    tests/test_bottom_up.cpp
    tests/test_symbol_table.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    src/top_down_parser.cpp
    src/bottom_up_parser.cpp
    src/parse_tree.cpp
    src/symbol_table.cpp
    src/display.cpp
)
target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests GTest::gtest_main)
```

---

## 4. Testing Strategy

### Layer 1: Lexer / POS Tagger Unit Tests

Test individual word tagging:
```cpp
TEST(LexerTest, Determiners) {
    Lexer l("the");
    auto tokens = l.tokenize();
    EXPECT_EQ(tokens[0].tag, POS::DET);
}
TEST(LexerTest, SuffixHeuristic_ly) {
    Lexer l("quickly");
    auto tokens = l.tokenize();
    EXPECT_EQ(tokens[0].tag, POS::ADV);
}
```

### Layer 2: Parser Unit Tests

For each grammar rule, write one sentence that should parse and one that should not:
```cpp
TEST(TopDownTest, SimpleSentence) {
    // "The cat sat" → S → NP VP
    auto tree = parse("The cat sat");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}
TEST(TopDownTest, FailsOnNonsense) {
    auto tree = parse("jumps the the");
    EXPECT_EQ(tree, nullptr);
}
```

### Layer 3: Symbol Table Tests

Given a known parse tree, verify symbol table entries:
```cpp
TEST(SymbolTableTest, ExtractsVerb) {
    auto tree = parse("The dog runs");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();
    auto verb_it = std::find_if(entries.begin(), entries.end(),
        [](auto& e){ return e.pos_tag == "V"; });
    EXPECT_NE(verb_it, entries.end());
    EXPECT_EQ(verb_it->lexeme, "runs");
    EXPECT_EQ(verb_it->grammar_role, "VP.head");
}
```

### Layer 4: End-to-End / Fixture Tests

Run the full binary against sample sentences and diff the output against golden files:
```bash
# In tests/fixtures/
./english-parser "The quick brown fox jumps over the lazy dog" > out.txt
diff out.txt tests/fixtures/expected/quick_fox.txt
```

---

## 5. Debugging Decision Tree

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| `parse()` returns `nullptr` for a valid sentence | POS tagger wrong-tagged a word (e.g. "runs" tagged as N instead of V) | Print token stream before parsing; check `pos_dict.cpp` |
| Parse tree has wrong depth (extra nesting or missing levels) | A `parse_NP()` consumed too many tokens; cursor advanced past correct boundary | Add `cursor_` print before/after each `parse_*()` call |
| Shift-reduce parser loops indefinitely | `try_reduce()` always returns true even with no match, causing infinite loop | Check that `try_reduce()` returns `false` when no pattern matches |
| Bottom-up stack doesn't reach S | A grammar rule pattern is incorrect (wrong symbol names) | Print the stack state after each shift/reduce step |
| Symbol table has missing entries | Tree traversal skips a subtree (e.g. PP children not visited) | Add `assert(node != nullptr)` at start of `traverse()`; trace the tree |
| ASCII tree renders with wrong connectors | `is_last` flag computed incorrectly; off-by-one in children index | Print `children.size()` and the current child index explicitly |
| Unknown words all get the same wrong POS | Suffix heuristic isn't being reached; dictionary lookup short-circuits | Check that unknown-word path (not in dict) falls through to suffix rules |
| Expression parser fails on multi-digit numbers | Tokenizer splits `42` into `4` and `2` (character-by-character) | Tokenizer must use `isdigit()` loop to accumulate full number tokens |
| Segfault on `children[i]` access | `unique_ptr` child was moved out of the tree mid-traversal | Never `std::move` children after tree is built; use `const ParseNode*` in traversal |
| Ambiguous sentence produces wrong parse | Backtracking not restoring cursor correctly | Save `size_t saved = cursor_` before trying alternative; restore on failure |
