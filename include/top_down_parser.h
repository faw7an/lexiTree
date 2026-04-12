#pragma once
#include "lexer.h"
#include "parse_tree.h"
#include <vector>
#include <memory>

class TopDownParser {
public:
    explicit TopDownParser(const std::vector<Token>& tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token> tokens_;
    size_t cursor_;

    std::unique_ptr<ParseNode> parse_S();
    std::unique_ptr<ParseNode> parse_NP();
    std::unique_ptr<ParseNode> parse_VP();
    std::unique_ptr<ParseNode> parse_PP();
    std::unique_ptr<ParseNode> parse_ADJ_list();

    std::unique_ptr<ParseNode> parse_EXPR();
    std::unique_ptr<ParseNode> parse_TERM();
    std::unique_ptr<ParseNode> parse_FACTOR();

    const Token& current() const;
    const Token& peek(int offset = 0) const;
    bool consume(POS expected, ParseNode* parent);
    bool at_end() const;
};
