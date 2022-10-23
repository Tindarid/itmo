#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
vector<int> ans;
long long dp[200][200];
long long n, k;
 
int main() {
    ifstream cin("num2part.in");
    ofstream cout("num2part.out");
    cin >> n >> k;
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
    long long cur = 0;
    int curn = n;
    for (int i = 1; i <= n; i++) {
        long long temp = 0;
        for (int j = i; j <= curn; j++)
            temp += dp[curn - i][j];
        if (cur + temp > k) {
            ans.push_back(i);
            curn -= i;
            i--;
        } else {
            cur += temp;
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if (i == ans.size() - 1)
            cout << endl;
        else
            cout << "+";
    }
    return 0;
}
