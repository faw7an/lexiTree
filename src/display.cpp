#include "display.h"
#include <iostream>

void Display::print_tree(const ParseNode* root) {
    if (!root) return;
    print_node(root, "", true, true);
}

void Display::print_node(const ParseNode* node, const std::string& prefix, bool is_root, bool is_last) {
    if (!is_root) {
        std::cout << prefix << (is_last ? "└── " : "├── ");
    }
    
    if (node->is_leaf()) {
        std::cout << node->label << ": \"" << node->lexeme << "\"\n";
    } else {
        std::cout << node->label << "\n";
    }

    std::string next_prefix = prefix + (is_root ? "" : (is_last ? "    " : "│   "));
    
    for (size_t i = 0; i < node->children.size(); ++i) {
        print_node(node->children[i].get(), next_prefix, false, i == node->children.size() - 1);
    }
}

void Display::print_strategy(const std::string& name) {
    std::cout << "========================================\n";
    std::cout << " Parsing Strategy: " << name << "\n";
    std::cout << "========================================\n\n";
}

void Display::print_symbol_table(const SymbolTable& table) {
    table.print();
}
