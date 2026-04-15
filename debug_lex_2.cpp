#include "lexer.h"
#include "pos_dict.h"
#include <iostream>
#include <vector>

int main() {
    load_dictionary("data/dictionary.txt");
    std::string inputs[] = {"The tall boy quickly runs to the small house", "Dogs chase cats"};
    for (const auto& input : inputs) {
        std::cout << "Input: [" << input << "]" << std::endl;
        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize();
        for (const auto& t : tokens) {
            std::cout << "  Word: [" << t.word << "] Tag: [" << pos_to_str(t.tag) << "]" << std::endl;
        }
    }
    return 0;
}
