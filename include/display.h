#pragma once
#include "parse_tree.h"
#include "symbol_table.h"
#include <string>

class Display {
public:
    static void print_tree(const ParseNode* root);
    static void print_strategy(const std::string& name);
    static void print_symbol_table(const SymbolTable& table);

private:
    static void print_node(const ParseNode* node, const std::string& prefix, bool is_root, bool is_last);
};
