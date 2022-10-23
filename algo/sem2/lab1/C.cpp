#include <iostream>
#include <fstream>
#include <string>
#define SIZE 2000000
#define LL long long
#define MAXLL 1000000000000000001LL
using namespace std;

struct Node {
    LL v;
    int flag;
    LL l, r;
    LL x;
    Node() {
        flag = 0;
        x = 0;
    }
};

LL n;
Node t[SIZE];

LL min(LL a, LL b) {
    if (a < b) {
        return a;
    }
    return b;
}

void treeBuild() { 
    for (LL i = n - 2; i >= 0; i--) {
        t[i].v = min(t[2 * i + 1].v, t[2 * i + 2].v); 
        t[i].flag = 0;
        t[i].l = t[2 * i + 1].l;
        t[i].r = t[2 * i + 2].r;
    } 
}

void push(LL node) {  
    int f = t[node].flag;
    if (f == 1) {
        t[2 * node + 1].v = t[node].v;
        t[2 * node + 2].v = t[node].v;
        t[2 * node + 1].x = 0;
        t[2 * node + 2].x = 0;
        t[2 * node + 1].flag = 1;
        t[2 * node + 2].flag = 1;
    } else {
        t[2 * node + 1].v += t[node].x;
        t[2 * node + 2].v += t[node].x;
        if (t[2 * node + 1].flag == 1) {

        } else if (t[2 * node + 1].flag == 2) {
            t[2 * node + 1].x += t[node].x;
        } else {
            t[2 * node + 1].flag = 2;
            t[2 * node + 1].x = t[node].x;
        }
        if (t[2 * node + 2].flag == 1) {

        } else if (t[2 * node + 2].flag == 2) {
            t[2 * node + 2].x += t[node].x;
        } else {
            t[2 * node + 2].flag = 2;
            t[2 * node + 2].x = t[node].x;
        }
    }
    t[node].flag = 0;
    t[node].x = 0;
}

void updateSet(LL node, LL a, LL b, LL v) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        t[node].flag = 1;
        t[node].v = v;
        t[node].x = 0;
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (t[node].flag != 0) {
        push(node);
    }
    updateSet(2 * node + 1, a, b, v);
    updateSet(2 * node + 2, a, b, v);
    t[node].v = min(t[2 * node + 1].v, t[2 * node + 2].v);
    return;
}

void updateAdd(LL node, LL a, LL b, LL v) {
    LL l = t[node].l;
    LL r = t[node].r;
    if (l >= a && r <= b) {
        if (t[node].flag == 2) {
            t[node].x += v;
            t[node].v += v;
        } else  if (t[node].flag == 1) {
            t[node].v += v;
        } else {
            t[node].x = v;
            t[node].v += v;
            t[node].flag = 2;
        }
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (t[node].flag != 0) {
        push(node);
    }
    updateAdd(2 * node + 1, a, b, v);
    updateAdd(2 * node + 2, a, b, v);
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
        return MAXLL;
    }
    if (t[node].flag != 0) {
        push(node);
    }
    LL ans = min(getAns(2 * node + 1, a, b), getAns(2 * node + 2, a, b)); 
    return ans;
}

int main() {
    ifstream cin("rmq2.in");
    ofstream cout("rmq2.out");
    LL k;
    cin >> k;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    for (LL i = 0; i < n; i++) {
        if (i < k) {
            cin >> t[n - 1 + i].v;
        } else {
            t[n - 1 + i].v = MAXLL;
        }
        t[n - 1 + i].l = i;
        t[n - 1 + i].r = i;
    }
    treeBuild();
    while (true) {
        string s;
        LL l, r, value;
        cin >> s;
        if (cin.eof()) {
            break;
        }
        cin >> l >> r;
        l--, r--;
        if (s == "set") {
            cin >> value;
            updateSet(0, l, r, value);
        } else if (s == "add") {
            cin >> value;
            updateAdd(0, l, r, value);
        } else {
            cout << getAns(0, l, r) << "\n";
        }
    }
    return 0;
}
