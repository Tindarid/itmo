#ifndef DECODER_H
#define DECODER_H
#include "tree.h"

class decoder {
    public:
        decoder(std::vector<size_t>);
        ~decoder();
        std::vector<char> decode(std::vector<char>);
    private:
        tree* htree;
};

#endif
