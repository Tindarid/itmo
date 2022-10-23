#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <set>
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
 
bool bfs(int v1, int v2) {
    queue<pair<int, int>> q;
    set<pair<int, int>> t;
    q.push(make_pair(v1, v2));
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        t.insert(cur);
        if (u1[cur.first].term != u2[cur.second].term) {
            return false;
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            auto it1 = u1[cur.first].m.find(c);
            auto it2 = u2[cur.second].m.find(c);
            bool a1 = it1 != u1[cur.first].m.end();
            bool a2 = it2 != u2[cur.second].m.end();
            if (a1 == true || a2 == true) {
                int t1, t2;
                if (a1 != true) {
                    t1 = 0;
                } else {
                    t1 = it1->second;
                }
                if (a2 != true) {
                    t2 = 0;
                } else {
                    t2 = it2->second;
                }
                pair<int, int> temp = make_pair(t1, t2);
                if (t.find(temp) == t.end()) {
                    q.push(temp);
                }
            }
        }
    }
    return true;
}
 
int main() {
    ifstream cin("equivalence.in");
    ofstream cout("equivalence.out");
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
    if (bfs(1, 1)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
