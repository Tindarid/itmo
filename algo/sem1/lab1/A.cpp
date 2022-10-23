#include <iostream>
#include <fstream>
#define MAXN 100000
using namespace std;

int main()
{
    ifstream cin("isheap.in");
    ofstream cout("isheap.out");
    int n, array[MAXN];
    bool flag = true;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> array[i];
    for(int i = 0; 2*i+2 < n; i++)
        if (array[i] > array[2*i+1] || array[i] > array[2*i+2])
            flag = false;
    cout << (flag?"YES":"NO") << endl;
    return 0;
}
