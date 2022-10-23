#include <iostream>
#include <fstream>
using namespace std;

int n, m;
int v[31][31];
bool used[31];

bool dfs (int a, int b)
{
    for (int i = 1; i <= 30; i++)
        if (v[a][i] == 1 && !used[i])
        {
            if (i == b) 
                return true;
            used[i] = true;
            bool temp = dfs(i, b);
            if (temp) return true;
            used[i] = false;
        }
    return false;
}

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n >> m;
    bool flag = false;
    for (int i = 0; i < m; i++)
    {
        int a, b, tempA, tempB;
        cin >> a >> b;
        if (a < 0)
            tempA = -a;
        else
            tempA = a + 15;
        if (b < 0)
            tempB = -b + 15;
        else
            tempB = b;
        v[tempA][tempB] = 1;
        if (b < 0)
            tempB = -b;
        else
            tempB = b + 15;
        if (a < 0)
            tempA = -a + 15;
        else
            tempA = a;
        v[tempB][tempA] = 1;    
    }
    /*for (int i = 1; i <= 30; i++)
    {
        cout << i;
        for (int j = 1; j <= 30; j++)
            if(v[i][j]==1)
                cout << " " << j;
        cout << endl;
    }*/
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 30; j++)
            used[j] = false;
        bool ans1 = dfs(i, i+15);
        for (int j = 1; j <= 30; j++)
            used[j] = false;
        bool ans2 = dfs(i+15, i);
        //cout << i << " " << ans1 << " " << ans2 << endl;
        if (ans1 && ans2) 
        {
            flag = true;
            break;
        }
    }
    if (flag) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
