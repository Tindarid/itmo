#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string mas[10100], mas2[10100];

int main()
{
    ifstream cin("bwt.in");
    ofstream cout("bwt.out");
    cin >> mas[0];
    int n = mas[0].length();
    for (int i = 1; i < n; i++) {
        mas[i] = mas[0].substr(i, n-i) + mas[0].substr(0, i);
    }

    for (int p = n - 1; p >= 0; p--)
    {
        int count[300], pos[300];
        for (int i = 0; i < 300; i++)
            count[i] = 0, pos[i] = 0;
        for (int i = 0; i < n; i++)
            count[mas[i][p] - 'a']++;
        for (int i = 1; i < 300; i++)
            pos[i] = pos[i - 1] + count[i - 1];
        for (int i = 0; i < n; i++)
        {
            mas2[pos[mas[i][p] - 'a']] = mas[i];
            pos[mas[i][p] - 'a']++;
        }
        for (int i = 0; i < n; i++)
            mas[i] = mas2[i];
    }
    
    for (int i = 0; i < n; i++)
        cout << mas[i][n-1];
    cout << endl;
    return 0;
}
