#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include "file/file_reader.h"
#include "file/file_writer.h"
#include <string>

class decompressor {
    public:
        decompressor(std::string src, std::string dest) : in(src), out(dest) {}
        void decompress();
    private:
        file_reader in;
        file_writer out;
};

#endif
