#include "bottom_up_parser.h"
#include <algorithm>
#include <iostream>

BottomUpParser::BottomUpParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), input_pos_(0) {}

bool BottomUpParser::at_end() const {
    return input_pos_ >= tokens_.size();
}

std::unique_ptr<ParseNode> BottomUpParser::parse() {
    input_pos_ = 0;
    stack_.clear();
    
    int loop_counter = 0;
    int max_loops = tokens_.size() * 10;

    while (loop_counter++ < max_loops) {
        if (stack_.size() == 1 && stack_.back().symbol == "S" && at_end()) {
            return std::move(stack_.back().node);
        }

        if (try_reduce()) {
            continue;
        } else if (!at_end()) {
            shift();
        } else {
            // Stuck: Cannot shift and cannot reduce, but not in accept state
            return nullptr;
        }
    }
    
    return nullptr; // Infinite loop guard triggered
}

void BottomUpParser::shift() {
    if (at_end()) return;

    auto& token = tokens_[input_pos_++];
    auto node = std::make_unique<ParseNode>();
    node->label = pos_to_str(token.tag);
    node->lexeme = token.word;
    node->type = NodeType::TERMINAL;
    
    stack_.push_back({std::move(node), pos_to_str(token.tag)});
}

bool BottomUpParser::stack_top_matches(const std::vector<std::string>& pattern) const {
    if (stack_.size() < pattern.size()) return false;
    
    size_t stack_idx = stack_.size() - pattern.size();
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (stack_[stack_idx + i].symbol != pattern[i]) {
            return false;
        }
    }
    return true;
}

bool BottomUpParser::try_reduce() {
    // Shift-reduce parsing priority for proper nested reductions:
    if (reduce_PP()) return true;
    if (reduce_NP()) return true;
    // VERY IMPORTANT FIX: If the next token could shift into a valid longer match,
    // we should NOT eagerly reduce VP or S.
    // However, our grammar is simple enough that we just attempt reduce in priority order.
    // To handle prepositions, shift-reduce parsers typically resolve shift/reduce conflicts 
    // by looking ahead. Let's do a simple 1-token lookahead to avoid reducing VP too early
    // when a PP could be formed.
    
    if (stack_top_matches({"V", "NP"}) || stack_top_matches({"V"}) || stack_top_matches({"AUX", "V"}) || stack_top_matches({"AUX", "NP"})) {
        if (!at_end() && (pos_to_str(tokens_[input_pos_].tag) == "PREP" || 
                          pos_to_str(tokens_[input_pos_].tag) == "PRON" ||
                          pos_to_str(tokens_[input_pos_].tag) == "DET" ||
                          pos_to_str(tokens_[input_pos_].tag) == "ADJ" ||
                          pos_to_str(tokens_[input_pos_].tag) == "PROPER_N" ||
                          pos_to_str(tokens_[input_pos_].tag) == "N" ||
                          pos_to_str(tokens_[input_pos_].tag) == "ADV" ||
                          pos_to_str(tokens_[input_pos_].tag) == "V" ||
                          pos_to_str(tokens_[input_pos_].tag) == "AUX")) {
            return false; // Shift to allow a longer VP rule to trigger (like V NP or V NP PP or V ADV) or S rule
        }
    }

    if (stack_top_matches({"INTJ"}) || stack_top_matches({"INTJ", "NP"})) {
        if (!at_end()) {
            return false; // Shift to allow INTJ S or INTJ NP ADV
        }
    }
    
    if (reduce_VP()) return true;
    if (reduce_S()) return true;
    return false;
}

bool BottomUpParser::reduce_PP() {
    if (stack_top_matches({"PREP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "PP";
        node->type = NodeType::NON_TERMINAL;
        
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        
        node->add_child(std::move(prep));
        node->add_child(std::move(np));
        
        stack_.push_back({std::move(node), "PP"});
        return true;
    }
    return false;
}

bool BottomUpParser::reduce_NP() {
    if (stack_top_matches({"DET", "ADJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj1));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"PRON"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pron));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"PROPER_N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pn = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pn));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    return false;
}

bool BottomUpParser::reduce_VP() {
    if (stack_top_matches({"AUX", "V", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADV", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adv));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adj));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    return false;
}

bool BottomUpParser::reduce_S() {
    if (stack_top_matches({"CONJ", "S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "CONJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(vp));
        node->add_child(std::move(conj));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "AUX", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(vp));
        node->add_child(std::move(aux));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(aux));
        node->add_child(std::move(np2));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    return false;
}
