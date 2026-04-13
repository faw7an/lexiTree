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
    std::unique_ptr<ParseNode> s_node = nullptr;
    
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
    
    // 0a. NP -> DET NUM N
    auto np_dnn2 = std::make_unique<ParseNode>();
    np_dnn2->label = "NP";
    np_dnn2->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dnn2.get()) && consume(POS::NUM, np_dnn2.get()) && consume(POS::N, np_dnn2.get())) return np_dnn2;
    cursor_ = saved_cursor;

    // 0b. NP -> NUM ADJ N
    auto np_nan = std::make_unique<ParseNode>();
    np_nan->label = "NP";
    np_nan->type = NodeType::NON_TERMINAL;
    if (consume(POS::NUM, np_nan.get()) && consume(POS::ADJ, np_nan.get()) && consume(POS::N, np_nan.get())) return np_nan;
    cursor_ = saved_cursor;

    // 0c. NP -> NUM N
    auto np_nn2 = std::make_unique<ParseNode>();
    np_nn2->label = "NP";
    np_nn2->type = NodeType::NON_TERMINAL;
    if (consume(POS::NUM, np_nn2.get()) && consume(POS::N, np_nn2.get())) return np_nn2;
    cursor_ = saved_cursor;

    // 1. NP -> DET ADJ ADJ N
    auto np1 = std::make_unique<ParseNode>();
    np1->label = "NP";
    np1->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np1.get()) && consume(POS::ADJ, np1.get()) && consume(POS::ADJ, np1.get()) && consume(POS::N, np1.get())) return np1;
    cursor_ = saved_cursor;

    // 1a. NP -> DET V N N
    auto np_dvnn = std::make_unique<ParseNode>();
    np_dvnn->label = "NP";
    np_dvnn->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dvnn.get()) && consume(POS::V, np_dvnn.get()) && consume(POS::N, np_dvnn.get()) && consume(POS::N, np_dvnn.get())) return np_dvnn;
    cursor_ = saved_cursor;

    // 1b. NP -> DET V N
    auto np_dvn = std::make_unique<ParseNode>();
    np_dvn->label = "NP";
    np_dvn->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dvn.get()) && consume(POS::V, np_dvn.get()) && consume(POS::N, np_dvn.get())) return np_dvn;
    cursor_ = saved_cursor;

    // 2. NP -> DET ADJ N
    auto np_dan = std::make_unique<ParseNode>();
    np_dan->label = "NP";
    np_dan->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dan.get()) && consume(POS::ADJ, np_dan.get()) && consume(POS::N, np_dan.get())) return np_dan;
    cursor_ = saved_cursor;

    // 3. NP -> DET N N
    auto np_dnn = std::make_unique<ParseNode>();
    np_dnn->label = "NP";
    np_dnn->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dnn.get()) && consume(POS::N, np_dnn.get()) && consume(POS::N, np_dnn.get())) return np_dnn;
    cursor_ = saved_cursor;

    // 4. NP -> DET N
    auto np3 = std::make_unique<ParseNode>();
    np3->label = "NP";
    np3->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np3.get()) && consume(POS::N, np3.get())) return np3;
    cursor_ = saved_cursor;

    // 5. NP -> N N
    auto np_nn = std::make_unique<ParseNode>();
    np_nn->label = "NP";
    np_nn->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np_nn.get()) && consume(POS::N, np_nn.get())) return np_nn;
    cursor_ = saved_cursor;

    // 6. NP -> V N
    auto np_vn = std::make_unique<ParseNode>();
    np_vn->label = "NP";
    np_vn->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, np_vn.get()) && consume(POS::N, np_vn.get())) return np_vn;
    cursor_ = saved_cursor;

    // 6a. NP -> ADJ ADJ N
    auto np_aan = std::make_unique<ParseNode>();
    np_aan->label = "NP";
    np_aan->type = NodeType::NON_TERMINAL;
    if (consume(POS::ADJ, np_aan.get()) && consume(POS::ADJ, np_aan.get()) && consume(POS::N, np_aan.get())) return np_aan;
    cursor_ = saved_cursor;

    // 6b. NP -> ADJ N
    auto np_an = std::make_unique<ParseNode>();
    np_an->label = "NP";
    np_an->type = NodeType::NON_TERMINAL;
    if (consume(POS::ADJ, np_an.get()) && consume(POS::N, np_an.get())) return np_an;
    cursor_ = saved_cursor;

    // 6c. NP -> ADJ V
    auto np_av = std::make_unique<ParseNode>();
    np_av->label = "NP";
    np_av->type = NodeType::NON_TERMINAL;
    if (consume(POS::ADJ, np_av.get()) && consume(POS::V, np_av.get())) return np_av;
    cursor_ = saved_cursor;

    // 6d. NP -> V
    auto np_v = std::make_unique<ParseNode>();
    np_v->label = "NP";
    np_v->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, np_v.get())) return np_v;
    cursor_ = saved_cursor;

    // 7. NP -> PRON
    auto np4 = std::make_unique<ParseNode>();
    np4->label = "NP";
    np4->type = NodeType::NON_TERMINAL;
    if (consume(POS::PRON, np4.get())) return np4;
    cursor_ = saved_cursor;

    // 8. NP -> PROPER_N
    auto np5 = std::make_unique<ParseNode>();
    np5->label = "NP";
    np5->type = NodeType::NON_TERMINAL;
    if (consume(POS::PROPER_N, np5.get())) return np5;
    cursor_ = saved_cursor;

    // 9. NP -> N
    auto np6 = std::make_unique<ParseNode>();
    np6->label = "NP";
    np6->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np6.get())) return np6;
    cursor_ = saved_cursor;

    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_VP() {
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> vp_node = nullptr;

    auto vp_aux_v_np_adv = std::make_unique<ParseNode>();
    vp_aux_v_np_adv->label = "VP";
    vp_aux_v_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_v_np_adv.get()) && consume(POS::V, vp_aux_v_np_adv.get())) {
        if (auto np = parse_NP()) {
            vp_aux_v_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, vp_aux_v_np_adv.get())) vp_node = std::move(vp_aux_v_np_adv);
        }
    }
    if (!vp_node) cursor_ = saved_cursor;

    if (!vp_node) {
        auto vp_aux2 = std::make_unique<ParseNode>();
        vp_aux2->label = "VP";
        vp_aux2->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux2.get()) && consume(POS::V, vp_aux2.get())) {
            if (auto np = parse_NP()) {
                vp_aux2->add_child(std::move(np));
                vp_node = std::move(vp_aux2);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_v_adv = std::make_unique<ParseNode>();
        vp_aux_v_adv->label = "VP";
        vp_aux_v_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_v_adv.get()) && consume(POS::V, vp_aux_v_adv.get()) && consume(POS::ADV, vp_aux_v_adv.get())) {
            vp_node = std::move(vp_aux_v_adv);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_adv_v = std::make_unique<ParseNode>();
        vp_aux_adv_v->label = "VP";
        vp_aux_adv_v->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_adv_v.get()) && consume(POS::ADV, vp_aux_adv_v.get()) && consume(POS::V, vp_aux_adv_v.get())) {
            vp_node = std::move(vp_aux_adv_v);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux3 = std::make_unique<ParseNode>();
        vp_aux3->label = "VP";
        vp_aux3->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux3.get()) && consume(POS::V, vp_aux3.get())) {
            vp_node = std::move(vp_aux3);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_adv = std::make_unique<ParseNode>();
        vp_aux_adv->label = "VP";
        vp_aux_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_adv.get()) && consume(POS::ADV, vp_aux_adv.get())) {
            vp_node = std::move(vp_aux_adv);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_np_adv = std::make_unique<ParseNode>();
        vp_aux_np_adv->label = "VP";
        vp_aux_np_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_np_adv.get())) {
            if (auto np = parse_NP()) {
                vp_aux_np_adv->add_child(std::move(np));
                if (consume(POS::ADV, vp_aux_np_adv.get())) vp_node = std::move(vp_aux_np_adv);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_np = std::make_unique<ParseNode>();
        vp_aux_np->label = "VP";
        vp_aux_np->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_np.get())) {
            if (auto np = parse_NP()) {
                vp_aux_np->add_child(std::move(np));
                vp_node = std::move(vp_aux_np);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_pp = std::make_unique<ParseNode>();
        vp_aux_pp->label = "VP";
        vp_aux_pp->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_pp.get())) {
            if (auto pp = parse_PP()) {
                vp_aux_pp->add_child(std::move(pp));
                vp_node = std::move(vp_aux_pp);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_adj = std::make_unique<ParseNode>();
        vp_aux_adj->label = "VP";
        vp_aux_adj->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_adj.get()) && consume(POS::ADJ, vp_aux_adj.get())) {
            vp_node = std::move(vp_aux_adj);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_aux_vp = std::make_unique<ParseNode>();
        vp_aux_vp->label = "VP";
        vp_aux_vp->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, vp_aux_vp.get())) {
            if (auto vp_child = parse_VP()) {
                vp_aux_vp->add_child(std::move(vp_child));
                vp_node = std::move(vp_aux_vp);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp_v_np_adv = std::make_unique<ParseNode>();
        vp_v_np_adv->label = "VP";
        vp_v_np_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, vp_v_np_adv.get())) {
            if (auto np = parse_NP()) {
                vp_v_np_adv->add_child(std::move(np));
                if (consume(POS::ADV, vp_v_np_adv.get())) vp_node = std::move(vp_v_np_adv);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp2 = std::make_unique<ParseNode>();
        vp2->label = "VP";
        vp2->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, vp2.get())) {
            if (auto np = parse_NP()) {
                vp2->add_child(std::move(np));
                vp_node = std::move(vp2);
            }
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp4 = std::make_unique<ParseNode>();
        vp4->label = "VP";
        vp4->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, vp4.get()) && consume(POS::ADV, vp4.get())) {
            vp_node = std::move(vp4);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    if (!vp_node) {
        auto vp5 = std::make_unique<ParseNode>();
        vp5->label = "VP";
        vp5->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, vp5.get())) {
            vp_node = std::move(vp5);
        }
        if (!vp_node) cursor_ = saved_cursor;
    }

    // PP Wrapping loop for all valid VPs
    if (vp_node) {
        bool matched = true;
        while (matched) {
            if (auto extra_pp = parse_PP()) {
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "VP";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(vp_node));
                wrapped->add_child(std::move(extra_pp));
                vp_node = std::move(wrapped);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>();
                leaf->label = "ADV";
                leaf->lexeme = current().word;
                leaf->type = NodeType::TERMINAL;
                cursor_++;
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "VP";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(vp_node));
                wrapped->add_child(std::move(leaf));
                vp_node = std::move(wrapped);
            } else {
                matched = false;
            }
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
