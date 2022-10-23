#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int n, m;
char S;
bool dp[50][50][50];
string s;

bool getAns(char start, int ind) {
    bool res = false;
    for (char i = 'A'; i <= 'Z' + 1; ++i) {
        if (dp[start - 'A'][s[ind] - 'a'][i - 'A'] == true) {
            if (ind + 1 == s.length() && i == 'Z' + 1) {
                return true;
            }
            res |= getAns(i, ind + 1);
        }
    }
    return res;
}

int main() {
    ifstream cin("automaton.in");
    ofstream cout("automaton.out");
    cin >> n >> S;
    for (int i = 0; i < n; ++i) {
        string temp, prod;
        char term;
        cin >> term >> temp >> prod;
        char t = prod[0], e = 'Z' + 1;
        if (prod.length() != 1) {
            e = prod[1];
        }
        dp[term - 'A'][t - 'a'][e - 'A'] = true;
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        if (getAns(S, 0)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}
