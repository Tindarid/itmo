#include <iostream>
#include <fstream>
#include <vector>
#define LL long long
using namespace std;

LL n, k = 1;
vector<vector<LL>> d;
vector<LL> tIn, tOut;
LL timer;
vector<vector<LL>> up;
vector<LL> euler, lb, rb, t;
vector<LL> pr;

void dfs(LL v, LL p) {
    if (pr.size() == 0) pr.resize(n + 1);
    pr[v] = p;
    lb[v] = euler.size();
    euler.push_back(v);
    tIn[v] = ++timer;
    up[v].resize(k + 5);
    up[v][0] = p;
    for (LL i = 1; i <= k; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (LL i = 0; i < d[v].size(); ++i) {
        if (d[v][i] != p) {
            dfs(d[v][i], v);
        }
    }
    tOut[v] = ++timer;
    rb[v] = euler.size();
    euler.push_back(v);
}

bool upper(LL a, LL b) {
    return (tOut[a] >= tOut[b]) && (tIn[a] <= tIn[b]);
}

LL lca(LL a, LL b) {
    if (upper(a, b)) {
        return a;
    } else if (upper(b, a)) {
        return b;
    }
    for (LL i = k; i >= 0; --i) {
        if (!upper(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

LL f(LL v) {
    return (v & -v);
}

LL get(LL v) {
    v++;
    LL ans = 0;
    for (v; v > 0; v -= f(v)) {
        ans += t[v];
    }
    return ans;
}

void upd(LL v, LL x) {
    v++;
    for (v; v < t.size(); v += f(v)) {
        t[v] += x;
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n;
    d.resize(n + 5);
    tIn.resize(n + 5);
    tOut.resize(n + 5);
    up.resize(n + 5);
    lb.resize(2 * n + 5, 0);
    rb.resize(2 * n + 5, 0);
    t.resize(2 * n + 5, 0);

    while ((1 << k) <= n) {
        ++k;
    }
    for (LL i = 2; i <= n; ++i) {
        LL u, v;
        cin >> u >> v;
        d[u].push_back(v);
        d[v].push_back(u);
    }
    up[0].resize(k + 5);
    dfs(1, 1);
    LL m;
    cin >> m;
    for (LL i = 0; i < m; ++i) {
        char c;
        cin >> c;
        if (c == '+') {
            LL v, u, d;
            cin >> v >> u >> d;
            upd(lb[v], d);
            upd(lb[u], d);
            int l = lca(u, v);
            upd(lb[lca(u, v)], -d);
            if (l != 1) {
                upd(lb[pr[l]], -d);
            }
        } else {
            LL v;
            cin >> v;
            cout << get(rb[v]) - get(lb[v] - 1) << endl;
        }
    }
/*    for (int i = 0; i < t.size(); ++i) {
        cout << get(i) << " ";
    }
    cout << endl;
    */
    return 0;
}
