#include <iostream>
#include <fstream>
using namespace std;

int n;
int ans[25];

void dfs(int ind, int am, int bm) 
{
    if (am < bm)
        return;
    if (ind == 2 * n + 1) {
        for (int i = 1; i <= 2 * n; i++)
            cout << ((ans[i] == -1)?")":"(");
        cout << endl;
        return;
    }
    if (am != n) 
    {
        ans[ind] = 1;
        dfs(ind + 1, am + 1, bm);
    }
    if (bm != n)
    {
        ans[ind] = -1;
        dfs(ind + 1, am, bm + 1);
    }
}

int main()
{
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    cin >> n;
    dfs(1, 0, 0);
    return 0;
}

