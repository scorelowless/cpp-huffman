#include <fstream>
#include <iterator>
#include <string>
#include "functions.h"

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
