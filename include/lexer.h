#pragma once
#include "pos_dict.h"
#include <string>
#include <vector>

struct Token {
    std::string word;
    POS tag;
    int position;
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input_;
    std::vector<std::string> split_words(const std::string& s);
    POS assign_pos(const std::string& word, bool is_first_word);
};
