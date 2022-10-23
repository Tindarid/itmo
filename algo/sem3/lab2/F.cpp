#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#define MAXN 100000
#define INF 1e15
#define LL long long
using namespace std;

LL d[3][MAXN + 1];
vector<vector<pair<int, LL>>> g;
int n, m;
int abc[3];

void de(int p) {
    for (int i = 0; i < n; ++i) {
        d[p][i] = INF;
    }
    set<pair<LL, int>> s;
    d[p][abc[p]] = 0;
    for (int i = 0; i < n; ++i) {
        s.insert(make_pair(d[p][i], i));
    }
    for (int i = 0; i < n; ++i) {
        auto it = s.begin();
        int cur = (*it).second;
        s.erase(it);
        for (int j = 0; j < g[cur].size(); ++j) {
            int v = cur, u = g[cur][j].first;
            LL c = g[cur][j].second;
            if (d[p][v] + c < d[p][u]) {
                s.erase(make_pair(d[p][u], u));
                d[p][u] = d[p][v] + c;
                s.insert(make_pair(d[p][u], u));
            }
        }
    }
}

int main() {
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        LL c;
        cin >> v >> u >> c;
        g[v - 1].push_back(make_pair(u - 1, c));
        g[u - 1].push_back(make_pair(v - 1, c));
    }
    cin >> abc[0] >> abc[1] >> abc[2];
    for (int i = 0; i < 3; ++i) {
        --abc[i];
        de(i);
    }

    set<LL> ans;
    ans.insert(d[0][abc[1]] + d[1][abc[2]]);
    ans.insert(d[0][abc[2]] + d[2][abc[1]]);
    ans.insert(d[1][abc[2]] + d[2][abc[0]]);
    ans.insert(d[1][abc[0]] + d[0][abc[2]]);
    ans.insert(d[2][abc[1]] + d[1][abc[0]]);
    ans.insert(d[2][abc[0]] + d[0][abc[1]]);

    LL anss = *(ans.begin());
    if (anss >= INF) {
        cout << -1 << endl;
    } else {
        cout << anss << endl;
    }
    return 0;
}
