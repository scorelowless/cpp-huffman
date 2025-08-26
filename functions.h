#ifndef CPP_HUFFMAN_FUNCTIONS_H
#define CPP_HUFFMAN_FUNCTIONS_H
#include <array>
#include <queue>
#include <queue>
#include <vector>

#include "node.h"
#include "node_comparator.h"

std::string get_file_content(const std::string&);
std::array<int, 256> get_char_frequency(const std::string&);
std::vector<std::pair<int, int>> convert_array_to_vector_of_pairs(std::array<int, 256>&);
void sort_by_value(std::vector<std::pair<int, int>>&);
std::priority_queue<node*, std::vector<node*>, node_comparator> create_nodes(const std::vector<std::pair<int, int>>&);
node* create_tree(std::priority_queue<node*, std::vector<node*>, node_comparator>);

#endif //CPP_HUFFMAN_FUNCTIONS_H