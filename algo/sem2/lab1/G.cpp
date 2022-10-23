#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n = (1 << 19);
int SHIFT = 200000;
int m = 0;

struct NodeX {
    int x;
    int type;
    int yU;
    int yD;
};

struct NodeY {
    int l, r;
    int v;
    int m;
    bool flag;
    NodeY() {
        m = 0;
        flag = false;
        v = 0;
    }
};

NodeY t[(1 << 20)];
vector<NodeX> coor(100005);

void treeBuild() { 
    for (int i = 0; i < n; i++) {
        t[n - 1 + i].l = i;
        t[n - 1 + i].r = i;
    }
    for (int i = n - 2; i >= 0; i--) {
        t[i].l = t[2 * i + 1].l;
        t[i].r = t[2 * i + 2].r;
    } 
}

void push(int node) {
    t[2 * node + 1].m += t[node].m;
    t[2 * node + 2].m += t[node].m;
    t[node].v += t[node].m;
    t[node].flag = false;
    t[2 * node + 1].flag = t[2 * node + 2].flag = true;;
    t[node].m = 0;
}

void updateAdd(int node, int a, int b, int v) {
    int l = t[node].l;
    int r = t[node].r;
    if (l >= a && r <= b) {
        t[node].flag = true;
        t[node].m += v;
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (t[node].flag) {
        push(node);
    }
    updateAdd(2 * node + 1, a, b, v);
    updateAdd(2 * node + 2, a, b, v);
    t[node].v = max(t[2 * node + 1].v + t[2 * node + 1].m, t[2 * node + 2].v + t[2 * node + 2].m);
    return;
}

bool compFunc(NodeX &a, NodeX &b) {
    if (a.x == b.x) {
        if (a.type == 1) {
            return true;
        } else {
            return false;
        }
    } else if (a.x < b.x) {
        return true;
    } else {
        return false;
    }
}

int findAns(int node) {
    if (t[node].l == t[node].r) {
        return node;
    }
    if (t[node].flag) {
        push(node);
    }
    if (t[node].v == (t[2 * node + 1].v + t[2 * node + 1].m)) {
        return findAns(2 * node + 1);
    } else {
        return findAns(2 * node + 2);
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        coor[2 * i].type = 1;
        coor[2 * i].x = x1 + SHIFT;
        coor[2 * i + 1].type = -1;
        coor[2 * i + 1].x = x2 + SHIFT;
        coor[2 * i + 1].yU = coor[2 * i].yU = y1 + SHIFT;
        coor[2 * i + 1].yD = coor[2 * i].yD = y2 + SHIFT;
    }
    sort(coor.begin(), coor.begin() + 2 * m, compFunc);
    treeBuild();
    int ans = 0, ansX = 0 , ansY = 0;
    for (int i = 0; i < 2 * m; i++) {
        updateAdd(0, coor[i].yU, coor[i].yD, coor[i].type);
        if ((t[0].v + t[0].m) > ans) {
            int node = findAns(0);
            ansX = coor[i].x;
            ans = t[node].v + t[node].m;
            ansY = t[node].l;
        }
    }
    cout << ans << endl << ansX - SHIFT << " " << ansY - SHIFT << endl;
    return 0;
}
