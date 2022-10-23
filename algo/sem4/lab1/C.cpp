#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 100005
using namespace std;

struct edge {
    int v, u, c, f;
};

const int INF = 1e9 + 5;
int n, m;
int s, t;
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

int ans = 0;
bool used[MAXN];

void in() {
    //ifstream cin("input.txt");
    cin >> n >> m >> s >> t;
    s--;
    t--;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            continue;
        }
        add_edge(a - 1, b - 1, 1);
    }
}

bool find_dfs(int v, vector<int>& vec) {
    if (v == t) {
        vec.push_back(t + 1);
        return true;
    }
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        if (g[v][i] == -1) {
            continue;
        }
        edge& ed = e[g[v][i]];
        if (ed.c == 0 || ed.f != 1) {
            continue;
        }
        int u = ed.u;
        if (!used[u] && find_dfs(u, vec)) {
            g[v][i] = -1;
            vec.push_back(v + 1);
            return true;
        }
    }
    return false;
}

void out() {
    if (ans < 2) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> temp1, temp2;
        find_dfs(s, temp1);
        for (int i = 0; i < n; ++i) {
            used[i] = false;
        }
        find_dfs(s, temp2);
        for (int i = temp1.size() - 1; i >= 0; --i) {
            cout << temp1[i] << " ";
        }
        cout << endl;
        for (int i = temp2.size() - 1; i >= 0; --i) {
            cout << temp2[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    in();
    ans = dinic();
    out();
}
