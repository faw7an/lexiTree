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
            std::cout << "Reduced: " << stack_.back().symbol << " (Stack size: " << stack_.size() << ")";
            if (stack_.back().node) {
                 std::cout << " Node labels: ";
                 for (const auto& child : stack_.back().node->children) {
                     std::cout << child->label << " ";
                 }
            }
            std::cout << std::endl;
            continue;
        } else if (!at_end()) {
            shift();
            std::cout << "Shifted: " << stack_.back().symbol << " (" << stack_.back().node->lexeme << ")" << std::endl;
        } else {
            // Stuck: Cannot shift and cannot reduce, but not in accept state
            // One last check: can we reduce S S to S or NP S to S?
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
    // 1. Always reduce Prepositional Phrases first
    if (reduce_PP()) return true;

    // 2. Lookahead Conflict Resolution
    if (!at_end()) {
        std::string next_tag = pos_to_str(tokens_[input_pos_].tag);

        // Conflict: VP -> ADJ vs. ADJ CONJ ADJ
        if (stack_top_matches({"ADJ"}) || stack_top_matches({"AUX", "ADJ"})) {
            if (next_tag == "N" || next_tag == "ADJ") return false; // SHIFT
            if (next_tag == "CONJ") {
                // Peek ahead 1 to see if it's an ADJ
                if (input_pos_ + 1 < tokens_.size()) {
                    std::string next_next = pos_to_str(tokens_[input_pos_ + 1].tag);
                    if (next_next == "ADJ") return false; // SHIFT
                }
            }
        }

        // Conflict: NP -> V N vs. S -> NP VP (where V is the start of VP)
        if (stack_top_matches({"V", "N"})) {
            if (stack_.size() >= 3) {
                std::string prev = stack_[stack_.size() - 3].symbol;
                if (prev == "NP" || prev == "PRON" || prev == "AUX" || prev == "ADV" || prev == "PREP" || prev == "CONJ") {
                    if (next_tag == "PREP" || next_tag == "ADV" || next_tag == "EOF") return false;
                    if (next_tag == "CONJ") {
                        if (input_pos_ + 1 < tokens_.size()) {
                            std::string next_next = pos_to_str(tokens_[input_pos_ + 1].tag);
                            if (next_next != "PRON") return false;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
        
        // Conflict: S -> NP VP vs. VP -> VP PP / VP ADV / CONJ S S
        if (stack_top_matches({"NP", "VP"})) {
            // Check if the next token is a CONJ that functions as a PREP
            bool next_is_prep = false;
            if (next_tag == "CONJ") {
                const auto& next_token = tokens_[input_pos_];
                if (next_token.word == "before" || next_token.word == "after" || next_token.word == "until" || next_token.word == "since") {
                    next_is_prep = true;
                }
            }

            // CRITICAL FIX: If we are inside a CONJ S S structure (e.g., "Although you were late..."),
            // we MUST reduce NP VP to S immediately, even if the next token is a PRON ("you").
            bool inside_complex = false;
            if (stack_.size() >= 3 && (stack_[stack_.size()-3].symbol == "CONJ" || stack_[stack_.size()-3].symbol == "PRON")) inside_complex = true;
            
            if (!inside_complex) {
                // Not inside a CONJ block? Apply standard relative-clause lookahead delays.
                if (next_tag == "PRON" || next_tag == "ADV" || next_tag == "PREP") {
                    if (!next_is_prep) return false;
                }
                if (next_tag == "CONJ") {
                    // Only shift CONJ if we suspect it's coordinating verbs or object NPs.
                    // But if it's NP VP CONJ, it's safer to reduce to S, UNLESS we are in an auxiliary inversion?
                    // Actually, S CONJ S is standard.
                }
                
                // Conflict: S -> NP VP vs. S -> S NP (Time/Location NP at end)
                if (next_tag == "DET" || next_tag == "ADJ" || next_tag == "N" || next_tag == "PRON" || next_tag == "PROPER_N") {
                     // Check if this might be a time NP at the end of the sentence
                     // We check if after this NP we are at end
                     // In BU we only know the next token. If we see a DET/N, we might want to SHIFT 
                     // to build a trailing NP for the whole sentence.
                     return false; 
                }
            }
        }
        
        // General verb modifiers: wait for objects/adverbs
        if (stack_top_matches({"V"}) || stack_top_matches({"AUX", "V"})) {
            if (next_tag == "DET" || next_tag == "ADJ" || next_tag == "N" || next_tag == "PROPER_N" || 
                next_tag == "PRON" || next_tag == "ADV" || next_tag == "PREP") {
                return false; // SHIFT to build longer VP
            }
        }
        // Conflict: S -> CONJ S vs. S -> CONJ S S
        if (stack_top_matches({"CONJ", "S"})) {
             if (!at_end()) {
                  auto next_tag = pos_to_str(tokens_[input_pos_].tag);
                  // If the next token can start an S (NP elements), wait!
                  if (next_tag == "PRON" || next_tag == "DET" || next_tag == "N" || next_tag == "PROPER_N" || next_tag == "ADJ" || next_tag == "ADV" || next_tag == "AUX") {
                       return false; // SHIFT
                  }
             }
        }

    }

    // 3. Perform reductions if no lookahead conflicts forced a shift
    if (reduce_NP()) return true;
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
    if (stack_top_matches({"DET", "ADJ", "CONJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj1));
        node->add_child(std::move(conj));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"NP", "PRON", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP"; node->type = NodeType::NON_TERMINAL;
        auto s_node = std::move(stack_.back().node); stack_.pop_back();
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pron));
        node->add_child(std::move(s_node));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"NP", "PRON", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP"; node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pron));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    
    if (stack_top_matches({"NP", "CONJ", "NP"})) {
        if (stack_[stack_.size()-2].node->lexeme == "and" || stack_[stack_.size()-2].node->lexeme == "or") {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP"; node->type = NodeType::NON_TERMINAL;
            auto np2 = std::move(stack_.back().node); stack_.pop_back();
            auto conj = std::move(stack_.back().node); stack_.pop_back();
            auto np1 = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np1));
            node->add_child(std::move(conj));
            node->add_child(std::move(np2));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

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
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;

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
        
        // CRITICAL: Check if this is the start of a VP for a main clause NP.
        // If stack is [NP, V] and next is N/DET, it's likely a predicate.
        if (stack_.size() >= 2 && stack_[stack_.size()-2].symbol == "NP") {
             if (!at_end()) {
                 auto next_tag = pos_to_str(tokens_[input_pos_].tag);
                 if (next_tag == "DET" || next_tag == "N" || next_tag == "ADJ" || next_tag == "PRON" || next_tag == "ADV" || next_tag == "PREP" || next_tag == "V" || next_tag == "AUX") {
                     should_reduce_to_np = false;
                 }
             }
        }

        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") should_reduce_to_np = false;
        
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

    if (stack_top_matches({"NP", "PRON"})) {
         return false;
    }

    if (stack_top_matches({"PRON"})) {
        if (!at_end()) {
            auto next_tag = pos_to_str(tokens_[input_pos_].tag);
            // Allow immediate NP reduction if the next is a verb or auxiliary (Main Subject case)
            if (next_tag == "V" || next_tag == "AUX" || next_tag == "ADV") {
                // Keep moving
            } else if (next_tag == "N" || next_tag == "DET" || next_tag == "PREP" || next_tag == "CONJ" || next_tag == "PRON") {
                return false;
            }
        }
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pron));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"PROPER_N"})) {
        if (!at_end()) {
            auto next_tag = pos_to_str(tokens_[input_pos_].tag);
            if (next_tag == "V" || next_tag == "AUX") {
                // Keep moving
            } else if (next_tag == "N" || next_tag == "DET" || next_tag == "ADV" || next_tag == "PREP" || next_tag == "CONJ" || next_tag == "PRON") {
                return false;
            }
        }
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pn = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pn));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"N"})) {
        if (!at_end()) {
            auto next_tag = pos_to_str(tokens_[input_pos_].tag);
            if (next_tag == "V" || next_tag == "AUX") {
                // Keep moving
            } else if (next_tag == "N" || next_tag == "DET" || next_tag == "ADV" || next_tag == "PREP" || next_tag == "PRON") {
                return false;
            } else if (next_tag == "CONJ") {
                if (input_pos_ + 1 < tokens_.size()) {
                    auto next_next = pos_to_str(tokens_[input_pos_ + 1].tag);
                    if (next_next == "N" || next_next == "ADJ" || next_next == "DET" || next_next == "PROPER_N") {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
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

    if (stack_top_matches({"AUX", "ADJ", "CONJ", "ADJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adj1));
        node->add_child(std::move(conj));
        node->add_child(std::move(adj2));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
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
    if (stack_top_matches({"NP", "ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        auto wrap_vp = std::make_unique<ParseNode>();
        wrap_vp->label = "VP"; wrap_vp->type = NodeType::NON_TERMINAL;
        wrap_vp->add_child(std::move(adv));
        wrap_vp->add_child(std::move(vp));
        node->add_child(std::move(wrap_vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adv));
        node->add_child(std::move(vp));
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
        
        auto inner_vp = std::make_unique<ParseNode>();
        inner_vp->label = "VP"; inner_vp->type = NodeType::NON_TERMINAL;
        
        auto innermost_vp = std::make_unique<ParseNode>();
        innermost_vp->label = "VP"; innermost_vp->type = NodeType::NON_TERMINAL;
        innermost_vp->add_child(std::move(v));
        
        inner_vp->add_child(std::move(innermost_vp));
        inner_vp->add_child(std::move(adv));
        
        node->add_child(std::move(aux));
        node->add_child(std::move(inner_vp));
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
        
        auto inner_vp = std::make_unique<ParseNode>();
        inner_vp->label = "VP"; inner_vp->type = NodeType::NON_TERMINAL;
        inner_vp->add_child(std::move(aux));
        
        node->add_child(std::move(inner_vp));
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
        if (!at_end()) {
             auto next_tag = pos_to_str(tokens_[input_pos_].tag);
             if (next_tag == "PRON") return false;
             if (next_tag == "CONJ") {
                 // Check if it's coordinating two object NPs instead of clauses
                 // For example, "I like apples and oranges"
                 if (input_pos_ + 1 < tokens_.size()) {
                     auto next_next = pos_to_str(tokens_[input_pos_ + 1].tag);
                     if (next_next == "N" || next_next == "ADJ" || next_next == "DET" || next_next == "PROPER_N") {
                         // But wait, if it's "while the students", DET N can start an S!
                         // In that case, we want to reduce V NP to VP.
                         // But if it's just coordinating objects "the apple and the orange", we want to shift CONJ.
                         // So we have an ambiguity. TD parses it fine. BU can wait for "and" vs "while".
                         const auto& conj_word = tokens_[input_pos_].word;
                         if (conj_word == "and" || conj_word == "or" || conj_word == "nor") {
                             return false; // shift for coordinating objects
                         }
                     }
                 } else {
                     return false;
                 }
             }
             // If next is V, and it's a MAIN verb, we should reduce this VP now
             if (next_tag == "V") {
                int pron_count = 0;
                for (const auto& item : stack_) if (item.symbol == "PRON") pron_count++;
                int remaining_verbs = 0;
                for (size_t i = input_pos_; i < tokens_.size(); ++i) {
                    if (tokens_[i].tag == POS::V || tokens_[i].tag == POS::AUX) remaining_verbs++;
                }
                if (remaining_verbs >= pron_count && pron_count > 0) {
                    // Reduce now so NP PRON S can form
                } else {
                    return false; // Shift next V? Maybe "give students grades"? 
                }
             }
        }
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
        
        auto inner_vp = std::make_unique<ParseNode>();
        inner_vp->label = "VP"; inner_vp->type = NodeType::NON_TERMINAL;
        inner_vp->add_child(std::move(v));
        
        node->add_child(std::move(inner_vp));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP"})) {
        // If we have NP PRON VP, we MUST reduce VP to S
        if (stack_.size() >= 3 && stack_[stack_.size()-3].symbol == "NP" && stack_[stack_.size()-2].symbol == "PRON") {
             auto node = std::make_unique<ParseNode>();
             node->label = "S";
             node->type = NodeType::NON_TERMINAL;
             auto vp = std::move(stack_.back().node); stack_.pop_back();
             node->add_child(std::move(vp));
             stack_.push_back({std::move(node), "S"});
             return true;
        }
        return false;
    }

    if (stack_top_matches({"V"})) {
        // Shift if it's the start of the sentence and more tokens follow.
        // BUT wait, TD is doing S -> S S -> VP VP for "Dogs chase cats".
        // In BU, if we shift "Dogs", then shift "chase", then "cats", we get V V N.
        // If we reduce Cats to NP, we have V V NP.
        // If we reduce V NP to VP, we have V VP.
        // If we reduce V to VP, we have VP VP.
        // If we reduce VP to S, we have S VP.
        // If we reduce VP to S, we have S S.
        // Then S S to S.
        
        if (!at_end()) {
            auto next_tag = pos_to_str(tokens_[input_pos_].tag);
            // If next is a verb or NP components, keep shifting to allow longer structures
            if (next_tag == "V" || next_tag == "NP" || next_tag == "N" || next_tag == "DET" || next_tag == "ADJ" || next_tag == "PRON") {
                return false;
            }
        }
        // If it's a verb but sitting at the start of the stack, and there's a verb following, 
        // it might be better as an NP (gerund) OR we should wait and see if it's S -> VP S or S -> VP.
        // But the TD parser is choosing S -> S S -> VP VP.
        
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
    if (stack_top_matches({"NP", "VP"})) {
         if (!at_end()) {
             auto next_tag = pos_to_str(tokens_[input_pos_].tag);
             bool preceded_by_rel = (stack_.size() >= 3 && (stack_[stack_.size()-3].symbol == "PRON" || stack_[stack_.size()-3].symbol == "CONJ"));
             if (!preceded_by_rel) {
                 if (next_tag == "PRON") return false;
                 // Standard shift/reduce delay for main verbs
                 // BUT DO NOT delay if the next is an NP component and we are at stack depth 2
                 // as that likely indicates a trailing NP that should be handled by S -> S NP
                 if (stack_.size() == 2) {
                      // Reduce now, then trailing NP will be shifted and reduced to S -> S NP
                 } else {
                     if (next_tag == "V" || next_tag == "AUX" || next_tag == "ADV" || next_tag == "PREP") return false;
                 }
             }
         }
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
        // If we have NP PRON VP or NP VP (and at end), we MUST reduce VP to S
        if (stack_.size() >= 3 && stack_[stack_.size()-3].symbol == "NP" && stack_[stack_.size()-2].symbol == "PRON") {
             auto node = std::make_unique<ParseNode>();
             node->label = "S";
             node->type = NodeType::NON_TERMINAL;
             auto vp = std::move(stack_.back().node); stack_.pop_back();
             node->add_child(std::move(vp));
             stack_.push_back({std::move(node), "S"});
             return true;
        }
        if (stack_.size() >= 2 && stack_[stack_.size()-2].symbol == "NP" && at_end()) {
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
        return false;
    }

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

    if (stack_top_matches({"S", "NP"})) {
         // ONLY reduce to S NP if it's the end of the sentence or following is another modifier.
         // Do not reduce if the preceding token was CONJ! S -> CONJ S S should be preferred.
         if (stack_.size() >= 3 && stack_[stack_.size()-3].symbol == "CONJ") return false;
         
         auto node = std::make_unique<ParseNode>();
         node->label = "S";
         node->type = NodeType::NON_TERMINAL;
         auto np = std::move(stack_.back().node); stack_.pop_back();
         auto s = std::move(stack_.back().node); stack_.pop_back();
         node->add_child(std::move(s));
         node->add_child(std::move(np));
         stack_.push_back({std::move(node), "S"});
         return true;
    }

    if (stack_top_matches({"S", "CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S"; node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(conj));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

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

    if (stack_top_matches({"NP", "ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        auto wrap_vp = std::make_unique<ParseNode>();
        wrap_vp->label = "VP"; wrap_vp->type = NodeType::NON_TERMINAL;
        wrap_vp->add_child(std::move(adv));
        wrap_vp->add_child(std::move(vp));
        node->add_child(std::move(wrap_vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"VP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto vp = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(vp));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"NP", "S"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto s = std::move(stack_.back().node); stack_.pop_back();
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            node->add_child(std::move(s));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
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
