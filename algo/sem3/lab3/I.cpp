#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAXN 1000001
#define ALH 26
using namespace std;

struct ver {
    int next[ALH];
    int par, link;
    int min, max;
};

ver g[MAXN + 1];
vector<int> term;
vector<int> term_l;
int siz;
int n;
string str;
vector<int> order;

void resolve(int v) {
    for (int i = 0; i < ALH; ++i) {
        g[v].next[i] = -1;
    }
}

void axo_init() {
    siz = 1;
    g[0].par = g[0].link = 0;
    resolve(0);
}

void axo_add(int numb) {
    int v = 0;
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        int ch = str[i] - 'a';
        if (g[v].next[ch] == -1) {
            resolve(siz);
            g[siz].link = -1;
            g[siz].par = v;
            g[siz].min = g[siz].max = -1;
            g[v].next[ch] = siz++;
        }
        v = g[v].next[ch];
    }
    term.push_back(v);
    term_l.push_back(len);
}

void setLink(int v, int ch) {
    int p = g[v].par;
    p = g[p].link;
    while (p != 0 && g[p].next[ch] == -1) {
        p = g[p].link;
    }
    if (p == -1) {
        g[v].link = 0;
    } else if (p == 0 && (g[p].next[ch] == -1 || g[p].next[ch] == v)) {
        g[v].link = 0;
    } else {
        g[v].link = g[p].next[ch];
    }
}

void prep() {
    for (int i = 0; i < ALH; ++i) {
        int temp = g[0].next[i];
        if (temp != -1) {
            setLink(temp, i);
            order.push_back(temp);
        }
    }
    for (int i = 0; i < order.size(); ++i) {
        for (int j = 0; j < ALH; ++j) {
            int temp = g[order[i]].next[j];
            if (temp != -1) {
                setLink(temp, j);
                order.push_back(temp);
            }
        }
    }
}

int resolve_min(int a, int b) {
    if (a == -1) {
        return b;
    }
    if (b == -1) {
        return a;
    }
    return min(a, b);
}

int resolve_max(int a, int b) {
    if (a == -1) {
        return b;
    }
    if (b == -1) {
        return a;
    }
    return max(a, b);
}

int main() {
    ifstream cin("search6.in");
    ofstream cout("search6.out");
    cin.tie(nullptr);
    cin >> n;
    axo_init();
    for (int i = 0; i < n; ++i) {
        cin >> str;
        axo_add(i);
    }
    prep();
    cin >> str;
    int v = 0;
    for (int i = 0; i < str.length(); ++i) {
        int ch = str[i] - 'a';
        while (v != 0 && g[v].next[ch] == -1) {
            v = g[v].link;
        }
        int temp = g[v].next[ch];
        if (temp != -1) {
            v = temp;
            g[temp].min = resolve_min(i, g[temp].min);
            g[temp].max = resolve_max(i, g[temp].max);
        } else {
            v = 0;
        }
    }
    for (int j = order.size() - 1; j >= 0; --j) {
        int temp = order[j];
        int link = g[temp].link;
        g[link].min = resolve_min(g[temp].min, g[link].min);
        g[link].max = resolve_max(g[temp].max, g[link].max);
    }

    for (int i = 0; i < n; ++i) {
        if (g[term[i]].min == -1) {
            cout << "-1 -1\n";
        } else {
            cout << 1 + g[term[i]].min - term_l[i] << " " << 1 + g[term[i]].max - term_l[i] << "\n";
        }
    }
    return 0;
}
