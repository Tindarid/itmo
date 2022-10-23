#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#define MOD 1000000007
using namespace std;

int n, m, k, l;
vector<vector<int>> d;
vector<int> g;
vector<int> anss;

int main() {
    ifstream cin("problem4.in");
    ofstream cout("problem4.out");
    cin >> n >> m >> k >> l;
    d.resize(n + 2);
    g.resize(k);
    anss.resize(n + 2);
    for (int i = 0; i < k; i++) {
        cin >> g[i];
        anss[g[i]] = 1;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        d[a].push_back(b);
    }
    for (int i = 0; i < l; ++i) {
        vector<int> temp;
        temp.resize(n + 2);
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k < d[j].size(); ++k) {
                temp[j] = (anss[d[j][k]] + temp[j]) % MOD;
            }
        }
        anss = temp;
    }
    cout << anss[1] << endl;
    return 0;
}
