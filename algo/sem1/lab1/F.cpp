#include <iostream>
#include <fstream>
#define MAXN 100000
using namespace std;

int absol (int a)
{
    if (a < 0) return -a;
    else return a;
}

int main()
{
    int n, m, sh[MAXN], tr[MAXN], ans1 = 0, ans2 = 0;
    ifstream cin("style.in");
    ofstream cout("style.out");
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> sh[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> tr[i];   
    int j = 0;
    for (int i = 0; i < n; i++)
        while (j < m)
        {
            if (absol(tr[j] - sh[i]) < absol(tr[ans1] - sh[ans2]))
                ans1 = j, ans2 = i;
            if (tr[j] >= sh[i])
                break;
            j++;
        }
    cout << sh[ans2] << " " << tr[ans1] << endl;
    return 0;
}
