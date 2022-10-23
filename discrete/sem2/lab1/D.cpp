#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
 
int n;
 
struct Node {
    double mas[101][101];
};
 
Node multip(Node &a, Node &b) {
    Node ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans.mas[i][j] = 0;
            for (int i1 = 0; i1 < n; ++i1) {
                ans.mas[i][j] += a.mas[i][i1] * b.mas[i1][j];
            }
        }
    }
    return ans;
}
 
int main() {
    ifstream cin("markchain.in");
    ofstream cout("markchain.out");
    cin >> n;
    Node mat;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mat.mas[i][j]; 
        }
    }
    Node ans = mat;
    for (int i1 = 0; i1 < 30; ++i1) {
        Node p = multip(ans, ans);
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (abs(ans.mas[i][j] - p.mas[i][j]) > 0.0001) {
                        flag = false;
                }
            }
        }
        ans = p;
        if (flag) {
            break;
        }
    }
    cout << setprecision(5) << fixed;
    double kek;
    for (int i = 0; i < n; ++i) {
        kek = 0;
        for (int j = 0; j < n; ++j) {
            kek += ans.mas[j][i];
        }
        cout << kek / n << "\n";
    }
    return 0;
}
