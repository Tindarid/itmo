#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;

int main() {
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u, c;
        cin >> v >> u >> c;
        g[v - 1].push_back(make_pair(u - 1, c));
        g[u - 1].push_back(make_pair(v - 1, c));
    }
    vector<int> ans(n, 1e9);
    set<pair<int, int>> s;
    ans[0] = 0;
    for (int i = 0; i < n; ++i) {
        s.insert(make_pair(ans[i], i));
    }
    for (int i = 0; i < n; ++i) {
        auto it = s.begin();
        int cur = (*it).second;
        s.erase(it);
        for (int j = 0; j < g[cur].size(); ++j) {
            int v = cur, u = g[cur][j].first, c = g[cur][j].second;
            if (ans[v] + c < ans[u]) {
                s.erase(make_pair(ans[u], u));
                ans[u] = ans[v] + c;
                s.insert(make_pair(ans[u], u));
            }
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
