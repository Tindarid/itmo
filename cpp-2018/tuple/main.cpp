#include <iostream>
#include <string>
#include "tuple.h"
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::move;
using tuple_namespace::tuple;
using tuple_namespace::get;

int main() {
    // Commented lines do not compile
    /*
    cout << "Testing tuple: " << endl;

    cout << "1. One type" << endl;
    tuple<float> test1(12.4f);
    cout << get<float>(test1) << " == " << 12.4f << endl;
    cout << get<0>(test1) << " == " << 12.4f << endl;
    //cout << get<-1>(test1) << " == " << 12.4f << endl;
    //cout << get<double>(test1) << endl;

    cout << "2. Simple" << endl;
    tuple<int, double, string> test2(10, 12.3, "test");
    cout << get<int>(test2) << " == " << 10 << endl;
    cout << get<double>(test2) << " == " << 12.3 << endl;
    cout << get<string>(test2) << " == " << "test" << endl;
    //cout << get<float>(test2) << endl;

    cout << "3. Type get" << endl;
    tuple<int, double, int, string> test3(10, 12.3, 20, "nursan");
    cout << get<double>(test3) << " == " << 12.3 << endl;
    cout << get<string>(test3) << " == " << "nursan" << endl;
    //cout << get<int>(test3) << endl;

    cout << "4. Index get" << endl;
    tuple<int, double, int, string> test4(10, 12.3, 20, "nursan");
    cout << get<0>(test4) << " == " << 10 << endl;
    cout << get<1>(test4) << " == " << 12.3 << endl;
    cout << get<2>(test4) << " == " << 20 << endl;
    cout << get<3>(test4) << " == " << "nursan" << endl;
    //cout << get<4>(test4) << endl;
    //cout << get<-3>(test4) << endl;

    cout << "5. Copy constructor" << endl;
    tuple<int, double> test5_1(1, 2);
    tuple<int, double> test5_2 = test5_1;
    cout << get<int>(test5_1) << " == " << 1 << endl;
    cout << get<double>(test5_1) << " == " << 2 << endl;
    cout << get<int>(test5_2) << " == " << 1 << endl;
    cout << get<double>(test5_2) << " == " << 2 << endl;

    cout << "6. Move semantics" << endl;
    string s1 = "hello";
    string s2 = "world";
    cout << "In s1: " << s1 << endl;
    cout << "In s2: " << s2 << endl;
    tuple<string, string> test6(move(s1), move(s2));
    cout << "Moved to tuple" << endl;
    cout << "In tuple: " << get<0>(test6) << " " << get<1>(test6) << endl;
    cout << "In s1: " << s1 << endl;
    cout << "In s2: " << s2 << endl;
    */

    cout << "7. Unique ptr" << endl;
    int a = 1;
    tuple<int, std::unique_ptr<int>> b(a, std::make_unique<int>(42));

    /*
    cout << "8." << endl;
    tuple<int> c(42);
    tuple<int> c_copy(c);
    cout << get<int>(c_copy) << endl;
    */
    return 0;
}
