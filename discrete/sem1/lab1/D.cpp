#include <iostream>
#include <fstream>
#include <string>
using namespace std;

long long n, s;
long long number[6];
string numberBin[6];
string ourNumber;

string toBinary(long long temp)
{
    string ans = "";
    while (temp > 0)
    {
        if (temp % 2)
            ans = '1' + ans;
        else
            ans = '0' + ans;
        temp /= 2;
    }
    while (ans.length() < 32)
        ans = '0' + ans;
    return ans;
        
}

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    string ans = "";
    long long temp = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> number[i];
        numberBin[i] = toBinary(number[i]);
    }
    cin >> s;
    ourNumber = toBinary(s);
    for (int i = 0; i < 32; i++)
    {
        long long temp2 = (1<<32)-1;
        if (ourNumber[i] == '0')
            continue;
        string tempStr = "(";
        for (int j = 1; j <= n; j++)
        {
            if (numberBin[j][i] == '0')
                tempStr += '~';
            tempStr += (j + '0');
            if (j!=n)
                tempStr += '&';
            if (numberBin[j][i] == '0')
                temp2 = (temp2 & ~number[j]); 
            else
                temp2 = (temp2 & number[j]); 
        }
        tempStr += ")";
        ans += tempStr;
        ans += '|';
        temp = (temp2 | temp);
    }
    if (ans[ans.length()-1] == '|')
        ans = ans.substr(0, ans.length() - 1);
    if (s == 0)
    {
        cout << "1&~1\n";
        return 0;
    }
    if (temp == s)
        cout << ans << endl;
    else
        cout << "Impossible\n";
    return 0;
}
