#include <iostream>
#include <array>
#include "functions.h"
using namespace std;

int main() {
    string in_file, out_file;
    //cin >> in_file >> out_file;
    in_file = "../test.txt";
    string content = get_file_content(in_file);
    array<int, 256> freq = get_char_frequency(content);

    for (int i = 0; i < 256; i++) {
        if (freq[i] == 0) continue;
        cout << static_cast<char>(i) << ' ' << freq[i] << endl;
    }
    return 0;
}