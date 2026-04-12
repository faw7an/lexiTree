#include <gtest/gtest.h>
#include "lexer.h"
#include "bottom_up_parser.h"

std::unique_ptr<ParseNode> parse_bu(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    BottomUpParser parser(tokens);
    return parser.parse();
}

TEST(BottomUpTest, SimpleSentence) {
    auto tree = parse_bu("The cat runs");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}

TEST(BottomUpTest, ComplexSentence) {
    auto tree = parse_bu("The quick brown fox jumps over the lazy dog");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(BottomUpTest, PronounSentence) {
    auto tree = parse_bu("She loves him");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[0]->children[0]->lexeme, "She");
}

TEST(BottomUpTest, PrepositionalPhrase) {
    auto tree = parse_bu("The dog sleeps in the house");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children.size(), 2); // V and PP
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(BottomUpTest, BareNounVerb) {
    auto tree = parse_bu("fox jumps");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
}

TEST(BottomUpTest, FailsOnNonsense) {
    auto tree = parse_bu("jumps the the");
    EXPECT_EQ(tree, nullptr);
}

TEST(BottomUpTest, IncompleteSentence) {
    auto tree = parse_bu("The dog");
    EXPECT_EQ(tree, nullptr);
}

TEST(BottomUpTest, AuxiliaryVerb) {
    auto tree = parse_bu("The dog is running");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children[0]->label, "AUX");
}
