#include <iostream>
#include <string>
#define MAXN 100005
#define P 31
using namespace std;

string s;
long long sum[MAXN];
long long mul[MAXN];

int main() {
    mul[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        mul[i] = mul[i - 1] * P;
    }
    cin >> s;
    sum[0] = (s[0] - 'a' + 1);
    for (int i = 1; i < s.length(); ++i) {
        sum[i] = sum[i - 1] + (s[i] - 'a' + 1) * mul[i];
    }
    int m;
    cin >> m;
    for (int i = 0, a, b, c, d; i < m; ++i) {
        cin >> a >> b >> c >> d;
        if (b - a != d - c) {
            cout << "No\n";
            continue;
        } else if (a == c && b == d) {
            cout << "Yes\n";
            continue;
        }
        long long h1 = sum[b - 1];
        long long h2 = sum[d - 1];
        if (a != 1) {
            h1 -= sum[a - 2];
        }
        if (c != 1) {
            h2 -= sum[c - 2];
        }
        if (a < c && h1 * mul[c - a] == h2 || c < a && h1 == h2 * mul[a - c]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
