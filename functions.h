#ifndef CPP_HUFFMAN_FUNCTIONS_H
#define CPP_HUFFMAN_FUNCTIONS_H
#include <array>
#include <queue>
#include <vector>

#include "node_comparator.h"
using namespace std;

int parse_input(int argc, char** argv, string &in_file, string &out_file, bool&);
string get_file_content(const string&);
array<int, 256> get_char_frequency(const string&);
priority_queue<node*, vector<node*>, node_comparator> create_nodes(const array<int, 256>&);
node* create_tree(priority_queue<node*, vector<node*>, node_comparator>);
array<vector<bool>, 256> create_translation_dictionary(const node*);
vector<bool> encode(const string&, const array<vector<bool>, 256>&);
vector<bool> serialize_tree(const node*);
void remove_tree(const node*);
string concatenate(const vector<bool>&, const vector<bool>&);
void save_to_file(const string&, const string&);
vector<bool> convert_string_to_vector(const string&);
pair<node*, vector<bool>> deserialize_tree(const vector<bool>&);
string decode(const node*, const vector<bool>&);

#endif //CPP_HUFFMAN_FUNCTIONS_H