#include <iostream>
#include <fstream>
using namespace std;

int n, k;
int ans[20][20];
bool used[20];
int amount[20];
int last[20];

void dfs(int curk, int allam) {
    if (curk == k - 1 && allam == n && amount[0]!=0) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < amount[i]; j++)
                cout << ans[i][j] << " "; 
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            if (i >= last[curk]) {
                ans[curk][amount[curk]] = i;
                amount[curk]++;
                int temp = last[curk];
                last[curk] = i;
                dfs(curk, allam + 1);
                last[curk] = temp;
                amount[curk]--;
            }
            if (i >= ans[curk][0]) {
                ans[curk + 1][amount[curk + 1]] = i;
                amount[curk + 1]++;
                last[curk + 1] = i;
                dfs(curk + 1, allam + 1);
                last[curk + 1] = 1;
                amount[curk + 1]--;
            }
            used[i] = false;
        }
    }
}

int main() {
    freopen("part2sets.in", "r", stdin);
    freopen("part2sets.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < 20; i++)
        last[i] = 1;
    dfs(0, 0);
    return 0;
}

