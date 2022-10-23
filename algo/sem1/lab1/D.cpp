#include <iostream>
#include <fstream>
using namespace std;

void swapMet(int &a, int &b)
{
    int temp = a;
    a = b;
    b = a;
    return;
}

int main()
{
    ifstream cin("radixsort.in");
    ofstream cout("radixsort.out");
    char strings[1005][1005], temp;
    int mas[1005];
    int n, m, k;
    //in
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> strings[i][j];
    }
    for (int i = 0; i < n; i++)
        mas[i] = i;
    //radixsort
    for (int p = m - 1; p >= m - k; p--)
    {
        int cnt[1005], mas2[1005], pos[1005];
        for (int i = 0; i < 1005; i++)
            cnt[i] = 0, pos[i] = 0;
        for (int i = 0; i < n; i++)
            cnt[strings[mas[i]][p]]++;
        for (int i = 1; i < 1005; i++)
            pos[i] = cnt[i-1] + pos[i-1];
        for (int i = 0; i < n; i++)
        {
            mas2[pos[strings[mas[i]][p]]]=mas[i];
            pos[strings[mas[i]][p]]++;
        }
        for (int i = 0; i < n; i++)
            mas[i] = mas2[i];
        
    }
    //out
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << strings[mas[i]][j];
        cout << endl;
    }
    return 0;
}
