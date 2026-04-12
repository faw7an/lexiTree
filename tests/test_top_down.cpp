#include <gtest/gtest.h>
#include "lexer.h"
#include "top_down_parser.h"

std::unique_ptr<ParseNode> parse(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    TopDownParser parser(tokens);
    return parser.parse();
}

TEST(TopDownTest, SimpleSentence) {
    auto tree = parse("The cat runs");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}

TEST(TopDownTest, ComplexSentence) {
    auto tree = parse("The quick brown fox jumps over the lazy dog");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(TopDownTest, PronounSentence) {
    auto tree = parse("She loves him");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[0]->children[0]->lexeme, "She");
}

TEST(TopDownTest, PrepositionalPhrase) {
    auto tree = parse("The dog sleeps in the house");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children.size(), 2); // V and PP
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(TopDownTest, BareNounVerb) {
    auto tree = parse("fox jumps");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
}

TEST(TopDownTest, FailsOnNonsense) {
    auto tree = parse("jumps the the");
    EXPECT_EQ(tree, nullptr);
}

TEST(TopDownTest, IncompleteSentence) {
    auto tree = parse("The dog");
    EXPECT_EQ(tree, nullptr); // NP but missing VP
}

TEST(TopDownTest, AuxiliaryVerb) {
    auto tree = parse("The dog is running");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children[0]->label, "AUX");
}
