#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int n, k;
vector <string> codes;

int main()
{
    freopen("telemetry.in", "r", stdin);
    freopen("telemetry.out", "w", stdout);
    cin >> n >> k;
    codes.push_back("");
    for (int i = 0; i < n; i++)
    {
        int tempn = codes.size();
        for (int p = 1; p < k; p++) {
            if (p % 2 == 0)
                for (int j = 0; j < tempn; j++)
                    codes.push_back((codes[j] + char('0' + p)));
            else
                for (int j = tempn - 1; j >= 0; j--)
                    codes.push_back((codes[j] + char('0' + p)));
            
        } 
        for (int j = tempn - 1; j >= 0; j--)
            codes[j] = (codes[j] + '0'); 
    }
    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;
    return 0;
}

