#include "lexer.h"
#include "pos_dict.h"
#include <iostream>
#include <vector>

int main() {
    load_dictionary("data/dictionary.txt");
    std::string input = "The boy runs";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    for (const auto& t : tokens) {
        std::cout << t.word << " : " << pos_to_str(t.tag) << std::endl;
    }
    return 0;
}
