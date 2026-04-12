#include <gtest/gtest.h>
#include "lexer.h"

TEST(LexerTest, Determiners) {
    Lexer l("the");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::DET);
}

TEST(LexerTest, PunctuationStripping) {
    Lexer l("Hello, world!");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].word, "Hello");
    EXPECT_EQ(tokens[1].word, "world");
}

TEST(LexerTest, SuffixHeuristic_ly) {
    Lexer l("quickly");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::ADV);
}

TEST(LexerTest, SuffixHeuristic_ing) {
    Lexer l("running");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::V);
}

TEST(LexerTest, SuffixHeuristic_ed) {
    Lexer l("walked");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::V);
}

TEST(LexerTest, SuffixHeuristic_tion_ness_ment) {
    Lexer l("action happiness placement");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].tag, POS::N);
    EXPECT_EQ(tokens[1].tag, POS::N);
    EXPECT_EQ(tokens[2].tag, POS::N);
}

TEST(LexerTest, ProperNounHeuristic) {
    Lexer l("the John runs");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[1].tag, POS::PROPER_N);
}

TEST(LexerTest, BasicSentence) {
    Lexer l("The quick brown fox jumps.");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[0].tag, POS::DET);
    EXPECT_EQ(tokens[1].tag, POS::ADJ);
    EXPECT_EQ(tokens[2].tag, POS::ADJ);
    EXPECT_EQ(tokens[3].tag, POS::N);
    EXPECT_EQ(tokens[4].tag, POS::V);
}

TEST(LexerTest, UnknownWord) {
    Lexer l("jabberwocky");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::UNKNOWN);
}

TEST(LexerTest, CaseInsensitiveLookup) {
    Lexer l("THE DOG RUNS");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].tag, POS::DET);
    EXPECT_EQ(tokens[1].tag, POS::N);
    EXPECT_EQ(tokens[2].tag, POS::V);
}
