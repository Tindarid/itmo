#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string s;
char st[20000];
int n = 0;
bool flag = true;

int main()
{
    ifstream cin("brackets.in");
    ofstream cout("brackets.out");
    cin >> s;
    for (int i = 0; i < s.length(); i++) 
    {
        if (n == 0)
        {
            st[n] = s[i];
            n++;
        }
        else if (st[n-1] == '(' && s[i] == ')' || st[n-1] == '[' && s[i] == ']' || st[n-1] == '{' && s[i] == '}')
            n--;
        else
        {
            st[n] = s[i];
            n++;
        }
    }
    if (n != 0) flag = false;
    if (flag) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
