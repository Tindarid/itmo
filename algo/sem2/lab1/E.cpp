#include <iostream>
#include <fstream>
#define LL long long
#define SIZE 7000000
using namespace std;

LL n, MOD, m;

struct Node {
    LL a, b, c, d, l, r;
    Node(LL a1, LL a2, LL a3, LL a4) {
        a = a1;
        b = a2;
        c = a3;
        d = a4;
    }
    Node() {

    }
};

Node t[SIZE];

Node multip(Node i1, Node i2) {
    LL r = MOD;
    Node a((i1.a * i2.a + i1.b * i2.c) % MOD, 
            (i1.a * i2.b + i1.b * i2.d) % MOD,
                    (i1.c * i2.a + i1.d * i2.c) % MOD,
                    (i1.c * i2.b + i1.d * i2.d) % MOD);
    return a;
}

void treeBuild() {
    for (int i = n - 2; i >= 0; i--) {
        t[i] = multip(t[2 * i + 1], t[2 * i + 2]); 
        t[i].l = t[2 * i + 1].l;
        t[i].r = t[2 * i + 2].r;
    } 
}

Node getAns(LL node, LL l, LL r) {
    Node resL(1, 0, 0, 1);
    Node resR(1, 0, 0, 1);
    while (l <= r) {
        if (l % 2 == 0) {
            resL = multip(resL, t[l]);
        }
        l /= 2;
        if (r % 2 == 1) {
            resR = multip(t[r], resR);
        }
        r = r / 2 - 1;
    }
    return multip(resL, resR);
}

int main() {
    ifstream cin("crypto.in");
    ofstream cout("crypto.out");
    LL k;
    cin >> MOD >> k >> m;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    for (int i = 0; i < k; i++) {
        if (i < n) {
            cin >> t[n - 1 + i].a >> t[n - 1 + i].b >> t[n - 1 + i].c >> t[n - 1 + i].d;
        } else {
            t[n - 1 + i].a = 1;
            t[n - 1 + i].b = 0;
            t[n - 1 + i].c = 0;
            t[n - 1 + i].d = 1;
        }
        t[n - 1 + i].l = i;
        t[n - 1 + i].r = i;
    }
    treeBuild();
    for (int i = 0; i < m; i++) {
        LL l, r;
        cin >> l >> r;
        Node res = getAns(0, l - 2 + n, r - 2 + n);
        cout << res.a << " " << res.b << "\n" << res.c << " " << res.d << "\n\n";
    }
    return 0;
}
