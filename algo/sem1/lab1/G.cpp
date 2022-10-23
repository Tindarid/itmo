#include <iostream>
#include <fstream>
using namespace std;
 
bool used[4][100001];
 
int main()
{
    ifstream cin("style.in");
    ofstream cout("style.out");
    for (int i = 0; i < 4; i++)
    {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            used[i][temp]=true;
        }
    }
    int l = 1, r = 100000;
    int i = 1, j = 1;
    int curused[4];
        curused[0]=curused[1]=curused[2]=curused[3]=0;
    while (j <= 100000 && i <= 100000)
    {
        while (j <= 100000){
            for (int i1 = 0; i1 < 4; i1++)
                if(used[i1][j] == true)
                    curused[i1]++;
            int temp = j;
            for (int i1 = 0; i1 < 4; i1++)
                if (curused[i1] == 0)
                {
                    j++;
                    break;
                }
            if (j == temp) 
                break;
        }
        while (i<=100000) {
            for (int i1 = 0; i1 < 4; i1++)
                if(used[i1][i] == true)
                    curused[i1]--;
            i++;
            int temp = i;
            for (int i1 = 0; i1 < 4; i1++)
                if (curused[i1] == 0)
                {
                    i--;
                    for (int i1 = 0; i1 < 4; i1++)
                        if(used[i1][i] == true)
                            curused[i1]++;
                    break;
                }
            if (temp!=i) break;
        }
        if (r-l>j-i && curused[0]!=0 && curused[1]!=0 && curused[2]!=0 && curused[3]!=0) 
            r = j, l = i;
        for (int i1 = 0; i1 < 4; i1++)
                if(used[i1][i] == true)
                    curused[i1]--;
        i++;
        j++;
         
    }
    for (int i1 = 0; i1 < 4; i1++)
    {
        for (int j1 = l; j1 <=r; j1++)
            if(used[i1][j1]==true)
            {
                cout << j1 << " ";
                break;
            }
    }
    return 0;
}
