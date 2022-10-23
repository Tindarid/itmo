#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#define MAXN 1000005
using namespace std;

int n;
int mas[MAXN], minmas[MAXN], maxmas[MAXN], r[MAXN];
char str[100];

int get_par(int a)
{
    if (mas[a] == a)
        return a;
    int res = get_par(mas[a]);
    mas[a] = res;
    return res;
}

int main()
{
	FILE * fin = fopen("dsu.in", "r");
	FILE * fout = fopen("dsu.out", "w");
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; i++) {
        mas[i] = i;
        minmas[i] = i;
        maxmas[i] = i;
        r[i] = 1;
    }
    int tmp, c, d;
    while (fscanf(fin, "%s", str) == 1) {
        
        if (str[0] == 'g') {
            fscanf(fin, "%d", &tmp);
            int temp = get_par(tmp);
            fprintf(fout, "%d %d %d\n", minmas[temp], maxmas[temp], r[temp]);
        }
        else {
            fscanf(fin, "%d%d", &c, &d);
            int a = get_par(c), b = get_par(d);
            if (a != b) {
                if (r[a] < r[b])
                    swap(a, b);
                mas[b] = a;
                r[a] += r[b];
                if (minmas[a] > minmas[b]) minmas[a] = minmas[b];
                if (maxmas[a] < maxmas[b]) maxmas[a] = maxmas[b];
            }
        }
    }
    return 0;
}
