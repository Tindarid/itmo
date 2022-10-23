#include <iostream>
#include "circular_buffer.h"
using namespace std;

template<typename T>
void print(circular_buffer<T> c) {
    for (auto& i : c) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    circular_buffer<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);
    c.push_back(5);
    c.push_back(6);
    c.clear();
    print(c);
}
