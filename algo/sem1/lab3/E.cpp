#include <iostream>
#include <fstream>
#define INF 1000000000
using namespace std;

int n;
int cost[1000];
int d[200][200];

int min(int a, int b) {
    if (a < b) 
        return a;
    return b;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    for (int j = 0; j <= n; j++)
        d[0][j] = INF;
    d[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            if (cost[i] > 100) {
                d[i][j] = min(d[i - 1][j - 1] + cost[i], d[i - 1][j]);
            } else {
                d[i][j] = min(d[i - 1][j] + cost[i], d[i - 1][j + 1]);
            }
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
