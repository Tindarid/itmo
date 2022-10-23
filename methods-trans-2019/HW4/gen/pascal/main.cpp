#include <iostream>
#include "lexer.h"
#include "parser.h"
using namespace std;

int main() {
  std::string s;

  std::cout << "Give me a string: ";
  getline(cin, s);
  unio res = parse(s);
  std::cout << "Your tree: " << std::endl;
  res.t->printTree(std::cout);
}
