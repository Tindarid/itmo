#include <iostream>
#include <fstream>
#include <string>
#define SIZE 2000000
#define LL long long
using namespace std;

LL n, t[SIZE];

void treeBuild() {
    for (LL i = n - 2; i >= 0; i--) {
        t[i] = t[2 * i + 1] + t[2 * i + 2]; 
    } 
}

LL sum(LL l, LL r) {
    LL res = 0;
    while (l <= r) {
        if (l % 2 == 0) {
            res += t[l];
        }
        l /= 2;
        if (r % 2 == 1) {
            res += t[r];
        }
        r = r/2 - 1;
    }
    return res;
}

void setElement(LL i, LL e) {
    t[i] = e;
    while (i != 0) {
        i = (i - 1) / 2;
        t[i] = t[2 * i + 1] + t[2 * i + 2]; 
    }
}

int main() {
    ifstream cin("rsq.in");
    ofstream cout("rsq.out");
    LL k;
    cin >> k;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    for (LL i = 0; i < k; i++) {
        cin >> t[n - 1 + i];
    }
    treeBuild();
    while (true) {
        string s;
        LL l, r;
        cin >> s;
        if (cin.eof()) {
            break;
        }
        cin >> l >> r;
        l--;
        if (s == "sum") {
            r--;
            cout << sum(l + n - 1, r + n - 1) << endl;
        } else {
            setElement(l + n - 1, r);
        }
    }
    return 0;
}
