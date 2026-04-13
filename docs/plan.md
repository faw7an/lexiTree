# Dictionary System Plan
## How to make the parser handle any word — including Kenyan names, uni jargon, and slang

---

## The Core Problem (and why a bigger list alone won't fully solve it)

English has ~170,000 active words, but **no dictionary can be complete forever**. New names, slang, technical terms, and proper nouns (Maasai Mara, KU, Strathmore, Matatu, Harambee...) will always appear. The real fix is a **layered system** where the dictionary handles known words, smart heuristics handle patterns, and anything left over defaults safely to **Noun (N)** — because unknown words used in a sentence are almost always acting as nouns.

---

## The 3-Layer Architecture

```
Input word
    │
    ▼
Layer 1: Dictionary Lookup          ← dictionary.txt (3800+ entries, exact match)
    │  Found? → return that POS
    │  Not found?
    ▼
Layer 2: Suffix Heuristics          ← patterns in lexer.cpp
    │  -ing → V      (running, sleeping, building)
    │  -ly  → ADV    (quickly, slowly, beautifully)   [min 4 chars — "fly" is NOT ADV]
    │  -ed  → V      (walked, talked, jumped)
    │  -tion/-ness/-ment → N   (action, happiness, payment)
    │  Uppercase mid-sentence → PROPER_N  (Nairobi, Fawzy, Maasai)
    │  Not matched?
    ▼
Layer 3: Default fallback           ← lexer.cpp
    └── return N                    ← ALWAYS noun for unknown words
```

This means:
- **"Maasai"** → not in dict → uppercase mid-sentence → **PROPER_N** ✓  
- **"matatu"** → not in dict → no suffix match → **N** (treated as noun) ✓  
- **"Strathmore"** → not in dict → uppercase → **PROPER_N** ✓  
- **"ugali"** → not in dict → **N** ✓  
- **"kicking"** → not in dict → ends in -ing → **V** ✓  
- **"governmental"** → not in dict → no suffix match → **N** (acceptable fallback)

---

## Step 1: Replace the hardcoded dictionary in `pos_dict.cpp`

The current `pos_dict.cpp` has a `static const unordered_map` baked into the source code with ~100 words. **Replace the entire file** with the version below that:
1. Loads `data/dictionary.txt` at startup
2. Falls back gracefully if the file is missing
3. Returns `POS::UNKNOWN` for unlisted words (lexer then applies heuristics)

### New `src/pos_dict.cpp`

```cpp
#include "pos_dict.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Runtime dictionary — populated by load_dictionary()
static std::unordered_map<std::string, POS> DICTIONARY;

std::string pos_to_str(POS tag) {
    switch(tag) {
        case POS::DET:     return "DET";
        case POS::N:       return "N";
        case POS::V:       return "V";
        case POS::ADJ:     return "ADJ";
        case POS::ADV:     return "ADV";
        case POS::PREP:    return "PREP";
        case POS::PRON:    return "PRON";
        case POS::CONJ:    return "CONJ";
        case POS::AUX:     return "AUX";
        case POS::NUM:     return "NUM";
        case POS::PROPER_N:return "PROPER_N";
        case POS::OP:      return "OP";
        case POS::LPAREN:  return "LPAREN";
        case POS::RPAREN:  return "RPAREN";
        case POS::UNKNOWN: return "UNKNOWN";
        default:           return "UNKNOWN";
    }
}

POS str_to_pos(const std::string& s) {
    if (s == "DET")      return POS::DET;
    if (s == "N")        return POS::N;
    if (s == "V")        return POS::V;
    if (s == "ADJ")      return POS::ADJ;
    if (s == "ADV")      return POS::ADV;
    if (s == "PREP")     return POS::PREP;
    if (s == "PRON")     return POS::PRON;
    if (s == "CONJ")     return POS::CONJ;
    if (s == "AUX")      return POS::AUX;
    if (s == "NUM")      return POS::NUM;
    if (s == "PROPER_N") return POS::PROPER_N;
    if (s == "INTJ")     return POS::INTJ;
    return POS::UNKNOWN;
}

void load_dictionary(const std::string& filename) {
    // Seed with minimal fallback so parser works even without the file
    DICTIONARY = {
        {"the",POS::DET},{"a",POS::DET},{"an",POS::DET},
        {"is",POS::AUX},{"are",POS::AUX},{"was",POS::AUX},
        {"he",POS::PRON},{"she",POS::PRON},{"it",POS::PRON},
        {"they",POS::PRON},{"i",POS::PRON},{"you",POS::PRON},
        {"we",POS::PRON},{"him",POS::PRON},{"her",POS::DET},
        {"and",POS::CONJ},{"but",POS::CONJ},{"or",POS::CONJ},
        {"in",POS::PREP},{"on",POS::PREP},{"at",POS::PREP},
        {"to",POS::PREP},{"over",POS::PREP},{"with",POS::PREP},
    };

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: dictionary file '" << filename
                  << "' not found. Parser will use suffix heuristics only.\n";
        return;
    }

    std::string line;
    int loaded = 0;
    while (std::getline(file, line)) {
        // Strip comments (# to end of line)
        auto hash = line.find('#');
        if (hash != std::string::npos) line = line.substr(0, hash);

        std::istringstream iss(line);
        std::string word, tag_str;
        if (!(iss >> word >> tag_str)) continue;

        POS tag = str_to_pos(tag_str);
        if (tag == POS::UNKNOWN) continue;

        // Lowercase all keys — lookup is always case-insensitive
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c){ return std::tolower(c); });
        DICTIONARY[word] = tag;
        loaded++;
    }
    std::cerr << "Loaded " << loaded << " dictionary entries from " << filename << "\n";
}

POS lookup_word(const std::string& word) {
    auto it = DICTIONARY.find(word);
    return (it != DICTIONARY.end()) ? it->second : POS::UNKNOWN;
}
```

