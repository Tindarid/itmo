#include <iostream>
#include <fstream>
using namespace std;
 
long long dp[200][200];
long long n, k;
int ans[200];
 
int main() {
    ifstream cin("part2num.in");
    ofstream cout("part2num.out");
    int ind = 0;
    while (cin >> ans[ind]) {
        n += ans[ind];
        ind++;
    }
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) {
            if (i == j) {
                dp[i][j] = 1;
                continue;
            }
            int temp = i - j;
            for (int j2 = j; j2 <= i; j2++)
                dp[i][j] += dp[temp][j2];

        }
    
    int maxn = 1, curn = n;
    for (int i = 0; i < ind; i++) {
        while (maxn != ans[i]) {
            for (int j = maxn; j <= n; j++)
                k += dp[curn - maxn][j];
            maxn++;
        }
        curn -= ans[i];
    }

    cout << k << endl;
    return 0;
}
