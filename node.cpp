#include "node.h"

node::node(node *left, node *right) {
    this->left = left;
    this->right = right;
    this->weight = left->get_weight() + right->get_weight();
    c = 0;
}

node::node(char c, int weight) {
    this->weight = weight;
    this->left = nullptr;
    this->right = nullptr;
    this->c = c;
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

char node::get_c() const {
    return this->c;
}

bool node::operator<(const node &other) const {
    return this->weight < other.weight;
}
