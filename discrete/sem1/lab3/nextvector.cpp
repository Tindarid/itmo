#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream cin("nextvector.in");
    ofstream cout("nextvector.out");
    string s;
    cin >> s;
    int n = s.length(), k, p;
    for (k = n - 1; k >= 0; k--)
        if (s[k] == '0')
            break;
    for (p = n - 1; p >= 0; p--)
        if (s[p] == '1')
            break;

    if (p == -1)
        cout << "-" << endl;
    else {
        for (int i = 0; i < p; i++)
            cout << s[i];
        cout << 0;
        for (int i = p + 1; i < n; i++)
            cout << 1;
        cout << endl;
    }

    if (k == -1)
        cout << "-" << endl;
    else {
        for (int i = 0; i < k; i++)
            cout << s[i];
        cout << 1;
        for (int i = k + 1; i < n; i++)
            cout << 0;
        cout << endl;
    }
    return 0;
}
