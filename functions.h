#ifndef CPP_HUFFMAN_FUNCTIONS_H
#define CPP_HUFFMAN_FUNCTIONS_H
#include <array>

std::string get_file_content(const std::string&);
std::array<int, 256> get_char_frequency(const std::string&);

#endif //CPP_HUFFMAN_FUNCTIONS_H