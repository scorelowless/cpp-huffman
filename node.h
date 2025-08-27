#ifndef CPP_HUFFMAN_NODE_H
#define CPP_HUFFMAN_NODE_H


class node{
private:
    node* left;
    node* right;
    int weight;
    char c;
public:
    node(node* left, node* right);
    node(char c, int weight);
    ~node();
    int get_weight() const;
    node* get_left() const;
    node* get_right() const;
    char get_c() const;
};


#endif //CPP_HUFFMAN_NODE_H