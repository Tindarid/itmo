#include <iostream>
#include <string>
using namespace std;

string s;
long long n;
int dp[105][105];
string sans[105][105];

int getAns(int l, int r, string & cur) {
    if (l >= r) {
        cur = "";
        return 0;
    }
    if (dp[l][r] != -1) {
        cur = sans[l][r];
        return dp[l][r];
    }
    int ans = 0;
    string temp = "";
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') || (s[l] == '{' && s[r] == '}')) {
        ans = getAns(l + 1, r - 1, temp) + 2; 
        cur = (s[l] + temp + s[r]);
    }
    for (int i = l; i < r; i++) {
        string temp3, temp4;
        int temp2 = getAns(l, i, temp3) + getAns(i + 1, r, temp4);
        if (temp2 > ans) {
            ans = temp2;
            cur = temp3 + temp4;
        }
    }
    dp[l][r] = ans;
    sans[l][r] = cur;
    return ans;
}

int main() {
    cin >> s;
    n = s.length();
    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 105; j++)
            dp[i][j] = -1;
    string temp;
    getAns(0, n - 1, temp);
    cout << temp << endl;
    return 0;
}

