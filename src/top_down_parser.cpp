#include "top_down_parser.h"

TopDownParser::TopDownParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), cursor_(0) {}

std::unique_ptr<ParseNode> TopDownParser::parse() {
    cursor_ = 0;

    bool is_expr = false;
    for (const auto& token : tokens_) {
        if (token.tag == POS::NUM || token.tag == POS::OP) {
            is_expr = true;
            break;
        }
    }

    std::unique_ptr<ParseNode> root;
    if (is_expr) {
        root = parse_EXPR();
    } else {
        root = parse_S();
    }
    
    // To be a fully valid parse, we must have consumed all tokens.
    if (root && at_end()) {
        return root;
    }
    
    return nullptr;
}

const Token& TopDownParser::current() const {
    if (at_end()) {
        // Return a dummy token representing EOF safely
        static const Token EOF_TOKEN{"", POS::UNKNOWN, -1};
        return EOF_TOKEN;
    }
    return tokens_[cursor_];
}

const Token& TopDownParser::peek(int offset) const {
    if (cursor_ + offset >= tokens_.size()) {
        static const Token EOF_TOKEN{"", POS::UNKNOWN, -1};
        return EOF_TOKEN;
    }
    return tokens_[cursor_ + offset];
}

bool TopDownParser::at_end() const {
    return cursor_ >= tokens_.size();
}

bool TopDownParser::consume(POS expected, ParseNode* parent) {
    if (at_end()) return false;
    if (current().tag == expected) {
        auto leaf = std::make_unique<ParseNode>();
        leaf->label = pos_to_str(expected);
        leaf->lexeme = current().word;
        leaf->type = NodeType::TERMINAL;
        parent->add_child(std::move(leaf));
        cursor_++;
        return true;
    }
    return false;
}

