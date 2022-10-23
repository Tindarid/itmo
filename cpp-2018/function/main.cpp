#include <iostream>
#include "function.h"
using std::cout;
using std::endl;
using my::function;

void q() {
    cout << "TEST 4 : PASSED" << endl;
}

int some(int a) {
    return a * 2;
}

struct functor {
    functor(){}
    functor(functor&&) {
        cout << "In move" << endl;
    }

    functor(const functor&) {
        cout << "In copy" << endl;
    }
    int operator()() const {
        return 1;
    }
};

int main()
{
    // 1
    function<std::string(int)> f1([] (int a) { return "TEST 1 : PASSED"; });
    cout << f1(1) << endl;

    // 2
    function<int(int)> f2(some);
    if (f2(2) == 4) {
        cout << "TEST 2 : PASSED" << endl;
    } else {
        cout << "TEST 2 : FAILED" << endl;
    }

    // 3
    function<int(int)> f3(f2);
    if (f3(5) == 10) {
        cout << "TEST 3 : PASSED" << endl;
    } else {
        cout << "TEST 3 : FAILED" << endl;
    }

    // 4
    function<void()> f4(q);
    f4();

    // 5
    functor p;
    function<int()> f5 = p;
    function<int()> f10 = std::move(p);
    if (f5() == 1) {
        cout << "TEST 5 : PASSED" << endl;
    } else {
        cout << "TEST 5 : FAILED" << endl;
    }

    // 6
    function<int(int)> f6(std::move(f3));
    if (f6(6) == 12) {
        cout << "TEST 6 : PASSED" << endl;
    } else {
        cout << "TEST 6 : FAILED" << endl;
    }
    // 7
    // Crashes after moving
    // f3(5);

    //8
    function<int(int,int,int,int,int)> f8;
    return 0;
}
