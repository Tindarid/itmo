#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 50000
#define LL long long
using namespace std;
using edge = pair<pair<LL, LL>, pair<LL, LL>>;

LL n, m, s;
LL r[MAXN + 5];
LL p[MAXN + 5];
bool used[2 * MAXN + 5];
vector<edge> edges;
vector<LL> ans;

bool comp(edge a, edge b) {
    return a.second.first > b.second.first;
}

void dsu_init() {
    for (LL i = 0; i < n; ++i) {
        r[i] = 0;
        p[i] = i;
    }
}

LL dsu_find(int v) {
    if (v != p[v]) {
        p[v] = dsu_find(p[v]);
    }
    return p[v];
}

void dsu_unite(int v, int u) {
    v = dsu_find(v);
    u = dsu_find(u);
    if (u != v) {
        if (r[u] < r[v]) {
            swap(u, v);
        }
        p[v] = u;
        if (r[v] == r[u]) {
            r[u]++;
        }
    }
}

int main() {
    ifstream cin("destroy.in");
    ofstream cout("destroy.out");
    cin >> n >> m >> s;
    for (LL i = 0; i < m; ++i) {
        LL v, u, c;
        cin >> v >> u >> c;
        edges.push_back({{v - 1, u - 1}, {c, i}});
    }
    sort(edges.begin(), edges.end(), comp);
    dsu_init();
    for (LL i = 0; i < m; ++i) {
        LL v = edges[i].first.first;
        LL u = edges[i].first.second;
        if (dsu_find(v) != dsu_find(u)) {
            dsu_unite(v, u);
            used[i] = true;
        }
    }
    for (LL i = m - 1; i >= 0; --i) {
        if (!used[i]) {
            LL c = edges[i].second.first;
            LL ind = edges[i].second.second;
            if (c <= s) {
                s -= c;
                ans.push_back(ind + 1);
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (LL i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
