#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include "file/file_reader.h"
#include "file/file_writer.h"
#include <string>

class compressor {
    public:
        compressor(std::string src, std::string dest) : in(src), out(dest) {}
        void compress();
    private:
        file_reader in;
        file_writer out;
};

#endif
