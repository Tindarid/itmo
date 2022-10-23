#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 100000
using namespace std;

struct edge {
    int v, u, c, f, x, y;
};

const int INF = 1e9 + 5;
int n;
int N, M;
int s, t;
int d[MAXN], p[MAXN], q[MAXN];
vector<int> g[MAXN];
vector<edge> e;

void add_edge(int a, int b, int c, int x, int y) {
	g[a].push_back(e.size());
	e.push_back({ a, b, c, 0, x, y });
	g[b].push_back(e.size());
	e.push_back({ b, a, 0, 0, x, y });
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

char matrix2[105][105];
int matrix[105][105];

void in() {
    //ifstream cin("input.txt");
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char c;
            cin >> c;
            matrix2[i][j] = c;
            int temp = (i + j) % 2;
            if (temp == 0 && c == 'W' || temp == 1 && c == 'B') {
                matrix[i][j] = 1;
            }
        }
    }
}

void dinic_clean() {
    e.clear();
    for (int i = 0; i < MAXN; ++i) {
        g[i].clear();
    }
}

struct ans {
    int t, x, y;
};

vector<vector<int>> new_g;
vector<int> used;

void color_dfs(int v) {
    used[v] = 1;
    for (int j = 0; j < new_g[v].size(); ++j) {
        int u = new_g[v][j];
        if (used[u] == 2) {
            color_dfs(u);
        }
    }
}

vector<ans> sol_sol() {
    vector<ans> res;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (matrix[i][j] == 0) {
                int from = i - j + N + M + 1;
                int to = i + j + 2 * (N + M);
                add_edge(from, to, 1, i, j);
            }
        }
    }
    s = 0;
    t = 4 * (N + M);
    n = t + 1;
    for (int i = 1; i < 2 * (N + M); ++i) {
        add_edge(s, i, 1, -1, -1);
    }
    for (int i = 2 * (N + M); i < t; ++i) {
        add_edge(i, t, 1, -1, -1);
    }
    new_g.resize(n);
    used.resize(n);
    for (int i = 0; i < n; ++i) {
        used[i] = 0;
    }
    dinic();
    for (auto&& ed : e) {
        if (ed.c != 0 && ed.v != s && ed.u != t) {
            used[ed.v] = used[ed.u] = 2;
            if (ed.f > 0) {
                new_g[ed.u].push_back(ed.v);
            } else {
                new_g[ed.v].push_back(ed.u);
            }
        }
    }
    for (int i = 1; i < 2 * (N + M); ++i) {
        bool flag = false;
        for (int j = 0; j < g[s].size(); ++j) {
            edge& ed = e[g[s][j]];
            if (ed.u == i && ed.f == 0 && ed.c == 1) {
                flag = true;
            }
        }
        if (flag && used[i] == 2) {
            for (int j = 0; j < new_g[i].size(); ++j) {
                used[i] = 1;
                color_dfs(new_g[i][j]);
            }
        }
    }
    for (int i = 1; i < 2 * (N + M); ++i) {
        if (used[i] == 2) {
            for (int j = 0; j < g[i].size(); ++j) {
                edge& ed = e[g[i][j]];
                if (ed.v != s && ed.c != 0) {
                    int x = ed.x + 1;
                    int y = ed.y + 1;
                    res.push_back({2, x, y});
                    break;
                }
            }
        }
    }
    for (int i = 2 * (N + M); i < t; ++i) {
        if (used[i] == 1) {
            for (int j = 0; j < g[i].size(); ++j) {
                edge& ed = e[g[i][j]];
                if (ed.u != t && ed.c == 0) {
                    int x = ed.x + 1;
                    int y = ed.y + 1;
                    res.push_back({1, x, y});
                    break;
                }
            }
        }
    }
    new_g.clear();
    used.clear();
    return res;
}

vector<ans> anss;
int ty;

void sol() {
    anss = sol_sol();
    ty = 1;
    dinic_clean();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = 1 - matrix[i][j];
        }
    }
    vector<ans> temp = sol_sol();
    if (temp.size() < anss.size()) {
        anss = temp;
        ty = 0;
    }
}

void out() {
    cout << anss.size() << endl;
    for (auto&& some : anss) {
        cout << some.t << " ";
        cout << some.x << " ";
        cout << some.y << " ";
        if ((some.x + some.y) % 2 == ty) {
            cout << "B\n";
        } else {
            cout << "W\n";
        }
    }
}

int main() {
    in();
    sol();
    out();
}
