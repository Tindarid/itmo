#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 100
using namespace std;

int n;
vector<pair<pair<int, int>, int>> edges;
const int INF = 1e8;
int r[MAXN + 1], p[MAXN + 1];

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp;
            cin >> temp;
            if (temp != 100000) {
                edges.push_back(make_pair(make_pair(i, j), temp));
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        p[i] = -1;
    }
    int ans;
    for (int i = 0; i < n; ++i) {
        ans = -1;
        for (int j = 0; j < edges.size(); ++j) {
            int v = edges[j].first.first;
            int u = edges[j].first.second;
            int c = edges[j].second;
            if (r[u] > r[v] + c) {
                r[u] = max(r[v] + c, -INF);
                p[u] = v;
                ans = u;
            }
        }
    }
    if (ans == -1) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (int i = 0; i < n; ++i) {
        ans = p[ans];
    }
    vector<int> ans_path;
    int cur = ans;
    while (ans_path.size() == 0 || ans != cur) {
        ans_path.push_back(cur);
        cur = p[cur];
    }
    reverse(ans_path.begin(), ans_path.end());
    cout << ans_path.size() << endl;
    for (int i = 0; i < ans_path.size(); ++i) {
        cout << ans_path[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
