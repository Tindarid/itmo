#include "decoder.h"
#include <stdexcept>

decoder::decoder(std::vector<size_t> table) {
    htree = new tree(table);
}

decoder::~decoder() {
    delete htree;
}

std::vector<char> decoder::decode(std::vector<char> data) {
    std::vector<char> ans;
    for (size_t i = 0; i < data.size(); ++i) {
        if (!htree->down(data[i])) {
            throw std::runtime_error("Incorrect data for decoding");
        }
        if (htree->isTerm()) {
            ans.push_back(htree->getSymbol());
            htree->reset();
        }
    }
    return ans;
}
