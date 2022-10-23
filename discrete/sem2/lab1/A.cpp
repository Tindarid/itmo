#include <iostream>
#include <fstream>
#include <iomanip>
#define SIZE 1000005 
using namespace std;

int a[SIZE], b[SIZE];

int main() {
    ifstream cin("exam.in");
    ofstream cout("exam.out");
    int k, n;
    double ans = 0;
    cin >> k >> n;
    for (int i = 0; i < k; i++) {
        cin >> a[i] >> b[i];
        ans += (1.0 * a[i] / n * b[i] / 100.0);
    }
    cout << setprecision(5) << fixed << ans << endl;
    return 0;
}

