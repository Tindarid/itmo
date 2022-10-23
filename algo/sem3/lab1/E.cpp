#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#define MAXN 20000
using namespace std;

vector<vector<int>> v;
bool used[MAXN + 1];
int tin[MAXN + 1], ret[MAXN + 1];
int timer;
vector<pair<int, int>> edges;
map<pair<int, int>, int> colors;
int maxColor;

void dfs2(int t, int p, int color) {
    used[t] = true;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (!used[temp]) {
            if (ret[temp] >= tin[t]) {
                maxColor++;
                colors.insert(make_pair(make_pair(t, temp), maxColor));
                colors.insert(make_pair(make_pair(temp, t), maxColor));
                dfs2(temp, t, maxColor);
            } else {
                colors.insert(make_pair(make_pair(temp, t), color));
                dfs2(temp, t, color);
            }
        } else if (colors.find(make_pair(temp, t)) == colors.end()) {
            colors.insert(make_pair(make_pair(t, temp), color));
            colors.insert(make_pair(make_pair(temp, t), color));
        }
    }
}

void dfs(int t, int p) {
    used[t] = true;
    tin[t] = ret[t] = ++timer;
    for (int i = 0; i < v[t].size(); ++i) {
        int temp = v[t][i];
        if (temp == p) {
            continue;
        } else if (!used[temp]) {
            dfs(temp, t);
            ret[t] = min(ret[t], ret[temp]); 
        } else {
            ret[t] = min(ret[t], tin[temp]);
        }
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int N, M;
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[b].push_back(a);
        v[a].push_back(b);
        edges.push_back(make_pair(a, b));
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    for (int i = 1; i <= N; ++i) {
        used[i] = false;
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            dfs2(i, 0, maxColor);
        }
    }
    cout << maxColor << endl;
    for (int i = 0; i < edges.size(); ++i) {
        auto it = colors.find(edges[i]);
        if (it == colors.end()) {
            it = colors.find(make_pair(edges[i].second, edges[i].first));
        }
        cout << it->second << " ";
    }
    cout << endl;
    return 0;
}
