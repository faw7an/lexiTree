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
    TopDownParser parser(tokens);
    auto root = parser.parse();
    if (root) {
        Display::print_strategy("Top-Down (Recursive Descent)");
        Display::print_tree(root.get());
    } else {
        std::cerr << "Error: Could not parse input as a valid sentence or expression." << std::endl;
        return 1;
    }
    return 0;
}
