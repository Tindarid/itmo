#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<vector<int>> v;
vector<int> ans;
int used[MAXN + 1];
bool flag;

void dfs(int t) {
    used[t] = 1;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (used[temp] == 0) {
            dfs(temp);
        } else if (used[temp] == 1) {
            flag = true;
        }
    }
    used[t] = 2;
    ans.push_back(t);
}

int main() {
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
    }

    for (int i = 1; i < v.size(); ++i) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());

    if (flag) {
        cout << "-1";
    } else {
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] << " ";
        }
    }
    cout << endl;
    return 0;
}
