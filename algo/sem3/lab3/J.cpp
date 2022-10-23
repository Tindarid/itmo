#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAXN 400005
using namespace std;

string s;
int len;
int lo[MAXN];
int sufmas[MAXN];
int cl[20][MAXN];
int lcp[MAXN];

bool comp(int i, int j, int l) {
    int le = lo[l];
    pair<int, int> a(cl[le][i], cl[le][i + l - (1 << le)]);
    pair<int, int> b(cl[le][j], cl[le][j + l - (1 << le)]);
    return a == b;
}

int find_lcp_bin(int i, int j) {
    int l = 0, r = len;
    int ans = 0;
    while (l < r) {
        int m = (l + r) / 2;
        if (comp(i, j, m)) {
            l = m + 1;
            ans = m;
        } else {
            r = m;
        }
    }
    return ans;
}

void find_lcp() {
    for (int i = 1; i < len - 1; ++i) {
        lcp[i] = find_lcp_bin(sufmas[i], sufmas[i + 1]);
    }
}

void prep() {
    int cur = 0;
    for (int i = 1; i <= len; ++i) {
        if ((1 << (cur + 1)) >= i) {
            lo[i] = cur;
        } else {
            cur++;
            lo[i] = cur;
        }
    }
}

void find_sufmas() {
    char sh = 'a' - 1;
    string str = s + sh;
    int a_size = 27;
    int cnt[MAXN];
    //0
    for (int i = 0; i < a_size; ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < len; ++i) {
        cnt[str[i] - sh]++;
    }
    for (int i = 1; i < a_size; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < len; ++i) {
        sufmas[--cnt[str[i] - sh]] = i;
    }
    int cla = 0;
    cl[0][sufmas[0]] = cla;
    for (int i = 1; i < len; ++i) {
        if (str[sufmas[i]] != str[sufmas[i - 1]]) {
            cla++;
        }
        cl[0][sufmas[i]] = cla;
    }
    //1 ... n - 1
    int pp[MAXN];
    for (int l = 0; (1 << l) < len; ++l) {
        for (int i = 0; i < len; ++i) {
            pp[i] = sufmas[i] - (1 << l);
            if (pp[i] < 0) {
                pp[i] += len;
            }
        }
        for (int i = 0; i < cla + 1; ++i) {
            cnt[i] = 0;
        }
        for (int i = 0; i < len; ++i) {
            cnt[cl[l][pp[i]]]++;
        }
        for (int i = 1; i < cla + 1; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = len - 1; i >= 0; --i) {
            sufmas[--cnt[cl[l][pp[i]]]] = pp[i];
        }
        cla = 0;
        cl[l + 1][sufmas[0]] = cla;
        for (int i = 1; i < len; ++i) {
            int m1 = (sufmas[i] + (1 << l)) % len;
            int m2 = (sufmas[i - 1] + (1 << l)) % len;
            if (cl[l][sufmas[i]] != cl[l][sufmas[i - 1]] || cl[l][m1] != cl[l][m2]) {
                cla++;
            }
            cl[l + 1][sufmas[i]] = cla;
        }
    }
}

int main() {
    ifstream cin("array.in");
    ofstream cout("array.out");
    cin >> s;
    len = s.length() + 1;
    find_sufmas();
    prep();
    find_lcp();
    for (int i = 1; i < len; ++i) {
        cout << sufmas[i] + 1 << " ";
    }
    cout << endl;
    for (int i = 1; i < len - 1; ++i) {
        cout << lcp[i] << " ";
    }
    cout << endl;
}
