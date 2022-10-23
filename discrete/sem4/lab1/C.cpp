#include <iostream>
#include <fstream>
#define MAXN 2005
#define LL long long
using namespace std;

const LL MOD = 1e9 + 7;
LL ans[MAXN], c[MAXN], tem[MAXN];
int k, m;

void in() {
    //ifstream cin("input.txt");
    cin >> k >> m;
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
    }
}

void sol() {
    for (int i = 0; i < MAXN; ++i) {
        tem[i] = -1;
    }
    ans[0] = 1;
    for (int n = 1; n <= m; ++n) {
        for (int i = 0; i < k; ++i) {
            int cost = c[i];
            if (cost > n) {
                continue;
            }
            int ind = n - cost;
            if (tem[ind] == -1) {
                tem[ind] = 0;
                for (int j = 0; j <= ind; ++j) {
                    tem[ind] = (tem[ind] + (ans[j] * ans[ind - j]) % MOD) % MOD;
                }
            }
            ans[n] = (ans[n] + tem[ind]) % MOD;
        }
    }
}

void out() {
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    in();
    sol();
    out();
}
