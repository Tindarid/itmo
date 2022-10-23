#include "encoder.h"
#include <algorithm>
#include <stdexcept>

encoder::encoder(std::vector<size_t> table) {
    htree = new tree(table);
}

encoder::~encoder() {
    delete htree;
}

std::vector<char> encoder::encode(std::vector<char> data) {
    std::vector<char> ans;
    for (size_t i = 0; i < data.size(); ++i) {
        uint64_t temp = htree->getCode(data[i]);
        int count = htree->getCodeLength(data[i]);
        if (count == 0) {
            throw std::runtime_error("File for encoding is corrupt");
        }
        for (int i = 0; i < count; ++i) {
            ans.push_back(temp % 2);
            temp /= 2;
        }
        std::reverse(ans.rbegin(), ans.rbegin() + count);
    }
    return ans;
}
