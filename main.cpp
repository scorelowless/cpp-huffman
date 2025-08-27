#include <string>

#include "functions.h"
using namespace std;

int main(int argc, char** argv){
    string in_file;
    bool compress;
    if (parse_input(argc, argv, in_file, compress)) return 1;
    if (compress) {
        // read the file contents
        const vector<unsigned char> content = get_file_content(in_file);
        // calculate the frequency of each char
        const array<int, 256> freq = get_char_frequency(content);
        // insert frequencies into priority queue
        const priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(freq);
        // create a Huffman tree based on frequencies
        const node* tree = create_tree(nodes);
        // create a translation dictionary - what sequence each char should be translated into
        const array<vector<bool>, 256> translation = create_translation_dictionary(tree);
        // translate all the contents of the file
        const vector<bool> encoded_data = encode(content, translation);
        // serialize the tree into bit sequence
        const vector<bool> encoded_tree = serialize_tree(tree);
        // free up the tree
        remove_tree(tree);
        // join the encoded contents of the file with encoded tree to form the whole output + filename
        const vector<unsigned char> out_file_content = concatenate(in_file, encoded_data, encoded_tree);
        // get the name of the out file
        string out_filename = get_out_filename(in_file);
        // save the output to the file
        save_to_file(out_filename, out_file_content);
    }
    else {
        // read the file contents and get the filename
        vector<unsigned char> content = get_file_content(in_file);
        // extract the filename
        const string filename = get_filename(in_file, content);
        // change the format into bit sequence
        const vector<bool> code = convert_unsigned_chars_to_bools(content);
        // divide the bit sequence into the tree part, serializing it, and into the encoded data part
        const pair<node*, vector<bool>> tree_and_code = deserialize_tree(code);
        // decode the encoded data according to the tree
        const vector<unsigned char> data = decode(tree_and_code.first, tree_and_code.second);
        // free up the tree
        remove_tree(tree_and_code.first);
        // save decoded data into the file
        save_to_file(filename, data);
    }
    return 0;
}