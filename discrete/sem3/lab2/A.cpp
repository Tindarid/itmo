#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#define MAXN 100
using namespace std;

int n, m;
int f[MAXN + 5];
vector<vector<int>> g;
vector<pair<int, int>> e;
vector<pair<int, int>> e_order;
vector<int> v_order;
map<pair<int, int>, pair<double, double>> e_ans;
map<int, pair<double, double>> v_ans;
vector<int> used;

void constr() {
    for (int i = 0; i < n; ++i) {
        int v = v_order[i];
        v_ans.insert(make_pair(v, make_pair(i, 0)));
    }
    for (int i = 0; i < n - 1; ++i) {
        e_ans.insert(make_pair(
                    make_pair(v_order[i], v_order[i + 1]), 
                    make_pair(i + 0.5, 0)
                    ));
        e_ans.insert(make_pair(
                    make_pair(v_order[i + 1], v_order[i]), 
                    make_pair(i + 0.5, 0)
                    ));
    }
    e_ans.insert(make_pair(
                make_pair(v_order.back(), v_order.front()), 
                make_pair((n - 1) / 2.0, (n - 1) / 2.0)
                ));
    e_ans.insert(make_pair(
                make_pair(v_order.front(), v_order.back()), 
                make_pair((n - 1) / 2.0, (n - 1) / 2.0)
                ));
    for (auto it = e_order.begin(); it != e_order.end(); ++it) {
        if (e_ans.find(*it) == e_ans.end()) {
            e.push_back(*it);
        }
    }
}

bool resolve(int v1, int u1, int v2, int u2) {
    if (v1 > u1) {
        swap(v1, u1);
    }
    if (v2 > u2) {
        swap(v2, u2);
    }
    if (v1 < v2 && v2 < u1 && u1 < u2) {
        return true;
    } else if (v2 < v1 && v1 < u2 && u2 < u1) {
        return true;
    } else {
        return false;
    }
}

void create_g() {
    g.resize(e.size());
    for (int i = 0; i < e.size(); ++i) {
        int v1 = e[i].first;
        int u1 = e[i].second;
        for (int j = i + 1; j < e.size(); ++j) {
            int v2 = e[j].first;
            int u2 = e[j].second;
            if (resolve(f[v1], f[u1], f[v2], f[u2])) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
}

bool dfs(int v, int color) {
    used[v] = color;
    color = (color + 1) % 2;
    bool ans = true;
    for (int i = 0; i < g[v].size(); ++i) {
        if (used[g[v][i]] == -1) {
            ans &= dfs(g[v][i], color);
        } else if (used[g[v][i]] != color) {
            ans = false;
        }
    }
    return ans;
}

bool find_dv() {
    used.resize(g.size(), -1);
    bool ans = true;
    for (int i = 0; i < g.size(); ++i) {
        if (used[i] == -1) {
            ans &= dfs(i, 1);
        }
    }
    return ans;
}

pair<double, double> find_ans(int v, int u, int color) {
    auto it = v_ans.find(v);
    auto st = v_ans.find(u);
    double x1 = it->second.first;
    double x2 = st->second.first;
    double x = (x1 + x2) / 2;
    double y = (x1 - x2) / 2;
    if (y < 0) {
        y = -y;
    }
    if (color == 1) {
        y = -y;
    }
    return make_pair(x, y);
}

void constr_edges() {
    for (int i = 0; i < g.size(); ++i) {
        int color = used[i];
        int v = e[i].first;
        int u = e[i].second;
        e_ans.insert(make_pair(make_pair(v, u), find_ans(v, u, color)));
    }
}

bool sol() {
    constr();
    create_g();
    if (!find_dv()) {
        return false;
    }
    constr_edges();
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        e_order.push_back(make_pair(v, u));
    }
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        v_order.push_back(v);
        f[v] = i;
    }
    if (sol()) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; ++i) {
            auto it = v_ans.find(i);
            cout << it->second.first << " " << it->second.second << " ";
        }
        cout << endl;
        for (int i = 0; i < e_order.size(); ++i) {
            auto it = e_ans.find(make_pair(e_order[i].first, e_order[i].second));
            cout << it->second.first << " " << it->second.second << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}
