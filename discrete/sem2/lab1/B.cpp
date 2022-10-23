#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    ifstream cin("shooter.in");
    ofstream cout("shooter.out");
    int n, m, k;
    double a[10005];
    double sum = 0;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = 1 - a[i];
        double q = a[i];
        for (int j = 0; j < m - 1; j++) {
            q *= a[i];
        }
        a[i] = q;
        sum += a[i];
    }
    cout << setprecision(13) << fixed << a[k - 1] / sum << endl;
    return 0;
}

