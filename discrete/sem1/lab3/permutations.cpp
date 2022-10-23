#include <iostream>
#include <fstream>
using namespace std;

int n;
bool used[10];
int ans[10];

void dfs(int a) 
{
    if (a == n + 1)
    {
        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!used[i])
        {
            ans[a] = i;
            used[i] = true;
            dfs(a + 1);
            used[i] = false;
        }
} 

int main()
{
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
    cin >> n;
    dfs(1);
    return 0;
}