std::unique_ptr<ParseNode> TopDownParser::parse_S() {
    size_t saved_cursor = cursor_;
    
    // S -> NP VP PP
    auto s1 = std::make_unique<ParseNode>();
    s1->label = "S";
    s1->type = NodeType::NON_TERMINAL;
    if (auto np = parse_NP()) {
        s1->add_child(std::move(np));
        if (auto vp = parse_VP()) {
            s1->add_child(std::move(vp));
            if (auto pp = parse_PP()) {
                s1->add_child(std::move(pp));
                return s1;
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP VP
    auto s2 = std::make_unique<ParseNode>();
    s2->label = "S";
    s2->type = NodeType::NON_TERMINAL;
    if (auto np = parse_NP()) {
        s2->add_child(std::move(np));
        if (auto vp = parse_VP()) {
            s2->add_child(std::move(vp));
            return s2;
        }
    }
    cursor_ = saved_cursor;
    
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_NP() {
    size_t saved_cursor = cursor_;
    
    // NP -> DET ADJ ADJ N
    auto np1 = std::make_unique<ParseNode>();
    np1->label = "NP";
    np1->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np1.get()) &&
        consume(POS::ADJ, np1.get()) &&
        consume(POS::ADJ, np1.get()) &&
        consume(POS::N, np1.get())) {
        return np1;
    }
    cursor_ = saved_cursor;

    // NP -> DET ADJ N
    auto np2 = std::make_unique<ParseNode>();
    np2->label = "NP";
    np2->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np2.get()) &&
        consume(POS::ADJ, np2.get()) &&
        consume(POS::N, np2.get())) {
        return np2;
    }
    cursor_ = saved_cursor;

    // NP -> DET N
    auto np3 = std::make_unique<ParseNode>();
    np3->label = "NP";
    np3->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np3.get()) &&
        consume(POS::N, np3.get())) {
        return np3;
    }
    cursor_ = saved_cursor;

    // NP -> PRON
    auto np4 = std::make_unique<ParseNode>();
    np4->label = "NP";
    np4->type = NodeType::NON_TERMINAL;
    if (consume(POS::PRON, np4.get())) {
        return np4;
    }
    cursor_ = saved_cursor;

    // NP -> PROPER_N
    auto np5 = std::make_unique<ParseNode>();
    np5->label = "NP";
    np5->type = NodeType::NON_TERMINAL;
    if (consume(POS::PROPER_N, np5.get())) {
        return np5;
    }
    cursor_ = saved_cursor;

    // NP -> N
    auto np6 = std::make_unique<ParseNode>();
    np6->label = "NP";
    np6->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np6.get())) {
        return np6;
    }
    cursor_ = saved_cursor;

    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_VP() {
    size_t saved_cursor = cursor_;

    // VP -> AUX V NP
    auto vp_aux1 = std::make_unique<ParseNode>();
    vp_aux1->label = "VP";
    vp_aux1->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux1.get()) && consume(POS::V, vp_aux1.get())) {
        if (auto np = parse_NP()) {
            vp_aux1->add_child(std::move(np));
            return vp_aux1;
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V
    auto vp_aux2 = std::make_unique<ParseNode>();
    vp_aux2->label = "VP";
    vp_aux2->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux2.get()) && consume(POS::V, vp_aux2.get())) {
        return vp_aux2;
    }
    cursor_ = saved_cursor;

    // VP -> V NP PP
    auto vp1 = std::make_unique<ParseNode>();
    vp1->label = "VP";
    vp1->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp1.get())) {
        if (auto np = parse_NP()) {
            vp1->add_child(std::move(np));
            if (auto pp = parse_PP()) {
                vp1->add_child(std::move(pp));
                return vp1;
            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> V NP
    auto vp2 = std::make_unique<ParseNode>();
    vp2->label = "VP";
    vp2->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp2.get())) {
        if (auto np = parse_NP()) {
            vp2->add_child(std::move(np));
            return vp2;
        }
    }
    cursor_ = saved_cursor;

    // VP -> V PP
    auto vp3 = std::make_unique<ParseNode>();
    vp3->label = "VP";
    vp3->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp3.get())) {
        if (auto pp = parse_PP()) {
            vp3->add_child(std::move(pp));
            return vp3;
        }
    }
    cursor_ = saved_cursor;

    // VP -> V ADV
    auto vp4 = std::make_unique<ParseNode>();
    vp4->label = "VP";
    vp4->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp4.get()) && consume(POS::ADV, vp4.get())) {
        return vp4;
    }
    cursor_ = saved_cursor;

    // VP -> V
    auto vp5 = std::make_unique<ParseNode>();
    vp5->label = "VP";
    vp5->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp5.get())) {
        return vp5;
    }
    cursor_ = saved_cursor;

    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_PP() {
    size_t saved_cursor = cursor_;

    auto pp = std::make_unique<ParseNode>();
    pp->label = "PP";
    pp->type = NodeType::NON_TERMINAL;
    
    if (consume(POS::PREP, pp.get())) {
        if (auto np = parse_NP()) {
            pp->add_child(std::move(np));
            return pp;
        }
    }
    
    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_EXPR() {
    size_t saved_cursor = cursor_;
    auto expr = std::make_unique<ParseNode>();
    expr->label = "EXPR";
    expr->type = NodeType::NON_TERMINAL;

    if (auto term = parse_TERM()) {
        expr->add_child(std::move(term));

        while (current().word == "+" || current().word == "-") {
            auto op = std::make_unique<ParseNode>();
            op->label = "OP";
            op->lexeme = current().word;
            op->type = NodeType::TERMINAL;
            cursor_++;
            expr->add_child(std::move(op));

            if (auto next_term = parse_TERM()) {
                expr->add_child(std::move(next_term));
            } else {
                cursor_ = saved_cursor;
                return nullptr;
            }
        }
        return expr;
    }

    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_TERM() {
    size_t saved_cursor = cursor_;
    auto term = std::make_unique<ParseNode>();
    term->label = "TERM";
    term->type = NodeType::NON_TERMINAL;

    if (auto factor = parse_FACTOR()) {
        term->add_child(std::move(factor));

        while (current().word == "*" || current().word == "/") {
            auto op = std::make_unique<ParseNode>();
            op->label = "OP";
            op->lexeme = current().word;
            op->type = NodeType::TERMINAL;
            cursor_++;
            term->add_child(std::move(op));

            if (auto next_factor = parse_FACTOR()) {
                term->add_child(std::move(next_factor));
            } else {
                cursor_ = saved_cursor;
                return nullptr;
            }
        }
        return term;
    }

    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_FACTOR() {
    size_t saved_cursor = cursor_;
    auto factor = std::make_unique<ParseNode>();
    factor->label = "FACTOR";
    factor->type = NodeType::NON_TERMINAL;

    if (consume(POS::NUM, factor.get())) {
        return factor;
    }

    cursor_ = saved_cursor;
    if (consume(POS::LPAREN, factor.get())) {
        if (auto expr = parse_EXPR()) {
            factor->add_child(std::move(expr));
            if (consume(POS::RPAREN, factor.get())) {
                return factor;
            }
        }
    }

    cursor_ = saved_cursor;
    return nullptr;
}
