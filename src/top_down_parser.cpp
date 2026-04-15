#include "top_down_parser.h"

TopDownParser::TopDownParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), cursor_(0) {}

std::unique_ptr<ParseNode> TopDownParser::parse() {
    cursor_ = 0;

    bool is_expr = false;
    for (const auto& token : tokens_) {
        if (token.tag == POS::OP) {
            is_expr = true;
            break;
        }
    }
    if (!is_expr && tokens_.size() > 0) {
        is_expr = true;
        for (const auto& token : tokens_) {
            if (token.tag != POS::NUM && token.tag != POS::OP && token.tag != POS::LPAREN && token.tag != POS::RPAREN) {
                is_expr = false;
                break;
            }
        }
    }

    std::unique_ptr<ParseNode> root;
    if (is_expr) {
        root = parse_EXPR();
    } else {
        root = parse_S();
    }
    
    if (root && at_end()) {
        return root;
    }
    
    return nullptr;
}

const Token& TopDownParser::current() const {
    if (at_end()) {
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
    
    POS actual = current().tag;
    bool match = (actual == expected);
    
    // Fallback for V/N ambiguity
    if (!match) {
        if (expected == POS::N && actual == POS::V) match = true;
        else if (expected == POS::V && actual == POS::N) match = true;
    }

    if (match) {
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
    std::unique_ptr<ParseNode> s_node = nullptr;
    
    // S -> ADV S (Handles Wh- questions like "Why do we...")
    auto s_adv_s = std::make_unique<ParseNode>();
    s_adv_s->label = "S";
    s_adv_s->type = NodeType::NON_TERMINAL;
    if (consume(POS::ADV, s_adv_s.get())) {
        if (auto s_child = parse_S()) {
            s_adv_s->add_child(std::move(s_child));
            s_node = std::move(s_adv_s);
        }
    }
    if (!s_node) cursor_ = saved_cursor;

    if (!s_node) {
        auto s_conj_s_s = std::make_unique<ParseNode>();
        s_conj_s_s->label = "S";
        s_conj_s_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s_s.get())) {
            if (auto s1_child = parse_S()) {
                s_conj_s_s->add_child(std::move(s1_child));
                if (auto s2_child = parse_S()) {
                    s_conj_s_s->add_child(std::move(s2_child));
                    s_node = std::move(s_conj_s_s);
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_conj_s = std::make_unique<ParseNode>();
        s_conj_s->label = "S";
        s_conj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s.get())) {
            if (auto s_child = parse_S()) {
                s_conj_s->add_child(std::move(s_child));
                s_node = std::move(s_conj_s);
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_tag_question = std::make_unique<ParseNode>();
        s_tag_question->label = "S";
        s_tag_question->type = NodeType::NON_TERMINAL;
        if (auto np1 = parse_NP()) {
            s_tag_question->add_child(std::move(np1));
            if (auto vp = parse_VP()) {
                s_tag_question->add_child(std::move(vp));
                if (consume(POS::AUX, s_tag_question.get())) {
                    if (auto np2 = parse_NP()) {
                        s_tag_question->add_child(std::move(np2));
                        s_node = std::move(s_tag_question);
                    }
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_np_vp_conj_np = std::make_unique<ParseNode>();
        s_np_vp_conj_np->label = "S";
        s_np_vp_conj_np->type = NodeType::NON_TERMINAL;
        if (auto np1 = parse_NP()) {
            s_np_vp_conj_np->add_child(std::move(np1));
            if (auto vp = parse_VP()) {
                s_np_vp_conj_np->add_child(std::move(vp));
                if (consume(POS::CONJ, s_np_vp_conj_np.get())) {
                    if (auto np2 = parse_NP()) {
                        s_np_vp_conj_np->add_child(std::move(np2));
                        s_node = std::move(s_np_vp_conj_np);
                    }
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
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
                        s_node = std::move(s_np_aux);
                    }
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s2 = std::make_unique<ParseNode>();
        s2->label = "S";
        s2->type = NodeType::NON_TERMINAL;
        if (auto np = parse_NP()) {
            s2->add_child(std::move(np));
            if (auto vp = parse_VP()) {
                s2->add_child(std::move(vp));
                s_node = std::move(s2);
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_aux = std::make_unique<ParseNode>();
        s_aux->label = "S";
        s_aux->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, s_aux.get())) {
            if (auto np = parse_NP()) {
                s_aux->add_child(std::move(np));
                if (auto vp = parse_VP()) {
                    s_aux->add_child(std::move(vp));
                    s_node = std::move(s_aux);
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    // S -> AUX NP NP (Handles copula questions like "Is that a cat")
    if (!s_node) {
        auto s_aux_np_np = std::make_unique<ParseNode>();
        s_aux_np_np->label = "S";
        s_aux_np_np->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, s_aux_np_np.get())) {
            if (auto np1 = parse_NP()) {
                s_aux_np_np->add_child(std::move(np1));
                if (auto np2 = parse_NP()) {
                    s_aux_np_np->add_child(std::move(np2));
                    s_node = std::move(s_aux_np_np);
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_vp = std::make_unique<ParseNode>();
        s_vp->label = "S";
        s_vp->type = NodeType::NON_TERMINAL;
        if (auto vp = parse_VP()) {
            s_vp->add_child(std::move(vp));
            s_node = std::move(s_vp);
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_intj_s = std::make_unique<ParseNode>();
        s_intj_s->label = "S";
        s_intj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s_intj_s.get())) {
            if (auto s = parse_S()) {
                s_intj_s->add_child(std::move(s));
                s_node = std::move(s_intj_s);
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s_intj_np_adv = std::make_unique<ParseNode>();
        s_intj_np_adv->label = "S";
        s_intj_np_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s_intj_np_adv.get())) {
            if (auto np = parse_NP()) {
                s_intj_np_adv->add_child(std::move(np));
                if (consume(POS::ADV, s_intj_np_adv.get())) {
                    s_node = std::move(s_intj_np_adv);
                }
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s3 = std::make_unique<ParseNode>();
        s3->label = "S";
        s3->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s3.get())) {
            if (auto np = parse_NP()) {
                s3->add_child(std::move(np));
                s_node = std::move(s3);
            }
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (!s_node) {
        auto s4 = std::make_unique<ParseNode>();
        s4->label = "S";
        s4->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s4.get())) {
            s_node = std::move(s4);
        }
        if (!s_node) cursor_ = saved_cursor;
    }

    if (s_node) {
        bool matched = true;
        while (matched) {
            if (auto extra_pp = parse_PP()) {
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(extra_pp));
                s_node = std::move(wrapped);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>();
                leaf->label = "ADV";
                leaf->lexeme = current().word;
                leaf->type = NodeType::TERMINAL;
                cursor_++;
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(leaf));
                s_node = std::move(wrapped);
            } else if (auto extra_s = parse_S()) {
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(extra_s));
                s_node = std::move(wrapped);
            } else {
                matched = false;
            }
        }
        return s_node;
    }
    
    return nullptr;
}




std::unique_ptr<ParseNode> TopDownParser::parse_NP() {
    size_t saved_cursor = cursor_;

    // Attempt from longest to shortest
    auto n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;
    
    // DET NUM ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET V N N
    if (consume(POS::DET, n.get()) && consume(POS::V, n.get()) && consume(POS::N, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET NUM N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET DET N
    if (consume(POS::DET, n.get()) && consume(POS::DET, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // NUM ADJ N
    if (consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET N
    if (consume(POS::DET, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // ADJ N
    if (consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET PROPER_N
    if (consume(POS::DET, n.get()) && consume(POS::PROPER_N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PRON
    if (consume(POS::PRON, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PROPER_N
    if (consume(POS::PROPER_N, n.get())) return n;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // N
    if (consume(POS::N, n.get())) {
        bool matched = true;
        while (matched) {
            if (auto pp = parse_PP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(n)); wrap->add_child(std::move(pp)); n = std::move(wrap);
            } else { matched = false; }
        }
        return n;
    }
    
    return nullptr;
}


std::unique_ptr<ParseNode> TopDownParser::parse_VP() {
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> vp_node = nullptr;

    // 1. AUX + chain (will have been waiting)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, v.get())) {
            size_t checkpoint = cursor_;
            if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            if (consume(POS::ADJ, v.get())) { vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            if (auto np = parse_NP()) { v->add_child(std::move(np)); vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            vp_node = std::move(v); goto finalize;
        }
    }

    // 2. ADJ (happy)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::ADJ, v.get())) { vp_node = std::move(v); goto finalize; }
    }

    // 3. PREP + VP (to give)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::PREP, v.get())) {
            if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
        }
    }

    // 4. V + chain (wants to give / give food)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, v.get())) {
            size_t checkpoint = cursor_;
            // V + NP + NP (give students grades)
            if (auto np1 = parse_NP()) {
                v->add_child(std::move(np1));
                size_t checkpoint2 = cursor_;
                if (auto np2 = parse_NP()) { v->add_child(std::move(np2)); vp_node = std::move(v); goto finalize; }
                else { cursor_ = checkpoint2; vp_node = std::move(v); goto finalize; } // VP -> V NP
            }
            cursor_ = checkpoint;
            // V + PREP + VP (to give)
            if (consume(POS::PREP, v.get())) {
                size_t checkpoint2 = cursor_;
                if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
                else cursor_ = checkpoint;
            }
            cursor_ = checkpoint;
            vp_node = std::move(v); goto finalize; // VP -> V
        }
    }

finalize:
    if (vp_node) {
        bool matched = true;
        while (matched) {
            if (auto pp = parse_PP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(pp)); vp_node = std::move(wrap);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADV"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(leaf)); vp_node = std::move(wrap);
            } else { matched = false; }
        }
        return vp_node;
    }
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
