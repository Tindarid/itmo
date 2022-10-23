#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#define MAXN 605
#define LL int
using namespace std;

const LL INF = 1e9;
int n, m;
int s, t, t1;
LL ans;
int N;

struct edge {
    int v, u;
    LL w, c, f;
};

vector<int> g[MAXN];
vector<edge> e;
int p[MAXN];
LL d[MAXN], pot[MAXN];
bool used[MAXN];

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
        used[i] = false;
    }
    d[s] = 0;
	for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        if (d[v] == INF) {
            break;
        }
        used[v] = true;
		for (int j = 0; j < g[v].size(); ++j) {
            edge& ed = e[g[v][j]];
            if (ed.w > ed.f) {
                LL temp = d[v] + ed.c + pot[v] - pot[ed.u];
                if (temp < d[ed.u]) {
                    d[ed.u] = temp;
                    p[ed.u] = g[v][j];
                }
            }
		}
	}
    return d[t] != INF;
}

LL min_flow() {
    LL res = 0;
    while (dijkstra()) {
        for (int i = 0; i < n; ++i) {
            pot[i] += d[i];
        }
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
    ifstream cin("assignment.in");
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            LL c;
            cin >> c;
            add_edge(i, N + j, 1, c);
        }
    }
    s = 0;
    n = 2 * N + 2;
    t = n - 1;
    for (int i = 1; i <= N; ++i) {
        add_edge(s, i, 1, 0);
    }
    for (int i = 1; i <= N; ++i) {
        add_edge(i + N, t, 1, 0);
    }
}

void sol() {
    ans = min_flow();
}

void out() {
    ofstream cout("assignment.out");
    cout << ans << endl;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            edge& ed = e[g[i][j]];
            if (ed.f == 1) {
                cout << ed.v << " " << ed.u - N << endl;
                break;
            }
        }
    }
}

int main() {
    in();
    sol();
    out();
}
