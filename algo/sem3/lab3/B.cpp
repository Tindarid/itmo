#include <iostream>
#include <string>
#define MAXN 1000005
using namespace std;

string s;
int p[MAXN];

void sol() {
    for (int i = 1; i < s.length(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = p[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        p[i] = j;
    }
}

int main() {
    cin >> s;
    sol();
    for (int i = 0; i < s.length(); ++i) {
        cout << p[i] << " ";
    }
    cout << endl;
    return 0;
}
