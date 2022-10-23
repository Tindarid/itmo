#include <iostream>
#include <fstream>
using namespace std;

int n, countc = -1;
int ansin[100005];

void dfs(int sum, int amount, int last)
{
    if (sum == n) 
    {
        for (int i = 0; i < amount; i++) 
            cout << ansin[i] << ((i == amount - 1)?"\n":"+");
        exit(0);
    }
    for (int i = last; i <= n; i++)
        if (sum + i <= n) {
            ansin[amount] = i;
            dfs(sum + i, amount + 1, i);
        }
}

int main()
{
    freopen("nextpartition.in", "r", stdin);
    freopen("nextpartition.out", "w", stdout);
    cin >> n;
    do {
        char temp;
        cin >> temp;
        countc++;
    } while (cin >> ansin[countc]);
    if (countc == 1) {
        cout << "No solution\n";
        return 0;
    }
    do {
        ansin[countc - 2]++;
        ansin[countc - 1]--;
    } while ((ansin[countc - 1] < ansin[countc - 2]) && (ansin[countc - 1] > 0));
    cout << n << "=";
    n = ansin[countc - 1];
    dfs(0, countc - 1, ansin[countc - 2]); 
    return 0;
}


