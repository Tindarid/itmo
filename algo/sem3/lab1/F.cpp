#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 10000
using namespace std;

vector<vector<int>> v, vt;
bool used[MAXN + 1];
int color[MAXN + 1];
vector<int> ans;
int curcolor;

void dfs1(int t) {
    used[t] = true;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (!used[temp]) {
            dfs1(temp);
        }
    }
    ans.push_back(t);
}

void dfs2(int t) {
    used[t] = true;
    color[t] = curcolor;
    for (int i = 0; i < vt[t].size(); ++i) {
        int temp = vt[t][i];
        if (!used[temp]) {
            dfs2(temp);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    vt.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        vt[b].push_back(a);
    }
    for (int i = 1; i < v.size(); ++i) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 1; i <= N; ++i) {
        used[i] = false;
    }
    for (int i = 0; i < ans.size(); ++i) {
        if (!used[ans[i]]) {
            curcolor++;
            dfs2(ans[i]);
        }
    }
    set<pair<int, int>> e;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            int from = i, to = v[i][j];
            if (color[from] != color[to]) {
                e.insert(make_pair(color[from], color[to]));
            }
        }
    }
    cout << e.size() << endl;
    return 0;
}
