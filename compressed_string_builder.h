#ifndef CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#define CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#include <string>
#include <vector>


class compressed_string_builder {
private:
    int ind;
    std::vector<unsigned char> result_string;
    std::vector<unsigned char> filename;
    std::vector<bool> buffer;
    void reduce();
public:
    explicit compressed_string_builder(const std::string&);
    void append(const std::vector<bool>&);
    std::vector<unsigned char> build();
};


#endif //CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H