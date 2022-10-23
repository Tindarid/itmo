#include <iostream>
#include "big_integer.h"
using namespace std;

int main() {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");
    cout << ((a * b) / a == b) << endl;
    return 0;
}
