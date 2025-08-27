#include <iostream>
#include <array>
#include <queue>
#include <vector>

#include "compressed_string_builder.h"
#include "functions.h"
#include "node.h"
using namespace std;

int main(int argc, char** argv){
    string in_file, out_file;
    bool compress;
    if (parse_input(argc, argv, in_file, out_file, compress)) return 1;
    if (compress) {
        const string content = get_file_content(in_file);
        array<int, 256> freq = get_char_frequency(content);
        vector<pair<int, int>> freq_key_value = convert_array_to_vector_of_pairs(freq);
        sort_by_value(freq_key_value);
        const priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(freq_key_value);
        node* tree = create_tree(nodes);
        const array<string, 256> translation = create_translation_dictionary(tree);
        const vector<bool> encoded_data = encode(content, translation);
        const vector<bool> encoded_tree = serialize_tree(tree);
        const string out_file_content = concatenate(encoded_data, encoded_tree);
        save_to_file(out_file, out_file_content);
    }
    else {
        const string content = get_file_content(in_file);
        const vector<bool> code = convert_string_to_vector(content);
        const pair<node*, vector<bool>> tree_and_code = deserialize_tree(code);
        string data = decode(tree_and_code.first, tree_and_code.second);
        save_to_file(out_file, data);
    }
    return 0;
}