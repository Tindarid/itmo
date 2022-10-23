#include <fstream>
#define SIZE (1 << 21)
#define SHIFT 500000
#define LL int
using namespace std;

struct Node {
    LL v;
    LL f;
    LL l, r;
    LL c;
    Node() {
        f = 0;
        v = 0;
        c = 0;
    }
};

LL n = (1 << 20), m;
Node t[SIZE];

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
    if (t[node].f == 1) {
        t[2 * node + 1].v = 0;
        t[2 * node + 2].v = 0;
        t[2 * node + 1].c = 0;
        t[2 * node + 2].c = 0;
    } else {
        t[2 * node + 1].v = t[2 * node + 1].r - t[2 * node + 1].l + 1;
        t[2 * node + 2].v = t[2 * node + 2].r - t[2 * node + 2].l + 1;
        t[2 * node + 1].c = 1;
        t[2 * node + 2].c = 1;
    }
    t[2 * node + 1].f = t[node].f;
    t[2 * node + 2].f = t[node].f;
    t[node].f = 0;
}

LL findRight(LL node) {
    if (t[node].c == 0) {
        return -1000;
    }
    if (t[node].l == t[node].r) {
        return t[node].l;
    }
    if (t[node].f) {
        push(node);
    }
    if (t[2 * node + 2].c != 0) {
        return findRight(2 * node + 2);
    } else {
        return findRight(2 * node + 1);
    }
}

LL findLeft(LL node) {
    if (t[node].c == 0) {
        return -1000;
    }
    if (t[node].l == t[node].r) {
        return t[node].l;
    }
    if (t[node].f) {
        push(node);
    }
    if (t[2 * node + 1].c != 0) {
        return findLeft(2 * node + 1);
    } else {
        return findLeft(2 * node + 2);
    }
}

void updateSet(LL node, LL a, LL b, LL v) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        t[node].f = v;
        if (v == 1) {
            t[node].v = 0;
            t[node].c = 0;
        } else {
            t[node].v = t[node].r - t[node].l + 1;
            t[node].c = 1;
        }
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (t[node].f) {
        push(node);
    }
    updateSet(2 * node + 1, a, b, v);
    updateSet(2 * node + 2, a, b, v);
    t[node].v = t[2 * node + 1].v + t[2 * node + 2].v;
    t[node].c = t[2 * node + 1].c + t[2 * node + 2].c;
    if (findRight(2 * node + 1) + 1 == findLeft(2 * node + 2)) {
        --t[node].c;
    }
    return;
}


int main() {
    ifstream cin("painter.in");
    ofstream cout("painter.out");
    cin >> m;
    treeBuild();
    for (LL i = 0; i < m; i++) {
        char s;
        LL l, r;
        cin >> s >> l >> r;
        l += SHIFT + 1;
        r += l - 1;
        if (s == 'W') {
            updateSet(0, l, r, 1);
        } else {
            updateSet(0, l, r, 2);
        }
        cout << t[0].c << " " << t[0].v << "\n";
    }
    return 0;
}
