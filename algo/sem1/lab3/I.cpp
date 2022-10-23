#include <iostream>
using namespace std;

int n, m;
bool matrix[300][300];
int d[300][300];
int ans1[100000], ans2[100000];

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    cin >> n >> m;
    int p = 1;
    while (p != n + 1) {
        int temp;
        cin >> temp;
        if (temp == 0)
            p++;
        matrix[p][temp] = true;
    }
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            int temp1 = 0, temp2 = 0, temp3 = 0;
            if (matrix[i][j])
                temp1 = d[i - 1][j - 1] + 1;
            temp2 = d[i][j - 1];
            temp3 = d[i - 1][j];
            d[i][j] = max(temp1, temp2);
            d[i][j] = max(d[i][j], temp3);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cout << d[i][j] << " ";
    int size = d[n][m];
    cout << size << endl;
    int l = n, r = m, cur = 0;
    while (cur != size) {
        int temp1 = 0, temp2 = 0, temp3 = 0;
        if (matrix[l][r])
            temp1 = d[l - 1][r - 1] + 1;
        temp2 = d[l][r - 1];
        temp3 = d[l - 1][r];
        if ( d[l][r] == temp2) {
            r--;
        }
        else if (d[l][r] == temp3) {
            l--;
        }
        else {
            ans1[cur] = l, ans2[cur] = r;
            cur++;
            l--, r--;
        }
    }
    for (int i = size - 1; i >= 0; i--)
        cout << ans1[i] << " " << ans2[i] << endl;
    return 0;
}
