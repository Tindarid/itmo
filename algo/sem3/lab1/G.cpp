#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;

vector<vector<int>> g;
vector<vector<int>> gt;
vector<int> topSort;
map<string, int> numbers;
map<int, string> names;
bool used[2 * MAXN + 5];
int color[2 * MAXN + 5];
int curcolor;

void dfs1(int t) {
    used[t] = true;
    for (int i = 0; i < g[t].size(); ++i) {
        int temp = g[t][i];
        if (!used[temp]) {
            dfs1(temp);
        }
    }
    topSort.push_back(t);
}

void dfs2(int t) {
    used[t] = true;
    color[t] = curcolor;
    for (int i = 0; i < gt[t].size(); ++i) {
        int temp = gt[t][i];
        if (!used[temp]) {
            dfs2(temp);
        }
    }
}
int findNumber(string s) {
    return (numbers.find(s))->second;
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(2 * n);
    gt.resize(2 * n);
    for (int i = 0; i < n; ++i) {
        string temp;
        cin >> temp;
        numbers.insert(make_pair("+" + temp, 2 * i));
        numbers.insert(make_pair("-" + temp, 2 * i + 1));
        names.insert(make_pair(i, temp));
    }
    for (int i = 0; i < m; ++i) {
        string from, temp, to;
        cin >> from >> temp >> to;
        g[findNumber(from)].push_back(findNumber(to));
        gt[findNumber(to)].push_back(findNumber(from));
        if (to[0] == '-') {
            to[0] = '+';
        } else {
            to[0] = '-';
        }
        if (from[0] == '-') {
            from[0] = '+';
        } else {
            from[0] = '-';
        }
        g[findNumber(to)].push_back(findNumber(from));
        gt[findNumber(from)].push_back(findNumber(to));
    }
    for (int i = 0; i < g.size(); ++i) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    for (int i = 0; i < g.size(); ++i) {
        used[i] = false;
    }
    reverse(topSort.begin(), topSort.end());
    for (int i = 0; i < topSort.size(); ++i) {
        if (!used[topSort[i]]) {
            curcolor++;
            dfs2(topSort[i]);
        }
    }
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
        if (color[2 * i] == color[2 * i + 1]) {
            cout << -1 << endl;
            return 0;
        }
        if (color[2 * i] > color[2 * i + 1]) {
            ans.push_back(names.find(i)->second);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}

