#include <iostream>
#include <fstream>
using namespace std;

int n, w, v;
int cows[50];
bool valid[600005];
int dp[600005];
int last[600005];
int moreValid[600005];

int getOnes(int k) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if ((k >> i) & 1) {
            res++;
        }
    }
    return res;
}

int main() {
    ifstream cin("skyscraper.in");
    ofstream cout("skyscraper.out");
    cin >> n >> w;
	for(int i = 0; i < n; i++){
        cin >> cows[i];
	}

    for(int i = (1 << n) - 1; i >= 0; i--) {
        int curSum = 0, t=0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                curSum += cows[j];
                if (curSum > w) {
                    t=1;
                    break;
                }
            }
        }
        if (t==0) {
            valid[i] = true;
            dp[i] = 1;
            last[i] = i;
            int j;
            for (j = 0; j < n; j++) {
                if (!((i >> j) & 1) && valid[i + (1 << j)]) {
                    break;
                }
            } 
            if (j == n) {
                moreValid[v++] = i;
            }
        }
    }

    for (int i = 1; i < (1 << n); i++) {
        if (valid[i]) {
            continue;
        }
        last[i] = (i & -i);
        dp[i] = n;

        int k = getOnes(i);
        if (v > (1 << (k - 1))) {
            int r = (i ^ last[i]), p = (i & -i), p2 = 0;
            do {
                if ((valid[(p2 | p)]) && (dp[(r ^ p2)] + 1 < dp[i])) {
                    dp[i] = dp[r ^ p2] + 1;
                    last[i] = p2 + p;
                }
                p2 = (r & (p2 - r));
            } while (p2);
        } else {
            for (int j = v - 1; j >= 1; j--) {
                k = i & moreValid[j];
                if (dp[i] <= dp[i ^ k] + 1) {
                    continue;
                }
                last[i] = k;
                dp[i] = dp[i ^ k] + 1;
            } 
        }
    }

    int ans = (1 << n) - 1;
    cout << dp[ans] << endl;
    while (ans > 0) {
        cout << getOnes(last[ans]);
        for (int i = 0; i < n; i++) {
            if ((last[ans] >> i) & 1) {
                cout << " " << i + 1;
            }
        }
        ans = (ans ^ last[ans]);
        cout << endl;
    }
    return 0;
}
