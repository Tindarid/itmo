#include <iostream>
#include <fstream>
#define INF 1000000010
using namespace std;

int n, k, mas[10005], d[10005], ans[10005];

int maxim(int b, int c) {
    int res = 0;
    for (int i = 0; i <= b; i++)
        if ((d[res] <= d[i]) && (mas[i] < c))
            res = i;
    return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> mas[i];
    mas[0] = -INF;
    d[0] = 0;
    for (int i = 1; i <= n; i++)
        d[i] = 1 + d[maxim(i - 1, mas[i])]; 
    int res = maxim(n, INF);
    int k2 = 0;
    while (true) {
        ans[k2] = mas[res];
        k2++;
        if (d[res] == 1)
            break;
        res = maxim(res - 1, mas[res]);
    }
    cout << k2 << endl;
    for (int i = k2 - 1; i >= 0; i--)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}
