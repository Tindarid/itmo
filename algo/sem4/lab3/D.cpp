#include <iostream>
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

int main() {
    LL a, b, n, m;
    cin >> a >> b >> n >> m;
    LL m1 = m, m2 = n;
    LL obrm1 = obr(m1, n), obrm2 = obr(m2, m);
    LL M = n * m;
    LL x = (m1 * obrm1 * a + M) % M + (m2 * obrm2 * b + M) % M;
    cout << x % M << endl;
}
