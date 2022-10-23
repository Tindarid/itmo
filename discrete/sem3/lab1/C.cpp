#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> ans;

bool gr(int a, int b) {
    cout << "1 " << a << " " << b << endl;
    cout.flush();
    string ans;
    cin >> ans;
    if (ans == "YES") {
        return true;
    } else {
        return false;
    }
}

void merge(int l, int m, int r) {
    vector<int> temp;
    int l1 = l, m1 = m;
    while ((l1 < m) && (m1 < r)) {
        if (gr(ans[l1], ans[m1])) {
            temp.push_back(ans[l1]);
            l1++;
        } else {
            temp.push_back(ans[m1]);
            m1++;
        }
    }
    while (l1 < m) {
        temp.push_back(ans[l1]);
        l1++;
    } 
    while (m1 < r) {
        temp.push_back(ans[m1]);
        m1++;
    }
    for (int i = l; i < r; ++i) {
        ans[i] = temp[i - l];
    }
}

void msort(int l, int r) {
    if (l + 1 >= r) {
        return;
    }
    int m = (l + r) / 2;
    msort(l, m);
    msort(m, r);
    merge(l, m, r);
}

bool checkGF() {
    for (int i = 0; i < ans.size() - 1; ++i) {
        if (gr(ans[i + 1], ans[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ans.push_back(i + 1);
    }
    msort(0, n);
    if (checkGF()) {
        cout << "0 ";
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << " ";
        }
    } else {
        for (int i = 0; i < n + 1; ++i) {
            cout << "0 ";
        }
    }
    cout << endl;
    cout.flush();
    return 0;
}
