#include <iostream>
#include <string>
#define MAXN 1000005
using namespace std;

string s;
int z[MAXN];
int len;

void sol() {
    len = s.length();
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
    int ans = len;
    for (int i = 1; i < len; ++i) {
        if (z[i] + i == len && len % i == 0) {
            ans = i;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
