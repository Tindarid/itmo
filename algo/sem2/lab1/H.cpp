#include <fstream>
#include <utility>
#define SIZE 300000
#define LL long long
#define MINMIN (-2147483650)
using namespace std;

struct Node {
    LL v;
    bool f;
    LL l, r;
    Node() {
        f = false;
        v = MINMIN;
    }
};

LL n, m, k;
Node t[SIZE];
LL zl[SIZE], zr[SIZE], z[SIZE];

void treeBuild() { 
    for (LL i = 0; i < n; i++) {
        t[n - 1 + i].l = i;
        t[n - 1 + i].r = i;
    }
    for (LL i = n - 2; i >= 0; i--) {
        t[i].l = t[2 * i + 1].l;
        t[i].r = t[2 * i + 2].r;
    } 
}

void push(LL node) {  
    t[2 * node + 1].v = max(t[node].v, t[2 * node + 1].v);
    t[2 * node + 2].v = max(t[node].v, t[2 * node + 2].v);
    t[2 * node + 1].f = true;
    t[2 * node + 2].f = true;
    t[node].f = false;
}

void update(LL node, LL a, LL b, LL v) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        t[node].f = true;
        t[node].v = max(v, t[node].v);
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (t[node].f) {
        push(node);
    }
    update(2 * node + 1, a, b, v);
    update(2 * node + 2, a, b, v);
    t[node].v = min(t[2 * node + 1].v, t[2 * node + 2].v);
    return;
}

LL getAns(LL node, LL a, LL b) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        return t[node].v;
    }
    if (l > b || r < a) {
        return -MINMIN;
    }
    if (t[node].f != 0) {
        push(node);
    }
    LL ans = min(getAns(2 * node + 1, a, b), getAns(2 * node + 2, a, b)); 
    return ans;
}

void dfs(LL node) {
    if (t[node].l == t[node].r) {
        return;
    }
    if (t[node].f) {
        push(node);
    }
    dfs(2 * node + 1);
    dfs(2 * node + 2);
}

int main() {
    ifstream cin("rmq.in");
    ofstream cout("rmq.out");
    cin >> k >> m;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    treeBuild();
    for (LL i = 0; i < m; i++) {
        cin >> zl[i] >> zr[i] >> z[i];
        zl[i]--;
        zr[i]--;
        update(0, zl[i], zr[i], z[i]);
    }
    dfs(0);
    bool flag = true;
    for (LL i = 0; i < m; i++) {
        if (getAns(0, zl[i], zr[i]) != z[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "consistent\n";
        for (LL i = 0; i < k; i++) {
            LL temp = t[n - 1 + i].v;
            if (temp == MINMIN) {
                cout << (1 << 31) - 1 << " ";
            } else {
                cout << temp << " ";
            }
        }
    } else {
        cout << "inconsistent";
    }
    cout << "\n";
    return 0;
}
