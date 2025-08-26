#include <fstream>
#include <iterator>
#include <string>
#include "functions.h"

#include <algorithm>

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

std::priority_queue<node> create_nodes(const std::vector<std::pair<int, int>>& V) {
    std::priority_queue<node> nodes;
    for (const auto& i : V) {
        nodes.emplace(static_cast<char>(i.first), i.second);
    }
    return nodes;
}