#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

int n;
vector<vector<int>> d;
vector<int> init;
vector<int> anss;

set<int>* dfs(int v) {
    set<int> *cur = new set<int>;
    cur->insert(init[v]);
    for (int i = 0; i < d[v].size(); ++i) {
        set<int> *temp = dfs(d[v][i]);
        anss[d[v][i]] = temp->size();
            if (temp->size() >= cur->size()) {
                for (auto j = cur->begin(); j != cur->end(); ++j) {
                    temp->insert(*j);
                }
                cur->clear();
                cur = temp;
            } else {
                for (auto j = temp->begin(); j != temp->end(); ++j) {
                    cur->insert(*j);
                }
                temp->clear();
            }
    }
    return cur;
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    ios_base::sync_with_stdio(false);
    cin >> n;
    d.resize(n + 2);
    anss.resize(n + 2);
    init.resize(n + 2);
    for (int i = 1; i <= n; ++i) {
        int p, c;
        cin >> p >> c;
        d[p].push_back(i);
        init[i] = c;
    }
    dfs(0);
    for (int i = 1; i <= n; ++i) {
        cout << anss[i] << " ";
    }
    cout << "\n";
}
