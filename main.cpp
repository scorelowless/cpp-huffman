#include <iostream>
#include "functions.h"
using namespace std;

int main() {
    string in_file, out_file;
    cin >> in_file >> out_file;
    string content = get_file_content(in_file);
    cout << content << endl;
    return 0;
}