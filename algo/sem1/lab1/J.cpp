#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

double A;
int n;

int main()
{
    //ifstream cin("garland.in");
    //ofstream cout("garland.out");
    cin >> n >> A;
    double l = -1, r = A+1, ans = 1;
    double m;
    for (int i = 0; i < 200; i++)
    {
        m = (l + r)/2.0;
        bool flag = true;
        double a1 = A, a2 = m;
        for (int j = 3; j <= n; j++)
        {
            double temp = a2;
            a2 = 2 * a2 - a1 + 2.0;
            a1 = temp;
            if (a2 <= 0) flag = false;
            if (j == n) ans = a2;
        }
        if (flag)
            r = m;
        else 
            l = m;
        
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}
