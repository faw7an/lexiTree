#pragma once
#include <string>

enum class POS {
    DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM, PROPER_N, OP, LPAREN, RPAREN, INTJ, UNKNOWN
};

std::string pos_to_str(POS tag);
POS str_to_pos(const std::string& s);
void load_dictionary(const std::string& filename);
POS lookup_word(const std::string& word);
