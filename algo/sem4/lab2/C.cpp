#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 1050
#define MAXK 35
#define LL int
using namespace std;

const LL INF = 1e9;
int N, K, P;
int C[MAXN][MAXK];
int w[MAXK][MAXK];
LL dp[MAXN][MAXK][MAXK];
vector<int> initial_g[MAXN];

int some(int n, int m) {
    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int jj = 0;
        vector<int> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[jj] = true;
            int ii = p[jj];
            int delta = 2 * INF;
            int f;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = w[ii][j] - u[ii] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = jj;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        f = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            jj = f;
        } while (p[jj] != 0);
        do {
            int f = way[jj];
            p[jj] = p[f];
            jj = f;
        } while (jj);
    }
    return -v[0];
}

int getAns(int v, int u, int t) {
    for (int i = 0; i < MAXK; ++i) {
        for (int j = 0; j < MAXK; ++j) {
            w[i][j] = 0;
        }
    }
    for(int i = 0; i < initial_g[v].size(); ++i) {
        int a = initial_g[v][i];
        for(int j = 0; j < K; j++) {
            w[i + 1][j + 1] = j != t ? dp[a][j][u] : INF;
        }
    }
    return some(initial_g[v].size(), K);
}

void in() {
    //ifstream cin("input.txt");
    cin >> N >> K >> P;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            cin >> C[i][j];
        }
    }
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        initial_g[a - 1].push_back(b - 1);
        initial_g[b - 1].push_back(a - 1);
    }
}

void sol(int v, int par) {
    for (int i = 0; i < initial_g[v].size(); ++i) {
        if (initial_g[v][i] == par) {
            initial_g[v].erase(initial_g[v].begin() + i); 
            --i;
        } else {
            sol(initial_g[v][i], v); 
        }
    }
    for (int i = 0; i < K; ++i) {
        LL penalty = C[v][i] + P;
        for (int a : initial_g[v]) {
            LL m = INF;
            for (int j = 0; j < K; ++j) {
                m = min(m, dp[a][j][i]);
            }
            penalty += m;
        }

        if (par == -1) {
            dp[v][i][0] = penalty;
            if (initial_g[v].size() <= K) {
                LL ans = getAns(v, i, -1);
                dp[v][i][0] = min(dp[v][i][0], C[v][i] + ans);
            }
        } else {
            for (int j = 0; j < K; ++j) {
                dp[v][i][j] = penalty;
            }
            if (initial_g[v].size() < K) {
                for (int j = 0; j < K; j++) {
                    LL ans = getAns(v, i, j);
                    dp[v][i][j] = min(dp[v][i][j], C[v][i] + ans);
                }
            }
        }
    }
}

void out() {
    LL ans = INF;
    for (int i = 0; i < K; ++i) {
        ans = min(ans, dp[0][i][0]);
    }
    cout << ans << endl;
}

int main() {
    in();
    sol(0, -1);
    out();
}
