#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 2000
using namespace std;

vector<vector<pair<int, long long>>> g;
bool used[MAXN + 1];
int n, m, s;
const long long INF = 1e18 * 3;

void dfs(int v) {
    used[v] = true;
    for (int j = 0; j < g[v].size(); ++j) {
        int u = g[v][j].first;
        if (!used[u]) {
            dfs(u);
        }
    }
}

int main() {
    cin >> n >> m >> s;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        long long c;
        cin >> v >> u >> c;
        g[v - 1].push_back(make_pair(u - 1, c));
    }
    vector<long long> r(n, INF);
    r[s - 1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int v = 0; v < g.size(); ++v) {
            for (int j = 0; j < g[v].size(); ++j) {
                int u = g[v][j].first;
                long long c = g[v][j].second;
                if (r[v] < INF && r[u] > r[v] + c) {
                    r[u] = r[v] + c;
                }
            }
        }
    }
    for (int v = 0; v < g.size(); ++v) {
        for (int j = 0; j < g[v].size(); ++j) {
            int u = g[v][j].first;
            long long c = g[v][j].second;
            if (r[v] < INF && r[u] > r[v] + c && !used[u]) {
                dfs(u);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (r[i] == INF) {
            cout << "*";
        } else if (used[i]) {
            cout << "-";
        } else {
            cout << r[i];
        }
        cout << endl;
    }
    return 0;
}
