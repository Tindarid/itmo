#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string a;
char b[200002];
int n = 0;
int main()
{
    ifstream cin("decode.in");
    ofstream cout("decode.out");
    cin >> a;
    for (int i = 0; i < a.length(); i++)
    {
        if (n == 0)
        {
            b[n]=a[i];
            n++;
        }
        else if (b[n-1]==a[i])
            n--;
        else
        {
            b[n]=a[i];
            n++;
        }
    }
    for (int i = 0; i < n; i++)
        cout << b[i];
    cout << endl;
    return 0;
}
            
    
