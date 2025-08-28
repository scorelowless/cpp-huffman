# cpp-huffman
An easy compression software based on Huffman algorithm.

## Usage
After compiling the program has two modes:

### Compression
`./cpp-huffman -c /path/to/the/file.txt`

Above line would create a file `file.hff` in the `/path/to/the/` directory - same path and name but different extension.

> [!Note]
> If there already exists `/path/to/the/file.hff`, the program will try to add *(1)*, *(2)*, etc. to the name.

### Decompression
`./cpp-huffman -d /path/to/the/file.hff`

Above line would create a file in the `/path/to/the/` directory. The file name and extension will be the same as the original file.

> [!Note]
> If there already exists the file that the cpp-huffman would create after decompression, the program will try to add *(1)*, *(2)*, etc. to the name, similarly to compression.

## Disclaimer
The project is still in the development. The developer doesn't take any accountability for potential loss of data.

Changes introduced in future version may not be able to decompress the .hff files created with older versions.
