#include <iostream>
#include <fstream>
using namespace std;

int n, k;
int dis[103][103];
int dis1[103][103];
int lit[103];
int disize[103];

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n >> k;
    bool ans = true;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> dis[i][j];
            dis1[i][j]=dis[i][j];
            if (dis[i][j] != -1)
                disize[i]++;
        }
    for (int i = 0; i < k; i++)
        lit[i] = -1;
    while (true) {
        bool flag = true;
        for (int i = 0; i < k; i++)
            if (disize[i] == 1) {
                flag = false;
                for (int j = 0; j < n; j++)
                    if (dis[i][j]!=-1)
                        lit[j] = dis[i][j];
            }
        if (flag) break;
        for (int i = 0; i < k; i++)
            for (int j = 0; j < n; j++)
                if (lit[j] != -1 && dis[i][j]!=-1 && disize[i] != 0) {
                    bool flag2 = true;
                    if (lit[j] == 0) flag2 = !flag2;
                    if (dis[i][j] == 0) flag2 = !flag2;
                    if (flag2) {
                        disize[i] = 0;
                        break;
                    }
                    else {
                        disize[i]--;
                        dis[i][j] = -1;
                    }
                }
    }
    for (int i = 0; i < k; i++) {
        bool r = false;
        for (int j = 0; j < n; j++) 
            if (dis1[i][j]!=-1) {
            if (lit[j] == -1)
                lit[j] = 0;
                bool flag2 = true;
                if (lit[j] == 0) flag2 = !flag2;
                if (dis1[i][j] == 0) flag2 = !flag2;
                r = (r | flag2); 
        }
        ans = (ans & r);
    }
    
    if (ans) cout << "NO\n";
    else cout << "YES\n";
    return 0;
}
