#include "lexer.h"
#include <iostream>
int main() {
    load_dictionary("data/dictionary.txt");
    Lexer lexer("Maasai Mara University is a big school");
    for (auto& t : lexer.tokenize()) std::cout << t.word << ":" << pos_to_str(t.tag) << " ";
    std::cout << "\n";
}
