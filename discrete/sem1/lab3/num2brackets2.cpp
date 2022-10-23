#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long n, k, ans;
long long dp[50][50];
vector<char> st;

int main()
{
    freopen("num2brackets2.in", "r", stdin);
    freopen("num2brackets2.out", "w", stdout);
    cin >> n >> k;
    dp[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++) {
            dp[i][j] = dp[i - 1][j + 1];
            if (j != 0)
                dp[i][j] += dp[i - 1][j - 1]; 
        }
    long long cur = 0;
    for (int i = 0, g = 0; i < 2 * n; i++) {
        int temp = 2 * n - i - 1;
        long long temp2 = cur;
        if (g < n) {
            temp2 += dp[temp][g + 1] * (1 << ((temp - g - 1)/2));
            if (k < temp2) {
                cout << '(';
                g++; 
                st.push_back('(');
                continue;
            }
            cur = temp2;
        }
        if (g > 0 && st[st.size() - 1] == '(') {
            temp2 += dp[temp][g - 1] * (1 << ((temp - g + 1)/2));
            if (k < temp2) {
                cout << ')';
                g--;
                st.pop_back();
                continue;
            } 
            cur = temp2;
        }
        if (g < n) {
            temp2 += dp[temp][g + 1] * (1 << ((temp - g - 1)/2));
            if (k < temp2) {
                cout << '[';
                g++;
                st.push_back('[');
                continue;
            } 
            cur = temp2;
        }
        cout << ']';
        st.pop_back();
        g--;
    }
    return 0;
}

