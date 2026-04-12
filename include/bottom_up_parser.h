#pragma once
#include "lexer.h"
#include "parse_tree.h"
#include <vector>
#include <memory>
#include <string>

struct StackItem {
    std::unique_ptr<ParseNode> node;
    std::string symbol;
};

class BottomUpParser {
public:
    explicit BottomUpParser(const std::vector<Token>& tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token> tokens_;
    size_t input_pos_;
    std::vector<StackItem> stack_;

    void shift();
    bool try_reduce();
    bool reduce_NP();
    bool reduce_VP();
    bool reduce_PP();
    bool reduce_S();
    
    bool stack_top_matches(const std::vector<std::string>& pattern) const;
    bool at_end() const;
};
