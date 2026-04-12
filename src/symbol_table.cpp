#include "symbol_table.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void SymbolTable::build(const ParseNode* root) {
    entries_.clear();
    counter_ = 1;
    if (root) {
        traverse(root, "", "Sentence");
    }
}

void SymbolTable::traverse(const ParseNode* node, const std::string& parent_label, const std::string& scope) {
    if (!node) return;

    if (node->is_leaf()) {
        std::string role;
        
        if (parent_label == "NP") {
            if (node->label == "DET") role = "NP.determiner";
            else if (node->label == "N" || node->label == "PRON" || node->label == "PROPER_N") role = "NP.head";
            else if (node->label == "ADJ") role = "NP.modifier";
            else role = parent_label + "." + node->label;
        } else if (parent_label == "VP") {
            if (node->label == "V") role = "VP.head";
            else if (node->label == "AUX") role = "VP.auxiliary";
            else if (node->label == "ADV") role = "VP.modifier";
            else role = parent_label + "." + node->label;
        } else if (parent_label == "PP") {
            if (node->label == "PREP") role = "PP.head";
            else role = parent_label + "." + node->label;
        } else {
            role = parent_label + "." + node->label;
        }

        entries_.push_back({counter_++, node->lexeme, node->label, role, scope});
    } else {
        std::string next_scope = scope;
        if (node->label == "PP") {
            next_scope = "Prepositional";
        }
        
        for (const auto& child : node->children) {
            traverse(child.get(), node->label, next_scope);
        }
    }
}

const std::vector<SymbolEntry>& SymbolTable::entries() const {
    return entries_;
}

void SymbolTable::print() const {
    if (entries_.empty()) return;

    // Calculate column widths
    size_t w_idx = 5; // "Index"
    size_t w_lex = 6; // "Lexeme"
    size_t w_pos = 7; // "POS Tag"
    size_t w_rol = 12; // "Grammar Role"
    size_t w_sco = 5; // "Scope"

    for (const auto& e : entries_) {
        w_lex = std::max(w_lex, e.lexeme.length());
        w_pos = std::max(w_pos, e.pos_tag.length());
        w_rol = std::max(w_rol, e.grammar_role.length());
        w_sco = std::max(w_sco, e.scope.length());
    }

    std::string line = "├" + std::string(w_idx + 2, '-') + "┼" 
                     + std::string(w_lex + 2, '-') + "┼" 
                     + std::string(w_pos + 2, '-') + "┼" 
                     + std::string(w_rol + 2, '-') + "┼" 
                     + std::string(w_sco + 2, '-') + "┤\n";
                     
    std::string top_line = "┌" + std::string(w_idx + 2, '-') + "┬" 
                         + std::string(w_lex + 2, '-') + "┬" 
                         + std::string(w_pos + 2, '-') + "┬" 
                         + std::string(w_rol + 2, '-') + "┬" 
                         + std::string(w_sco + 2, '-') + "┐\n";

    std::string bot_line = "└" + std::string(w_idx + 2, '-') + "┴" 
                         + std::string(w_lex + 2, '-') + "┴" 
                         + std::string(w_pos + 2, '-') + "┴" 
                         + std::string(w_rol + 2, '-') + "┴" 
                         + std::string(w_sco + 2, '-') + "┘\n";

    std::cout << top_line;
    std::cout << "│ " << std::left << std::setw(w_idx) << "Index" << " │ "
              << std::setw(w_lex) << "Lexeme" << " │ "
              << std::setw(w_pos) << "POS Tag" << " │ "
              << std::setw(w_rol) << "Grammar Role" << " │ "
              << std::setw(w_sco) << "Scope" << " │\n";
    std::cout << line;

    for (const auto& e : entries_) {
        std::cout << "│ " << std::left << std::setw(w_idx) << e.index << " │ "
                  << std::setw(w_lex) << e.lexeme << " │ "
                  << std::setw(w_pos) << e.pos_tag << " │ "
                  << std::setw(w_rol) << e.grammar_role << " │ "
                  << std::setw(w_sco) << e.scope << " │\n";
    }
    std::cout << bot_line;
}
