#include <iostream>
#include <fstream>
using namespace std;

int n, k;
bool used[20];
int ans[20];

void dfs(int a, int last) 
{
    if (a == k + 1)
    {
        for (int i = 1; i <= k; i++)
            cout << ans[i] << " ";
        cout << endl;
        return;
    }
    for (int i = last + 1; i <= n; i++)
        if (!used[i])
        {
            ans[a] = i;
            used[i] = true;
            dfs(a + 1, i);
            used[i] = false;
        }
} 

int main()
{
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);
    cin >> n >> k;
    dfs(1, 0);
    return 0;
}

