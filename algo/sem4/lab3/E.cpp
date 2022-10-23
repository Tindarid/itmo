#include <iostream>
#include <cmath>
#define LL long long
using namespace std;

LL gcd(LL a, LL b, LL& x, LL& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	LL x1, y1;
	LL d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

LL obr(LL a, LL MOD) {
    LL x, y;
    LL g = gcd(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

LL b_pow(LL a, LL st, LL MOD) {
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

int main() {
    LL n, e, C;
    cin >> n >> e >> C;
    LL p, q;
    for (int i = 2; i < sqrt(n); ++i) {
        if (n % i == 0) {
            p = i;
            q = n / i;
        }
    }
    LL phi = (p - 1) * (q - 1);
    LL d = obr(e, phi);
    LL M = b_pow(C, d, n);
    cout << M << endl;
}
