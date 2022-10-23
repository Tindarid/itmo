#include <iostream>
#include <fstream>
#include <vector>
#define LL long long
using namespace std;

const LL MOD = 998244353LL;

int n, m;
int ma;
vector<LL> p, q;
vector<LL> sum, mul, divv;

void in() {
    //ifstream cin("input.txt");
    cin >> n >> m;
    ma = max(n, m);
    p.resize(2010, 0);
    q.resize(2010, 0);
    for (int i = 0; i < n + 1; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < m + 1; ++i) {
        cin >> q[i];
    }
}

void sol() {
    //sum
    sum.resize(ma + 1);
    for (int i = 0; i < ma + 1; ++i) {
        sum[i] = (p[i] + q[i]) % MOD;
    }
    //mul
    mul.resize(n + m + 1, 0);
    for (int i = 0; i < n + m + 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            mul[i] = (mul[i] + (p[j] * q[i - j]) % MOD) % MOD;
        }
    }
    //div
    divv.resize(1005, 0);
    vector<LL> ob(1005, 0);
    ob[0] = 1;
    for (int i = 1; i < ob.size(); ++i) {
        for (int j = 1; j <= i; ++j) {
            ob[i] = (ob[i] + (q[j] * ob[i - j]) % MOD) % MOD;
        }
        ob[i] = (-ob[i] + MOD) % MOD; 
    }
    for (int i = 0; i < divv.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            divv[i] = (divv[i] + (p[j] * ob[i - j]) % MOD) % MOD;
        }
    }
}

void out() {
    cout << ma << endl;
    for (int i = 0; i < sum.size(); ++i) {
        cout << sum[i] << " ";
    }
    cout << endl;
    cout << n + m << endl;
    for (int i = 0; i < mul.size(); ++i) {
        cout << mul[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 1000; ++i) {
        cout << divv[i] << " ";
    }
    cout << endl;
}

int main() {
    in();
    sol();
    out();
}
