#include "decompressor.h"
#include "lib/decoder.h"
#include <algorithm>

void decompressor::decompress() {
    std::vector<size_t> table(257);
    const int size = 4096;
    char buffer[size];

    unsigned int r = in.read(buffer, table.size() * 8);
    if (r < table.size()) {
        throw std::runtime_error("Incorrect file for decoding");
    }
    for (size_t i = 0; i < table.size(); ++i) {
        uint64_t temp = 0;
        for (size_t j = 0; j < 8; ++j) {
            temp <<= 8;
            temp += (unsigned char)buffer[i * 8 + j];
        }
        table[i] = temp;
    }

    size_t all = table[256];
    table.pop_back();

    decoder coder(table);
    while(in.ready()) {
        unsigned int r = in.read(buffer, size);
        std::vector<char> data;
        for (size_t i = 0; i < r; ++i) {
            unsigned char cur = buffer[i];
            for (size_t j = 0; j < 8; ++j) {
                data.push_back(cur % 2);
                cur /= 2;
            }
            std::reverse(data.rbegin(), data.rbegin() + 8);
        }
        std::vector<char> ans = coder.decode(data);
        if (ans.size() > all) {
            ans.resize(all);
        }
        all -= ans.size();
        for (size_t i = 0, j = 0; i < ans.size(); ++i) {
            buffer[j] = ans[i];
            j++;
            if (j == size) {
                out.write(buffer, size);
                j = 0;
            } else if (i == ans.size() - 1) {
                out.write(buffer, j);
            }
        }
    }
    if (all != 0) {
        throw std::runtime_error("Incorrect file for decoding");
    }
}
