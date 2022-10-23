#include <iostream>
#include <vector>
#include <string>
#include <complex>
#define M_PI 3.14159265358979323846
using namespace std;

typedef complex<double> base;
 
int rev(int num, int lgn) {
	int res = 0;
	for (int i = 0; i < lgn; ++i) {
		if (num & (1 << i)) {
			res |= (1 << (lgn - 1 - i));
        }
    }
	return res;
}
 
void fft(vector<base> &a, bool invert) {
	int n = a.size();
	int lgn = 0;
	while ((1 << lgn) < n) {
        ++lgn;
    }
	for (int i = 0; i < n; ++i) {
		if (i < rev(i, lgn)) {
			swap(a[i], a[rev(i, lgn)]);
        }
    }
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert) {
		for (int i = 0; i < n; ++i) {
			a[i] /= n;
        }
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
	n <<= 1;
	fa.resize(n), fb.resize(n);
 
	fft(fa, false),  fft(fb, false);
	for (size_t i = 0; i < n; ++i) {
		fa[i] *= fb[i];
    }
	fft(fa, true);
 
	res.resize(n);
	for (size_t i = 0; i < n; ++i) {
		res[i] = int(fa[i].real() + 0.5);
    }
    int carry = 0;
	for (size_t i = 0; i < n; ++i) {
		res[i] += carry;
		carry = res[i] / 10;
		res[i] %= 10;
	}
}

bool flag;
vector<int> c, d, ans;
string s1, s2;

void in() {
    getline(cin, s1);
    getline(cin, s2);
    bool flag1 = false, flag2 = false;
    if (s1[0] == '-') {
        s1 = s1.substr(1);
        flag1 = true;
    }
    if (s2[0] == '-') {
        s2 = s2.substr(1);
        flag2 = true;
    }
    flag = flag1 ^ flag2;
    for (int i = s1.length() - 1; i >= 0; --i) {
        c.push_back(s1[i] - '0');
    }
    for (int i = s2.length() - 1; i >= 0; --i) {
        d.push_back(s2[i] - '0');
    }
}

void sol() {
    multiply(c, d, ans);
}

void out() {
    if (flag) {
        cout << "-";
    }
    while (ans.back() == 0) {
        ans.pop_back();
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i];
    }
    cout << endl;
}

int main() {
    in();
    if (s1 == "0" || s2 == "0") {
        cout << 0 << endl;
        return 0;
    }
    sol();
    out();
}
