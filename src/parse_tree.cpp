#include "parse_tree.h"

void ParseNode::add_child(std::unique_ptr<ParseNode> child) {
    if (child) {
        children.push_back(std::move(child));
    }
}
