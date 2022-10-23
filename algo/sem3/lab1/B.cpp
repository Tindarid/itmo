#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define MAXN 20000
using namespace std;

vector<vector<pair<int, int>>> v;
vector<int> ans;
bool used[MAXN + 1];
int tin[MAXN + 1], ret[MAXN + 1];
int timer;

void dfs(int t, int p) {
    used[t] = true;
    tin[t] = ret[t] = timer++;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i].first;
        if (temp == p) {
            continue;
        } else if (!used[temp]) {
            dfs(temp, t);
            ret[t] = min(ret[t], ret[temp]); 
            if (ret[temp] > tin[t]) {
                ans.push_back(v[t][i].second);
            }
        } else {
            ret[t] = min(ret[t], tin[temp]);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(make_pair(b, i + 1));
        v[b].push_back(make_pair(a, i + 1));
    }
    for (int i = 1; i < v.size(); ++i) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
