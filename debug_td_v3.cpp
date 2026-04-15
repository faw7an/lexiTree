#include "lexer.h"
#include "top_down_parser.h"
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
    TopDownParser parser(tokens);
    auto root = parser.parse();
    if (root) std::cout << "SUCCESS" << std::endl;
    else std::cout << "FAIL" << std::endl;
    return 0;
}
