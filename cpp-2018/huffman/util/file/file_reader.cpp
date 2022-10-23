#include "file_reader.h"
#include <fstream>
#include <string>

file_reader::file_reader(std::string s) {
    f.open(s, std::ifstream::in | std::ifstream::binary);
    if (!f.is_open()) {
        throw std::runtime_error("No such file");
    }
    f.seekg(0, f.end);
    length = initialLength = f.tellg();
    f.seekg(0, f.beg);
}

void file_reader::reset() {
    f.seekg(0, f.beg);
    length = initialLength;
}

file_reader::~file_reader() {
    f.close();
}

bool file_reader::ready() {
    return (length != 0);
}

int file_reader::read(char* buffer, int size) {
    if (size > length) {
        size = length;
    }
    length -= size;
    f.read(buffer, size);
    return size;
}

