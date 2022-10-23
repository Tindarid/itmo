#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool solution(string s) {
    // 1 2 3 4
    if (s.length() < 10) {
        return true;
    }
    // 5
    if (s.length() == 10) {
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == '0') {
                return true;
            }
        }
        return false;
    }

    bool mas[6][6];
    int k = 0;
    for (int i = 1; i < 6; ++i) {
        for (int j = 0; j != i; ++j) {
            if (s[k] == '0') {
                mas[j][i] = mas[i][j] = false;
            } else {
                mas[j][i] = mas[i][j] = true;
            }
            ++k;
        }
    }
    for (int i = 0; i < 6; ++i) {
        mas[i][i] = false;
    }

    int st[6];
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        st[i] = 0;
        for (int j = 0; j < 6; ++j) {
            if (mas[i][j]) {
                st[i]++;
            }
        }
        sum += st[i];
    }

    if (sum > 24) {
        return false;
    }
    // k 5 without check
    for (int i = 0; i < 6; ++i) {
        if (sum - 2 * st[i] == 20) {
            return false;
        }
    }
    // k 5 sh check
    for (int i = 0; i < 6; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            for (int p = j + 1; p < 6; ++p) {
                if (mas[i][p] && mas[p][j] && !mas[i][j] && st[p] == 2) {
                    if (sum >= 22) {
                        return false;

                    }
                }
                if (mas[p][i] && mas[i][j] && !mas[p][j] && st[i] == 2) {
                    if (sum >= 22) {
                        return false;
                    }
                }
                if (mas[i][j] && mas[j][p] && !mas[i][p] && st[j] == 2) {
                    if (sum >= 22) {
                        return false;
                    }
                }
            }
        }
    }
    // k 3 3 check
    for (int i = 0; i < 6; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            for (int p = j + 1; p < 6; ++p) {
                bool flag = true;
                for (int v = 0; v < 6; ++v) {
                    if (v != i && v != j && v != p) {
                        if (!mas[i][v] || !mas[j][v] || !mas[p][v]) {
                            flag = false;
                        }
                    }
                }
                if (flag) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ifstream cin("planaritycheck.in");
    ofstream cout("planaritycheck.out");
    int k;
    cin >> k;
    string s;
    getline(cin, s);
    for (int i = 0; i < k; ++i) {
        getline(cin, s);
        if (solution(s)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
