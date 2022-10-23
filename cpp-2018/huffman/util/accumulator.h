#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include <vector>

class accumulator {
    public:
        accumulator();
        std::vector<char> acc(std::vector<char>);
        bool isStill();
        char finish();
    private:
        char temp;
        int pos;
};

#endif
