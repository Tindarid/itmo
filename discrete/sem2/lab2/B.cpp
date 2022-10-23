#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <set>
using namespace std;

string s;
int n, m, k;
vector<multimap<char, short>> d;
vector<short> g;

bool nka() {
    set<short> cur;
    cur.insert(1);
    int l = s.length();
    for (int i = 1; i <= l; ++i) {
        set<short> temp;
        for (auto it1 = cur.begin(); it1 != cur.end(); ++it1) {
            pair<multimap<char, short>::iterator, multimap<char, short>::iterator> p = d[*it1].equal_range(s[i - 1]);
            for (multimap<char, short>::iterator it = p.first; it != p.second; ++it) {
                temp.insert(it->second);
            } 
        }
        cur.swap(temp);
    }
    for (int i = 0; i < g.size(); ++i) {
        auto it = cur.find(g[i]);
        if (it != cur.end()) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream cin("problem2.in");
    ofstream cout("problem2.out");
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
    if (nka()) {
        cout << "Accepts\n";
    } else {
        cout << "Rejects\n";
    }
    return 0;
}
