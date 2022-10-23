#include <iostream>
#include <fstream>
#define MAXN 100000
using namespace std;

int main()
{
    ifstream cin("binsearch.in");
    ofstream cout("binsearch.out");
    int n, m, ints[MAXN];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> ints[i];
    cin >> m;
    for (int j = 0; j < m; j++)
    {
        int ans1 = -2, ans2 = -2, a;
        cin >> a;
        //left
        int l = -1, r = n, c = 0;
        while (r - l > 1)
        {
            c = (r+l)/2;
            if (ints[c] < a)
                l = c;
            else
                r = c;
        }
        if (ints[r]==a)
            ans1 = r;
        l = -1, r = n;
        //right
        while (r - l > 1)
        {
            c = (r+l)/2;
            if (ints[c] <= a)
                l = c;
            else
                r = c;
        }
        if (ints[l]==a)
            ans2 = l;
        cout << ans1+1 << " " << ans2+1 << endl;
    }
    return 0;
}
