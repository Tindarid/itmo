#include <iostream>
#include <fstream>
#include <regex>
#include "gen/lexer.hpp"
#include "gen/parser.hpp"
using std::endl;

extern std::vector<std::pair<std::string, std::string>> reg_to_action;
extern std::string header, cpp;

std::string tab = "  ";

void yyerror(const char *s) {
  throw std::runtime_error(std::string("parser: ") + std::string(s));
}

void generateCpp(std::ofstream &out) {
  out << "#include <string>" << endl;
  out << "#include <iostream>" << endl;
  out << "#include <regex>" << endl;
  out << cpp << endl;

  out << "token cur_tokenn;" << endl;
  out << "int cur_pos;" << endl;
  out << "std::string str_to_parse;" << endl;
  out << "std::string cur_string;" << endl;
  out << "std::smatch matcher;" << endl;
  out << endl;

  out << "void scan_string(std::string &s) {" << endl;
  out << tab << "cur_tokenn = (token)0;" << endl;
  out << tab << "cur_string = \"\";" << endl;
  out << tab << "cur_pos = 0;" << endl;
  out << tab << "str_to_parse = s;" << endl;
  out << "}" << endl << endl;

  out << "token cur_token() {" << endl;
  out << tab << "return cur_tokenn;" << endl;
  out << "}" << endl << endl;

  out << "bool str_matches(std::string reg) {" << endl;
  out << tab << "return std::regex_search(str_to_parse.cbegin() + cur_pos, ";
  out << "str_to_parse.cend(), matcher, std::regex(reg));" << endl;
  out << "}" << endl << endl;

  bool end_presented = false;
  std::string end = "$";

  out << "token next_token_ext() {" << endl;
  out << tab << "while (true) {" << endl;
  for (int i = 0; i < reg_to_action.size(); ++i) {
    if (i == 0) {
      out << tab << tab << "if (";
    } else {
      out << " else if (";
    }

    out << "str_matches(\"" + reg_to_action[i].first + "\") and matcher.position(0) == 0) {" << endl;
    if (reg_to_action[i].first == end) {
      throw std::runtime_error("You cannot match end token");
    }

    out << tab << tab << tab << "cur_string = matcher.str();" << endl;
    out << tab << tab << tab << "cur_pos += cur_string.length();" << endl;
    out << endl;

    out << tab << tab << tab << reg_to_action[i].second << endl;
    out << endl;

    out << tab << tab << tab << "continue;" << endl;
    out << tab << tab << "}";
  }
  out << " else if (";
  out << "str_matches(\"" + end + "\") and matcher.position(0) == 0) {" << endl;
  out << tab << tab << tab << "cur_string = matcher.str();" << endl;
  out << tab << tab << tab << "cur_pos += cur_string.length();" << endl;
  out << tab << tab << tab << "return END;" << endl;
  out << tab << tab << "}";

  out << endl << tab << tab << "throw std::runtime_error(std::string(\"cannot parse next char: \") + str_to_parse[cur_pos]);" << endl;
  out << tab << "}" << endl;
  out << "}" << endl << endl;

  out << "void next_token() {" << endl;
  out << tab << "cur_tokenn = next_token_ext();" << endl;
  out << "}" << endl;
}

void generateHeader(std::ofstream &out) {
  out << "#pragma once" << endl;
  out << header << endl;
  out << "extern std::string cur_string;" << endl;
  out << "void next_token();" << endl;
  out << "token cur_token();" << endl;
  out << "void scan_string(std::string &s);" << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [lexer file]" << endl;
    return 1;
  }

  std::string filename(argv[1]);
  if (!std::regex_match(filename, std::regex(".*\\.l")) or filename.length() <= 2) {
    std::cerr << "Filename must have .l extension" << endl;
    return 1;
  }

  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Cannot open lexer file" << endl;
    return 1;
  }

  std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  yy_scan_string(content.data());
  yyparse();

  if (reg_to_action.size() < 1) {
    std::cerr << "Must be at least one token rule" << endl;
    return 1;
  }

  std::string prefix = filename.substr(0, filename.length() - 2);

  std::ofstream outCpp(prefix + ".cpp");
  if (!outCpp.is_open()) {
    std::cerr << "Cannot open cpp file to generate lexer" << endl;
    return 1;
  }
  generateCpp(outCpp);

  std::ofstream outHeader(prefix + ".h");
  if (!outHeader.is_open()) {
    std::cerr << "Cannot open header file to generate lexer" << endl;
    return 1;
  }
  generateHeader(outHeader);

  return 0;
}
