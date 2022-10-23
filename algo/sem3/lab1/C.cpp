#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define MAXN 20000
using namespace std;

vector<vector<int>> v;
vector<int> ans;
bool used[MAXN + 1];
int tin[MAXN + 1], ret[MAXN + 1];
int timer;

void addCutPoint(int v) {
    for (auto i = ans.begin(); i != ans.end(); ++i) {
        if (*i == v) {
            return;
        }
    }
    ans.push_back(v);
}

void dfs(int t, int p) {
    used[t] = true;
    int sons = 0;
    tin[t] = ret[t] = ++timer;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (temp == p) {
            continue;
        } else if (!used[temp]) {
            dfs(temp, t);
            ret[t] = min(ret[t], ret[temp]); 
            if (p != 0 && ret[temp] >= tin[t]) {
                addCutPoint(t);
            }
            sons++;
        } else {
            ret[t] = min(ret[t], tin[temp]);
        }
    }
    if (p == 0 && sons > 1) {
        addCutPoint(t);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[b].push_back(a);
        v[a].push_back(b);
    }
    for (int i = 1; i < v.size(); ++i) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i = ans.begin(); i != ans.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}
