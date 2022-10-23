#include <iostream>
#include <fstream>
#define MAXN 1000005
using namespace std;

long long m, n, sum;
long long mas[MAXN], p[MAXN], mas2[MAXN];

int main()
{
    ifstream cin("bureaucracy.in");
    ofstream cout("bureaucracy.out");
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> mas2[i];
        sum += mas2[i];
    }
    
    if (m >= sum) {
        cout << "-1" << endl;
        return 0;
    }
    
    int n2 = 0;
    sum = 0; 
    for (int i = 0; i < n; i++) {
        if (mas2[i] > m/n) {
            mas[n2] = (mas2[i] - m/n);
            n2++;
        }
        else {
            sum += (m/n - mas2[i]);
        }
    }
    m = m%n + sum;
    n = n2;
    
    for (int i = 0; i < n - 1; i++)
        p[i] = i + 1;
    p[n - 1] = 0;
    
    int cur = 0;
    while (m > 0) {
        mas[cur]--;
        if (mas[cur] == 0) 
            n--;
        int temp = cur;
        while (true) {
            temp = p[temp];
            if (mas[temp] != 0)
                break;
        }
        p[cur] = temp;
        cur = temp;
        m--;
    }
    
    cout << n << endl;
    int cur2 = cur;
    for (int i = 0; i < n; i++)
    {
        while (mas[cur] == 0) {
            cur = p[cur];
        }
        cout << mas[cur] << " ";
        cur = p[cur];
    }
    cout << endl;
    return 0;
}
