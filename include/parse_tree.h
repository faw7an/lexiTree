#pragma once
#include <string>
#include <vector>
#include <memory>

enum class NodeType { TERMINAL, NON_TERMINAL };

struct ParseNode {
    std::string label;
    std::string lexeme;
    NodeType type;
    std::vector<std::unique_ptr<ParseNode>> children;

    void add_child(std::unique_ptr<ParseNode> child);
    bool is_leaf() const { return type == NodeType::TERMINAL; }
};
