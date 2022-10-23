#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 1000
using namespace std;

long long g[MAXN][MAXN];
int n;
bool used[MAXN];

bool allUsed() {
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            return false;
        }
    }
    return true;
}

void reUse() {
    for (int i = 0; i < n; ++i) {
        used[i] = false;
    }
}

void dfs2(int v, long long w) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && w >= g[v][i]) {
            dfs2(i, w);
        }
    }
}

void dfs1(int v, long long w) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && w >= g[i][v]) {
            dfs1(i, w);
        }
    }
}

int main() {
    ifstream cin("avia.in");
    ofstream cout("avia.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    long long l = 0;
    long long r = 2000000000LL;
    while (l < r) {
        long long m = (l + r) / 2;
        bool good = false;
        reUse();
        dfs1(0, m);
        if (allUsed()) {
            reUse();
            dfs2(0, m);
            if (allUsed()) {
                good = true;
            }
        }
        if (good) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << r << endl;
    return 0; }
