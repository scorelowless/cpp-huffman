#ifndef CPP_HUFFMAN_FUNCTIONS_H
#define CPP_HUFFMAN_FUNCTIONS_H
#include <array>
#include <queue>
#include <queue>
#include <vector>

#include "node.h"
#include "node_comparator.h"

int parse_input(int argc, char** argv, std::string &in_file, std::string &out_file, bool&);
std::string get_file_content(const std::string&);
std::array<int, 256> get_char_frequency(const std::string&);
std::vector<std::pair<int, int>> convert_array_to_vector_of_pairs(std::array<int, 256>&);
void sort_by_value(std::vector<std::pair<int, int>>&);
std::priority_queue<node*, std::vector<node*>, node_comparator> create_nodes(const std::vector<std::pair<int, int>>&);
node* create_tree(std::priority_queue<node*, std::vector<node*>, node_comparator>);
std::array<std::string, 256> create_translation_dictionary(node*);
std::vector<bool> encode(const std::string&, const std::array<std::string, 256>&);
std::vector<bool> serialize_tree(const node*);
std::string concatenate(const std::vector<bool>&, const std::vector<bool>&);
void save_to_file(const std::string&, const std::string&);
std::vector<bool> convert_string_to_vector(const std::string&);
std::pair<node*, std::vector<bool>> deserialize_tree(const std::vector<bool>&);

#endif //CPP_HUFFMAN_FUNCTIONS_H