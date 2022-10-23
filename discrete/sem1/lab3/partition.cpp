#include <iostream>
#include <fstream>
using namespace std;

int n;
int ans[50];

void dfs(int sum, int amount, int last)
{
    if (sum == n) 
    {
        for (int i = 0; i < amount; i++) 
            cout << ans[i] << ((i == amount - 1)?"\n":"+");
        return;
    }
    for (int i = last; i <= n; i++)
        if (sum + i <= n) {
            ans[amount] = i;
            dfs(sum + i, amount + 1, i);
        }
}

int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n;
    dfs(0, 0, 1);
    return 0;
}

