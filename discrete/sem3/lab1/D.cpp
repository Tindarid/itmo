#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 1000
using namespace std;

int n;
bool mat[MAXN + 1][MAXN + 1];

int main() {
    ifstream cin("guyaury.in");
    ofstream cout("guyaury.out");
    cin >> n;
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == '1') {
                mat[i][j] = true;
            } else {
                mat[j][i] = true;
            }
        }
    }

    vector<int> l;
    for (int i = 0; i < n; ++i) {
        if (l.empty()) {
            l.push_back(i);
        } else {
            auto save = l.begin();
            while (save != l.end() && mat[*save][i]) {
                ++save;
            }
            l.insert(save, i);
        }
    }

    vector<int> l2;
    int j = l.front(), i;        
    for (i = l.size() - 1; i >= 2; --i) {
        if (mat[l[i]][j]) {
            break;
        }
    }
    l2.insert(l2.begin(), l.begin(), l.begin() + i + 1);
    l.erase(l.begin(), l.begin() + i + 1);

    for (auto it = l.begin(); it != l.end();) {
        auto save = l2.begin();
        while (save != l2.end() && mat[*save][*it]) {
            ++save;
        }
        it++;
        if (save != l2.end()) {
            l2.insert(save, l.begin(), it);
            l.erase(l.begin(), it);
            it = l.begin();
        }
    }
    for (auto it = l2.begin(); it != l2.end(); ++it) {
        cout << *it + 1 << " ";
    }
    cout << endl;
    return 0;
}
