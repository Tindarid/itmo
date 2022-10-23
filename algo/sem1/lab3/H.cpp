#include <iostream>
#include <fstream>
using namespace std;

bool matrix[105][105];
int n;
int dp[105];

int dfs(int v) {
    if (dp[v] != -1)
        return dp[v];
    int res1 = 0, res2 = 1;

    for (int i = 1; i <= n; i++) 
        if (matrix[v][i]) { 
            res1 += dfs(i);
            for (int j = 1; j <= n; j++)
                if (matrix[i][j])
                    res2 += dfs(j);
        }

    if (res1 > res2)
        dp[v] = res1;
    else
        dp[v] = res2;
    return dp[v];
}

int main() {
    cin >> n;
    int t;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        if (temp == 0)
            t = i;
        matrix[temp][i] = true;
    }
    for (int i = 0; i <= n; i++)
        dp[i] = -1;
    cout << dfs(t) << endl;
    return 0;
}
