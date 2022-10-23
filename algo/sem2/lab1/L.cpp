#include <fstream>
#include <string>
#include <utility>
#define SIZE 2000000
#define LL int
using namespace std;

LL n, k, m, t[SIZE];

LL find(LL l, LL r) {
    LL res = n + 1;
    while (l <= r) {
        if (l % 2 == 0) {
            res = min(t[l], res);
        }
        l /= 2;
        if (r % 2 == 1) {
            res = min(t[r], res);
        }
        r = r/2 - 1;
    }
    return res;
}

void treeBuild() {
    for (int i = n - 1; i < n + k - 1; i++) {
        t[i] = i - n + 1;
    }
    for (int i = n + k - 1; i < 2 * n - 1; i++) {
        t[i] = n + 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        t[i] = min(t[2 * i + 1], t[2 * i + 2]);
    }
}

void setElement(LL i, LL e) {
    t[i] = e;
    while (i != 0) {
        i = (i - 1) / 2;
        t[i] = min(t[2 * i + 1], t[2 * i + 2]); 
    }
}

int main() {
    ifstream cin("parking.in");
    ofstream cout("parking.out");
    cin >> k >> m;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    treeBuild();
    for (int i = 0; i < m; i++) {
        string s;
        LL ind;
        cin >> s >> ind;
        ind--;
        if (s == "enter") {
            LL temp = find(n - 1 + ind, n - 1 + k - 1);
            if (temp == n + 1) {
                temp = find(n - 1, ind + n - 1);
            }
            cout << temp + 1 << endl;
            setElement(temp + n - 1, n + 1);
        } else {
            setElement(ind + n - 1, ind);
        }
    }
    return 0;
}
