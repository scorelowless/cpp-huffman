#include <fstream>
#include <filesystem>

#include "compressed_string_builder.h"
#include "functions.h"
using namespace std;

int parse_input(int argc, char** argv, string &filename, bool& compress) {
    if (argc != 3) return 1;
    if (string(argv[1]) != "-c" && string(argv[1]) != "-d") return 1;
    filename = argv[2];
    compress = string(argv[1]) != "-d";
    return 0;
}

vector<unsigned char> get_file_content(const string &filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);
    const auto size = file.tellg();
    if (size < 0) throw std::runtime_error("Failed to get file size: " + filename);
    file.seekg(0);

    vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

void save_empty_to_file(const string &filename) {
    string data_string = filesystem::path(filename).filename().string();
    vector<unsigned char> data = vector<unsigned char>(data_string.begin(), data_string.end());
    data.emplace_back(0);
    save_to_file(get_out_filepath(filename), data);
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
    // if file has only one unique char
    if (tree->get_left() == nullptr) {
        ret[tree->get_c()] = vector<bool>(1, false);
        return ret;
    }
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


vector<unsigned char> concatenate(const string& filename, const vector<bool>& data, const vector<bool>& tree) {
    compressed_string_builder builder(filesystem::path(filename).filename().string());
    builder.append(tree);
    builder.append(data);
    return builder.build();
}

string get_out_filepath(const string &filepath) {
    filesystem::path p(filepath);
    return p.replace_extension(".hff");
}

string get_unique_out_filepath(const string &filepath) {
    const filesystem::path file(filepath);
    if (!filesystem::exists(file)) return filepath;
    const filesystem::path parent(file.parent_path());
    const string stem = file.stem().string();
    const string ext = file.extension().string();
    int counter = 1;
    filesystem::path final_path;
    do {
        final_path = parent / (stem + " (" + to_string(counter) + ')' + ext);
        counter++;
    } while (filesystem::exists(final_path));
    return final_path.string();
}

void save_to_file(const string &filepath, const vector<unsigned char> &data) {
    const string final_filepath = get_unique_out_filepath(filepath);
    ofstream outfile(final_filepath, ios::binary);
    outfile.write(reinterpret_cast<const char*>(data.data()), static_cast<streamsize>(data.size()));
}

string get_filename(const string& filepath, vector<unsigned char> &data) {
    const string filename(reinterpret_cast<char*>(data.data()));
    data.erase(data.begin(), data.begin() + static_cast<long>(filename.size()) + 1);
    const filesystem::path p(filepath);
    const filesystem::path outfile = p.parent_path() / filename;
    return outfile.string();
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
    //if the tree has only one node
    if (n->get_left() == nullptr) {
        for (int i = 0; i < data.size(); i++) {
            ret.emplace_back(n->get_c());
        }
        return ret;
    }
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