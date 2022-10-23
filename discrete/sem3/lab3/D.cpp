#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct myset {
    int size;
    int s;
    myset(int a, int b) : size(a), s(b) {

    }
};

int n, m;
bool indep[20000];
vector<myset> sets;

bool check_small(int a) {
    if (!indep[a]) {
        return false;
    }
    bool ans = true;
    for (int i = 0; i < n; ++i) {
        if ((a & (1 << i))) {
            ans &= check_small(a ^ (1 << i));
        }
    }
    return ans;
}

bool check1() {
    return indep[0];
}

bool check2() {
    bool ans = true;
    for (int i = 0; i < m; ++i) {
        ans &= check_small(sets[i].s);
    }
    return ans;
}

bool check3() {
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (sets[i].size > sets[j].size) {
                int temp = sets[i].s & ~sets[j].s;
                bool flag = false;
                for (int b = 0; b < n; ++b) {
                    if ((temp & (1 << b))) {
                        if (indep[sets[j].s | (1 << b)]) {
                            flag = true;
                            break;
                        }
                    }
                }
                if (!flag) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool comp(myset &a, myset &b) {
    return a.size > b.size;
}

int main() {
    ifstream cin("check.in");
    ofstream cout("check.out");
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int amount;
        cin >> amount;
        int ind = 0;
        for (int j = 0; j < amount; ++j) {
            int e;
            cin >> e;
            ind |= (1 << (--e));
        }
        sets.push_back(myset(amount, ind));
        indep[ind] = true;
    }
    sort(sets.begin(), sets.end(), comp);
    if (check1() && check2() && check3()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
