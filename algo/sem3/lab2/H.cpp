#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define LL long long
#define MAXN 200000
using namespace std;

LL ans[MAXN + 1];
int n, m;
queue<int> q;
vector<vector<pair<int, int>>> g;
bool used[MAXN + 1];

void resolve(int v) {
    if (!used[v]) {
        q.push(v);
        used[v] = true;
    }
}

void bfs() {
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        used[x] = false;
        for (int i = 0; i < g[x].size(); ++i) {
            int y = g[x][i].first;
            int a = g[x][i].second;
            if (ans[x] + ans[y] < ans[a]) {
                ans[a] = ans[x] + ans[y];
                resolve(a);
            }
        }
    }
}

int main() {
    ifstream cin("dwarf.in");
    ofstream cout("dwarf.out");
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> ans[i];
    }
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, x, y;
        cin >> a >> x >> y;
        a--; x--; y--;
        g[x].push_back(make_pair(y, a));
        g[y].push_back(make_pair(x, a));
        resolve(x);
        resolve(y);
    }
    bfs();
    cout << ans[0] << endl;
    return 0;
}
