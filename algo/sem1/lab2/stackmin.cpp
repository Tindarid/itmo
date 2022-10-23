#include <iostream>
#include <fstream>
using namespace std;

int n = 0, k, n1= 0;
int st[1000005];
int minst[1000005];

int main()
{
    FILE * fin = fopen("stack-min.in", "r");
    FILE * fout = fopen("stack-min.out", "w");
    fscanf(fin, "%d", &k);
    for (int i = 0; i < k; i++)
    {
        int temp = 1;
        fscanf(fin, "%d", &temp);
        if (temp == 1)
        {
            int temp2 = 0;
            fscanf(fin, "%d", &temp2);
            st[n] = temp2;
            n++;
            if (n1 == 0 || (temp2 <= minst[n1-1]))
            {
                minst[n1] = temp2;
                n1++;
            }
        }
        else if (temp == 2)
        {
            n--;
            if (st[n] == minst[n1-1])
                n1--;
        }
        else
        {
            fprintf(fout, "%d\n", minst[n1-1]);         
        }
    }
    //system("pause");
    return 0;
}
