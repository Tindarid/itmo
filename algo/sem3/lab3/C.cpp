#include <iostream>
#include <string>
#define MAXN 1000005
using namespace std;

string s;
int z[MAXN];

void sol() {
    int len = s.length();
    for (int i = 1, l = 0, r = 0; i < len; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < len && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r + 1) {
            r = i + z[i] - 1;
            l = i;
        }
    }
}

int main() {
    cin >> s;
    sol();
    for (int i = 1; i < s.length(); ++i) {
        cout << " " << z[i];
    }
    cout << endl;
    return 0;
}
