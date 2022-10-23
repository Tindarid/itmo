#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#define MAXN 20000
using namespace std;

vector<vector<int>> v;
map<pair<int, int>, int> cr;
bool used[MAXN + 1];
int tin[MAXN + 1], ret[MAXN + 1];
int timer;
int ans[MAXN + 1];
int curComp;

bool is_cr(int v, int u) {
    auto it = cr.find(make_pair(v, u));
    if (it->second == 1) {
        return false;
    }
    return true;
}

void dfs(int t, int comp) {
    ans[t] = comp;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (ans[temp] == 0) {
            if (ret[temp] > tin[t] && !is_cr(t, temp)) {
                curComp++;
                dfs(temp, curComp);
            } else {
                dfs(temp, comp);
            }
        }
    }
}

void dfs_for_bridges(int t, int p) {
    used[t] = true;
    tin[t] = ret[t] = timer++;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (temp == p) {
            continue;
        } else if (!used[temp]) {
            dfs_for_bridges(temp, t);
            ret[t] = min(ret[t], ret[temp]); 
        } else {
            ret[t] = min(ret[t], tin[temp]);
        }
    }
}

void check(int v, int u) {
    auto it = cr.find(make_pair(v, u));
    if (it == cr.end()) {
        cr.insert(make_pair(make_pair(v, u), 1)); 
    } else {
        cr.erase(it);
        cr.insert(make_pair(make_pair(v, u), 10)); 
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
        check(a, b);
        check(b, a);
    }
    for (int i = 1; i < v.size(); ++i) {
        if (!used[i]) {
            dfs_for_bridges(i, 0);
        }
    }
    for (int i = 1; i < v.size(); ++i) {
        if (ans[i] == 0) {
            curComp++;
            dfs(i, curComp);
        }
    }
    cout << curComp << endl;
    for (int i = 1; i < v.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
