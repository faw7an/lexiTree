#include "lexer.h"
#include "top_down_parser.h"
#include "bottom_up_parser.h"
#include "display.h"
#include "pos_dict.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    load_dictionary("data/dictionary.txt");
    std::string input = "The boy runs";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    std::cout << "DEBUG: Tokens size: " << tokens.size() << std::endl;
    for (const auto& t : tokens) {
        std::cout << "DEBUG: Word [" << t.word << "] Tag [" << pos_to_str(t.tag) << "]" << std::endl;
    }
    TopDownParser parser(tokens);
    auto root = parser.parse();
    if (root) {
        std::cout << "DEBUG: SUCCESS" << std::endl;
        Display::print_strategy("Top-Down");
        Display::print_tree(root.get());
    } else {
        std::cout << "DEBUG: FAIL" << std::endl;
    }
    return 0;
}
