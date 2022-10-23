#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX_TEMP 1000005
using namespace std;

int n, k = 1;
vector<vector<int>> d;
vector<vector<int>> r;
vector<int> tIn, tOut;
int timer;
vector<vector<int>> up;
vector<vector<int>> upMin;

void dfs(int v, int p, int m) {
    tIn[v] = ++timer;
    up[v].resize(k + 5);
    up[v][0] = p;
    upMin[v].resize(k + 5);
    upMin[v][0] = m;
    for (int i = 1; i <= k; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        upMin[v][i] = min(upMin[up[v][i - 1]][i - 1], upMin[v][i - 1]);
    }
    for (int i = 0; i < d[v].size(); ++i) {
        if (d[v][i] != p) {
            dfs(d[v][i], v, r[v][i]);
        }
    }
    tOut[v] = ++timer;
}

bool upper(int a, int b) {
    return (tOut[a] >= tOut[b]) && (tIn[a] <= tIn[b]);
}

int lca(int a, int b) {
    int ans, a1 = a, b1 = b;
    if (upper(a, b)) {
        ans = a;
    } else if (upper(b, a)) {
        ans = b;
    } else {
        for (int i = k; i >= 0; --i) {
            if (!upper(up[a][i], b)) {
                a = up[a][i];
            }
        }
        ans = up[a][0];
    }
    a = a1, b = b1;
    int min1 = MAX_TEMP, min2 = MAX_TEMP;
    for (int i = k; i >= 0; --i) {
        if (upper(ans, up[a][i])) {
            min1 = min(min1, upMin[a][i]);
            a = up[a][i];
        }
    }
    for (int i = k; i >= 0; --i) {
        if (upper(ans, up[b][i])) {
            min2 = min(min2, upMin[b][i]);
            b = up[b][i];
        }
    }
    return min(min1, min2);
}

int main() {
    ifstream cin("minonpath.in");
    ofstream cout("minonpath.out");
    cin >> n;
    d.resize(n + 5);
    r.resize(n + 5);
    tIn.resize(n + 5);
    tOut.resize(n + 5);
    up.resize(n + 5);
    upMin.resize(n + 5);

    while ((1 << k) <= n) {
        ++k;
    }
    for (int i = 2; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        d[x].push_back(i);
        r[x].push_back(y);
    }
    up[0].resize(k + 5);
    dfs(1, 1, MAX_TEMP);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}
