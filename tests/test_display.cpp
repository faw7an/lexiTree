#include <gtest/gtest.h>
#include "parse_tree.h"
#include "display.h"
#include <sstream>

TEST(DisplayTest, SimpleTreeRendering) {
    auto root = std::make_unique<ParseNode>();
    root->label = "S";
    root->type = NodeType::NON_TERMINAL;

    auto np = std::make_unique<ParseNode>();
    np->label = "NP";
    np->type = NodeType::NON_TERMINAL;

    auto det = std::make_unique<ParseNode>();
    det->label = "DET";
    det->lexeme = "The";
    det->type = NodeType::TERMINAL;

    auto n = std::make_unique<ParseNode>();
    n->label = "N";
    n->lexeme = "dog";
    n->type = NodeType::TERMINAL;

    np->add_child(std::move(det));
    np->add_child(std::move(n));

    auto vp = std::make_unique<ParseNode>();
    vp->label = "VP";
    vp->type = NodeType::NON_TERMINAL;

    auto v = std::make_unique<ParseNode>();
    v->label = "V";
    v->lexeme = "runs";
    v->type = NodeType::TERMINAL;

    vp->add_child(std::move(v));

    root->add_child(std::move(np));
    root->add_child(std::move(vp));

    // Redirect stdout to capture output
    testing::internal::CaptureStdout();
    Display::print_tree(root.get());
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = 
        "S\n"
        "├── NP\n"
        "│   ├── DET: \"The\"\n"
        "│   └── N: \"dog\"\n"
        "└── VP\n"
        "    └── V: \"runs\"\n";

    EXPECT_EQ(output, expected);
}
