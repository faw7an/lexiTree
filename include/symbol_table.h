#pragma once
#include "parse_tree.h"
#include <string>
#include <vector>

struct SymbolEntry {
    int index;
    std::string lexeme;
    std::string pos_tag;
    std::string grammar_role;
    std::string scope;
};

class SymbolTable {
public:
    void build(const ParseNode* root);
    void print() const;
    const std::vector<SymbolEntry>& entries() const;

private:
    std::vector<SymbolEntry> entries_;
    int counter_ = 1;
    void traverse(const ParseNode* node, const std::string& parent_label, const std::string& scope);
};
