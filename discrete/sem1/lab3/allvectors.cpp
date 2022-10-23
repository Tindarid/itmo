#include <iostream>
#include <fstream>
using namespace std;

char temp[100];
int n;
FILE * fin, * fout;

void get_code(int a) 
{
    if (a == n) {
        cout << temp << endl;
        return;
    }  
    temp[a] = '0';
    get_code(a + 1);
    temp[a] = '1';
    get_code(a + 1);
}

int main()
{
    freopen("allvectors.in", "r", stdin);
    freopen("allvectors.out", "w", stdout);
    cin >> n;
    temp[n] = '\0';
    get_code(0);
    return 0;
}
