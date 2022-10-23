#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;
using ver = pair<int, int>;

int n;
vector<vector<int>> g;
bool used[MAXN + 5];
vector<int> mt;
vector<int> ans;
vector<ver> f;
 
bool kun(int v) {
    if (!used[v]) {
        used[v] = true;
        for (int i = 0; i < g[v].size(); ++i) {
            int u = g[v][i];
            if (mt[u] == -1 || kun(mt[u])) {
                mt[u] = v;
                return true;
            }
        }
    }
	return false;
}

bool comp(ver& a, ver& b) {
    return a.second > b.second;
}

void refresh() {
    for (int i = 0; i < n; ++i) {
        used[i] = false;
    }
}

int main() {
    ifstream cin("matching.in");
    ofstream cout("matching.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        f.push_back(make_pair(i, w));
    }
    sort(f.begin(), f.end(), comp);
    mt.resize(n, -1);
    g.resize(n);
    for (int v = 0; v < n; ++v) {
        int amount;
        cin >> amount;
        for (int i = 0; i < amount; ++i) {
            int u;
            cin >> u;
            g[v].push_back(u - 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        int v = f[i].first;
        refresh();
        kun(v);
    }
    ans.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        if (mt[i] != -1 ) {
            ans[mt[i]] = i + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
