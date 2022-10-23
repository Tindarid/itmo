#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<pair<int, pair<int, int>>> edges;
int par[MAXN + 1], r[MAXN + 1];

int findSet(int v) {
    if (v != par[v]) {
        par[v] = findSet(par[v]);
    }
    return par[v];
}

void unite(int v, int u) {
	v = findSet(v);
	u = findSet(u);
	if (v != u) {
		if (r[v] < r[u]) {
			swap(v, u);
        }
		par[u] = v;
		if (r[v] == r[u]) {
			r[v]++;
        }
    }
}

bool inOneSet(int v, int u) {
    return findSet(v) == findSet(u);
}

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back(make_pair(c, make_pair(a, b)));
    }
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= N; ++i) {
        par[i] = i;
        r[i] = 0;
    }
    long long ans = 0;
    for (int i = 0; i < M; ++i) {
        int v = edges[i].second.first;
        int u = edges[i].second.second;
        int c = edges[i].first;
        if (!inOneSet(v, u)) {
            ans += c;
            unite(v, u);
        }
    }
    cout << ans << endl;
}
