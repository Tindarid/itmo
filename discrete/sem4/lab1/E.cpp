#include <iostream>
#include <cmath>
#define MAXN 5005
#define LL long long
using namespace std;

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

LL binom[MAXN][MAXN];
LL A[MAXN], B[MAXN], ob[MAXN], ans[MAXN];

void prep() {
    binom[0][0] = 1;
    binom[1][1] = 1; 
    binom[1][0] = 1;
    for (int i = 2; i < MAXN; ++i) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % MOD;
        }
    }
}

int main() {
    int n, k;
    prep();
    cin >> k >> n;
    int a = ceil((k - 1) / 2.0);
    int b = ceil(k / 2.0);
    for (int i = 0; i < a; ++i) {
        A[i] = binom[k - i - 2][i];
        if (i % 2) { 
            A[i] = (MOD - A[i]) % MOD;
        }
    }
    for (int i = 0; i < b; ++i) {
        B[i] = binom[k - i - 1][i];
        if (i % 2) { 
            B[i] = (MOD - B[i]) % MOD;
        }
    }
    ob[0] = find_reverse(B[0]);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
            ob[i] = (ob[i] + (B[j] * ob[i - j]) % MOD) % MOD;
        }
        ob[i] = (ob[i] * ob[0]) % MOD;
        ob[i] = (MOD - ob[i]) % MOD; 
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            ans[i] = (ans[i] + (A[j] * ob[i - j]) % MOD) % MOD;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
}
