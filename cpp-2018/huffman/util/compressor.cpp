#include "compressor.h"
#include "lib/encoder.h"
#include "accumulator.h"

void compressor::compress() {
    std::vector<size_t> table(256);
    const int size = 4096;
    char buffer[size];
    size_t all = 0;
    while (in.ready()) {
        int r = in.read(buffer, size);
        for (int i = 0; i < r; ++i) {
            table[(unsigned char)buffer[i]]++;
            all++;
        }
    }
    in.reset();
    encoder coder(table);

    table.push_back(all);
    for (size_t i = 0; i < table.size(); ++i) {
        uint64_t cur = table[i];
        for (size_t j = 8; j > 0; --j) {
            buffer[i * 8 + j - 1] = (unsigned char)(cur % 256);
            cur >>= 8;
        }
    }
    out.write(buffer, table.size() * 8);

    accumulator acc;
    while (in.ready()) {
        int r = in.read(buffer, size);
        std::vector<char> data(buffer, buffer + r);
        std::vector<char> ans = acc.acc(coder.encode(data));
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
    if (acc.isStill()) {
        buffer[0] = acc.finish();
        out.write(buffer, 1);
    }
}
