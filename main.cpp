#include <iostream>
#include <array>
#include <queue>
#include <vector>

#include "functions.h"
#include "node.h"
using namespace std;

int main() {
    string in_file, out_file;
    //cin >> in_file >> out_file;
    in_file = "../test.txt";
    string content = get_file_content(in_file);
    array<int, 256> freq = get_char_frequency(content);
    vector<pair<int, int>> freq_key_value = convert_array_to_vector_of_pairs(freq);
    sort_by_value(freq_key_value);
    priority_queue<node*, vector<node*>, node_comparator> nodes = create_nodes(freq_key_value);
    node* tree = create_tree(nodes);

    return 0;
}