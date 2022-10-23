#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n, k = 1;
vector<vector<int>> d;
vector<int> tIn, tOut;
int timer;
vector<vector<int>> up;

void dfs(int v, int p) {
    tIn[v] = ++timer;
    up[v].resize(k + 5);
    up[v][0] = p;
    for (int i = 1; i <= k; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int i = 0; i < d[v].size(); ++i) {
        if (d[v][i] != p) {
            dfs(d[v][i], v);
        }
    }
    tOut[v] = ++timer;
}

bool upper(int a, int b) {
    return (tOut[a] >= tOut[b]) && (tIn[a] <= tIn[b]);
}

int lca(int a, int b) {
    if (upper(a, b)) {
        return a;
    } else if (upper(b, a)) {
        return b;
    }
    for (int i = k; i >= 0; --i) {
        if (!upper(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n;
    d.resize(n + 5);
    tIn.resize(n + 5);
    tOut.resize(n + 5);
    up.resize(n + 5);

    while ((1 << k) <= n) {
        ++k;
    }
    for (int i = 2; i <= n; ++i) {
        int x;
        cin >> x;
        d[x].push_back(i);
    }
    up[0].resize(k + 5);
    dfs(1, 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}
