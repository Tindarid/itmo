#include <iostream>
#include "lexer.h"
#include "parser.h"
using namespace std;

int main() {
  std::string s;

  while (true) {
    getline(cin, s);
    unio res = parse(s);
    cout << res.e->count(0) << endl;
  }
}
