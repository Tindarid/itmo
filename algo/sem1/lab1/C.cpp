#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#define MAXN 1000000
using namespace std;

int n, arr[MAXN];

void mysort (int l, int r)
{
    int x = arr[l+rand()%(r-l+1)], i = l, j = r;
    while (i <= j)
    {
        while (arr[i]<x) i++;
        while (arr[j]>x) j--;
        if (i<=j)
        {
            int temp = arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++;
            j--;
        }      
    }
    if (l < j)
        mysort(l, j);
    if (r > i)
        mysort(i, r);
    return;
}
int main()
{
    ifstream cin("sort.in");
    ofstream cout("sort.out");
    srand(time(0));
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    mysort(0, n-1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
