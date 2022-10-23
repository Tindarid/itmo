#include <iostream>
#include <vector>
#include <string>
#define stack stackstepa
#define pop popstepa
#define push pushtepa
#include <fstream>
using namespace std;

vector<char> stack;

char pop() {
char temp = stack[stack.size()-1];
stack.resize(stack.size() - 1);
return temp;
}

void push(char v) {
stack.push_back(v);
}

int main() {
ifstream cin("decode.in");
ofstream cout("decode.out");

char nextsym = 0;
string temp;
cin >> temp;
for (int i = 0; i < temp.length(); ++i) {
nextsym = temp[i];
if (stack.size()){
char c = pop();
if (c != nextsym) {
push(c);
push(nextsym);
}
}
else
stack.push_back(nextsym);
}
cout << endl;
for (int i = 0; i<stack.size(); i++)
cout << stack[i];
//for (auto item : stack) {
//cout « item;
//}
return 0;
}
