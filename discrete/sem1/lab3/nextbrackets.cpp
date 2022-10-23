#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int n;
string ans;

int main()
{
    freopen("nextbrackets.in", "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
    cin >> ans;
    n = ans.length();
    int tempi = -1, tempam = 0, tempbm = 0;
    for (int i = 0, am = 0, bm = 0, balanse = 0; i < n - 1; i++) {
        if ((ans[i] == '(') && (balanse > 0))
            tempi = i, tempam = am, tempbm = bm;
        if (ans[i] == '(') 
            am++, balanse++;
        else
            bm++, balanse--;
    } 
    if (tempi == -1) {
        cout << '-' << endl;
        return 0;
    }
    for (int i = 0; i < tempi; i++)
        cout << ans[i];
    cout << ')';
    for (int i = 0; i < n/2 - tempam; i++)
        cout << '(';
    for (int i = 0; i < n/2 - tempbm - 1; i++)
        cout << ')';
    cout << endl;
    return 0;
}

