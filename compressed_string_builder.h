#ifndef CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#define CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H
#include <string>
#include <vector>


class compressed_string_builder {
private:
    std::string result_string;
    std::string buffer;
    void reduce();
public:
    compressed_string_builder();
    void append(const std::string&);
    std::pair<std::string, int> build();
};


#endif //CPP_HUFFMAN_COMPRESSED_STRING_BUILDER_H