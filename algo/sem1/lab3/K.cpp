#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long n, m, res;
int d[2000][2000];
int dp[2000][2000];

vector<int> getVector(int a) {
    vector<int> m1;
    while (a > 0) {
        m1.push_back(a%2);
        a /= 2;
    }
    while (m1.size() != n)
        m1.push_back(0);
    return m1;
}

bool isGood(int a, int b) {
    vector<int> m1 = getVector(a), m2 = getVector(b);
    for (int i = 0; i < n - 1; i++)
        if (m1[i] == m2[i])
            if (m1[i + 1] == m2[i + 1])
                if (m1[i] == m1[i + 1])
                    return false;
    return true;
}

int main() {
    ifstream cin("nice.in");
    ofstream cout("nice.out");
    cin >> n >> m;
    if (m < n) {
        int temp = n; n = m; m = temp;
    }
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < (1 << n); j++)
            if (isGood(i, j))
                d[i][j] = 1;
    for (int j = 0; j < (1 << n); j++)
        dp[0][j] = 1;
    for (int i = 1; i < m; i++)
        for (int j = 0; j < (1 << n); j++)
            for (int j2 = 0; j2 < (1 << n); j2++)
                dp[i][j] += d[j][j2] * dp[i - 1][j2];
    for (int j = 0; j < (1 << n); j++)
        res += dp[m - 1][j]; 
    cout << res << endl;
    return 0;
}
