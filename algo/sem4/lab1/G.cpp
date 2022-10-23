#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define MAXN 100000
using namespace std;

struct edge {
    int v, u, c, f, x, y;
};

const int INF = 1e6 + 5;
int n, m;
int s, t;
int d[MAXN], p[MAXN], q[MAXN];
vector<int> g[MAXN];
vector<edge> e;
string mat[60];

void add_edge(int a, int b, int c, int x, int y) {
	g[a].push_back(e.size());
	e.push_back({ a, b, c, 0, x, y });
	g[b].push_back(e.size());
	e.push_back({ b, a, 0, 0, x, y });
}
 
bool bfs() {
	int qh = 0, qt = 0;
	q[qt++] = s;
    for (int i = 0 ; i < 2 * n * m; ++i) {
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
        for (int i = 0; i < 2 * n * m; ++i) {
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

bool used[MAXN];

bool check(int v) {
    used[v] = true;
    if (v == t) {
        return true;
    }
    bool ans = false;
    for (int i = 0; i < g[v].size(); ++i) {
        edge& ed = e[g[v][i]];
        if (!used[ed.u] && ed.c >= 2) {
            ans = ans || check(ed.u);
        }
    }
    return ans;
}

void in() {
    //ifstream cin("input.txt");
    cin >> m >> n;
    string str;
    getline(cin, str);
    for (int i = 0; i < m; ++i) {
        getline(cin, mat[i]);
    }
}

bool good[MAXN];

void find_dfs(int v) {
    good[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        edge& ed = e[g[v][i]];
        if (!good[ed.u] && ed.f < ed.c) {
            find_dfs(ed.u);
        }
    }
}

void sol2() {
    find_dfs(s);
    for (int i = 0; i < e.size(); i++) {
        edge& ed = e[i];
        if (good[ed.v] != good[ed.u] && ed.x != -1 && ed.c != 0 && ed.f == 1) {
            mat[ed.x][ed.y] = '+';
        }
    }
}

void add_edge2(int v, int u, int i, int j) {
    int temp;
    if (j < n - 1 && mat[i][j + 1] != '#') {
        temp = v + 2;
        add_edge(u, temp, INF, -1, -1);
    }
    if (j > 0 && mat[i][j - 1] != '#') {
        temp = v - 2;
        add_edge(u, temp, INF, -1, -1);
    }
    if (i < m - 1 && mat[i + 1][j] != '#') {
        temp = v + 2 * n;
        add_edge(u, temp, INF, -1, -1);
    }
    if (i > 0 && mat[i - 1][j] != '#') {
        temp = v - 2 * n;
        add_edge(u, temp, INF, -1, -1);
    }
}

void sol() {
    int count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int v = count++;
            int u = count++;
            char c = mat[i][j];
            if (c == 'A') {
                add_edge(v, u, INF, -1, -1);
                s = v;
            } else if (c == 'B') {
                add_edge(v, u, INF, -1, -1);
                t = u;
            } else if (c == '.') {
                add_edge(v, u, 1, i, j);
            } else if (c == '#') {
                continue;
            } else {
                add_edge(v, u, INF, -1, -1);
            }
            add_edge2(v, u, i, j);
        }
    }
}

int main() {
    in();
    sol();
    if (check(s)) {
        cout << -1 << endl;
        return 0 ;
    }
    cout << dinic() << endl;
    sol2();
    for (int i = 0; i < m; ++i) {
        cout << mat[i] << endl;
    }
}
