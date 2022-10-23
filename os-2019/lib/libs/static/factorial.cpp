#include "factorial.h"

long long factorial::count(int ind) {
    long long res = 1;
    for (int i = 2; i <= ind; ++i) {
        res *= i;
    }
    return res;
}

