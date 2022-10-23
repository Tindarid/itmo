#include "file_writer.h"
#include <fstream>
#include <string>

file_writer::file_writer(std::string s) {
    f.open(s, std::ofstream::out | std::ofstream::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
}

file_writer::~file_writer() {
    f.close();
}

void file_writer::write(char* buffer, int size) {
    f.write(buffer, size);
}
