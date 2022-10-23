#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 100000
#define MOD 1000000007
using namespace std;

int n, M, k, l;
vector<vector<int>> d;
vector<vector<int>> m;
int anss[SIZE + 5];
int visited[SIZE + 5];
bool isGood[SIZE + 5];
vector<int> g;
vector<int> ans;
bool vis[SIZE + 5];

void colo(int v) {
    isGood[v] = true;
    for (int i = 0; i < d[v].size(); ++i) {
        if (!isGood[d[v][i]]) {
            colo(d[v][i]);
        }
    }
    return;
}

bool isCycle(int v) {
    visited[v] = 2;
    bool res = true;
    for (int i = 0; i < m[v].size(); ++i) {
        if (visited[m[v][i]] == 2 && isGood[m[v][i]]) {
            res = false;
        }
        if (visited[m[v][i]] == 0) {
            res = res & isCycle(m[v][i]);
        }
    }
    visited[v] = 1;
    return res;
}

void dfs(int v) {
    vis[v] = true;
    for (int i = 0; i < m[v].size(); ++i) {
        if (!vis[m[v][i]]) {
            dfs(m[v][i]);
        }
    }
    ans.push_back(v);
}

void topo() {
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}

void findAns() {
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < m[ans[i]].size(); ++j) {
            anss[m[ans[i]][j]] = (anss[ans[i]] + anss[m[ans[i]][j]]) % MOD;
        }
    }
}

int main() {
    ifstream cin("problem3.in");
    ofstream cout("problem3.out");
    cin >> n >> M >> k;
    d.resize(n + 5);
    m.resize(n + 5);
    g.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> g[i];
    }
    for (int i = 0; i < M; ++i) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        d[b].push_back(a);
        m[a].push_back(b);
    }

    for (int i = 0; i < k; ++i) {
        colo(g[i]);
    }
    if (!isGood[1]) {
        cout << 0 << endl;
        return 0;
    }
    if (!isCycle(1)) {
        cout << -1 << endl;
        return 0;
    }
    anss[1] = 1;
    topo();
    findAns();
    int ansss = 0;
    for (int i = 0; i < g.size(); ++i) {
        ansss = (ansss + anss[g[i]]) % MOD;
    }
    cout << ansss << endl;
    return 0;
}
