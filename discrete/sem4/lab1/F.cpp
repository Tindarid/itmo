#include <iostream>
#define MAXN 1005
#define LL long long
using namespace std;

const LL MOD = 104857601LL;
LL n; int k;
LL a[2 * MAXN], c[MAXN], temp_c[MAXN];

void in() {
    cin >> k >> n;
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    c[0] = 1;
    for (int i = 0; i < k; ++i) {
        cin >> c[i + 1];
        c[i + 1] = (MOD - c[i + 1]) % MOD;
    }
}

void sol() {
    for (n = n - 1; n >= k; n /= 2) {
        for (int i = k; i < 2 * k; ++i) {
            a[i] = 0;
            for (int j = 1; j <= k; ++j) {
                a[i] = (a[i] + (MOD - (c[j] * a[i - j]) % MOD) % MOD) % MOD;
            }
        }
        for (int i = 0; i <= k; ++i) {
            temp_c[i] = 0;
            for (int j = 0; j <= 2 * i; ++j) {
                LL temp1 = 0, temp2 = 0;
                if (j <= k) {
                    temp1 = c[j];
                }
                int ind = 2 * i - j;
                if (ind <= k) {
                    if (ind % 2) {
                        temp2 = (MOD - c[ind]) % MOD;
                    } else {
                        temp2 = c[ind];
                    }
                }
                temp_c[i] = (temp_c[i] + (temp1 * temp2) % MOD) % MOD;
            }
        }
        for (int i = 0; i <= k; ++i) {
            c[i] = temp_c[i];
        }
		for (int i = 0, j = 0; i < 2 * k; i++) {
			if (i % 2 == n % 2) {
				a[j++] = a[i];
			}
		}
    }
}

void out() {
    cout << a[n] << endl;
}

int main() {
    in();
    sol();
    out();
}
