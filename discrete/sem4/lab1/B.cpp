#include <iostream>
#include <fstream>
#define MAXN 105
#define LL long long
using namespace std;

int n, m;
LL s[MAXN][MAXN], ans[3][MAXN];
const LL MOD = 998244353LL;

LL b_pow(LL a, LL st) {
    a %= MOD;
	LL res = 1LL;
	while (st) {
		if (st & 1LL) {
			res = (a * res) % MOD;
        }
		a = (a * a) % MOD;
		st >>= 1;
	}
	return res;
}

LL find_reverse(LL b) {
    return b_pow(b, MOD - 2LL);
}

void count_s() {
    for (int i = 2; i <= m; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            for (int k = 0; k <= j; ++k) {
                s[i][j] = (s[i][j] + (s[i - 1][k] * s[1][j - k]) % MOD) % MOD;
            }
        }
    }
}

void in() {
    //ifstream cin("input.txt");
    cin >> n >> m;
    for (int i = 0; i < n + 1; ++i) {
        cin >> s[1][i];
    }
}

void sol() {
    count_s();
    //sqrt
    ans[0][0] = 1;
    LL fact = 1, some = 1;
    for (int i = 1; i < m + 1; ++i) {
        fact = (((fact * i) % MOD) * 2) % MOD;
        some = (some * (1 - (i - 1) * 2 + MOD) % MOD) % MOD;
        LL temp = (some * find_reverse(fact)) % MOD;
        for (int j = 0; j < m + 1; ++j) {
            ans[0][j] = (ans[0][j] + (s[i][j] * temp) % MOD) % MOD;
        }
    }
    //e
    ans[1][0] = 1;
    fact = 1;
    for (int i = 1; i < m + 1; ++i) {
        fact = (fact * i) % MOD;
        LL temp = find_reverse(fact);
        for (int j = 0; j < m + 1; ++j) {
            ans[1][j] = (ans[1][j] + (s[i][j] * temp) % MOD) % MOD;
        }
    }
    //ln
    ans[2][0] = 0;
    for (int i = 1; i < m + 1; ++i) {
        LL temp = find_reverse(i);
        if (i % 2 == 0) {
            temp = (MOD - temp) % MOD;
        }
        for (int j = 0; j < m + 1; ++j) {
            ans[2][j] = (ans[2][j] + (s[i][j] * temp) % MOD) % MOD;
        }
    }
}

void out() {
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < m; ++i) {
            cout << ans[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    in();
    sol();
    out();
}
