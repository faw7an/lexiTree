import re

def fix_top_down():
    with open('src/top_down_parser.cpp', 'r') as f:
        content = f.read()

    np_rules = """
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
"""
    content = content.replace('    // NP -> DET N\n', np_rules)

    vp_rules_top = """
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
"""
    content = content.replace('    // VP -> AUX V NP\n', vp_rules_top)

    vp_rules_mid = """
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
"""
    content = content.replace('    // VP -> AUX V\n', vp_rules_mid)

    vp_rules_np_pp = """
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
"""
    content = content.replace('    // VP -> AUX NP\n', vp_rules_np_pp)

    vp_rules_v_np_adv = """
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
"""
    content = content.replace('    // VP -> V NP PP\n', vp_rules_v_np_adv)

    with open('src/top_down_parser.cpp', 'w') as f:
        f.write(content)

def fix_bottom_up():
    with open('src/bottom_up_parser.cpp', 'r') as f:
        content = f.read()

    np_rules = """
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
    if (stack_top_matches({"DET", "N"})) {"""
    content = content.replace('    if (stack_top_matches({"DET", "N"})) {', np_rules)

    np_rules_nn = """
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
    if (stack_top_matches({"N"})) {"""
    content = content.replace('    if (stack_top_matches({"N"})) {', np_rules_nn)

    vp_rules_top = """
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
    if (stack_top_matches({"AUX", "V", "NP"})) {"""
    content = content.replace('    if (stack_top_matches({"AUX", "V", "NP"})) {', vp_rules_top)

    vp_rules_mid = """
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
    if (stack_top_matches({"AUX", "V"})) {"""
    content = content.replace('    if (stack_top_matches({"AUX", "V"})) {', vp_rules_mid)

    vp_rules_np_pp = """
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
    if (stack_top_matches({"AUX", "NP"})) {"""
    content = content.replace('    if (stack_top_matches({"AUX", "NP"})) {', vp_rules_np_pp)

    vp_rules_v_np_adv = """
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
    if (stack_top_matches({"V", "NP", "PP"})) {"""
    content = content.replace('    if (stack_top_matches({"V", "NP", "PP"})) {', vp_rules_v_np_adv)

    with open('src/bottom_up_parser.cpp', 'w') as f:
        f.write(content)

fix_top_down()
fix_bottom_up()
