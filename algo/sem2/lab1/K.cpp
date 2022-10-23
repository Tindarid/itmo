#include <fstream>
#define SIZE 100000
#define LL long long
using namespace std;

struct Node {
    LL h, s;

    Node() {
        s = 0;
        h = 0;
    }
};

LL m, n, k;
Node t[3 * SIZE];
LL sum[SIZE + 5], hsum[SIZE + 5];

LL hashFunc(LL a) {
    return a * a;
}

void treeBuild() {
    for (LL i = n - 2; i >= 0; i--) {
        t[i].s = t[2 * i + 1].s + t[2 * i + 2].s; 
        t[i].h = t[2 * i + 1].h + t[2 * i + 2].h; 
    } 
}

bool getAns(LL l, LL r) {
    LL l1 = l, r1 = r;
    LL s = 0, h = 0;
    while (l <= r) {
        if (l % 2 == 0) {
            s += t[l].s;
            h += t[l].h;
        }
        l /= 2;
        if (r % 2 == 1) {
            s += t[r].s;
            h += t[r].h;
        }
        r = r / 2 - 1;
    }
    if (/*sum[r1 - l1 + 1] == s && */h == hsum[r1 - l1 + 1]) {
        return true;
    }
    return false;
}

void setElement(LL i, LL e) {
    t[i].s = e;
    t[i].h = hashFunc(e);
    while (i != 0) {
        i = (i - 1) / 2;
        t[i].s = t[2 * i + 1].s + t[2 * i + 2].s; 
        t[i].h = t[2 * i + 1].h + t[2 * i + 2].h; 
    }
}

int main() {
    ifstream cin("permutation.in");
    ofstream cout("permutation.out");
    cin >> k;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    for (LL i = 0; i < k; i++) {
        cin >> t[n - 1 + i].s;
        t[n - 1 + i].h = hashFunc(t[n - 1 + i].s);
    }
    treeBuild();
    cin >> m;
    for (LL i = 1; i <= 100000; i++) {
        sum[i] = sum[i - 1] + i;
        hsum[i] = hsum[i - 1] + hashFunc(i);
    }
    LL Z, X, Y;
    for (LL i = 0; i < m; i++) {
        cin >> Z >> X >> Y;
        if (Z == 1) {
            setElement(X - 2 + n, Y);
        } else {
            if (getAns(X - 2 + n, Y - 2 + n)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
