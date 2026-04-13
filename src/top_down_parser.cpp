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
    
    // S -> NP AUX NP VP
    auto s_np_aux = std::make_unique<ParseNode>();
    s_np_aux->label = "S";
    s_np_aux->type = NodeType::NON_TERMINAL;
    if (auto np1 = parse_NP()) {
        s_np_aux->add_child(std::move(np1));
        if (consume(POS::AUX, s_np_aux.get())) {
            if (auto np2 = parse_NP()) {
                s_np_aux->add_child(std::move(np2));
                if (auto vp = parse_VP()) {
                    s_np_aux->add_child(std::move(vp));
                    return s_np_aux;
                }
            }
        }
    }
    cursor_ = saved_cursor;

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

    // S -> AUX NP VP
    auto s_aux = std::make_unique<ParseNode>();
    s_aux->label = "S";
    s_aux->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, s_aux.get())) {
        if (auto np = parse_NP()) {
            s_aux->add_child(std::move(np));
            if (auto vp = parse_VP()) {
                s_aux->add_child(std::move(vp));
                return s_aux;
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> VP
    auto s_vp = std::make_unique<ParseNode>();
    s_vp->label = "S";
    s_vp->type = NodeType::NON_TERMINAL;
    if (auto vp = parse_VP()) {
        s_vp->add_child(std::move(vp));
        return s_vp;
    }
    cursor_ = saved_cursor;

    // S -> INTJ S
    auto s_intj_s = std::make_unique<ParseNode>();
    s_intj_s->label = "S";
    s_intj_s->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s_intj_s.get())) {
        if (auto s = parse_S()) {
            s_intj_s->add_child(std::move(s));
            return s_intj_s;
        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ NP ADV
    auto s_intj_np_adv = std::make_unique<ParseNode>();
    s_intj_np_adv->label = "S";
    s_intj_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s_intj_np_adv.get())) {
        if (auto np = parse_NP()) {
            s_intj_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, s_intj_np_adv.get())) {
                return s_intj_np_adv;
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ NP
    auto s3 = std::make_unique<ParseNode>();
    s3->label = "S";
    s3->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s3.get())) {
        if (auto np = parse_NP()) {
            s3->add_child(std::move(np));
            return s3;
        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ
    auto s4 = std::make_unique<ParseNode>();
    s4->label = "S";
    s4->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s4.get())) {
        return s4;
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


    // NP -> DET N N
    auto np_dnn = std::make_unique<ParseNode>();
    np_dnn->label = "NP";
    np_dnn->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dnn.get()) &&
        consume(POS::N, np_dnn.get()) &&
        consume(POS::N, np_dnn.get())) {
        return np_dnn;
    }
    cursor_ = saved_cursor;

    // NP -> N N
    auto np_nn = std::make_unique<ParseNode>();
    np_nn->label = "NP";
    np_nn->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np_nn.get()) &&
        consume(POS::N, np_nn.get())) {
        return np_nn;
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


    // VP -> AUX V NP ADV
    auto vp_avna = std::make_unique<ParseNode>();
    vp_avna->label = "VP";
    vp_avna->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_avna.get()) && consume(POS::V, vp_avna.get())) {
        if (auto np = parse_NP()) {
            vp_avna->add_child(std::move(np));
            if (consume(POS::ADV, vp_avna.get())) {
                return vp_avna;
            }
        }
    }
    cursor_ = saved_cursor;

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


    // VP -> AUX V PP
    auto vp_avp = std::make_unique<ParseNode>();
    vp_avp->label = "VP";
    vp_avp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_avp.get()) && consume(POS::V, vp_avp.get())) {
        if (auto pp = parse_PP()) {
            vp_avp->add_child(std::move(pp));
            return vp_avp;
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V ADV
    auto vp_ava = std::make_unique<ParseNode>();
    vp_ava->label = "VP";
    vp_ava->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_ava.get()) && consume(POS::V, vp_ava.get()) && consume(POS::ADV, vp_ava.get())) {
        return vp_ava;
    }
    cursor_ = saved_cursor;

    // VP -> AUX ADV V
    auto vp_aadv = std::make_unique<ParseNode>();
    vp_aadv->label = "VP";
    vp_aadv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aadv.get()) && consume(POS::ADV, vp_aadv.get()) && consume(POS::V, vp_aadv.get())) {
        return vp_aadv;
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



    // VP -> AUX NP ADV
    auto vp_aux_np_adv = std::make_unique<ParseNode>();
    vp_aux_np_adv->label = "VP";
    vp_aux_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_np_adv.get())) {
        if (auto np = parse_NP()) {
            vp_aux_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, vp_aux_np_adv.get())) {
                return vp_aux_np_adv;
            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX NP PP
    auto vp_anp_pp = std::make_unique<ParseNode>();
    vp_anp_pp->label = "VP";
    vp_anp_pp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_anp_pp.get())) {
        if (auto np = parse_NP()) {
            vp_anp_pp->add_child(std::move(np));
            if (auto pp = parse_PP()) {
                vp_anp_pp->add_child(std::move(pp));
                return vp_anp_pp;
            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX NP
    auto vp_aux_np = std::make_unique<ParseNode>();
    vp_aux_np->label = "VP";
    vp_aux_np->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_np.get())) {
        if (auto np = parse_NP()) {
            vp_aux_np->add_child(std::move(np));
            return vp_aux_np;
        }
    }
    cursor_ = saved_cursor;


    // VP -> AUX ADJ
    auto vp_aux_adj = std::make_unique<ParseNode>();
    vp_aux_adj->label = "VP";
    vp_aux_adj->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_adj.get()) && consume(POS::ADJ, vp_aux_adj.get())) {
        return vp_aux_adj;
    }
    cursor_ = saved_cursor;

    // VP -> AUX VP (Recursive Stacking)
    auto vp_aux_vp = std::make_unique<ParseNode>();
    vp_aux_vp->label = "VP";
    vp_aux_vp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_vp.get())) {
        if (auto vp_child = parse_VP()) {
            vp_aux_vp->add_child(std::move(vp_child));
            return vp_aux_vp;
        }
    }
    cursor_ = saved_cursor;


    // VP -> V NP ADV
    auto vp_vna = std::make_unique<ParseNode>();
    vp_vna->label = "VP";
    vp_vna->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp_vna.get())) {
        if (auto np = parse_NP()) {
            vp_vna->add_child(std::move(np));
            if (consume(POS::ADV, vp_vna.get())) {
                return vp_vna;
            }
        }
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
