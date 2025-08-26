#include "compressed_string_builder.h"

void compressed_string_builder::reduce() {
    while (buffer.size() >= 8) {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++) {
            c = (c << 1) | (buffer[i] - '0');
        }
        buffer.erase(0, 8);
        result_string.push_back(static_cast<char>(c)); // can I do that?
    }
}

compressed_string_builder::compressed_string_builder() = default;

void compressed_string_builder::append(const std::string& add) {
    buffer += add;
    reduce();
}

std::pair<std::string, int> compressed_string_builder::build() {
    if (!buffer.empty()) {
        unsigned char c = 0;
        for (char i : buffer) {
            c = (c << 1) | (i - '0');
        }
        c <<= (8 - buffer.size());
        result_string.push_back(static_cast<char>(c));
    }
    return {result_string, buffer.size()};
}