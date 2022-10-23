#include <iostream>
#include <string>
using namespace std;

string s;
long long n;
int dp[105][105];

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int getAns(int l, int r) {
    if (l >= r)
        return 0;
    if (dp[l][r] != -1)
        return dp[l][r];
    int ans = 0;
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') || (s[l] == '{' && s[r] == '}'))
        ans = getAns(l + 1, r - 1) + 2; 
    for (int i = l; i < r; i++)
        ans = max(ans, getAns(l, i) + getAns(i + 1, r));
    dp[l][r] = ans;
    return ans;
}

int main() {
    cin >> s;
    n = s.length();
    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 105; j++)
            dp[i][j] = -1;
    cout << getAns(0, n - 1) << endl; 
    return 0;
}

