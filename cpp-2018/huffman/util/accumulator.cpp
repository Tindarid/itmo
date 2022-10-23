#include "accumulator.h"

accumulator::accumulator() {
    pos = 0;
    temp = 0;
}

std::vector<char> accumulator::acc(std::vector<char> data) {
    std::vector<char> ans;
    for (size_t i = 0; i < data.size(); ++i) {
        temp <<= 1;
        temp |= data[i];
        pos++;
        if (pos == 8) {
            ans.push_back(temp);
            pos = 0;
            temp = 0;
        }
    }
    return ans;
}

bool accumulator::isStill() {
    return !(pos == 0);
}

char accumulator::finish() {
    while (pos != 8) {
        temp <<= 1;
        pos++;
    }
    return temp;
}
