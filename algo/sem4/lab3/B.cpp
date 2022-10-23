#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 1;
const int MAXM = 1e3 + 1;
int lp[MAXN], p[MAXN];
int lp2[MAXN];

void erat() {
    int size = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            p[size++] = i;
        }
        for (int j = 0, temp = i * p[j]; j < size && p[j] <= lp[i] && temp < MAXN; ++j, temp = i * p[j]) {
            lp[temp] = p[j];
            lp2[temp] = i;
        }
    }
}

void fact(int a) {
    while (lp[a]) {
        printf("%d ", lp[a]);
        a = lp2[a];
    }
    printf("\n");
}

int main() {
    erat();
    int n, a;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        fact(a);
    }
}
