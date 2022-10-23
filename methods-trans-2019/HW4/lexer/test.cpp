#include <iostream>
#include <fstream>
#include "gen/lexer.hpp"
#include "gen/parser.hpp"

extern std::vector<std::pair<std::string, std::string>> reg_to_action;
extern std::string header;

void yyerror(const char *s) {
  std::cerr << "parser: " << s << std::endl;
}

//extern int yydebug;

int main() {
  //yydebug = 1;
  std::ifstream in("./test/lexer.l");
  std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

  std::cout << "File contents: " << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << content << std::endl;
  std::cout << "------------------------------------" << std::endl;

  yy_scan_string(content.data());
  yyparse();

  std::cout << header << std::endl;
  std::cout << "------------------------------------" << std::endl;
  for (int i = 0; i < reg_to_action.size(); ++i) {
    std::cout << reg_to_action[i].first << " -> " << reg_to_action[i].second << std::endl;
  }
}
