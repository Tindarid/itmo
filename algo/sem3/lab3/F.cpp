#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <map>
#define MAXL 10000
#define LL long long
#define P 31
using namespace std;

int n;
vector<string> mas;
LL mul[MAXL + 1];

void prep_mul() {
    mul[0] = 1;
    for (int i = 1; i < MAXL; ++i) {
        mul[i] = mul[i - 1] * P;
    }
}

bool comp(string a, string b) {
    return a.length() < b.length();
}

int main() {
    prep_mul();
    cin >> n;
    mas.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }    
    sort(mas.begin(), mas.end(), comp);
    int l = 1, r = mas[0].length() + 1;
    int save_a = -1, save_b = -1;
    while (l < r) {
        int m = (l + r) / 2;
        map<LL, pair<int, int>> ans;
        for (int i = 0; i < n; ++i) {
            int curlen = mas[i].length();
            if (m > curlen) {
                continue;
            }
            LL h = 0;
            for (int j = 0; j < m; ++j) {
                char c = mas[i][j];
                h += (c - 'a' + 1) * mul[m - j - 1];
            }
            set<LL> hashes;
            for (int j = 0; j < curlen; ++j) {
                if (j + m - 1 >= curlen) {
                   continue;
                } 
                if (j != 0) {
                    char c = mas[i][j + m - 1];
                    char c1 = mas[i][j - 1];
                    h -= (c1 - 'a' + 1) * mul[m - 1];
                    h *= P;
                    h += (c - 'a' + 1);
                }
                if (hashes.find(h) != hashes.end()) {
                    continue;
                }
                hashes.insert(h);
                auto it = ans.find(h);
                if (it == ans.end() && i == 0) {
                    ans.insert({h, {j, 1}});
                } else if (it != ans.end() && it->second.second <= i) {
                    int some = it->second.first;
                    int some2 = it->second.second + 1;
                    ans.erase(it);
                    ans.insert({h, {some, some2}});
                }
            }
        }
        bool flag = false;
        for (auto it = ans.begin(); it != ans.end(); ++it) {
            if (it->second.second == n) {
                save_a = it->second.first;
                save_b = save_a + m - 1;
                flag = true;
            }
        }
        if (flag) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    string ans = "";
    for (int i = save_a; i <= save_b; ++i) {
        ans += mas[0][i];
    }
    cout << ans << endl;
    return 0;
}
