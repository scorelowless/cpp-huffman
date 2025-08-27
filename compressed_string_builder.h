#ifndef CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#define CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#include <string>
#include <vector>


class compressed_string_builder {
private:
    std::vector<unsigned char> result_string;
    std::vector<bool> buffer;
    void reduce();
public:
    compressed_string_builder();
    void append(const std::vector<bool>&);
    std::vector<unsigned char> build();
};


#endif //CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H