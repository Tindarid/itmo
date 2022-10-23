#include <string>
#include <iostream>
#include <regex>

  #include "lexer.h"

token cur_tokenn;
int cur_pos;
std::string str_to_parse;
std::string cur_string;
std::smatch matcher;

void scan_string(std::string &s) {
  cur_tokenn = (token)0;
  cur_string = "";
  cur_pos = 0;
  str_to_parse = s;
}

token cur_token() {
  return cur_tokenn;
}

bool str_matches(std::string reg) {
  return std::regex_search(str_to_parse.cbegin() + cur_pos, str_to_parse.cend(), matcher, std::regex(reg));
}

token next_token_ext() {
  while (true) {
    if (str_matches("[ \t\n]+") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

                      

      continue;
    } else if (str_matches("\\(") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return LBR;    

      continue;
    } else if (str_matches("\\)") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return RBR;    

      continue;
    } else if (str_matches("\\*") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return MUL; 

      continue;
    } else if (str_matches("\\/") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return DIV;  

      continue;
    } else if (str_matches("\\-") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return MINUS; 

      continue;
    } else if (str_matches("\\+") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return PLUS; 

      continue;
    } else if (str_matches("\\=") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return EQUAL; 

      continue;
    } else if (str_matches("\\>\\>") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       return SHIFT; 

      continue;
    } else if (str_matches("[0-9]+") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       cur_unio.num = std::stoi(cur_string); return NUM; 

      continue;
    } else if (str_matches("[a-z]") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();

       cur_unio.ch = cur_string[0]; return VAR; 

      continue;
    } else if (str_matches("$") and matcher.position(0) == 0) {
      cur_string = matcher.str();
      cur_pos += cur_string.length();
      return END;
    }
    throw std::runtime_error(std::string("cannot parse next char: ") + str_to_parse[cur_pos]);
  }
}

void next_token() {
  cur_tokenn = next_token_ext();
}
