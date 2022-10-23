#include <iostream>
#define MOD 1000000000
using namespace std;

int n, d[105][10];

int main() {
    cin >> n;
    for (int i = 0; i <= 9; i++)
       d[1][i] = 1; 
    d[1][0] = d[1][8] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 9; j++) {
            int temp1 = 0, temp2 = 0, temp3 = 0;
            if (j == 5)
                continue;
            switch(j) {
                case 0:
                    temp1 = 4, temp2 = 6;
                    break;
                case 1:
                    temp1 = 8, temp2 = 6;
                    break;
                case 2:
                    temp1 = 7, temp2 = 9;
                    break;
                case 3:
                    temp1 = 8, temp2 = 4;
                    break;
                case 4:
                    temp1 = 9, temp2 = 3;
                    break;
                case 6:
                    temp1 = 7, temp2 = 1;
                    break;
                case 7:
                    temp1 = 6, temp2 = 2;
                    break;
                case 8:
                    temp1 = 3, temp2 = 1;
                    break;
                case 9:
                    temp1 = 4, temp2 = 2;
                    break;
                default:
                    break;
            }
            d[i][j] = ((d[i][j] + d[i - 1][temp1]) % MOD + d[i - 1][temp2]) % MOD;
            if (j == 4 || j == 6)
                d[i][j] = (d[i][j] + d[i - 1][0]) % MOD;
        }
    int ans = 0;
    for (int i = 0; i <= 9; i++)
        ans = (ans + d[n][i]) % MOD;
    cout << ans << endl;
    return 0;
}

