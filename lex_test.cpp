#include "lexer.h"
#include "pos_dict.h"
#include <iostream>
int main() {
    load_dictionary("data/dictionary.txt");
    Lexer lexer("why do we attack exams this week");
    for (auto& t : lexer.tokenize()) std::cout << t.word << ":" << pos_to_str(t.tag) << " ";
    std::cout << "\n";
}