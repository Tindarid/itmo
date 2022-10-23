#include <iostream>
#include <fstream>
#include "gen/lexer.hpp"
#include "gen/parser.hpp"

extern std::string header, union_code, start_token;
extern std::vector<std::string> tokens;
extern std::map<std::string, std::string> token_type;
extern std::map<std::string, rule> rules;

void yyerror(const char *s) {
  std::cerr << "parser: " << s << std::endl;
}

//extern int yydebug; 
int main() {
  //yydebug = 1;
  std::ifstream in("./test/parser.y");
  std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

  std::cout << "File contents: " << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << content << std::endl;
  std::cout << "------------------------------------" << std::endl;

  yy_scan_string(content.data());
  yyparse();

  std::cout << "HEADER: " << std::endl;
  std::cout << header << std::endl << std::endl;
  std::cout << "UNION: " << std::endl;
  std::cout << union_code << std::endl << std::endl;
  std::cout << "START: " << std::endl;
  std::cout << start_token << std::endl << std::endl;

  std::cout << "TYPES: " << std::endl;
  for (auto it = token_type.begin(); it != token_type.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
  }
  std::cout << std::endl;
  std::cout << "TOKENS: " << std::endl;
  for (auto it = tokens.begin(); it != tokens.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;

  std::cout << "RULES: " << std::endl;
  for (auto it = rules.begin(); it != rules.end(); ++it) {
    std::cout << it->first << ": " << std::endl;
    for (auto it2 = it->second.vars.begin(); it2 != it->second.vars.end(); ++it2) {
      for (const auto& s : it2->rules) {
        std::cout << s << " ";
      }
      std::cout << it2->code << std::endl;
    }
  }
  std::cout << "------------------------------------" << std::endl;
}
