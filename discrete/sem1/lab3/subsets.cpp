#include <iostream>
#include <fstream>
using namespace std;

int n;
int ans[20];
bool used[20];

void dfs(int ind, int last) {
    for (int i = 0; i < ind; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    for (int i = last; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            ans[ind] = i;
            dfs(ind + 1, i);
            used[i] = false;
        }
    }
}

int main() {
    freopen("subsets.in", "r", stdin);
    freopen("subsets.out", "w", stdout);
    cin >> n;
    dfs(0, 1);
    return 0;
}

