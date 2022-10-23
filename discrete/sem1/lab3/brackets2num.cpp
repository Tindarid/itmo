#include <iostream>
#include <fstream>
#include <string>
using namespace std;

long long n, ans;
string s;
long long dp[50][50];

int main()
{
    freopen("brackets2num.in", "r", stdin);
    freopen("brackets2num.out", "w", stdout);
    cin >> s;
    n = s.length() / 2;
    dp[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++) {
            dp[i][j] = dp[i - 1][j + 1];
            if (j != 0)
                dp[i][j] += dp[i - 1][j - 1]; 
        }
    for (int i = 0, g = 0, temp = 2 * n - 1; i < 2 * n; i++, temp--) {
        long long temp2 = dp[temp][g + 1];
        if (s[i] == ')') {
            ans += temp2;
            g--; 
        } else {
            g++;
        }
    }
    cout << ans << endl;
    return 0;
}

