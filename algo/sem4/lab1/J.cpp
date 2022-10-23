#include <iostream>
#include <vector>
#include <fstream>
#define LL long long
#define MAXN 5005
using namespace std;
using pa = pair<pair<int, int>, pair<int, int>>;
using edge = pair<int, int>;

int n, w;
const LL INF = 1000000000000LL;
vector<pa> pas;
int g[MAXN][MAXN];

int dist(pa& a, pa& b) {
    int temp1, temp2;
    if (a.first.first > b.first.first) {
        temp1 = a.first.first - b.second.first;
    } else {
        temp1 = b.first.first - a.second.first;
    }
    if (a.first.second > b.first.second) {
        temp2 = a.first.second - b.second.second;
    } else {
        temp2 = b.first.second - a.second.second;
    }
    return max(0, max(temp1, temp2));
}

void add_edge(int v, int u, int c) {
    g[v][u] = c;
    g[u][v] = c;
}

void in() {
    //ifstream cin("input.txt");
    cin >> n >> w;
    for (int i = 0; i < n; ++i) {
        LL x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pas.push_back({{x1, y1}, {x2, y2}});
    }
    for (int i = 1; i <= n; ++i) {
        LL temp = min(pas[i - 1].first.second, pas[i - 1].second.second);
        add_edge(i, 0, temp);
    }
    for (int i = 1; i <= n; ++i) {
        LL temp = w - max(pas[i - 1].first.second, pas[i - 1].second.second);
        add_edge(i, n + 1, temp);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            LL temp = dist(pas[i - 1], pas[j - 1]);
            add_edge(i, j, temp);
        }
    }
    add_edge(0, n + 1, w);
    n += 2;
}

vector<LL> d, p;
bool used[MAXN];

void de() {
    int s = 0;
    d.resize(n, INF);
    p.resize(n);
	d[s] = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int u = 0; u < n; ++u) {
			if (!used[u] && (v == -1 || d[u] < d[v])) {
				v = u;
            }
        }
		if (d[v] == INF) {
			break;
        }
		used[v] = true;
		for (int u = 0; u < n; ++u) {
            LL len = g[v][u];
			if (d[v] + len < d[u]) {
				d[u] = d[v] + len;
				p[u] = v;
			}
		}
	}
}

void out() {
    cout << d[n - 1] << endl;
}

int main() {
    in();
    de();
    out();
}
