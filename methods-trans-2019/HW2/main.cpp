#include <iostream>
#include "parser.h"
using namespace std;

int main() {
  std::string s;
  parser p;

  std::cout << "Give me a string: ";
  getline(cin, s);
  tree res = p.parse(s);

  std::cout << "Your tree: " << std::endl;
  res.printTree(std::cout);
}
