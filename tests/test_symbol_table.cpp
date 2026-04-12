#include <gtest/gtest.h>
#include "lexer.h"
#include "top_down_parser.h"
#include "symbol_table.h"
#include <algorithm>

std::unique_ptr<ParseNode> get_tree(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    TopDownParser parser(tokens);
    return parser.parse();
}

TEST(SymbolTableTest, ExtractsVerb) {
    auto tree = get_tree("The dog runs");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();
    
    auto verb_it = std::find_if(entries.begin(), entries.end(),
        [](const auto& e){ return e.pos_tag == "V"; });
    
    EXPECT_NE(verb_it, entries.end());
    EXPECT_EQ(verb_it->lexeme, "runs");
    EXPECT_EQ(verb_it->grammar_role, "VP.head");
    EXPECT_EQ(verb_it->scope, "Sentence");
}

TEST(SymbolTableTest, PrepPhraseScope) {
    auto tree = get_tree("The dog sleeps in the house");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();

    auto prep_it = std::find_if(entries.begin(), entries.end(),
        [](const auto& e){ return e.pos_tag == "PREP"; });
    
    EXPECT_NE(prep_it, entries.end());
    EXPECT_EQ(prep_it->grammar_role, "PP.head");
    EXPECT_EQ(prep_it->scope, "Prepositional");
    
    auto noun_it = std::find_if(entries.rbegin(), entries.rend(),
        [](const auto& e){ return e.pos_tag == "N"; });
    
    EXPECT_NE(noun_it, entries.rend());
    EXPECT_EQ(noun_it->lexeme, "house");
    EXPECT_EQ(noun_it->grammar_role, "NP.head");
    EXPECT_EQ(noun_it->scope, "Prepositional");
}

TEST(SymbolTableTest, CheckGrammarRoles) {
    auto tree = get_tree("The quick brown fox jumps");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();

    EXPECT_EQ(entries.size(), 5);
    EXPECT_EQ(entries[0].grammar_role, "NP.determiner"); // The
    EXPECT_EQ(entries[1].grammar_role, "NP.modifier");   // quick
    EXPECT_EQ(entries[2].grammar_role, "NP.modifier");   // brown
    EXPECT_EQ(entries[3].grammar_role, "NP.head");       // fox
    EXPECT_EQ(entries[4].grammar_role, "VP.head");       // jumps
}
