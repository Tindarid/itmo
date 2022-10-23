#include "pow.h"

extern "C" {
    long long count(int number, int st) {
        long long res = 1;
        for (int i = 0; i < st; ++i) {
            res *= number;
        }
        return res;
    }
}
