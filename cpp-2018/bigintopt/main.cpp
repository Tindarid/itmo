#include <iostream>
#include "big_integer.h"
#include "myvector/myvector.h"
using namespace std;

void printVector(myvector &a) {
    for (size_t i = 0; i < a.size(); ++i)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    big_integer a = 65536;

    cout << ((a*a) >> 31) << endl;
    return 0;
}
