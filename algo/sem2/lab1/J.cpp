#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#define SIZE 3000000
#define LL int
#define MAXLL 10000009
using namespace std;

struct Node {
    LL v;
    bool f;
    LL l, r;
    LL i;
    Node() {
        f = false;
    }
};

LL n, m, k;
Node t[SIZE];

void treeBuild() { 
    for (LL i = 0; i < n; i++) {
        if (i < k) {
            t[n - 1 + i].v = 0;
        } else {
            t[n - 1 + i].v = MAXLL;
        }
        t[n - 1 + i].l = i;
        t[n - 1 + i].r = i;
        t[n - 1 + i].i = n - 1 + i;
    }
    for (LL i = n - 2; i >= 0; i--) {
        t[i].v = min(t[2 * i + 1].v, t[2 * i + 2].v); 
        t[i].l = t[2 * i + 1].l;
        t[i].r = t[2 * i + 2].r;
        t[i].i = i;
    } 
}

void push(LL node) {  
    t[2 * node + 1].v = max(t[2 * node + 1].v, t[node].v);
    t[2 * node + 2].v = max(t[2 * node + 2].v, t[node].v);
    t[2 * node + 1].f = true;
    t[2 * node + 2].f = true;
    t[node].f = false;
}

void updateSet(LL node, LL a, LL b, LL v) {
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
    updateSet(2 * node + 1, a, b, v);
    updateSet(2 * node + 2, a, b, v);
    t[node].v = min(t[2 * node + 1].v, t[2 * node + 2].v);
    return;
}

/*
LL getAns(LL node, LL a, LL b) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        return t[node].v;
    }
    if (l > b || r < a) {
        return MAXLL;
    }
    if (t[node].f) {
        push(node);
    }
    return min(getAns(2 * node + 1, a, b), getAns(2 * node + 2, a, b)); 
}
*/

Node getAns(LL node, LL a, LL b) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        return t[node];
    }
    if (l > b || r < a) {
        Node temp;
        temp.v = MAXLL;
        return temp;
    }
    if (t[node].f) {
        push(node);
    }
    Node n1 = getAns(2 * node + 1, a, b);
    Node n2 = getAns(2 * node + 2, a, b); 
    if (n1.v < n2.v) {
        return n1;
    }
    return n2;
}


LL findInd(Node node, LL value) {
    if (node.l == node.r) {
        return node.l;
    }
    if (node.f) {
        push(node.i);
    }
    if (t[2 * node.i + 1].v == value) {
        return findInd(t[2 * node.i + 1], value);
    } else {
        return findInd(t[2 * node.i + 2], value);
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> k >> m;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    treeBuild();
    for (LL i = 0; i < m; i++) {
        string s;
        LL l, r, value;
        cin >> s >> l >> r;
        l--, r--;
        if (s == "defend") {
            cin >> value;
            updateSet(0, l, r, value);
        } else {
            Node ans = getAns(0, l, r);
            cout << ans.v << " " << findInd(ans, ans.v) + 1 << "\n";
        }
    }
    return 0;
}
