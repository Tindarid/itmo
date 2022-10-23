#include <iostream>
#include <string>
#include <ctime>
#include "util/compressor.h"
#include "util/decompressor.h"

void compr(std::string src, std::string dest) {
    std::cout << "Compressing from " + src + " to " + dest << std::endl;
    compressor c(src, dest);
    auto cur = std::clock();
    c.compress();
    std::cout << "Compressed succesfully in: ";
    std::cout << std::fixed << 1.0 * (std::clock() - cur) / CLOCKS_PER_SEC;
    std::cout << "s" << std::endl;
}

void decompr(std::string src, std::string dest) {
    std::cout << "Decompressing from " + src + " to " + dest << std::endl;
    decompressor c(src, dest);
    auto cur = std::clock();
    c.decompress();
    std::cout << "Decompressed succesfully in: ";
    std::cout << std::fixed << 1.0 * (std::clock() - cur) / CLOCKS_PER_SEC;
    std::cout << "s" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        if (argc == 2 && (std::string)argv[1] == "-h") {
            std::cout << "-d to decompress\n-c to compress\n-h help information\n";
            std::cout << "Compressing and decompressing should be with 2 filenames" << std::endl;
        } else {
            std::cout << "Error, please type with arg -h" << std::endl;
        }
        return 0;
    }
    std::string mode = argv[1];
    std::string src = argv[2];
    std::string dest = argv[3];

    if (mode == "-c") {
        try {
            compr(src, dest);
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }
    } else if (mode == "-d") {
        try {
            decompr(src, dest);
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }
    } else {
        std::cout << "Error, please type with arg -h" << std::endl;
    }
}

