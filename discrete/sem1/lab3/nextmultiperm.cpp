#include <iostream>
#include <fstream>
using namespace std;

int perm[100005];
int n;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    return;
}

int main() {
    freopen("nextmultiperm.in", "r", stdin);
    freopen("nextmultiperm.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> perm[i];
    int temp1 = -1, temp2 = -1;
    for (int i = 0; i < n - 1; i++)
        if (perm[i] < perm[i + 1])
            temp1 = i;
    if (temp1 == -1) {
        for (int i = 0; i < n; i++)
            cout << "0 ";
        cout << endl;
        return 0;
    }
    int min = 1000000;
    for (int i = temp1 + 1; i < n; i++)
        if (perm[i] > perm[temp1] && perm[i] <= min) {
            min = perm[i];
            temp2 = i;
        }
    swap(perm[temp1], perm[temp2]);
    for (int i = temp1 + 1; i < temp1 + (n - temp1) / 2 + 1; i++)
        swap(perm[i], perm[n - i + temp1]);

    for (int i = 0; i < n; i++)
        cout << perm[i] << " ";
    cout << endl;
    return 0;
}
    
