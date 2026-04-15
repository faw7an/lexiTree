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
        std::cout << "SUCCESS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    return 0;
}
