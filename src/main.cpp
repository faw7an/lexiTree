#include "lexer.h"
#include "top_down_parser.h"
#include "bottom_up_parser.h"
#include "display.h"
#include "pos_dict.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    load_dictionary("data/dictionary.txt");

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--bottom-up] [--dot filename] \"sentence to parse\"" << std::endl;
        return 1;
    }

    bool use_bottom_up = false;
    std::string dot_filename = "";
    std::string input = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--bottom-up") {
            use_bottom_up = true;
        } else if (arg == "--dot" && i + 1 < argc) {
            dot_filename = argv[++i];
        } else {
            input = arg;
        }
    }

    if (input.empty()) {
        std::cerr << "Error: No input sentence provided." << std::endl;
        return 1;
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
        
        if (!dot_filename.empty()) {
            Display::export_dot(root.get(), dot_filename);
        }
        
        bool is_expr = false;
        for (const auto& token : tokens) {
            if (token.tag == POS::OP) {
                is_expr = true;
                break;
            }
        }
        if (!is_expr && tokens.size() > 0) {
            is_expr = true;
            for (const auto& token : tokens) {
                if (token.tag != POS::NUM && token.tag != POS::OP && token.tag != POS::LPAREN && token.tag != POS::RPAREN) {
                    is_expr = false;
                    break;
                }
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
