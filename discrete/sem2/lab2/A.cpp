#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
using namespace std;

string s;
int n, m, k;
vector<map<char, int>> d;
vector<int> g;

bool dka() {
    int cur = 1;
    for (int i = 0; i < s.length(); ++i) {
        map<char, int>::iterator it = d[cur].find(s[i]);
        if (it != d[cur].end()) {
            cur = it->second;
        } else {
            return false;
        }
    }
    for (int i = 0; i < g.size(); ++i) {
        if (g[i] == cur) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream cin("problem1.in");
    ofstream cout("problem1.out");
    cin >> s >> n >> m >> k;
    d.resize(n + 1);
    g.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> g[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        d[a].insert(make_pair(c, b));
    }
    if (dka()) {
        cout << "Accepts\n";
    } else {
        cout << "Rejects\n";
    }
    return 0;
}
