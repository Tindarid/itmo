#include <iostream>
#include <fstream>
#include <vector>
#define INF 10000000000LL
using namespace std;
 
long long n;
long long matrix[20][20];
long long dp[20][10000];
 
long long min(int a, int b) {
    if (a < b)
        return a;
    return b;
}
 
long long getAns(int v, int vect) {
    if (dp[v][vect] == INF) {
        for (long long i = 0; i < n; i++) {
            if ((vect) & (1 << i)) {
                dp[v][vect] = min(dp[v][vect], getAns(i, vect - (1 << i)) + matrix[v][i]);
            }
        }
    }
    return dp[v][vect];
}
 
int main() {
    //ifstream cin("input.txt"); ofstream cout("output.txt");
    cin >> n;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            cin >> matrix[i][j];
    for (long long i = 0; i <= n; i++)
        for (long long j = 0; j <= (1 << (n)); j++)
            dp[i][j] = INF;
    for (long long i = 0; i <= n; i++)
        dp[i][0] = 0;
    long long vect = (1 << n) - 1;
    long long ans = INF, tempi = 0;
    for (long long i = 0; i < n; i++) {
        if (ans > getAns(i, vect - (1 << i))) {
            tempi = i;
            ans = getAns(i, vect - (1 << i));
        }
    }
    vect -= (1 << tempi);
    long long cur = tempi;
    cout << ans << endl << tempi + 1 << " ";
    while (vect != 0) {
        for (long long i = 0; i < n; i++) {
            if ((dp[cur][vect] == (dp[i][vect - (1 << i)] + matrix[i][cur])) && ((vect) & (1 << i))) {
                cout << i + 1 << " ";
                vect -= (1 << i);
                cur = i;
            }
        }
    }
    return 0;
}
