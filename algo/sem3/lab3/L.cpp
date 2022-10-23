#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAXN 100005
using namespace std;

string s;
int len;
int lo[MAXN];
int sufmas[MAXN];
int cl[20][MAXN];
int last;

void find_sufmas() {
    char sh = 32;
    string str = s;
    int a_size = 126 - 32 + 1;
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
        last = l + 1;
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
    ifstream cin("shifts.in");
    ofstream cout("shifts.out");
    int k;
    cin >> s >> k;
    k--;
    len = s.length();
    find_sufmas();
    for (int i = 0; i < len; ++i) {
        if (k == cl[last][i]) {
            for (int j = i; j < len; ++j) {
                cout << s[j];
            }
            for (int j = 0; j < i; ++j) {
                cout << s[j];
            }
            cout << endl;
            return 0;
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}
