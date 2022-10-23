#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define MAXN 20000
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
    cin >> m;
    int count = m * (m - 1) / 2;
    int some = 0;
    string str;
    getline(cin, str);
    for (int i = 0; i < m; ++i) {
        getline(cin, str);
        for (int j = i + 1; j < m; ++j) {
            some++;
            char c = str[j];
            if (c == '.') {
                add_edge(some, i + 1 + count, 3);
                add_edge(some, j + 1 + count, 3);
            } else if (c == 'l') {
                add_edge(some, i + 1 + count, 1);
                add_edge(some, j + 1 + count, 2);
            } else if (c == 'L') {
                add_edge(some, i + 1 + count, 0);
                add_edge(some, j + 1 + count, 3);
            } else if (c == 'W') {
                add_edge(some, i + 1 + count, 3);
                add_edge(some, j + 1 + count, 0);
            } else {
                add_edge(some, i + 1 + count, 2);
                add_edge(some, j + 1 + count, 1);
            }
        }
    }
    for (int i = 1; i <= count; ++i) {
        add_edge(s, i, 3);
    }
    t = count + 1 + m;
    for (int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        add_edge(i + 1 + count, t, a);
    }
    n = t + 1;
}

void out() {
    int count = m * (m - 1) / 2;
    char ans[105][105];
    int edgecount = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j) {
                ans[i][j] = '#';
            } else if (j > i) {
                int a = e[edgecount].f;
                edgecount += 2;
                int b = e[edgecount].f;
                edgecount += 2;
                if (a == 3) {
                    ans[i][j] = 'W';
                } else if (b == 3) {
                    ans[i][j] = 'L';
                } else if (a == 2) {
                    ans[i][j] = 'w';
                } else {
                    ans[i][j] = 'l';
                }
            } else {
                char so = ans[j][i];
                if (so == 'W') {
                    ans[i][j] = 'L';
                } else if (so == 'L') {
                    ans[i][j] = 'W';
                } else if (so == 'l') {
                    ans[i][j] = 'w';
                } else {
                    ans[i][j] = 'l';
                }
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
}

int main() {
    in();
    dinic();
    out();
}
