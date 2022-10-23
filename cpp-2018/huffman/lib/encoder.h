#ifndef ENCODER_H
#define ENCODER_H
#include "tree.h"

class encoder {
    public:
        encoder(std::vector<size_t>);
        ~encoder();
        std::vector<char> encode(std::vector<char>);
    private:
        tree* htree;
};

#endif
