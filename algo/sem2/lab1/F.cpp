#include <fstream>
#include <utility>
#define SIZE 100010
#define LL long long
using namespace std;

LL a[SIZE];
LL f[SIZE];
LL st[SIZE][40];
LL n, m, u, v, ans;

LL fl(LL a) {
    if (a == 1) {
        return 0;
    } else {
        return fl(a / 2) + 1;
    }
}

int main() {
    ifstream cin("sparse.in");
    ofstream cout("sparse.out");
    cin >> n >> m >> a[1];
    for (int i = 2; i <= n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
        f[i] = fl(i);
    }
    cin >> u >> v;

    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }

    for (int j = 1; j <= f[n]; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 1; i <= m; i++) {
        LL l = min(u, v);
        LL r = max(u, v);
        LL j = f[r - l + 1];
        ans = min(st[l][j], st[r - (1 << j) + 1][j]);
        if (i == m) {
            break;
        }
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }
    cout << u << " " << v << " " << ans << "\n";
    return 0;
}
