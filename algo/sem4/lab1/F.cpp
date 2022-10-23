#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define MAXN 200
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

void dinic_clean() {
    e.clear();
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

double ti[MAXN][MAXN];

double sqr(int a) {
    return a * a;
}

double dist(pair<int, int> a, pair<int, int> b) {
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

double ans = 0;
double maxtime = 0;

void in() {
    //ifstream cin("input.txt");
    cin >> m;
    n = 2 * m + 2;
    t = n - 1;
    vector<pair<pair<int, int>, int>> temp1;
    vector<pair<int, int>> temp2;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        temp1.push_back({{a, b}, c});
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        temp2.push_back({a, b});
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            ti[i][j] = 1.0 * dist(temp1[i].first, temp2[j]) / temp1[i].second;
            maxtime = max(maxtime, ti[i][j]);
        }
    }
    ans = maxtime;
}

void add_edges(double mid) {
    for (int i = 0; i < m; ++i) {
        add_edge(s, i + 1, 1);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (ti[i][j] <= mid) {
                add_edge(i + 1, j + m + 1, 1);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        add_edge(i + m + 1, t, 1);
    }
}

void binary_search() {
    double l = 0;
    double r = maxtime;
    for (int step = 0; step < 1000; ++step) {
        double mid = (l + r) / 2.0;
        dinic_clean();
        add_edges(mid);
        if (dinic() == m) {
            r = mid;
            ans = mid;
        } else {
            l = mid;
        }
    }
}

void out() {
    binary_search();
    cout << fixed << setprecision(13);
    cout << ans << endl;
}

int main() {
    in();
    out();
}
