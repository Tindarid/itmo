#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

struct Node {
    bool term;
    map<char, int> m;

    Node() {
        term = false;
    }
};

int n1, m1, k1, n2, m2, k2;
vector<Node> u1, u2;
bool visited1[100001], visited2[100001];

bool dfs(int v1, int v2) {
    visited1[v1] = visited2[v2] = true;
    if (u1[v1].term != u2[v2].term) {
        return false;
    }
    bool res = true;
    for (auto it = u1[v1].m.begin(); it != u1[v1].m.end(); ++it) {
        int t1 = it->second;
        auto temp = u2[v2].m.find(it->first);
        if (temp == u2[v2].m.end()) {
            return false;
        }
        int t2 = temp->second;
        //d
        if (!visited1[t1] && !visited2[t2]) {
            res = res & dfs(t1, t2);
        }
    }
    return res;
}

int main() {
    ifstream cin("isomorphism.in");
    ofstream cout("isomorphism.out");
    cin >> n1 >> m1 >> k1;
    u1.resize(n1 + 1);
    for (int i = 0; i < k1; i++) {
        int a;
        cin >> a;
        u1[a].term = true;
    }
    for (int i = 0; i < m1; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        u1[a].m.insert(make_pair(c, b));
    }
    cin >> n2 >> m2 >> k2;
    u2.resize(n2 + 1);
    for (int i = 0; i < k2; i++) {
        int a;
        cin >> a;
        u2[a].term = true;
    }
    for (int i = 0; i < m2; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        u2[a].m.insert(make_pair(c, b));
    }
    if (dfs(1, 1)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
