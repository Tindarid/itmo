#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

double L, t[1002], v[1002], l[1002];
int n;
    
double timeC(double curL)
{
    if (curL > l[n])
        return t[n];
    if (curL < 0) 
        return 0;
    double resTime = 0; int i = 0;
    while (i != n && l[i] < curL)
    {
        i++;
        resTime = t[i] - (l[i]-curL)/v[i];
    }
    return resTime;
        
}

int main()
{
    ifstream cin("trains.in");
    ofstream cout("trains.out");
    double r = 0;
    cin >> L >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i] >> v[i];
        l[i] = v[i] * t[i];
        l[i]+=l[i-1];
        t[i]+=t[i-1];
    }
    for (int i = 0; i <= n; i++)
    {
        if (r < (timeC(l[i]+L) - t[i])) r = timeC(l[i]+L) - t[i];
        if (r < (t[i] - timeC(l[i]-L))) r = t[i] - timeC(l[i]-L);
    }
    cout << setprecision(5) << fixed << r << endl;
    return 0;
}
