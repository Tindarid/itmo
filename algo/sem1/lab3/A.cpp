#include <iostream>
#include <fstream>
using namespace std;

int n, k, mas[10005], d[10005], ans[10005];

int maxim(int a, int b) {
    int res = b;
    for (int i = b; (i >= 1) && (i >= a); i--)
        if (d[res] <= d[i])
            res = i;
    return res;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    cin >> n >> k;
    for (int i = 2; i < n; i++) 
        cin >> mas[i];
    for (int i = 1; i <= n; i++)
        d[i] = mas[i] + d[maxim(i - k, i - 1)]; 
    int res = n, k2 = 0;
    while (true) {
        ans[k2] = res;
        k2++;
        if (res == 1)
            break;
        res = maxim(res - k, res - 1);
    }
    cout << d[n] << endl;
    cout << k2 - 1 << endl;
    for (int i = k2 - 1; i >= 0; i--)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}
