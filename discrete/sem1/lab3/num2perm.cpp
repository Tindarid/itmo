#include <iostream>
#include <fstream>
using namespace std;

long long n, k;
bool used[20];
long long ans[20];

void printAns() {
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << endl;
}

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
        printAns();
        exit(0);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i])
        {
            if (k < (fact(n - a - 1) + curn)) {
                ans[a] = i;
                used[i] = true;
                dfs(a + 1, curn);
                used[i] = false;
            }
            else
                curn += fact(n - a - 1);
        }
    }
} 

int main()
{
    freopen("num2perm.in", "r", stdin);
    freopen("num2perm.out", "w", stdout);
    cin >> n >> k;
    dfs(0, 0);
    return 0;
}

