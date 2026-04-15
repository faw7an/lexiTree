#!/bin/bash
# Remove s_aux_np_np from the top
sed -i '/\/\/ S -> AUX NP NP/,/if (!s_node) cursor_ = saved_cursor;/d' src/top_down_parser.cpp

# Re-insert s_aux_np_np right below s_aux
awk '
/s_aux->label = "S";/ { in_s_aux = 1 }
/if \(!s_node\) cursor_ = saved_cursor;/ {
    print
    if (in_s_aux) {
        print ""
        print "    // S -> AUX NP NP (Handles copula questions like \"Is that a cat\")"
        print "    if (!s_node) {"
        print "        auto s_aux_np_np = std::make_unique<ParseNode>();"
        print "        s_aux_np_np->label = \"S\";"
        print "        s_aux_np_np->type = NodeType::NON_TERMINAL;"
        print "        if (consume(POS::AUX, s_aux_np_np.get())) {"
        print "            if (auto np1 = parse_NP()) {"
        print "                s_aux_np_np->add_child(std::move(np1));"
        print "                if (auto np2 = parse_NP()) {"
        print "                    s_aux_np_np->add_child(std::move(np2));"
        print "                    s_node = std::move(s_aux_np_np);"
        print "                }"
        print "            }"
        print "        }"
        print "        if (!s_node) cursor_ = saved_cursor;"
        print "    }"
        in_s_aux = 0
    }
    next
}
{ print }
' src/top_down_parser.cpp > tmp.cpp && mv tmp.cpp src/top_down_parser.cpp
