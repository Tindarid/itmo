#include <iostream>
#include <fstream>
using namespace std;

int n = 0, k;
int st[500005];
int sumst[500005];

int main()
{
    ifstream cin("hemoglobin.in");
    ofstream cout("hemoglobin.out");
    cin >> k;
    char temp3 = '+';
    for (int i = 0; i < k; i++)
    {
        int temp = 1; 
        cin >> temp3;
        if (temp3 == '+')
        {
            cin >> temp;
            st[n] = temp;
            n++;
            if (n==1)
                sumst[0] = temp;
            else
                sumst[n-1] = sumst[n-2] + temp;
        }
        else if (temp3 == '-')
        {
            if (n == 1)
                cout << sumst[0] << endl;
            else
                cout << sumst[n-1] - sumst[n-2] << endl;
            n--;
        }
        else if (temp3 == '?')
        {
            cin >> temp;
            if (n == 1 || temp == n)
                cout << sumst[n-1] << endl;
            else
                cout << sumst[n-1] - sumst[n-temp-1] << endl;
        }
    }
    return 0;
}
