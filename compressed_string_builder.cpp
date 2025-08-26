#include "compressed_string_builder.h"

void compressed_string_builder::reduce() {
    while (buffer.size() >= 8) {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++) {
            c = c << 1 | buffer[i];
        }
        buffer.erase(buffer.begin(), buffer.begin() + 8);
        result_string.push_back(static_cast<char>(c)); // can I do that?
    }
}

compressed_string_builder::compressed_string_builder() = default;

void compressed_string_builder::append(const std::vector<bool>& add) {
    buffer.insert(buffer.end(), add.begin(), add.end());
    reduce();
}

std::pair<std::string, int> compressed_string_builder::build() {
    if (!buffer.empty()) {
        unsigned char c = 0;
        for (bool i : buffer) {
            c = c << 1 | i;
        }
        c <<= 8 - buffer.size();
        result_string.push_back(static_cast<char>(c));
    }
    return {result_string, buffer.size()};
}