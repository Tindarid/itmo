#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> p;
long long n, sum;

bool Comp (long long a, long long b)
{
    return a > b;
}

int main()
{
    ifstream cin("huffman.in");
    ofstream cout("huffman.out");
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    while (p.size() >= 2) {
         sort(p.begin(), p.end(), Comp);
         int n2 = p.size();
         p[n2 - 2] += p[n2 - 1];
         sum += p[n2 - 2];
         p.resize(n2 - 1);
    }
    cout << sum << endl;
    return 0;
}
