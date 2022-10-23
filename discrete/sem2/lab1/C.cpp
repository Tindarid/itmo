#include <iostream>
#include <fstream>
#include <iomanip>
#define SIZE 100005
using namespace std;

int a[SIZE];
double b[SIZE];

int main() {
    ifstream cin("lottery.in");
    ofstream cout("lottery.out");
    int n, m;
    double ans = 0.0, cur = 1.0;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }
    cur /= a[0];
    for (int i = 1; i < m; i++) {
        ans += cur * ((a[i] - 1.0) / a[i]) * b[i - 1];
        cur /= a[i];
    }
    ans += cur * b[m - 1];
    cout << setprecision(10) << fixed << n - ans << endl;
    return 0;
}

