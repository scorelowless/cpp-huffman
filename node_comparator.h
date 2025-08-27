#ifndef CPP_HUFFMAN_NODE_COMPARATOR_H
#define CPP_HUFFMAN_NODE_COMPARATOR_H
#include "node.h"


struct node_comparator {
    bool operator()(const node* lhs, const node* rhs) const;
};


#endif //CPP_HUFFMAN_NODE_COMPARATOR_H