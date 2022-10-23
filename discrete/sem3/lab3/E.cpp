#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 20
using namespace std;
using x = pair<int, int>;

int n, m;
bool dep[(1 << MAXN) + 5];
vector<x> sset;

bool comp(x a, x b) {
    return a.second > b.second;
}

int main() {
    ifstream cin("cycles.in");
    ofstream cout("cycles.out");
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        sset.push_back({i, w});
    }
    sort(sset.begin(), sset.end(), comp);
    for (int i = 0; i < m; ++i) {
        int amount, some, temp = 0;
        cin >> amount;
        for (int j = 0; j < amount; ++j) {
            cin >> some;
            temp |= (1 << (some - 1));
        }
        dep[temp] = true;
        for (int j = temp; j < (1 << n); ++j) {
            if ((temp | j) == j) {
                dep[j] = true;
            }
        }
    }
    long long ans = 0;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        int ind = sset[i].first;
        int w = sset[i].second;
        int b = (1 << ind);
        if (!dep[cur | b]) {
            ans += w;
            cur |= b;
        }
    }
    cout << ans << endl;
    return 0;
}
