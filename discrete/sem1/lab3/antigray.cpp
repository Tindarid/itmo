#include <iostream>
#include <fstream>
using namespace std;

int n;
char temp[100];

void get_code(int a) 
{
    if (a == n - 1) {
        for (int i = 0; i <= 2; i++) {
            cout << i;
            for (int j = 0; j < n - 1; j++)
                cout << char(((temp[j] - '0' + i) % 3) + '0'); 
            cout << endl;
        }
        return;
    }  
    temp[a] = '0';
    get_code(a + 1);
    temp[a] = '1';
    get_code(a + 1);
    temp[a] = '2';
    get_code(a + 1);    
}

int main()
{
    freopen("antigray.in", "r", stdin);
    freopen("antigray.out", "w", stdout);
    cin >> n;
    get_code(0);
    return 0;
}
