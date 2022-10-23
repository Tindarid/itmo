#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <algorithm>
#define MAXN 4000
using namespace std;

int n;
deque<int> d;
int mat[MAXN + 1][MAXN + 1];

int main() {
    ifstream cin("fullham.in");
    ofstream cout("fullham.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        d.push_back(i);
    }
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == '1') {
                mat[i][j] = mat[j][i] = 1;
            }
        }
    }
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        if (mat[d[0]][d[1]] != 1) {
            int j = 2;
            while (mat[d[0]][d[j]] != 1 || mat[d[1]][d[j + 1]] != 1) {
                ++j;
            }
            reverse(d.begin() + 1, d.begin() + j + 1);
        }
        d.push_back(d[0]);
        d.pop_front();
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