### Updated `src/lexer.cpp` — assign_pos fallback fix

Change the last line of `assign_pos()` from returning `POS::UNKNOWN` to returning `POS::N`:

```cpp
POS Lexer::assign_pos(const std::string& word, bool is_first_word) {
    if (word.empty()) return POS::UNKNOWN;

    // --- operator / numeric tokens ---
    if (word == "+" || word == "-" || word == "*" || word == "/") return POS::OP;
    if (word == "(") return POS::LPAREN;
    if (word == ")") return POS::RPAREN;
    bool all_digits = true;
    for (char c : word) if (!std::isdigit(c)) { all_digits = false; break; }
    if (all_digits) return POS::NUM;

    // --- dictionary lookup (case-insensitive) ---
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    POS tag = lookup_word(lower);
    if (tag != POS::UNKNOWN) return tag;

    // --- suffix heuristics (for words NOT in dictionary) ---
    if (lower.size() > 3 && lower.substr(lower.size()-3) == "ing") return POS::V;
    if (lower.size() >= 4 && lower.substr(lower.size()-2) == "ly")  return POS::ADV;
    if (lower.size() > 2 && lower.substr(lower.size()-2) == "ed")   return POS::V;
    if (lower.size() > 4 &&
       (lower.substr(lower.size()-4) == "tion" ||
        lower.substr(lower.size()-4) == "ness" ||
        lower.substr(lower.size()-4) == "ment"))                    return POS::N;

    // Capitalised mid-sentence → proper noun (Nairobi, Fawzy, Maasai)
    if (!is_first_word && std::isupper(word[0])) return POS::PROPER_N;

    // ── FINAL FALLBACK: unknown words are treated as Nouns ──
    // Names (Wanjiku, Kipchoge, Strathmore), slang (matatu, ugali),
    // technical terms — all work as nouns in a parse tree.
    return POS::N;
}
```

> **The `-ly` fix** on line 4 of the heuristics changes `> 2` to `>= 4`. Without this, the 3-letter word "fly" was matched as ADV (`f-l-y` ends in `ly`). With the fix, only words 4+ characters long get the ADV treatment.

---

## Step 2: Update `main.cpp` to call `load_dictionary()`

Add one line near the top of `main()` before the Lexer is created:

```cpp
int main(int argc, char* argv[]) {
    // ── load dictionary at startup ──
    load_dictionary("data/dictionary.txt");
    // ... rest of main unchanged
```

Make sure `#include "pos_dict.h"` is at the top of `main.cpp` — it likely already is.

---

## Step 3: Place the dictionary file

Put `dictionary.txt` in the `data/` folder of your project:

```
cpp-Project/
├── data/
│   └── dictionary.txt    ← 3800+ entries, this file
├── src/
│   ├── pos_dict.cpp      ← updated (loads from file)
│   ├── lexer.cpp         ← updated (N fallback + -ly fix)
│   └── main.cpp          ← updated (calls load_dictionary)
└── ...
```

Rebuild with:
```bash
g++ -std=c++17 src/*.cpp -Iinclude -o english-parser
./english-parser "The quick brown fox jumps over the lazy dog"
```

---

