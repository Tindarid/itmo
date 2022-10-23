#include <iostream>
#include <fstream>
using namespace std;

int n, k;
int ans[100005];

void dfs(int a, int last) 
{
    if (a == k)
    {
        for (int i = 0; i < k; i++)
            cout << ans[i] << " ";
        cout << endl;
        exit(0);
    }
    for (int i = last + 1; i <= n; i++) {
            ans[a] = i;
            dfs(a + 1, i);
    }
} 

int main()
{
    freopen("nextchoose.in", "r", stdin);
    freopen("nextchoose.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < k; i++)
        cin >> ans[i];
    for (int i = k - 1; i >= 0; i--)
        if (n - ans[i] >= k - i)
            dfs(i, ans[i]);
    cout << -1 << endl;
    return 0;
}

