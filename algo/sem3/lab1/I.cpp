#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define MAXN 10000
using namespace std;

vector<pair<int, int>> v;
vector<double> minEdge;
vector<int> endEdge;
bool used[MAXN];

double calc(pair<int, int> a, pair<int, int> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        v.push_back(make_pair(x, y));
    }
    double maxEdge = calc(make_pair(MAXN, MAXN), make_pair(-MAXN, -MAXN)) + 1;
    for (int i = 0; i < n; ++i) {
        minEdge.push_back(maxEdge);
        endEdge.push_back(-1);
    }
    double ans = 0;
    minEdge[0] = 0;
    for (int i = 0; i < n; ++i) {
        int cur = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                if (cur == -1 || (minEdge[j] < minEdge[cur])) {
                    cur = j;
                }
            }
        }
        used[cur] = true;
        if (endEdge[cur] != -1) {
            ans += calc(v[cur], v[endEdge[cur]]);
        }
        for (int j = 0; j < n; ++j) {
            double temp = calc(v[cur], v[j]);
            if (temp < minEdge[j]) { 
                minEdge[j] = temp;
                endEdge[j] = cur;
            }
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}

