#include <iostream>
#include <fstream>
#define MAXN 70000
using namespace std;

int main()
{
    //ifstream cin("antiqs.in");
    //ofstream cout("antiqs.out");
    int n, mas[MAXN];
    cin >> n;
    for (int i = 0; i < n; i++)
        mas[i] = i+1;
    for (int i = 0; i < n; i++)
        swap(mas[i], mas[i/2]);
    for (int i = 0; i < n; i++)
        cout << mas[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}
