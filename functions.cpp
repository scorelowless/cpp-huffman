#include <fstream>
#include <iterator>
#include <string>
#include "functions.h"

std::string get_file_content(const std::string &filename) {
    std::ifstream infile(filename);
    return {(std::istreambuf_iterator<char>(infile)),
                         std::istreambuf_iterator<char>()};
}
