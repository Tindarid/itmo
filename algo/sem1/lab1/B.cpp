#include <iostream>
#include <fstream>
#include <string>
#include <utility>
using namespace std;

pair <int, int> heapMas[10000005];
int n, countKey, keys[10000005];

void siftUp(int v)
{
    while (v > 0 && heapMas[(v-1)/2].first>heapMas[v].first)
    {
        swap(keys[heapMas[(v-1)/2].second], keys[heapMas[v].second]);
        swap(heapMas[(v-1)/2], heapMas[v]);
        v = (v-1)/2;
    }
}

void siftDown(int v)
{
    while (true)
    {
        int c1 = 2*v + 1, c2 = 2*v + 2; 
        if (c1 >= n) return;
        if (c2 >= n) c2 = c1;
        if (heapMas[v].first <= heapMas[c1].first
             && heapMas[v].first <= heapMas[c2].first)
            return;
        int min = c1;
        if (heapMas[c2].first < heapMas[c1].first) min = c2;
        swap(keys[heapMas[min].second], keys[heapMas[v].second]);
        swap(heapMas[min], heapMas[v]);
        v = min;
    }
    
}

void add(int a)
{
    heapMas[n].first = a;
    heapMas[n].second = countKey;
    keys[countKey]=n;
    n++;
    siftUp(n-1);
}
int main()
{
    ifstream cin("priorityqueue.in");
    ofstream cout("priorityqueue.out");
    string s;
    while (cin >> s)
    {
        if (s=="push")
        {
            countKey++;
            int k;
            cin >> k;
            add(k);
        }
        else if (s=="decrease-key")
        {
            countKey++;
            int numb, newKey;
            cin >> numb >> newKey;
            heapMas[keys[numb]].first=newKey;
            siftUp(keys[numb]);
        }
        else if (s=="extract-min")
        {
            countKey++;
            if (n == 0)
                cout << "*\n";
            else
            {
                cout << heapMas[0].first << endl;
                swap(keys[heapMas[0].second], keys[heapMas[n-1].second]);
                swap(heapMas[0], heapMas[n-1]);
                n--;
                siftDown(0);
            }
        }
    }
    return 0;
}
