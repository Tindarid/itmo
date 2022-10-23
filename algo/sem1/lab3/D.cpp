#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int d[1005][1005];

int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();
    for (int i = 0; i <= n; i++)
        d[i][0] = i;
    for (int i = 0; i <= m; i++)
        d[0][i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            d[i][j] = d[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]);
            d[i][j] = min(d[i][j], d[i - 1][j] + 1);
            d[i][j] = min(d[i][j], d[i][j - 1] + 1);
        }
    cout << d[n][m] << endl;
    return 0;
}
