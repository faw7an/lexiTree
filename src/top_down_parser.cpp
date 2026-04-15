#include "top_down_parser.h"
#include <iostream>

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
    // Only treat as expression if ALL tokens are math-related (NUM, OP, PAREN)
    // AND there's at least one NUM or OP.
    if (!is_expr && tokens_.size() > 0) {
        bool all_math = true;
        bool has_val = false;
        for (const auto& token : tokens_) {
            if (token.tag != POS::NUM && token.tag != POS::OP && token.tag != POS::LPAREN && token.tag != POS::RPAREN) {
                all_math = false;
                break;
            }
            if (token.tag == POS::NUM) has_val = true;
        }
        if (all_math && has_val) is_expr = true;
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
    // DISABLE fallback for N as V to prevent V from being stolen by NP
    if (!match) {
        if (expected == POS::V && actual == POS::N) match = true;
    }

    if (getenv("PARSER_DEBUG")) {
        std::cout << "Consuming " << pos_to_str(expected) << "? Actual: " << pos_to_str(actual) << " (" << current().word << ") -> " << (match ? "MATCH" : "FAIL") << std::endl;
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
    if (getenv("PARSER_DEBUG")) std::cout << "Entering parse_S at " << current().word << std::endl;
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> s_node = nullptr;

    // S -> NP VP
    {
        auto s2 = std::make_unique<ParseNode>();
        s2->label = "S";
        s2->type = NodeType::NON_TERMINAL;
        if (auto np = parse_NP()) {
            if (auto vp = parse_VP()) {
                s2->add_child(std::move(np));
                s2->add_child(std::move(vp));
                s_node = std::move(s2);
            }
        }
        if (s_node) {
            // Check if we consumed all tokens. If not, maybe it's S -> S S or something else.
            if (at_end()) goto post_process;
            else {
                cursor_ = saved_cursor;
                s_node = nullptr;
            }
        }
        cursor_ = saved_cursor;
    }

    // S -> ADV S (Handles Wh- questions like "Why do we...")
    {
        auto s_adv_s = std::make_unique<ParseNode>();
        s_adv_s->label = "S";
        s_adv_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::ADV, s_adv_s.get())) {
            if (auto s_child = parse_S()) {
                s_adv_s->add_child(std::move(s_child));
                s_node = std::move(s_adv_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_conj_s_s = std::make_unique<ParseNode>();
        s_conj_s_s->label = "S";
        s_conj_s_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s_s.get())) {
            // S -> CONJ S S (Longest match: Although S S)
            if (auto s1_child = parse_S_base()) {
                s_conj_s_s->add_child(std::move(s1_child));
                if (auto s2_child = parse_S()) {
                    s_conj_s_s->add_child(std::move(s2_child));
                    s_node = std::move(s_conj_s_s);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    // S -> S CONJ S (I went home because it rained)
    {
        auto s_s_conj_s = std::make_unique<ParseNode>();
        s_s_conj_s->label = "S"; s_s_conj_s->type = NodeType::NON_TERMINAL;
        if (auto s1 = parse_S_base()) {
            size_t before_conj = cursor_;
            if (current().tag == POS::CONJ) {
                auto conj = std::make_unique<ParseNode>();
                conj->label = "CONJ"; conj->lexeme = current().word; conj->type = NodeType::TERMINAL;
                cursor_++;
                if (auto s2 = parse_S()) {
                     s_s_conj_s->add_child(std::move(s1));
                     s_s_conj_s->add_child(std::move(conj));
                     s_s_conj_s->add_child(std::move(s2));
                     s_node = std::move(s_s_conj_s);
                } else {
                     cursor_ = before_conj;
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_conj_s = std::make_unique<ParseNode>();
        s_conj_s->label = "S";
        s_conj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s.get())) {
            if (auto s_child = parse_S()) {
                s_conj_s->add_child(std::move(s_child));
                s_node = std::move(s_conj_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    // S -> AUX NP NP (Handles copula questions like "Is that a cat")
    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_np = std::make_unique<ParseNode>();
        s_np->label = "S";
        s_np->type = NodeType::NON_TERMINAL;
        if (auto np = parse_NP()) {
            s_np->add_child(std::move(np));
            s_node = std::move(s_np);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_vp = std::make_unique<ParseNode>();
        s_vp->label = "S";
        s_vp->type = NodeType::NON_TERMINAL;
        if (auto vp = parse_VP()) {
            s_vp->add_child(std::move(vp));
            s_node = std::move(s_vp);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_intj_s = std::make_unique<ParseNode>();
        s_intj_s->label = "S";
        s_intj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s_intj_s.get())) {
            if (auto s = parse_S()) {
                s_intj_s->add_child(std::move(s));
                s_node = std::move(s_intj_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
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
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s3 = std::make_unique<ParseNode>();
        s3->label = "S";
        s3->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s3.get())) {
            if (auto np = parse_NP()) {
                s3->add_child(std::move(np));
                s_node = std::move(s3);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s4 = std::make_unique<ParseNode>();
        s4->label = "S";
        s4->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s4.get())) {
            s_node = std::move(s4);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    return nullptr;

post_process:
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

std::unique_ptr<ParseNode> TopDownParser::parse_S_base() {
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> s_node = nullptr;

    if (auto np = parse_NP()) {
        if (auto vp = parse_VP()) {
            s_node = std::make_unique<ParseNode>();
            s_node->label = "S"; s_node->type = NodeType::NON_TERMINAL;
            s_node->add_child(std::move(np));
            s_node->add_child(std::move(vp));
            return s_node;
        }
    }
    cursor_ = saved_cursor;
    if (auto vp = parse_VP()) {
        s_node = std::make_unique<ParseNode>();
        s_node->label = "S"; s_node->type = NodeType::NON_TERMINAL;
        s_node->add_child(std::move(vp));
        return s_node;
    }
    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_NP() {
    size_t saved_cursor = cursor_;

    // 1. RELATIVE CLAUSE: NP -> NP REL_PRO S
    // Try to match a base NP first, then see if a relative clause follows.
    // To avoid infinite recursion, we try the non-recursive patterns first.

    // 1. Base NP patterns (from longest to shortest)
    auto n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;
    
    // PRON (Rel Pro support)
    if (current().tag == POS::PRON && (current().word == "who" || current().word == "that" || current().word == "which")) {
        // Only return nullptr if we're not inside a recursive call that expects an NP
        // But parse_NP is the entry point.
    }

    // DET NUM ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET V N N
    if (consume(POS::DET, n.get()) && consume(POS::V, n.get()) && consume(POS::N, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET V N
    if (consume(POS::DET, n.get()) && consume(POS::V, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET NUM N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET DET N
    if (consume(POS::DET, n.get()) && consume(POS::DET, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // NUM ADJ N
    if (consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // NUM N
    if (consume(POS::NUM, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET N
    if (consume(POS::DET, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // ADJ N
    if (consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // ADJ PROPER_N PROPER_N
    if (consume(POS::ADJ, n.get()) && consume(POS::PROPER_N, n.get()) && consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // ADJ PROPER_N
    if (consume(POS::ADJ, n.get()) && consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PROPER_N PROPER_N
    if (consume(POS::PROPER_N, n.get()) && consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET PROPER_N
    if (consume(POS::DET, n.get()) && consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PRON
    if (consume(POS::PRON, n.get())) {
        // If we consumed "who/that" as a standalone PRON, we need to check if it's the start of a Rel Clause
        // But usually "who" is a Rel Clause start. 
        // Let's allow it as a standalone NP (for "Who is he?") but also check for extras.
        goto check_extra;
    }
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PROPER_N
    if (consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // N N N
    if (consume(POS::N, n.get()) && consume(POS::N, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // N N
    if (consume(POS::N, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // N
    if (consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // V (Gerund acting as NP)
    if (consume(POS::V, n.get())) goto check_extra;
    
    return nullptr;

check_extra:
    bool matched = true;
    while (matched) {
        size_t cp = cursor_;
        if (auto pp = parse_PP()) {
            auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
            wrap->add_child(std::move(n)); wrap->add_child(std::move(pp)); n = std::move(wrap);
        } else if (current().tag == POS::PRON && (current().word == "who" || current().word == "that" || current().word == "which")) {
            // Relative clause: NP -> NP PRON S
            auto rel_pron = std::make_unique<ParseNode>();
            rel_pron->label = "PRON"; rel_pron->lexeme = current().word; rel_pron->type = NodeType::TERMINAL;
            cursor_++;
            
            // Try NP -> NP PRON S (e.g., "the cheese that the mouse stole")
            if (auto s = parse_S()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(n)); wrap->add_child(std::move(rel_pron)); wrap->add_child(std::move(s));
                n = std::move(wrap);
            } else {
                cursor_ = cp + 1; // rewind to just after PRON
                // Try NP -> NP PRON VP (e.g., "the cat that chased the mouse")
                if (auto vp = parse_VP()) {
                    auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                    wrap->add_child(std::move(n)); wrap->add_child(std::move(rel_pron)); wrap->add_child(std::move(vp));
                    n = std::move(wrap);
                } else {
                    cursor_ = cp; 
                    matched = false;
                }
            }
        } else if (current().tag == POS::CONJ && (current().word == "and" || current().word == "or")) {
            // NP list/conjunction: NP -> NP CONJ NP
            auto conj = std::make_unique<ParseNode>();
            conj->label = "CONJ"; conj->lexeme = current().word; conj->type = NodeType::TERMINAL;
            cursor_++;
            if (auto next_np = parse_NP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(n)); wrap->add_child(std::move(conj)); wrap->add_child(std::move(next_np));
                n = std::move(wrap);
            } else { cursor_ = cp; matched = false; }
        } else { matched = false; }
    }
    return n;
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
                if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
                else {
                    cursor_ = checkpoint;
                    v->children.pop_back(); // Remove PREP
                }
            }
            cursor_ = checkpoint;
            // V + PP
            if (auto pp = parse_PP()) { v->add_child(std::move(pp)); vp_node = std::move(v); goto finalize; }
            
            cursor_ = checkpoint;
            vp_node = std::move(v); goto finalize; // VP -> V
        }
    }

finalize:
    if (vp_node) {
        bool matched = true;
        while (matched) {
            size_t cp = cursor_;
            if (auto pp = parse_PP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(pp)); vp_node = std::move(wrap);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADV"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(leaf)); vp_node = std::move(wrap);
            } else if (current().tag == POS::ADJ) {
                // VP -> VP ADJ (is tall)
                auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADJ"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(leaf)); vp_node = std::move(wrap);
            } else { matched = false; }
        }
    }
    // If we didn't match a VP but there's an ADV, try VP -> ADV VP
    if (!vp_node) {
        cursor_ = saved_cursor;
        if (current().tag == POS::ADV) {
            auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADV"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
            if (auto sub_vp = parse_VP()) {
                vp_node = std::make_unique<ParseNode>();
                vp_node->label = "VP"; vp_node->type = NodeType::NON_TERMINAL;
                vp_node->add_child(std::move(leaf));
                vp_node->add_child(std::move(sub_vp));
            } else { cursor_ = saved_cursor; }
        }
    }
    return vp_node;
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
