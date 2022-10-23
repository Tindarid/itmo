#include <fstream>
#include <vector>
#include <set>
#define MAXN 1050
#define LL long long
using namespace std;

const LL INF = 9223372036854775807LL;
int n, m;
int s, t;
LL ans;

struct edge {
    int v, u;
    LL w, c, f;
};

vector<int> g[MAXN];
vector<edge> e;
int p[MAXN];
LL d[MAXN];

void add_edge(int v, int u, LL w, LL c) {
	g[v].push_back(e.size());
	e.push_back({v, u, w, c, 0});
	g[u].push_back(e.size());
	e.push_back({u, v, 0, -c, 0});
}

bool dijkstra() {
    for (int i = 0; i < n; ++i) {
        d[i] = INF;
        p[i] = -1;
    }
    d[s] = 0;
	set<pair<LL, int>> q;
	q.insert({d[s], s});
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (int j = 0; j < g[v].size(); ++j) {
            edge& ed = e[g[v][j]];
            if (ed.w > ed.f) {
                if (d[v] + ed.c < d[ed.u]) {
                    d[ed.u] = d[v] + ed.c;
                    p[ed.u] = g[v][j];
                    q.insert({d[ed.u], ed.u});
                }
            }
		}
	}
    return d[t] != INF;
}

LL min_flow() {
    LL res = 0;
    while (dijkstra()) {
        LL m = INF;
        int i = t;
        while (i != s) {
            edge& ed = e[p[i]];
            m = min(m, ed.w - ed.f);
            i = ed.v;
        }
        i = t;
        while (i != s) {
            int j = p[i];
            i = e[j].v;
            e[j].f     += m;
            e[j^1].f   -= m;
            res += m * e[j].c;
        }
    }
    return res;
}

void in() {
    ifstream cin("mincost.in");
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        LL w, c;
        cin >> v >> u >> w >> c;
        add_edge(v - 1, u - 1, w, c);
    }
    s = 0;
    t = n - 1;
}

void sol() {
    ans = min_flow();
}

void out() {
    ofstream cout("mincost.out");
    cout << ans << endl;
}

int main() {
    in();
    sol();
    out();
}
