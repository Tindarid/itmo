#include <iostream>
#include <string>
#include <fstream>
#include <set>
using namespace std;

int main()
{
    freopen("chaincode.in", "r", stdin);
    freopen("chaincode.out", "w", stdout);
    int n;
    set <string> codes;
    cin >> n;
    string temp(n, '0');
    codes.insert(temp);
    while (true) 
    {
        cout << temp << endl;
        temp = temp.substr(1, n - 1) + '1';
        if (codes.find(temp) == codes.end()) {
            codes.insert(temp);
            continue;
        }
        temp[n - 1] = '0';
        if (codes.find(temp) == codes.end()) {
            codes.insert(temp);
            continue;
        }
        break;
    }
    return 0;
}
