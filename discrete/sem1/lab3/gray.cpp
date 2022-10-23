#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int n;
vector <string> codes;

int main()
{
    freopen("gray.in", "r", stdin);
    freopen("gray.out", "w", stdout);
    cin >> n;
    codes.push_back("");
    for (int i = 0; i < n; i++)
    {
        int tempn = codes.size();
        for (int j = tempn - 1; j >= 0; j--)
        {
            codes.push_back("1" + codes[j]);            
            codes[j] = ("0" + codes[j]); 
        }
    }
    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;
    return 0;
}
