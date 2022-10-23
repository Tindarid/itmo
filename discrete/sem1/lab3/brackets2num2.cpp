#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

long long n, ans;
string s;
long long dp[50][50];
vector<char> st;

int main()
{
    freopen("brackets2num2.in", "r", stdin);
    freopen("brackets2num2.out", "w", stdout);
    cin >> s;
    n = s.length() / 2;
    dp[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++) {
            dp[i][j] = dp[i - 1][j + 1];
            if (j != 0)
                dp[i][j] += dp[i - 1][j - 1]; 
        }
    for (int i = 0, g = 0; i < 2 * n; i++) {
        int temp = 2 * n - i - 1;
        if (s[i] == '(') {
            g++; 
            st.push_back('(');
            continue;
        } 
        if (g < n)
            ans += dp[temp][g + 1] * (1 << ((temp - g - 1)/2));
        if (s[i] == ')') {
            g--;
            st.pop_back();
            continue;
        } 
        if (g > 0 && st[st.size() -1] == '(')
            ans += dp[temp][g - 1] * (1 << ((temp - g + 1)/2));
        if (s[i] == '[') {
            g++;
            st.push_back('[');
            continue;
        } 
        if (g < n)
            ans += dp[temp][g + 1] * (1 << ((temp - g - 1)/2));
        g--;
        st.pop_back();
    }
    cout << ans << endl;
    return 0;
}

