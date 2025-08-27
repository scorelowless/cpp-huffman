#ifndef CPP_HUFFMAN_FUNCTIONS_H
#define CPP_HUFFMAN_FUNCTIONS_H
#include <array>
#include <queue>
#include <vector>

#include "node_comparator.h"
using namespace std;

int parse_input(int argc, char** argv, string &filename, bool&);
vector<unsigned char> get_file_content(const string&);
array<int, 256> get_char_frequency(const vector<unsigned char>&);
priority_queue<node*, vector<node*>, node_comparator> create_nodes(const array<int, 256>&);
node* create_tree(priority_queue<node*, vector<node*>, node_comparator>);
array<vector<bool>, 256> create_translation_dictionary(const node*);
vector<bool> encode(const vector<unsigned char>&, const array<vector<bool>, 256>&);
vector<bool> serialize_tree(const node*);
void remove_tree(const node*);
vector<unsigned char> concatenate(const string&, const vector<bool>&, const vector<bool>&);
string get_out_filename(const string&);
void save_to_file(const string&, const vector<unsigned char>&);
string get_filename(string&, vector<unsigned char>&);
vector<bool> convert_unsigned_chars_to_bools(const vector<unsigned char>&);
pair<node*, vector<bool>> deserialize_tree(const vector<bool>&);
vector<unsigned char> decode(const node*, const vector<bool>&);

#endif //CPP_HUFFMAN_FUNCTIONS_H