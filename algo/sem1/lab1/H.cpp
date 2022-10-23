#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int n, k;
int mas[30000005];

int findk(int l, int r)
{
    int i = l, j = r, x = mas[l + rand()%(r-l)];
    while (i <= j)
    {
        while (mas[i] < x) i++;
        while (mas[j] > x) j--;
        if (i <= j)
        {
            int temp = mas[i];
            mas[i] = mas[j];
            mas[j] = temp;
            i++;
            j--;
        }
    }
    if (l < j && k <= j)
        findk(l, j);
    if (r > i && k >= i)
        findk(i, r);
    return mas[k];
}
int main()
{
    ifstream cin("kth.in");
    ofstream cout("kth.out");
    srand(time(0));
    int A, B, C;
    cin >> n >> k;
    k--;
    cin >> A >> B >> C >> mas[0] >> mas[1];
    for (int i = 2; i < n; i++)
        mas[i] = A * mas[i-2] + B * mas[i-1] + C;
    cout << findk(0, n-1) << endl;
    
    return 0;
}
