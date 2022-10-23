#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 505
using namespace std;

struct edge {
    int v, u, c, f;
};

const int INF = 1e9 + 5;
int n, n1, n2;
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
    cin >> n1 >> n2;
    n = n1 + n2 + 2;
    t = n - 1;
    for (int i = 1; i <= n1; ++i) {
        add_edge(0, i, 1);
    }
    for (int i = 1; i <= n1; ++i) {
        int a;
        while (true) {
            cin >> a;
            if (a == 0) {
                break;
            }
            add_edge(i, a + n1, 1);
        }
    }
    for (int i = 1; i <= n2; ++i) {
        add_edge(i + n1, t, 1);
    }
}

void out() {
    vector<pair<int, int>> ans;
    for (edge& ed : e) {
        if (ed.c != 0 && ed.f == 1) {
            if (ed.v != 0 && ed.u != t) {
                ans.push_back({ed.v, ed.u - n1});
            }
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}

int main() {
    in();
    dinic();
    out();
}
