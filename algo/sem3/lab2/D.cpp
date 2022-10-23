#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n, m, s, k;
vector<vector<pair<int, int>>> g;
int d[105][10005];
const int INF = 2 * 1e9;

int main() {
    cin >> n >> m >> k >> s;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u, c;
        cin >> v >> u >> c;
        g[v - 1].push_back(make_pair(u - 1, c));
    }
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = INF;
        }
    }
    d[0][s - 1] = 0;
    for (int i = 0; i < k; ++i) {
        for (int v = 0; v < n; ++v) {
            for (int j = 0; j < g[v].size(); ++j) {
                int u = g[v][j].first, c = g[v][j].second;
                if (d[i][v] != INF) {
                    d[i + 1][u] = min(d[i + 1][u], d[i][v] + c);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (d[k][i] == INF) {
            cout << -1 << endl;
        } else {
            cout << d[k][i] << endl;
        }
    }
}
