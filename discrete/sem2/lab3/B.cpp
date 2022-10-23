#include <fstream>
#include <string>
using namespace std;

int n;
char S;
int dp[30][30];
int ans[30];
string temp;

bool dfs(char start) {
    bool res = true;
    if (ans[start - 'A'] == 1) {
        return true;
    }
    if (ans[start - 'A'] == 0) {
        return false;
    }
    for (char i = 'A'; i <= 'Z'; ++i) {
        if (dp[start - 'A'][i - 'A'] == 1) {
            res &= dfs(i);
        }
    }
    return res;
}

int main() {
    ifstream cin("epsilon.in");
    ofstream cout("epsilon.out");
    cin >> n >> S;
    getline(cin, temp);
    for (int i = 0; i < n; ++i) {
        getline(cin, temp);
        if (temp.length() == 4) {
            ans[temp[0] - 'A'] = 1;
        } else {
            int temp2 = 1;
            for (int j = 4; j < temp.length(); ++j) {
                if (temp[j] >= 'a' && temp[j] <= 'z') {
                    temp2 = 2;
                }
            }
            for (int j = 4; j < temp.length(); ++j) {
                if (temp[j] >= 'A' && temp[j] <= 'Z') {
                    ans[temp[0] - 'A'] = 2;
                }
            }
            for (int j = 4; j < temp.length(); ++j) {
                if (temp[j] >= 'A' && temp[j] <= 'Z') {
                    if (dp[temp[0] - 'A'][temp[j] - 'A'] == 1) {
                        continue;
                    }
                    dp[temp[0] - 'A'][temp[j] - 'A'] = temp2;
                }
            }
        }
    }
    for (char i = 'A'; i <= 'Z'; ++i) {
        if (dfs(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}
