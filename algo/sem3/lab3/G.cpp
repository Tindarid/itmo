#include <iostream>
#include <fstream>
#include <string>
#define MAXN 1000005
#define ALH 26
using namespace std;

struct ver {
    int link, length;
    int next[ALH];
};

ver g[MAXN * 2];
int endv, siz;
string mas[MAXN];

void resolve(int ind) {
    for (int i = 0; i < ALH; ++i) {
        g[ind].next[i] = -1;
    }
}

void extend(char c) {
    int cur = siz++, v = endv;
    g[cur].length = g[endv].length + 1;
    resolve(cur);
    int ch = c - 'a';
    while (v != -1 && g[v].next[ch] == -1) {
        g[v].next[ch] = cur;
        v = g[v].link;
    }
    if (v != -1) {
        int u = g[v].next[ch];
        if (g[u].length != g[v].length + 1) {
            int clone = siz++;
			g[clone].length = g[v].length + 1;
			g[clone].link = g[u].link;
            for (int i = 0; i < ALH; ++i) {
                g[clone].next[i] = g[u].next[i];
            }
			while (v != -1 && g[v].next[ch] == u) {
				g[v].next[ch] = clone;
                v = g[v].link;
            }
			g[u].link = g[cur].link = clone;
        } else {
            g[cur].link = u;
        }
    } else {
        g[cur].link = 0;
    }
    endv = cur;
}

void construct(string& s) {
    g[0].length = 0;
    g[0].link = -1;
    resolve(0);
    siz = 1;
    for (int i = 0; i < s.length(); ++i) {
        extend(s[i]);
    }
}

bool tr(string& str) {
    int cur = 0;
    for (int i = 0; i < str.length(); ++i) {
        cur = g[cur].next[str[i] - 'a'];
        if (cur == -1) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream cin("search4.in");
    ofstream cout("search4.out");
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }
    cin >> s;
    construct(s);
    for (int i = 0; i < n; ++i) {
        if (tr(mas[i])) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
