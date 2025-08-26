#include "node.h"

node::node(node *left, node *right) {
    this->left = left;
    this->right = right;
    this->weight = left->get_weight() + right->get_weight();
}

node::~node() = default;

node* node::get_left() const {
    return this->left;
}

node* node::get_right() const {
    return this->right;
}

int node::get_weight() const {
    return this->weight;
}
