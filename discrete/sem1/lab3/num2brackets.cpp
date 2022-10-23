#include <iostream>
#include <fstream>
using namespace std;

long long n, k;
char ans[50];
long long dp[50][50];

int main()
{
    freopen("num2brackets.in", "r", stdin);
    freopen("num2brackets.out", "w", stdout);
    cin >> n >> k;
    dp[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++) {
            dp[i][j] = dp[i - 1][j + 1];
            if (j != 0)
                dp[i][j] += dp[i - 1][j - 1]; 
        }
    for (int i = 0, g = 0, temp = 2 * n - 1; i < 2 * n; i++, temp--) {
        long long temp2 = dp[temp][g + 1];
        if (temp2 <= k) {
            k -= temp2;
            g--; 
            cout << ')';
        } else {
            g++;
            cout << '(';
        }
    }
    cout << endl;
    return 0;
}

