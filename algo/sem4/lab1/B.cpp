#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 105
using namespace std;

struct edge {
    int v, u, c, f;
};

const int INF = 1e9 + 5;
int n, m;
const int s = 0; int t;
int d[MAXN], p[MAXN], q[MAXN];
vector<int> g[MAXN];
vector<edge> e;

void add_edge(int a, int b, int c) {
	g[a].push_back(e.size());
	e.push_back({ a, b, c, 0 });
	g[b].push_back(e.size());
	e.push_back({ b, a, 0, 0 });
}
 
bool bfs() {
	int qh = 0, qt = 0;
	q[qt++] = s;
    for (int i = 0 ; i < n; ++i) {
        d[i] = -1;
    }
	d[s] = 0;
	while (qh < qt && d[t] == -1) {
		int v = q[qh++];
		for (int i = 0; i < g[v].size(); ++i) {
			int id = g[v][i], u = e[id].u;
			if (d[u] == -1 && e[id].f < e[id].c) {
				q[qt++] = u;
				d[u] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}
 
int dfs(int v, int flow) {
	if (flow == 0) {
        return 0;
    }
	if (v == t) {
        return flow;
    }
	for (; p[v] < g[v].size(); ++p[v]) {
		int id = g[v][p[v]], u = e[id].u;
		if (d[u] != d[v] + 1) {
            continue;
        }
		int pushed = dfs(u, min(flow, e[id].c - e[id].f));
		if (pushed) {
			e[id].f   += pushed;
			e[id^1].f -= pushed;
			return pushed;
		}
	}
	return 0;
}
 
int dinic() {
	int flow = 0;
	while (bfs()) {
        for (int i = 0; i < n; ++i) {
            p[i] = 0;
        }
		while (true) {
            int pushed = dfs(s, INF);
            if (pushed == 0) {
                break;
            }
			flow += pushed;
        }
	}
	return flow;
}

void in() {
    //ifstream cin("input.txt");
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a - 1, b - 1, c);
        add_edge(b - 1, a - 1, c);
    }
    t = n - 1;
}

int ans = 0;
bool good[MAXN];

void find_dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        edge& ed = e[g[v][i]];
        if (ed.c != 0) {
            if (!good[ed.u] && good[v] && ed.f < ed.c) {
                good[ed.u] = true;
                find_dfs(ed.u);
            }
        }
    }
}

void out() {
    good[s] = true;
    find_dfs(s);
    vector<int> result;
    for (int i = 0; i < e.size(); i += 4) {
        edge& ed = e[i];
        if (good[ed.v] != good[ed.u]) {
            result.push_back(i / 4 + 1);
        }
    }
    cout << result.size() << " " << ans << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    in();
    ans = dinic();
    out();
}
