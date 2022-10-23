#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int mas[30];
string str;

int main()
{
    ifstream cin("mtf.in");
    ofstream cout("mtf.out");
    for (int i = 0; i <= 'z' - 'a'; i++)
        mas[i] = i + 1;
    cin >> str;
    for (int i = 0; i < str.length(); i++)
    {
        cout << mas[str[i]- 'a'] << " ";
        if (mas[str[i] - 'a'] != 1) {
            int temp = mas[str[i] - 'a'];
            for (int j = 0; j <= 'z' - 'a'; j++)
                if (mas[j] <= temp)
                    mas[j]++;
            mas[str[i]- 'a'] = 1;
        }
    }
    cout << endl;
    return 0;
}
