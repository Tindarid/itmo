#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using matrix = vector<vector<long long>>;

matrix g;
matrix fake;
int n, m;
long long t;

matrix mul_min(matrix g1, matrix g2) {
    if (g1[0][0] == -1) {
        return g2;
    } else if (g2[0][0] == -1) {
        return g1;
    }
    matrix ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i].push_back(g1[i][0] + g2[0][j]);
            for (int q = 1; q < n; ++q) {
                ans[i][j] = min(g1[i][q] + g2[q][j], ans[i][j]);
            }
        }
    }
    return ans;
}

matrix mul_max(matrix g1, matrix g2) {
    if (g1[0][0] == -1) {
        return g2;
    } else if (g2[0][0] == -1) {
        return g1;
    }
    matrix ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i].push_back(g1[i][0] + g2[0][j]);
            for (int q = 1; q < n; ++q) {
                ans[i][j] = max(g1[i][q] + g2[q][j], ans[i][j]);
            }
        }
    }
    return ans;
}

matrix bin_pow_max(matrix t, int q) {
	if (q == 0) {
		return fake;
    }
    if (q % 2 == 1) {
		return mul_max(bin_pow_max(t, q - 1), t);
    } else {
		matrix b = bin_pow_max(t, q / 2);
		return mul_max(b, b);
	}
}

matrix bin_pow_min(matrix t, int q) {
	if (q == 0) {
		return fake;
    }
    if (q % 2 == 1) {
		return mul_min(bin_pow_min(t, q - 1), t);
    } else {
		matrix b = bin_pow_min(t, q / 2);
		return mul_min(b, b);
	}
}

bool used[50]; 

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (g[v][i] != 0 && !used[i]) {
            dfs(i);
        }
    }
}

int main() {
    fake.resize(1);
    fake[0].push_back(-1);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n; ++i) {
        g[i].resize(n);
    }
    for (int i = 0; i < m; ++i) {
        int v, u;
        long long c;
        cin >> v >> u >> c;
        g[v - 1][u - 1] = g[u - 1][v - 1] = c;
    }
    cin >> t;
    dfs(0);
    if (!used[n - 1]) {
        cout << "Impossible";
        return 0;
    }
    long long l = 0, r = t, m;
    while (l < r) {
        m = (l + r) / 2;
        matrix a1 = bin_pow_min(g, m);
        matrix a2 = bin_pow_max(g, m);
        long long min_t = a1[0][n - 1];
        long long max_t = a2[0][n - 1];
        if (t > max_t) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    matrix a1 = bin_pow_min(g, l);
    matrix a2 = bin_pow_max(g, r);
    long long min_t = a1[0][n - 1];
    long long max_t = a2[0][n - 1];
    if (t <= max_t && t >= min_t) {
        cout << "Possible\n";
    } else {
        cout << "Impossible\n";
    }
    return 0;
}
