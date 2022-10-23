#include <iostream>
using namespace std;

int n, koef = 1;
bool func[1030];
char arg[1030][15];
bool ans[1030];
bool matrix[1030][1030];

int main()
{
    cin >> n;
    for (int temp = n; temp >= 1; temp--)
        koef *= 2;
    for (int i = 0; i < koef; i++)
    {
        cin >> arg[i];
        char temp;
        cin >> temp;
        if (temp == '0') matrix[0][i] = false;
        else matrix[0][i] = true;
    }
    for (int i = 1; i < koef; i++)
        for (int j = 0; j < koef - i; j++)
            matrix[i][j] = matrix[i-1][j] ^ matrix[i-1][j+1];
    for (int i = 0; i < koef; i++)
        ans[i] = matrix[i][0];
    for (int i = 0; i < koef; i++)
        cout << arg[i] << " " << ans[i] << "\n";
    return 0;
}
