#include "top_down_parser.h"
#include "pos_dict.h"
#include <iostream>
#include <vector>

int main() {
    load_dictionary("data/dictionary.txt");
    std::vector<Token> tokens = {
        {"The", POS::DET, 0},
        {"boy", POS::N, 1},
        {"runs", POS::V, 2}
    };
    TopDownParser parser(tokens);
    auto root = parser.parse();
    if (root) std::cout << "SUCCESS" << std::endl;
    else std::cout << "FAIL" << std::endl;
    return 0;
}
