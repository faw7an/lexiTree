#pragma once
#include <string>

enum class POS {
    DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM, PROPER_N, OP, LPAREN, RPAREN, UNKNOWN
};

std::string pos_to_str(POS tag);
POS lookup_word(const std::string& word);
