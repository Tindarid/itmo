#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using task = pair<int, int>;

int n;
long long ans;
vector<task> q;
set<int> open_space;

bool cmp(task a, task b) { 
    return a.second > b.second;
}

int main() {
    ifstream cin("schedule.in");
    ofstream cout("schedule.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int d, w;
        cin >> d >> w;
        q.push_back(make_pair(d, w));
    }
    sort(q.begin(), q.end(), cmp);
    for (int i = 1; i <= n; ++i) {
        open_space.insert(i);
    }
    for (int i = 0; i < n; ++i) {
        int d = q[i].first;
        int w = q[i].second;
        auto check = open_space.upper_bound(d);
        if (d == 0 || check == open_space.begin()) {
            ans += w;
            check = open_space.end();
        }
        open_space.erase(--check);
    }
    cout << ans << endl;
    return 0;
}
