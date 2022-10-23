#include <iostream>
#include <ctime>
#define LL long long
#define K 10
using namespace std;

LL mul(LL a, LL b, LL MOD) {
    if (!a || !b) {
        return 0;
    }
    if (a & 1LL) {
        return (b + mul(a - 1, b, MOD)) % MOD;
    }
    return (mul(a >> 1, b, MOD) * 2) % MOD;
}

LL b_pow(LL a, LL st, LL MOD) {
    a %= MOD;
	LL res = 1LL;
	while (st) {
		if (st & 1LL) {
            res = mul(a, res, MOD);
        }
        a = mul(a, a, MOD);
		st >>= 1;
	}
	return res % MOD;
}

bool pr(LL n) {
    if (n == 2 || n == 3 || n == 5 || n == 7) {
        return true;
    }
    if (n == 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
        return false;
    }
    int S = 0;
    LL t = n - 1;
    while (t % 2 == 0) {
        t /= 2;
        ++S;
    }
    for (int i = 0; i < K; ++i) {
        LL y = rand() % (n - 4) + 2;
        LL x = b_pow(y, t, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        for (int j = 0; j < S; ++j) {
            x = mul(x, x, n);
            if (x == 1) {
                return false;
            }
            if (x == n - 1) {
                break;
            }
        }
        if (x != n - 1) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        LL a;
        cin >> a;
        cout << (pr(a) ? "YES" : "NO") << endl;
    }
}
