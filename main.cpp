#include <string>

#include "functions.h"
using namespace std;

int main(int argc, char** argv){
    string filepath;
    bool compress;
    if (parse_input(argc, argv, filepath, compress)) return 1;
    if (compress) {
        // read the file contents
        const vector<unsigned char> in_file_content = get_file_content(filepath);
        // if file is empty, save only the file's filename
        if (in_file_content.empty()) {
            save_empty_to_file(filepath);
            return 0;
        }
        // calculate the frequency of each char
        const array<int, 256> char_frequency = get_char_frequency(in_file_content);
        // insert frequencies into priority queue
        const priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(char_frequency);
        // create a Huffman tree based on frequencies
        const node* tree = create_tree(nodes);
        // create a translation dictionary - what sequence each char should be translated into
        const array<vector<bool>, 256> translation = create_translation_dictionary(tree);
        // translate all the contents of the file
        const vector<bool> encoded_contents = encode(in_file_content, translation);
        // serialize the tree into bit sequence
        const vector<bool> encoded_tree = serialize_tree(tree);
        // free up the tree
        remove_tree(tree);
        // join the encoded contents of the file with encoded tree to form the whole output + filename
        const vector<unsigned char> out_file_content = concatenate(filepath, encoded_contents, encoded_tree);
        // get the name of the out file
        const string out_filename = get_out_filepath(filepath);
        // save the output to the file
        save_to_file(out_filename, out_file_content);
    }
    else {
        // read the file contents and get the filename
        vector<unsigned char> in_file_content = get_file_content(filepath);
        // extract the filename
        const string out_filename = get_filename(filepath, in_file_content);
        // if there was only filename - the input file was empty
        if (in_file_content.empty()) {
            save_to_file(out_filename, in_file_content);
            return 0;
        }
        // change the format into bit sequence
        const vector<bool> bitstream = convert_unsigned_chars_to_bools(in_file_content);
        // divide the bit sequence into the tree part, serializing it, and into the encoded data part
        const pair<node*, vector<bool>> tree_and_bitstream = deserialize_tree(bitstream);
        // decode the encoded data according to the tree
        const vector<unsigned char> out_file_content = decode(tree_and_bitstream.first, tree_and_bitstream.second);
        // free up the tree
        remove_tree(tree_and_bitstream.first);
        // save decoded data into the file
        save_to_file(out_filename, out_file_content);
    }
    return 0;

    // TODO: exception handling
}