#include <fstream>
#include <utility>
#define SIZE 20000005
#define LL long long
using namespace std;

int n;
LL x, y;
int a[SIZE]; 
LL d[SIZE];
LL m, z, t;
LL ans;
int c[SIZE], b[SIZE];

int main() {
    ios_base:: sync_with_stdio(false);
    ifstream cin("sum0.in");
    ofstream cout("sum0.out");
    cin >> n >> x >> y >> a[0];
    cin >> m >> z >> t >> b[0];
    d[0] = a[0];
    for (int i = 1; i < n; ++i) {
        a[i] = (x * a[i - 1] + y) & (65535LL);
        d[i] = d[i - 1] + a[i];
    }
    for (int i = 1; i < 2 * m; ++i) {
        b[i] = (z * b[i - 1] + t) & (1073741823LL);
        c[i - 1] = b[i - 1] % n;
    }
    c[2 * m - 1] = b[2 * m - 1] % n;
    for (int i = 0; i < 2 * m; i += 2) {
        if (c[i + 1] < c[i]) {
            swap(c[i + 1], c[i]);
        }
    }
    for (int i = 0; i < 2 * m; i += 2) {
        ans += d[c[i + 1]] - d[c[i] - 1];
    }
    cout << ans << "\n";
    return 0;
}
