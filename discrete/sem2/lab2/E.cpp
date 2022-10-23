#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <map>
#define MOD 1000000007
using namespace std;

int n, m, k, l;
int isT[105];
int d[105][30][105];
map<set<int>, int> ma;
int ansd[105][30][105];
int isTa[105];

int main() {
    ifstream cin("problem5.in");
    ofstream cout("problem5.out");
    cin >> n >> m >> k >> l;
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        isT[a] = 1;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        d[a][c - 'a'][b] = 1;
    }

    queue<set<int>> q;
    set<int> temp1;
    set<set<int>> se;
    temp1.insert(1);
    q.push(temp1);
    ma.insert(make_pair(temp1, 1));
    int curq = 2;
    se.insert(temp1);
    while(!q.empty()) {
        set<int> cur = q.front();
        q.pop();
        for (char c = 'a'; c <= 'z'; ++c) {
            set<int> temp;
            bool flag = false;
            for (auto it = cur.begin(); it != cur.end(); ++it) {
                for (int i = 1; i <= n; ++i) {
                    if (d[*it][c - 'a'][i] == 1) {
                        temp.insert(i);
                        if (isT[i] == 1) {
                            flag = true;
                        }
                    }
                }
            }
            if (!temp.empty()) {
                if (se.find(temp) == se.end()) {
                    q.push(temp);
                    se.insert(temp);
                    ma.insert(make_pair(temp, curq));
                    curq++;
                }
                ansd[ma.find(cur)->second][c - 'a'][ma.find(temp)->second] = 1;
                if (flag) {
                    isTa[ma.find(temp)->second] = 1;
                }
            }
        }
    }
    
    vector<int> anss(isTa, isTa + sizeof isTa / sizeof isTa[0]);
    for (int i = 0; i < l; ++i) {
        vector<int> temp;
        temp.resize(anss.size() + 5);
        for (int j = 1; j <= 100; ++j) {
            for (char c = 'a'; c <= 'z'; ++c) {
                for (int k = 0; k <= 100; ++k) {
                    if (ansd[j][c - 'a'][k] == 1) {
                        temp[j] = (anss[k] + temp[j]) % MOD;
                    }
                }
            }
        }
        anss = temp;
    }
    cout << anss[1] << endl;
    return 0;
}
