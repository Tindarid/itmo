#include <iostream>
#include <string>
#include <vector>
#define MAXN 2000005
using namespace std;

string s, p, t;
int z[MAXN];

void sol() {
    int len = s.length();
    for (int i = 1, l = 0, r = 0; i < len; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < len && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r + 1) {
            r = i + z[i] - 1;
            l = i;
        }
    }
}

int main() {
    cin >> p >> t;
    s = p + "#" + t;
    sol();
    int temp = p.length();
    vector<int> ans;
    for (int i = temp + 1; i < s.length(); ++i) {
        if (z[i] == temp) {
            ans.push_back(i - temp);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