## Step 4: How to add new words yourself

The dictionary file is plain text — one word per line, format: `word TAG`. Comments start with `#`.

**Example — adding Kenyan/local words:**
```text
# ── Kenyan / local words ──
nairobi N
mombasa N
kisumu N
maasai PROPER_N
kikkikuyu PROPER_N
matatu N
boda N
ugali N
sukuma N
harambee N
safari N
mzungu N
wanjiku PROPER_N
kipchoge PROPER_N
mmu N
strathmore N
kenyatta N
maseno N
egerton N
```

**Example — adding your university's terminology:**
```text
cat N
cat V
cdf N
assignment N
semester N
transcript N
coursework N
elective N
prerequisite N
internship N
dissertation N
```

**Example — fixing a misclassified word:**
If "data" is parsing wrong (it's a plural noun but sometimes used as non-count):
```text
data N
datum N
```

**Rules for adding entries:**
1. One word per line, lowercase
2. Use exactly one tag: `DET N V ADJ ADV PREP PRON CONJ AUX NUM PROPER_N`
3. Lines starting with `#` are comments — use them to organise sections
4. Later entries in the file overwrite earlier ones for the same word
5. Put your custom additions at the **bottom** of the file under `# ── CUSTOM ──`

---

## Step 5: When a word still fails (debugging guide)

If a sentence fails to parse, the problem is almost always a wrong POS tag. Find which word is wrong using this mental checklist:

| Symptom | What to check |
|---------|---------------|
| Parser returns null for `"X verbs"` | Is the verb (e.g. "loves", "drinks") tagged V? Check it's in `dictionary.txt` under V. |
| A noun is being treated as a verb | That word was given V tag in dict. Add it: `wordname N` at bottom of dict. |
| "fly" tagged as ADV | You have the old `> 2` check in `assign_pos`. Change it to `>= 4`. |
| Name like "Nairobi" tagged as N not PROPER_N | It's the first word of the sentence — the uppercase heuristic skips position 0. Add it: `nairobi PROPER_N`. |
| Slang word breaks parse | It's probably UNKNOWN → now defaults to N. If it's acting as a verb (e.g. "vibing"), add `vibing V` to dict. |
| Sentence with "his/her/their" fails NP rule | These are DET in the grammar, not PRON. Both are in the dict as DET. |

---

## Why unknown words default to N (not UNKNOWN)

The parser's grammar rules use POS tags to match tokens. If a word is tagged `UNKNOWN`, no grammar rule ever matches it, and the entire parse fails even if the rest of the sentence is perfect.

Defaulting to `N` means:
- **"Wanjiku runs"** → `PROPER_N V` → parser tries `NP(PROPER_N) VP(V)` → **succeeds** ✓  
- **"The matatu runs"** → `DET N V` → `NP(DET N) VP(V)` → **succeeds** ✓  
- **"Harambee builds communities"** → `N V N` → `NP(N) VP(V NP(N))` → **succeeds** ✓  
- **"jabberwocky"** → `N` → can serve as subject or object ✓

The only case where this fails is if an unknown word is *actually* functioning as a verb, adjective, or preposition in the sentence. In practice, proper names and new nouns appear far more frequently than unknown verbs (which almost always have recognisable -ing/-ed suffixes anyway).

---

## Dictionary Coverage Summary

The generated `dictionary.txt` contains **3,812 entries** covering:

| POS Tag | Count | What's covered |
|---------|-------|----------------|
| V       | 1,689 | ~400 verbs × base/3ps/past/pp/ing forms; all irregular verbs explicit |
| N       | 1,056 | People, body, animals, nature, objects, abstract, African/Kenyan terms |
| ADJ     | 547   | Size, color, emotion, temporal, spatial, academic/technical |
| ADV     | 160   | Degree, frequency, time, place, manner |
| PRON    | 57    | All personal, demonstrative, relative, indefinite pronouns |
| DET     | 38    | Articles, possessives, quantifiers |
| PREP    | 67    | All English prepositions |
| CONJ    | 64    | Coordinating + subordinating conjunctions |
| AUX     | 44    | All modal + be/have/do forms |
| NUM     | 44    | Number words (one–trillion, ordinals) |
| INTJ    | 46    | Interjections (oh, wow, hey, etc.) |

**What it doesn't cover** (handled by fallback):
- Archaic or highly specialised vocabulary
- Proper nouns (people's names, place names) → PROPER_N via uppercase heuristic
- New slang / Swahili / local words → N via default fallback
- Novel compound words → N via default fallback
