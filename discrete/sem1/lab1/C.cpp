#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int n;
int sizeFunc[1000];
int amountArg[40];
int amountFunc[1000];
bool functions[1000][40];
bool matrix[1000][40][40];
char arg[40][5];
bool ans1, ans2, ans3, ans4, ans5;

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> sizeFunc[i] >> s;
        for (int j = 0; j < s.length(); j++)
            matrix[i][0][j] = functions[i][j] = s[j] - '0';   
        amountFunc[i] = s.length();   
    }
    int k = 0;
    for (int i1 = 0; i1 <= 1; i1++)
        for (int i2 = 0; i2 <= 1; i2++)
            for (int i3 = 0; i3 <= 1; i3++)
                for (int i4 = 0; i4 <= 1; i4++)
                    for (int i5 = 0; i5 <= 1; i5++)
                    {
                        arg[k][0] = i1 + '0', arg[k][1] = i2 + '0', arg[k][2] = i3 + '0', 
                                        arg[k][3] = i4 + '0', arg[k][4] = i5 + '0';
                        amountArg[k] = i1 + i2 + i3 + i4 + i5;
                        k++;
                    }
    for (int j = 0; j < n; j++)
    {
        //0
        if (functions[j][0])
            ans1 = true;
        //1
        if (!functions[j][amountFunc[j] - 1])
            ans2 = true;
        //Mono
        if (!ans3)
        {
            for (int i1 = 0; i1 < amountFunc[j]; i1++)
                for (int i2 = 0; i2 < amountFunc[j]; i2++)
                {
                    bool flag = true;
                    for (int i = 4; i >= 5 - sizeFunc[j]; i--)
                        if (arg[i1][i] > arg[i2][i])
                            flag = false;
                    if (flag)
                        if (functions[j][i1] && !functions[j][i2])
                            ans3 = true; 
                }
        }
        //Samodvo
        if (!ans4)
        {
            if (sizeFunc[j] == 0)
                ans4 = true;
            int temp1 = amountFunc[j] / 2 - 1;
            int temp2 = temp1 + 1;
            while(temp1 >= 0)
            {
                if (functions[j][temp1] == functions[j][temp2])
                {
                    ans4 = true;
                }
                temp1--;
                temp2++;
            }
        }
        //Linear
        if (!ans5)
        {
            for (int i = 1; i < amountFunc[j]; i++)
                for (int i2 = 0; i2 < amountFunc[j] - i; i2++)
                    matrix[j][i][i2] = (matrix[j][i-1][i2] ^ matrix[j][i-1][i2+1]);   
            for (int i = 0; i < amountFunc[j]; i++)
                if(matrix[j][i][0])
                {
                    if (amountArg[i] > 1)
                        ans5 = true;
                }         
        }
    }
    if (ans1 && ans2 && ans3 && ans4 && ans5)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
