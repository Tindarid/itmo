#include <iostream>
#include <fstream>
using namespace std;

int n;
int mas[400];

int main()
{
    ifstream cin("saloon.in");
    ofstream cout("saloon.out");
    for (int i = 0; i <= 200; i++)
        mas[i] = 0;
    
    cin >> n;
    int k = 0, p = 0;
    for (int i = 1; i <= n; i++) {
        int sth, stm, count;
        cin >> sth >> stm >> count;
        int st = sth * 60 + stm;
        while (st >= mas[p] && k > 0) {
            p++;
            k--;
        }
        if (count < k) {
            cout << sth << " " << stm << endl;
            continue;
        }
        if (k != 0) {
            mas[p + k] = mas[p] + k * 20;           
        } else {
            mas[p + k] = st + 20;
        }
        st = mas[p+k];
        cout << st/60 << " " << st%60 << endl;
        k++;
    }
    
    return 0;
}
