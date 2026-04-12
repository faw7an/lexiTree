#include "lexer.h"
#include "top_down_parser.h"
#include "bottom_up_parser.h"
#include "display.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--bottom-up] \"sentence to parse\"" << std::endl;
        return 1;
    }

    bool use_bottom_up = false;
    std::string input = "";

    if (argc >= 3 && std::string(argv[1]) == "--bottom-up") {
        use_bottom_up = true;
        input = argv[2];
    } else {
        input = argv[1];
    }

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    std::unique_ptr<ParseNode> root;

    if (use_bottom_up) {
        BottomUpParser parser(tokens);
        root = parser.parse();
        Display::print_strategy("Bottom-Up (Shift-Reduce)");
    } else {
        TopDownParser parser(tokens);
        root = parser.parse();
        Display::print_strategy("Top-Down (Recursive Descent)");
    }

    if (root) {
        Display::print_tree(root.get());
        
        bool is_expr = false;
        for (const auto& token : tokens) {
            if (token.tag == POS::NUM || token.tag == POS::OP) {
                is_expr = true;
                break;
            }
        }
        
        if (!is_expr) {
            std::cout << "\nSymbol Table:\n";
            SymbolTable table;
            table.build(root.get());
            Display::print_symbol_table(table);
        }
    } else {
        std::cerr << "Error: Could not parse input as a valid sentence or expression." << std::endl;
        return 1;
    }

    return 0;
}
