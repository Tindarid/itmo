#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string s;
int mas[1000]; int n = 0;
int main()
{
    ifstream cin("postfix.in");
    ofstream cout("postfix.out");
    getline(cin, s);
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '*' || s[i] == '+' || s[i] == '-')
        {
            int temp1 = mas[n-1], temp2 = mas[n-2], temp3 = 0;
            if (s[i] == '*')
                temp3 = temp1 * temp2;
            else if (s[i] == '-')
                temp3 = temp2 - temp1;
            else
                temp3 = temp2 + temp1;
            n--;
            mas[n-1] = temp3;
        }
        else if (s[i] >= '1' && s[i] <= '9')
            mas[n++] = s[i] - '0';
    }           
    cout << mas[n-1] << endl;
    return 0;
}
