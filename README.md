# C++17 English Parse Tree Compiler

## Overview
This project is a custom compiler built in C++17 that analyzes and parses English sentences and basic arithmetic expressions. It processes raw string input through a lexical analyzer, constructs an Abstract Syntax Tree (AST) using either Top-Down or Bottom-Up parsing strategies, and visually renders the resulting parse tree in the terminal. For English sentences, it also generates a structured Symbol Table that categorizes words by their part of speech and grammatical role.

## Features
- **Lexical Analysis**: Custom tokenizer that categorizes words into Parts of Speech (POS) using a built-in dictionary and fallback suffix heuristics (e.g., "-ing", "-ly", "-ed").
- **Top-Down Parsing**: A Recursive Descent parser that processes Context-Free Grammar (CFG) rules with backtracking.
- **Bottom-Up Parsing**: A Shift-Reduce parser implementation utilizing a custom 1-token lookahead to resolve shift/reduce conflicts.
- **AST Visualization**: Renders the Abstract Syntax Tree in a clean, hierarchical ASCII format.
- **Symbol Table Generation**: Performs a post-parse traversal of the AST to extract lexical scopes, grammar roles (e.g., NP.head, VP.auxiliary), and POS tags, presented in a formatted ASCII table.
- **Arithmetic Expressions**: Supports parsing standard math expressions (addition, subtraction, multiplication, division, and parentheses) honoring standard operator precedence.

## Requirements
- C++17 compatible compiler (e.g., g++, clang++)
- Bash (for running test scripts)

## Build Instructions
To compile the project from the source code, run the following command in the project root directory:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o english-parser
```

## Usage
The compiled executable takes a string as input and parses it using the Top-Down parser by default.

### Top-Down Parsing (Default)
```bash
./english-parser "The quick brown fox jumps over the lazy dog"
```

### Bottom-Up Parsing
Use the `--bottom-up` flag to force the parser to use the Shift-Reduce strategy.
```bash
./english-parser --bottom-up "A man is holding a book"
```

### Arithmetic Expressions
Math expressions are evaluated using the Top-Down parser. Note that the symbol table is automatically suppressed for mathematical inputs.
```bash
./english-parser "10 - 2 + 5 * (3 + 4)"
```

## Supported Grammar

### English Sentences
- S -> NP VP | NP VP PP
- NP -> DET ADJ ADJ N | DET ADJ N | DET N | PRON | PROPER_N | N
- VP -> AUX V NP | AUX V | V NP PP | V NP | V PP | V ADV | V
- PP -> PREP NP

### Arithmetic Expressions
- EXPR -> TERM (OP TERM)*
- TERM -> FACTOR (OP FACTOR)*
- FACTOR -> NUM | LPAREN EXPR RPAREN

## Project Structure
- `include/`: Header files defining classes and data structures (`lexer.h`, `top_down_parser.h`, etc.).
- `src/`: Implementation files for the Lexer, Parsers, AST Nodes, and Display utilities.
- `tests/`: Unit tests and fixture files (e.g., `sentences.txt`) for verifying the parser's integrity.
- `run_smoke_tests`: A bash script that verifies the core functionality against a set of predefined grammatical and mathematical inputs.
