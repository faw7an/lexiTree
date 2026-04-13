import re

# 1. Update top_down_parser.cpp
with open('src/top_down_parser.cpp', 'r') as f:
    td_content = f.read()

aux_np_adv_rule = """
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
"""
td_content = td_content.replace('    // VP -> AUX NP PP\n', aux_np_adv_rule)

aux_vp_rule = """
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
"""
td_content = td_content.replace('    // VP -> AUX ADJ\n    auto vp_aux_adj = std::make_unique<ParseNode>();\n    vp_aux_adj->label = "VP";\n    vp_aux_adj->type = NodeType::NON_TERMINAL;\n    if (consume(POS::AUX, vp_aux_adj.get()) && consume(POS::ADJ, vp_aux_adj.get())) {\n        return vp_aux_adj;\n    }\n    cursor_ = saved_cursor;\n', aux_vp_rule)

with open('src/top_down_parser.cpp', 'w') as f:
    f.write(td_content)


# 2. Update bottom_up_parser.cpp
with open('src/bottom_up_parser.cpp', 'r') as f:
    bu_content = f.read()

aux_np_adv_bu = """
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
    if (stack_top_matches({"AUX", "NP", "PP"})) {"""
bu_content = bu_content.replace('    if (stack_top_matches({"AUX", "NP", "PP"})) {', aux_np_adv_bu)

aux_vp_bu = """
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
"""
bu_content = bu_content.replace('    if (stack_top_matches({"AUX", "ADJ"})) {\n        auto node = std::make_unique<ParseNode>();\n        node->label = "VP";\n        node->type = NodeType::NON_TERMINAL;\n        auto adj = std::move(stack_.back().node); stack_.pop_back();\n        auto aux = std::move(stack_.back().node); stack_.pop_back();\n        node->add_child(std::move(aux));\n        node->add_child(std::move(adj));\n        stack_.push_back({std::move(node), "VP"});\n        return true;\n    }\n', aux_vp_bu)

with open('src/bottom_up_parser.cpp', 'w') as f:
    f.write(bu_content)

# 3. Update README.md
with open('README.md', 'r') as f:
    readme_content = f.read()

# Try to find the VP line and append
import re
readme_content = re.sub(r'(VP -> .*?)(?=\n)', r'\1 | AUX NP ADV | AUX VP', readme_content)

with open('README.md', 'w') as f:
    f.write(readme_content)

