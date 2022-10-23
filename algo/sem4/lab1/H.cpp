#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAXN 1000000
using namespace std;

struct edge {
    int v, u, c, f;
};

const int INF = 1e9 + 5;
int n, m;
int s, t;
int N, M, K, S, T;
int d[MAXN], p[MAXN], q[MAXN];
vector<int> g[MAXN];
vector<edge> e;
vector<pair<int, int>> t_e;

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
    ifstream cin("bring.in");
    cin >> N >> M >> K >> S >> T;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        t_e.push_back({a, b});
    }
}

int ans;

void sol() {
    s = 0;
    int s1 = 1;
    int t1 = 2;
    t = 3;
    n = N + 4;
    add_edge(s, s1, K);
    add_edge(s1, S + 3, INF);
    add_edge(T + 3, t1, INF);
    add_edge(t1, t, K);
    while (true) {
        ans++;
        for (int i = 0; i < e.size(); ++i) {
            e[i].f = 0;
        }
        for (int i = 0; i < t_e.size(); ++i) {
            int v = t_e[i].first;
            int u = t_e[i].second;
            int a = v + n - 1 - N;
            int b = u + n - 1;
            add_edge(a, b, 1);
            a = u + n - 1 - N;
            b = v + n - 1;
            add_edge(a, b, 1);
        }
        add_edge(s1, S + n - 1, INF);
        add_edge(T + n - 1, t1, INF);
        n += N;
        if (dinic() == K) {
            break;
        }
    }
}

queue<int> temp2[100];

void out() {
    ofstream cout("bring.out");
    cout << ans << endl;
    for (int i = 0; i < K; ++i) {
        temp2[S].push(i + 1);
    }
    for (int i = 0; i < ans; ++i) {
        vector<pair<int, int>> temp;
        for (int j = 4 + N * i; j < 4 + N * (i + 1); ++j) {
            for (int ii = 0; ii < g[j].size(); ++ii) {
                edge& ed = e[g[j][ii]];
                if (ed.c != 0 && ed.f == 1 && ed.u != 2) {
                    int v = (j - 4) % N + 1;
                    int u = (ed.u - 4) % N + 1;
                    int some = temp2[v].front();
                    temp.push_back({some, u});
                    temp2[v].pop();
                    temp2[u].push(some);
                }
                if (ed.u == 2) {
                    int v = (j - 4) % N + 1;
                    temp2[v].pop();
                }
            }
        }
        cout << temp.size() << " ";
        for (int j = 0; j < temp.size(); ++j) {
            cout << temp[j].first << " " << temp[j].second << " ";
        }
        cout << endl;
    }
}

int main() {
    in();
    sol();
    out();
}
