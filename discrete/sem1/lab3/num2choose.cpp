#include <iostream>
#include <fstream>
using namespace std;

long long n, k, m;
bool used[40];
long long ans[40];

void printAns() {
    for (int i = 0; i < k; i++)
        cout << ans[i] << " ";
    cout << endl;
}

long long binomi(long long k, long long n) {
    long long res = 1;
    if (k == n)
        return res;
    for (long long i = n; i > n - k; i--)
        res *= i;
    for (long long i = 1; i <= k; i++)
        res /= i;
    return res;
}

void dfs(int a, int last, long long curn) 
{
    if (a == k) {
        printAns();
        exit(0);
    }
    for (int i = last + 1; i <= n; i++)
        if (!used[i]) {
            long long temp = 0;
            for (int j = i + 1; j <= n; j++)
                temp++;
            temp = binomi(k - a - 1, temp);
            if (m < (temp + curn)) {
                ans[a] = i;
                used[i] = true;
                dfs(a + 1, i, curn);
                used[i] = false;
            }
            else {
                curn += temp;            
            }
        }
} 

int main()
{
    freopen("num2choose.in", "r", stdin);
    freopen("num2choose.out", "w", stdout);
    cin >> n >> k >> m;
    dfs(0, 0, 0);
    return 0;
}


