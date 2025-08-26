#include <fstream>
#include <iterator>
#include <string>
#include "functions.h"

#include <algorithm>
#include <stack>

#include "compressed_string_builder.h"
#include "node_comparator.h"

std::string get_file_content(const std::string &filename) {
    std::ifstream infile(filename);
    return {(std::istreambuf_iterator<char>(infile)),
                         std::istreambuf_iterator<char>()};
}

std::array<int, 256> get_char_frequency(const std::string& text) {
    std::array<int, 256> ret{};
    for (const char i : text) {
        ret[i]++;
    }
    return ret;
}

std::vector<std::pair<int, int>> convert_array_to_vector_of_pairs(std::array<int, 256>& arr) {
    std::vector<std::pair<int, int>> ret{};
    for (int i = 0; i < 256; i++) {
        if (arr[i] == 0) continue;
        ret.emplace_back(i, arr[i]);
    }
    return ret;
}

void sort_by_value(std::vector<std::pair<int, int>>& V) {
    sort(V.begin(), V.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
}

std::priority_queue<node*, std::vector<node*>, node_comparator> create_nodes(
    const std::vector<std::pair<int, int> > &V) {
    std::priority_queue<node*, std::vector<node*>, node_comparator> nodes;
    for (const auto& i : V) {
        node* n = new node(static_cast<char>(i.first), i.second);
        nodes.emplace(n);
    }
    return nodes;
}

node* create_tree(std::priority_queue<node*, std::vector<node*>, node_comparator> nodes) {
    while (nodes.size() >= 2) {
        node* n1 = nodes.top();
        nodes.pop();
        node* n2 = nodes.top();
        nodes.pop();
        node* n = new node(n1, n2);
        nodes.emplace(n);
    }
    return nodes.top();
}

void dfs(node* n, const std::string &sequence, std::array<std::string, 256>& dictionary) {
    if (n->get_left() == nullptr) { // leaf, letter
        dictionary[n->get_c()] = sequence;
        return;
    }
    dfs(n->get_left(), sequence + "0", dictionary);
    dfs(n->get_right(), sequence + "1", dictionary);
}

std::array<std::string, 256> create_translation_dictionary(node* tree) {
    std::array<std::string, 256> ret{};
    dfs(tree, "", ret);
    return ret;
}

std::pair<std::string, int> encode(const std::string& s, const std::array<std::string, 256>& dictionary) {
    compressed_string_builder sb;
    for (const char i : s) {
        sb.append(dictionary[i]);
    }
    return sb.build();
}

void recursive_tree_serialization(const node* n, std::vector<bool>& data) {
    if (n->get_left() == nullptr) { // leaf, letter
        data.emplace_back(1);
        for (int i = 7; i >= 0; i--) {
            data.emplace_back(n->get_c() >> i & 1);
        }
        return;
    }
    data.emplace_back(0);
    recursive_tree_serialization(n->get_left(), data);
    recursive_tree_serialization(n->get_right(), data);

}

std::vector<bool> serialize_tree(const node* tree) {
    std::vector<bool> ret{};
    recursive_tree_serialization(tree, ret);
    return ret;
}