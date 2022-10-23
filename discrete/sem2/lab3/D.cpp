#include <fstream>
#include <string>
#include <vector>
#include <utility>
#define MOD 1000000007
using namespace std;

int n, length;
string w;
char S;
long long dp[200][200][200];
vector<vector<char>> net;
vector<vector<pair<char, char>>> soot;

void init() {
    for (char i = 'A'; i <= 'Z'; ++i) {
        for (int k = 0; k < net[i - 'A'].size(); ++k) {
            for (int j = 0; j < length; ++j) {
                if (w[j] == net[i - 'A'][k]) {
                    dp[i - 'A'][j][j] = 1;
                }
            }
        }
    }
}

void proc() {
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            for (char c = 'A'; c <= 'Z'; ++c) {
                for (int so = 0; so < soot[c - 'A'].size(); ++so) {
                    for (int k = i; k < j; ++k) {
                        dp[c - 'A'][i][j] += (dp[soot[c - 'A'][so].first - 'A'][i][k] 
                                            * dp[soot[c - 'A'][so].second - 'A'][k + 1][j]) % MOD;
                    }
                }
            }
        }
    }
}

int main() {
    ifstream in("nfc.in");
    ofstream out("nfc.out");
    in >> n >> S;
    net.resize(50);
    soot.resize(50);
    for (int i = 0; i < n; ++i) {
        string temp, prod;
        char term;
        in >> term >> temp >> prod;
        if (prod.length() != 1) {
            soot[term - 'A'].push_back(make_pair(prod[0], prod[1]));
        } else if (prod.length() == 1) {
            net[term - 'A'].push_back(prod[0]);
        }
    }
    in >> w;
    length = w.length();
    init();
    proc();
    out << dp[S - 'A'][0][length - 1] << endl;
    return 0;
}
