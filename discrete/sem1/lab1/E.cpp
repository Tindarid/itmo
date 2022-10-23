#include <iostream>
#include <fstream>
#include <string>
#define MAXN 30
#define MAXM 10
using namespace std;

int n;
int perem[MAXN];
bool used[MAXN];
int v[MAXN][MAXM];
bool ansv[MAXN][40];
bool ansTv[MAXN];
int maxPath = 0;
int maxStep = 0;
string ans="";

bool dfs(int ver, int ur)
{
    if (used[ver])
    {
        if (ur > maxPath)
            maxPath = ur;
        return ansTv[ver];
    }
    used[ver] = true;
    int tecAns = 0;
    for (int i = 1; i <= perem[ver]; i++) {
        if (!used[v[ver][i]]) {           
            ansTv[v[ver][i]] = dfs(v[ver][i], ur+1);
        }  
        if (ansTv[v[ver][i]])
            tecAns += (1<<((perem[ver]-i+1)-1));            
    }
    if (ur > maxPath)
        maxPath = ur;
    return ansv[ver][tecAns];
}
int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        if (m == 0) {
            maxStep++;
            continue;
        }
        perem[i] = m;
        for (int j = 1; j <= m; j++) {
            cin >> v[i][j];
        }
        for (int j = 0; j < (1<<m); j++) {
            cin >> ansv[i][j];
        }
    }
    maxStep = (1<<maxStep);
    for (int i = 0; i < maxStep; i++)
    {
        int tempi = i;
        for (int j = 1; j <= n; j++)
            used[j] = false;
        for (int j = n; j >= 1; j--)
            if (perem[j] == 0)
            {
                used[j] = true;
                int temp = (tempi - ((tempi>>1)<<1));
                ansTv[j] = temp;
                tempi = (tempi>>1);
            }
        if (dfs(n, 0))
            ans+='1';
        else
            ans+='0';
    }
    cout << maxPath+1 << endl << ans << endl;
    //system("pause");
    return 0;
}
