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
        // read the file contents
        const string content = get_file_content(in_file);
        // calculate the frequency of each char
        array<int, 256> freq = get_char_frequency(content);
        // change the format in which above-mentioned frequencies are stored
        vector<pair<int, int>> freq_key_value = convert_array_to_vector_of_pairs(freq);
        // sort the frequencies by the values
        sort_by_value(freq_key_value);
        // insert frequencies into priority queue
        const priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(freq_key_value);
        // create a Huffman tree based on frequencies
        node* tree = create_tree(nodes);
        // create a translation dictionary - what sequence each char should be translated into
        const array<string, 256> translation = create_translation_dictionary(tree);
        // translate all the contents of the file
        const vector<bool> encoded_data = encode(content, translation);
        // serialize the tree into bit sequence
        const vector<bool> encoded_tree = serialize_tree(tree);
        // join the encoded contents of the file with encoded tree to form the whole output
        const string out_file_content = concatenate(encoded_data, encoded_tree);
        // save the output to the file
        save_to_file(out_file, out_file_content);
    }
    else {
        // read the file contents
        const string content = get_file_content(in_file);
        // change the format into bit sequence
        const vector<bool> code = convert_string_to_vector(content);
        // divide the bit sequence into the tree part, serializing it, and into the encoded data part
        const pair<node*, vector<bool>> tree_and_code = deserialize_tree(code);
        // decode the encoded data according to the tree
        string data = decode(tree_and_code.first, tree_and_code.second);
        // save decoded data into the file
        save_to_file(out_file, data);
    }
    return 0;
}