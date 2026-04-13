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
        case POS::INTJ:    return "INTJ";
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