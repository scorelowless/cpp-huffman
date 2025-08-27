#include "compressed_string_builder.h"

void compressed_string_builder::reduce() {
    while (buffer.size() >= 8) {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++) {
            c = c << 1 | buffer[i];
        }
        buffer.erase(buffer.begin(), buffer.begin() + 8);
        result_string.push_back(static_cast<char>(c));
    }
}

compressed_string_builder::compressed_string_builder() = default;

void compressed_string_builder::append(const std::vector<bool>& add) {
    buffer.insert(buffer.end(), add.begin(), add.end());
    reduce();
}

std::vector<unsigned char> compressed_string_builder::build() {
    const unsigned char trailing_zeros = (8 - buffer.size()) % 8;
    if (!buffer.empty()) {
        unsigned char c = 0;
        for (const bool i : buffer) {
            c = c << 1 | static_cast<unsigned char>(i);
        }
        c <<= trailing_zeros;
        result_string.emplace_back(c);
    }
    result_string.insert(result_string.begin(), trailing_zeros);
    return result_string;
}
