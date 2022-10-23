#include <iostream>
#include <fstream>
using namespace std;

int tempperm[100005];
int n;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    return;
}

void prevp() {
    int perm[100005];
    for (int i = 0; i < n; i++)
        perm[i] = tempperm[i];
    int temp1 = -1, temp2 = -1;
    for (int i = 0; i < n - 1; i++)
        if (perm[i] > perm[i + 1])
            temp1 = i;
    if (temp1 == -1) {
        for (int i = 0; i < n; i++)
            cout << "0 ";
        cout << endl;
        return;
    }
    int max = -1;
    for (int i = temp1 + 1; i < n; i++)
        if (perm[i] < perm[temp1] && perm[i] >= max) {
            max = perm[i];
            temp2 = i;
        }
    swap(perm[temp1], perm[temp2]);
    for (int i = temp1 + 1; i < temp1 + (n - temp1) / 2 + 1; i++)
        swap(perm[i], perm[n - i + temp1]);

    for (int i = 0; i < n; i++)
        cout << perm[i] << " ";
    cout << endl;
    return;
}

void nextp() {
    int perm[100005];
    for (int i = 0; i < n; i++)
        perm[i] = tempperm[i];
    int temp1 = -1, temp2 = -1;
    for (int i = 0; i < n - 1; i++)
        if (perm[i] < perm[i + 1])
            temp1 = i;
    if (temp1 == -1) {
        for (int i = 0; i < n; i++)
            cout << "0 ";
        cout << endl;
        return;
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
    return;
}

int main() {
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> tempperm[i];
    prevp();
    nextp();
    return 0;
}
