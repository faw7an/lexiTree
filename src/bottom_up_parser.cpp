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
    
    // Fallback for V/N ambiguity
    POS tag = token.tag;
    if (tag == POS::V || tag == POS::N) {
        // If the top-down parser can match both, we should ideally try both
        // For shift-reduce, we pick the most likely one or use the stack context.
        // As a simple fix, we'll keep the token's original tag but add logic 
        // in reduce_VP/NP to treat N as V or V as N if needed.
        // Actually, let's look at the stack to decide.
        if (stack_.empty()) {
            // Start of sentence: "Building..." is more likely N
        } else if (stack_.back().symbol == "DET" || stack_.back().symbol == "ADJ") {
            tag = POS::N;
        } else if (stack_.back().symbol == "NP" || stack_.back().symbol == "AUX" || stack_.back().symbol == "PRON") {
            tag = POS::V;
        }
    }

    node->label = pos_to_str(tag);
    node->lexeme = token.word;
    node->type = NodeType::TERMINAL;
    
    stack_.push_back({std::move(node), pos_to_str(tag)});
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
    // Print stack for debugging
    if (getenv("PARSER_DEBUG")) {
        std::cout << "Stack: ";
        for (const auto& item : stack_) std::cout << item.symbol << " ";
        std::cout << " | Next: " << (at_end() ? "EOF" : pos_to_str(tokens_[input_pos_].tag)) << std::endl;
    }

    // Shift-reduce parsing priority for proper nested reductions:
    if (reduce_PP()) return true;
    if (reduce_NP()) return true;

    // S -> S ADV or S PP or S S (Wait until no more shifts are possible)
    if (stack_top_matches({"S", "S"}) || stack_top_matches({"S", "PP"}) || stack_top_matches({"S", "ADV"})) {
        if (!at_end()) return false;
    }

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
    if (stack_top_matches({"NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "NUM", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(num));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
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


    if (stack_top_matches({"DET", "DET", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det2 = std::move(stack_.back().node); stack_.pop_back();
        auto det1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det1));
        node->add_child(std::move(det2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "N", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n3 = std::move(stack_.back().node); stack_.pop_back();
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        node->add_child(std::move(n3));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "V", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(v));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

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

    if (stack_top_matches({"DET", "DET", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det2 = std::move(stack_.back().node); stack_.pop_back();
        auto det1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det1));
        node->add_child(std::move(det2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "NUM", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(num));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "V", "N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") {
            // Do not eagerly reduce, allow DET V N N to match
        } else {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto n = std::move(stack_.back().node); stack_.pop_back();
            auto v = std::move(stack_.back().node); stack_.pop_back();
            auto det = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(det));
            node->add_child(std::move(v));
            node->add_child(std::move(n));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
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
    if (stack_top_matches({"NUM", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(num));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"ADJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj1));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
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
    if (stack_top_matches({"NUM", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(num));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"V", "N"})) {
        if (stack_.size() >= 3 && (stack_[stack_.size()-3].symbol == "NP" || stack_[stack_.size()-3].symbol == "AUX" || stack_[stack_.size()-3].symbol == "DET")) {
            // Do not reduce V N, let it be V NP
        } else {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto n = std::move(stack_.back().node); stack_.pop_back();
            auto v = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(v));
            node->add_child(std::move(n));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

    if (stack_top_matches({"ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"ADJ", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"N", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n3 = std::move(stack_.back().node); stack_.pop_back();
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        node->add_child(std::move(n3));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"N", "N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
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
    if (stack_top_matches({"V"})) {
        // Look ahead: if next is EOF or ADV, maybe it's S -> VP or VP -> V?
        // If it's DET V, it's definitely an NP (e.g. "the building")
        if (stack_.size() > 1 && stack_[stack_.size()-2].symbol == "DET") {
             auto node = std::make_unique<ParseNode>();
             node->label = "NP";
             node->type = NodeType::NON_TERMINAL;
             auto v = std::move(stack_.back().node); stack_.pop_back();
             node->add_child(std::move(v));
             stack_.push_back({std::move(node), "NP"});
             return true;
        }

        bool should_reduce_to_np = false;
        if (stack_.size() > 1 && stack_[stack_.size() - 2].symbol == "PREP") should_reduce_to_np = true;
        if (stack_.size() > 1 && stack_[stack_.size() - 2].symbol == "V") should_reduce_to_np = true;
        // DO NOT reduce V to NP if it's acting as a predicate in NP VP or if it's the start of a VP
        if (stack_.size() > 1 && (stack_[stack_.size()-2].symbol == "DET" || stack_[stack_.size()-2].symbol == "ADJ")) should_reduce_to_np = true;
        
        if (!at_end() && (pos_to_str(tokens_[input_pos_].tag) == "AUX" || pos_to_str(tokens_[input_pos_].tag) == "V")) should_reduce_to_np = true;
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") should_reduce_to_np = false;
        
        // Fix: If it's "young boy", young is ADJ, boy is N but might be V. 
        // If boy is V, and it's DET ADJ V, we should reduce V to NP only if it's not the main verb.
        // But the shift logic already tried to tag it.
        
        if (should_reduce_to_np) {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto v = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(v));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
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

    if (stack_top_matches({"N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
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

    if (stack_top_matches({"AUX", "PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"ADJ"})) {
        // Look ahead: if next is N, do NOT reduce ADJ to VP
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
        
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
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
    if (stack_top_matches({"AUX", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(pp));
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
    if (stack_top_matches({"V", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
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
    if (stack_top_matches({"NP", "VP", "AUX", "NP"})) {
        // Look ahead: if next is EOF, it's a tag question.
        if (at_end()) {
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
    }

    // CONJ S S (Longest match first)
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

    if (stack_top_matches({"ADV", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adv));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(pp));
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
    if (stack_top_matches({"CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s));
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
