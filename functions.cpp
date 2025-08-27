#include <fstream>

#include "compressed_string_builder.h"
#include "functions.h"
using namespace std;

int parse_input(int argc, char** argv, string &in_file, string &out_file, bool& compress) {
    if (argc != 4) return 1;
    if (string(argv[1]) != "-c" && string(argv[1]) != "-d") return 1;
    in_file = argv[2];
    out_file = argv[3];
    compress = string(argv[1]) != "-d";
    return 0;
}

vector<unsigned char> get_file_content(const string &filename) {
    ifstream file(filename, ios::binary | ios::ate);
    const auto size = file.tellg();
    file.seekg(0);

    vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

array<int, 256> get_char_frequency(const vector<unsigned char>& data) {
    array<int, 256> ret{};
    for (const unsigned char i : data) {
        ret[i]++;
    }
    return ret;
}

priority_queue<node*, vector<node*>, node_comparator> create_nodes(const array<int, 256>& freq) {
    priority_queue<node*, vector<node*>, node_comparator> nodes;
    for (int i = 0; i < 256; i++) {
        if (freq[i] == 0) continue;
        nodes.push(new node(static_cast<char>(i), freq[i]));
    }
    return nodes;
}

node* create_tree(priority_queue<node*, vector<node*>, node_comparator> nodes) {
    while (nodes.size() >= 2) {
        node* n1 = nodes.top();
        nodes.pop();
        node* n2 = nodes.top();
        nodes.pop();
        nodes.emplace(new node(n1, n2));
    }
    return nodes.top();
}

void dfs(const node* n, const vector<bool> &sequence, array<vector<bool>, 256>& dictionary) {
    if (n->get_left() == nullptr) { // leaf, letter
        dictionary[n->get_c()] = sequence;
        return;
    }
    vector<bool> left = sequence;
    left.emplace_back(0);
    vector<bool> right = sequence;
    right.emplace_back(1);
    dfs(n->get_left(), left, dictionary);
    dfs(n->get_right(), right, dictionary);
}

array<vector<bool>, 256> create_translation_dictionary(const node* tree) {
    array<vector<bool>, 256> ret{};
    const vector<bool> seq;
    dfs(tree, seq, ret);
    return ret;
}

vector<bool> encode(const vector<unsigned char>& s, const array<vector<bool>, 256>& dictionary) {
    vector<bool> ret{};
    for (const unsigned char i : s) {
        ret.insert(ret.end(), dictionary[i].begin(), dictionary[i].end());
    }
    return ret;
}

void recursive_tree_serialization(const node* n, vector<bool>& data) {
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

vector<bool> serialize_tree(const node* tree) {
    vector<bool> ret{};
    recursive_tree_serialization(tree, ret);
    return ret;
}

void remove_tree(const node* n) {
    if (n->get_left() != nullptr) {
        remove_tree(n->get_left());
        remove_tree(n->get_right());
    }
    delete n;
}


vector<unsigned char> concatenate(const vector<bool>& data, const vector<bool>& tree) {
    compressed_string_builder builder;
    builder.append(tree);
    builder.append(data);
    return builder.build();
}

void save_to_file(const string &filename, const vector<unsigned char> &data) {
    ofstream outfile(filename, ios::binary);
    outfile.write(reinterpret_cast<const char*>(data.data()), static_cast<long>(data.size()));
}

vector<bool> convert_unsigned_chars_to_bools(const vector<unsigned char> &data) {
    vector<bool> ret{};
    for (int i = 1; i < data.size() - 1; i++) {
        for (int j = 7; j >= 0; j--) {
            ret.emplace_back(data[i] >> j & 1);
        }
    }
    for (int i = 7; i >= data[0]; i--) {
        ret.emplace_back(data[data.size() - 1] >> i & 1);
    }
    return ret;
}

node* recursive_tree_deserialization(const vector<bool>& data, int& i) {
    if (data[i] == 1) {
        i++;
        unsigned char c = 0;
        for (int j = i; j < i + 8; ++j) {
            c = c << 1 | data[j];
        }
        i += 8;
        return new node(static_cast<char>(c), 0);
    }
    else {
        i++;
        node* left = recursive_tree_deserialization(data, i);
        node* right = recursive_tree_deserialization(data, i);
        return new node(left, right);
    }
}

pair<node*, vector<bool>> deserialize_tree(const vector<bool>& data) {
    int i = 0;
    node* tree = recursive_tree_deserialization(data, i);
    return {tree, vector<bool>(data.begin() + i, data.end())};
}

vector<unsigned char> decode(const node* n, const vector<bool>& data) {
    vector<unsigned char> ret;
    const node* current = n;
    for (const bool& i : data) {
        if (!i) {
            current = current->get_left();
        }
        else {
            current = current->get_right();
        }
        if (current->get_left() == nullptr) { // leaf, letter
            ret.emplace_back(current->get_c());
            current = n;
        }
    }
    return ret;
}