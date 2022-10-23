#include <iostream>
#include <fstream>
using namespace std;

long long n;
bool used[20];
long long ans[20];

long long fact(long long temp) {
    if (temp < 0)
        return 0;
    long long ans = 1;
    for (long long i = temp; i >= 2; i--)
        ans *= i;
    return ans;
}

void dfs(long long a, long long curn) 
{
    if (a == n) {
        cout << curn << endl;
        exit(0);
    }
    for (int i = 1; i <= n; i++) {
        if (i == ans[a]) {
            used[i] = true;
            dfs(a + 1, curn);
        }
        if (!used[i]) {
            curn += fact(n - a - 1);
        }
    }
} 

int main()
{
    freopen("perm2num.in", "r", stdin);
    freopen("perm2num.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> ans[i];
    dfs(0, 0);
    return 0;
}


