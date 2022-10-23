#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int n;
vector <string> codes;
string temp;

void get_code(int a) 
{
    if (a == n) {
        codes.push_back(temp);
        return;
    }  
    temp[a] = '0';
    get_code(a + 1);
    if (a == 0 || temp[a - 1] == '0')
    {
        temp[a] = '1';
        get_code(a + 1);
    }
}

int main()
{
    freopen("vectors.in", "r", stdin);
    freopen("vectors.out", "w", stdout);
    cin >> n;
    temp.resize(n);
    get_code(0);
    cout << codes.size() << endl;
    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;
    return 0;
}

