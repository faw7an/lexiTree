#include "lexer.h"
#include <cctype>
#include <sstream>
#include <algorithm>

Lexer::Lexer(const std::string& input) : input_(input) {}

std::vector<std::string> Lexer::split_words(const std::string& s) {
    std::vector<std::string> words;
    std::string current_word = "";
    
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        
        if (std::isspace(c)) {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
            words.push_back(std::string(1, c));
        } else if (c == '.' || c == ',' || c == ':' || c == ';' || c == '!' || c == '?') {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else if (c == '\'') {
            continue; // Strips apostrophe so "won't" becomes "wont"
        } else if (std::isdigit(c)) {
            if (!current_word.empty() && !std::isdigit(current_word[0])) {
                words.push_back(current_word);
                current_word.clear();
            }
            current_word += c;
        } else {
            current_word += c;
        }
    }
    if (!current_word.empty()) {
        words.push_back(current_word);
    }
    return words;
}

POS Lexer::assign_pos(const std::string& word, bool is_first_word) {
    if (word.empty()) return POS::UNKNOWN;
    
    if (word == "+" || word == "-" || word == "*" || word == "/") return POS::OP;
    if (word == "(") return POS::LPAREN;
    if (word == ")") return POS::RPAREN;
    
    bool is_all_digits = true;
    for (char c : word) {
        if (!std::isdigit(c)) {
            is_all_digits = false;
            break;
        }
    }
    if (is_all_digits) return POS::NUM;

    std::string lower_word = word;
    std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                   [](unsigned char c){ return std::tolower(c); });
                   
    if (lower_word == "that") return POS::PRON;

    POS tag = lookup_word(lower_word);
    if (tag != POS::UNKNOWN) {
        return tag;
    }

    if (lower_word.size() > 3 && lower_word.substr(lower_word.size() - 3) == "ing") {
        return POS::V;
    }
    if (lower_word.size() >= 4 && lower_word.substr(lower_word.size() - 2) == "ly") {
        return POS::ADV;
    }
    if (lower_word.size() > 2 && lower_word.substr(lower_word.size() - 2) == "ed") {
        return POS::V;
    }
    if ((lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "tion") ||
        (lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "ness") ||
        (lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "ment")) {
        return POS::N;
    }

    if (!is_first_word && std::isupper(word[0])) {
        return POS::PROPER_N;
    }

    return POS::N;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::vector<std::string> words = split_words(input_);
    
    for (size_t i = 0; i < words.size(); ++i) {
        bool is_first = (i == 0);
        POS tag = assign_pos(words[i], is_first);
        tokens.push_back({words[i], tag, static_cast<int>(i)});
    }
    
    return tokens;
}
