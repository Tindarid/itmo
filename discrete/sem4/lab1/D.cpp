#include <iostream>
#include <string>
#include <vector>
#define MAXN 7
#define LL long long
using namespace std;

vector<LL> mul(const vector<LL>& a, const vector<LL>& b) {
    vector<LL> res(MAXN, 0);
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j <= i; ++j) {
            res[i] += a[j] * b[i - j];
        }
    }
    return res;
}

vector<LL> b_pow(const vector<LL>& a, LL st) {
    vector<LL> res(MAXN, 0);
    vector<LL> b = a;
    res[0] = 1;
	while (st) {
		if (st & 1LL) {
			res = mul(b, res);
        }
		b = mul(b, b);
		st >>= 1;
	}
	return res;
}

struct Expr { 
    Expr() {}
    virtual vector<LL> eval() {
        return vector<LL>();
    }
};

struct B : Expr { 
    vector<LL> eval() {
        vector<LL> res(MAXN, 0);
        res[1] = 1;
        return res;
    }
};

struct List : Expr { 
    Expr* inner; 
    List(Expr* e) { inner = e; } 
    vector<LL> eval() {
        vector<LL> res(MAXN, 0);
        res[0] = 1;
        vector<LL> temp[MAXN];
        temp[1] = inner->eval();
        temp[1][0] = 0;
        for (int i = 2; i < MAXN; ++i) {
            temp[i] = mul(temp[1], temp[i - 1]);
        }
        for (int i = 1; i < MAXN; ++i) {
            for (int j = 1; j < MAXN; ++j) {
                res[i] += temp[j][i];
            }
        }
        return res;
    }
};

vector<LL> prepp[MAXN];

struct Set : Expr { 
    Expr* inner; 
    Set(Expr* e) { inner = e; } 
    vector<LL> eval() {
        vector<LL> res(MAXN, 0);
        res[0] = 1;
        vector<LL> a = inner->eval();
        for (int n = 1; n < MAXN; ++n) {
            res = mul(res, b_pow(prepp[n], a[n]));
        }
        return res;
    }
};

struct Pair : Expr { 
    Expr *a, *b;
    Pair(Expr* e1, Expr* e2) { a = e1; b = e2; } 
    vector<LL> eval() {
        return mul(a->eval(), b->eval());
    }
};

Expr* parse(const string& s, int l, int r) {
    if (s[l] == 'L') {
        return new List(parse(s, l + 2, r - 1));
    } else if (s[l] == 'S') {
        return new Set(parse(s, l + 2, r - 1));
    } else if (s[l] == 'P') {
        int balance = 0, i;
        for (i = l; i < r; ++i) {
            if (balance == 1 && s[i] == ',') {
                break;
            }
            if (s[i] == '(') {
                balance++;
            } else if (s[i] == ')') {
                balance--;
            }
        }
        return new Pair(parse(s, l + 2, i), parse(s, i + 1, r - 1));
    } else {
        return new B();
    }
}

int main() {
    string s;
    cin >> s;

    prepp[1] = {1, 1, 1, 1, 1, 1, 1};
    prepp[2] = {1, 0, 1, 0, 1, 0, 1};
    prepp[3] = {1, 0, 0, 1, 0, 0, 1};
    prepp[4] = {1, 0, 0, 0, 1, 0, 0};
    prepp[5] = {1, 0, 0, 0, 0, 1, 0};
    prepp[6] = {1, 0, 0, 0, 0, 0, 1};

    Expr* parsed = parse(s, 0, s.length());
    vector<LL> ans = parsed->eval();

    for (int i = 0; i < MAXN; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
