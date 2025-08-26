#include <iostream>
#include <array>
#include <queue>
#include <vector>

#include "compressed_string_builder.h"
#include "functions.h"
#include "node.h"
using namespace std;

int main() {
    string in_file, out_file;
    //cin >> in_file >> out_file;
    in_file = "../test.txt";
    const string content = get_file_content(in_file);
    array<int, 256> freq = get_char_frequency(content);
    vector<pair<int, int>> freq_key_value = convert_array_to_vector_of_pairs(freq);
    sort_by_value(freq_key_value);
    const priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(freq_key_value);
    node* tree = create_tree(nodes);
    const array<string, 256> translation = create_translation_dictionary(tree);
    const pair<string, int> encoded_data = encode(content, translation);

    for (int i = 0; i < 256; i++) {
        if (translation[i].empty()) continue;
        cout << static_cast<char>(i) << ' ' << translation[i] << endl;
    }
    cout << endl << encoded_data.second << endl << encoded_data.first << endl;
    return 0;
}