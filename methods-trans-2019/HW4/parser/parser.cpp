#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <set>
#include <map>

#include "gen/lexer.hpp"
#include "gen/parser.hpp"
using std::endl;

std::string tab = "  ";
std::string empty = "EMPTY";
std::string end = "END";

extern std::string cpp, header, union_code, start_token;
extern std::vector<std::string> tokens;
extern std::map<std::string, std::string> token_type, rule_type;
extern std::map<std::string, rule> rules;
std::map<std::string, std::set<std::string>> FIRST;
std::map<std::string, std::set<std::string>> FOLLOW;
std::set<std::string> tokens_set;

void yyerror(const char *s) {
  throw std::runtime_error(std::string("parser: ") + std::string(s));
}

void outputSets(std::map<std::string, std::set<std::string>> se) {
  for (const auto& it : se) {
    std::cout << it.first << ":";
    for (const auto& s : it.second) {
      std::cout << " " << s;
    }
    std::cout << endl;
  }
}

bool is_token(const std::string& s) {
  return tokens_set.find(s) != tokens_set.end();
}

int countSets(std::map<std::string, std::set<std::string>> &se) {
  int res = 0;

  for (const auto &t : se) {
    res += t.second.size();
  }

  return res;
}

bool firstChanged() {
  static int size = 0;

  int cur_size = countSets(FIRST);

  if (size == cur_size) {
    return false;
  } else {
    size = cur_size;
    return true;
  }
}

bool followChanged() {
  static int size = 0;

  int cur_size = countSets(FOLLOW);

  if (size == cur_size) {
    return false;
  } else {
    size = cur_size;
    return true;
  }
}

std::set<std::string> fi(std::vector<std::string> &w, int i) {
  std::set<std::string> res;
  if (w.empty()) {
    res.insert(empty);
  } else if (i >= w.size()) {
    res.insert(empty);
  } else if (is_token(w[i])) {
    res.insert(w[i]);
  } else {
    auto it = FIRST.find(w[i]);
    if (it == FIRST.end()) {
      throw std::runtime_error(w[i] + " is not a token and rule, but used in grammar rules, strange ...");
    }
    if (it->second.find(empty) != it->second.end()) {
      for (auto &tt : it->second) {
        if (tt != empty) res.insert(tt);
      }
      auto temp = fi(w, i + 1);
      for (auto &tt : temp) {
        res.insert(tt);
      }
    } else {
      for (auto &tt : it->second) {
        res.insert(tt);
      }
    }
  }
  return res;
}

void generateFirst() {
  std::set<std::string> res;
  do {
    for (auto &r : rules) {
      res.clear();
      for (auto &p : r.second.vars) {
        auto temp = fi(p.rules, 0);
        for (auto &tt : temp) {
          res.insert(tt);
        }
      }
      auto it = FIRST.find(r.first);
      if (it == FIRST.end()) {
        throw std::runtime_error("Something strange: can't find rule " + r.first + " in FIRST set");
      }
      for (const auto& f : res) {
        it->second.insert(f);
      }
    }
  } while (firstChanged());
}

void generateFollow() {
  do {
    for (auto &r : rules) {
      auto it = FOLLOW.find(r.first);
      if (it == FOLLOW.end()) {
        throw std::runtime_error("Something strange: can't find rule " + r.first + " in FOLLOW set");
      }
      auto &AJ = it->second;

      for (auto &p : r.second.vars) {
        auto &w = p.rules;
        for (int i = 0; i < w.size(); ++i) {
          if (!is_token(w[i])) {
            auto it2 = FOLLOW.find(w[i]);
            if (it2 == FOLLOW.end()) {
              throw std::runtime_error("Something strange: can't find rule " + w[i] + " in FOLLOW set");
            }
            auto &AI = it2->second;

            auto fiw = fi(w, i + 1);
            for (auto &tt : fiw) {
              if (tt != empty/* and is_token(tt)*/) {
                AI.insert(tt);
              }
            }
            if ((fiw.find(empty) != fiw.end()) or (i == w.size() - 1)) {
              for (auto &tt : AJ) {
                AI.insert(tt);
              }
            }
          }
        }
      }
    }
  } while (followChanged());
}

int check() {
  if (rules.size() < 1) {
    std::cerr << "Must be at least one rule" << endl;
    return 1;
  }

  if (tokens.size() < 1) {
    std::cerr << "Must be at least one token" << endl;
    return 1;
  }

  for (const auto &t : tokens) {
    if (t == empty || t == end) {
      std::cerr << "Your cannot use " << t << " token" << std::endl;
      return 1;
    }
  }

  std::set<std::string> terms(tokens.begin(), tokens.end());
  tokens_set = std::set<std::string>(tokens.begin(), tokens.end());
  tokens_set.insert(end);
  tokens_set.insert(empty);

  for (const auto &t : rules) {
    terms.insert(t.first);
  }

  if (terms.find(start_token) == terms.end()) {
    std::cerr << "Start rule is not presented in rule list" << std::endl;
    return 1;
  }

  for (auto &r : rules) {
    for (auto &s : r.second.vars) {
      for (const auto &t : s.rules) {
        if (terms.find(t) == terms.end()) {
          std::cerr << t << " is not a token or rule" << endl;
          return 1;
        }
      }
    }
  }

  for (auto &r : rules) {
    FIRST.insert({r.first, std::set<std::string>()});
    FOLLOW.insert({r.first, std::set<std::string>()});
  }
  FOLLOW.find(start_token)->second.insert(end);

  return 0;
}

void generateCpp(std::ofstream &out) {
  out << "#include <string>" << endl;
  out << cpp << endl;

  //out << "extern enum token;" << endl;
  out << "struct unio;" << endl;
  out << "unio cur_unio;" << endl;
  out << "void next_token();" << endl;
  out << "token cur_token();" << endl;

  out << "unio parse(std::string &s) {" << endl;
  out << tab << "scan_string(s);" << endl;
  out << tab << "next_token();" << endl;
  out << tab << "return " << start_token << "();" << endl;
  out << "}" << endl << endl;
  out << "static unio consume(token t) {" << endl;
  out << tab << "if (t != cur_token()) throw std::runtime_error(\"unexpected token in consume\");" << endl;
  out << tab << "unio temp = cur_unio;" << endl;
  out << tab << "cur_unio = unio();" << endl;
  out << tab << "next_token();" << endl;
  out << tab << "return temp;" << endl;
  out << "}" << endl << endl;

  for (auto &r : rules) {
    out << "unio " << r.first << "() {" << endl;
    out << tab << "unio res = unio();" << endl;
    out << tab << "switch (cur_token()) {" << endl;
    bool exists_somebody = false;
    bool exists_me = false;
    std::vector<std::string> somebody;
    for (auto &alpha : r.second.vars) {
      auto& w = alpha.rules;
      if (!w.empty()) {
        auto fir = fi(w, 0);
        if (fir.find(empty) != fir.end()) {
          exists_somebody = true;
          somebody = w;
          fir.erase(empty);
        }
        for (auto& f : fir) {
          out << tab << tab << "case " << f << ": {" << endl;
          for (int i = 0; i < w.size(); ++i) {
            auto& r = w[i];
            out << tab << tab << tab << "auto val" << (i + 1) << " = ";
            if (is_token(r)) {
              out << "consume(" << r << ");" << endl;
            } else {
              out << r << "();" << endl;
            }
          }
          auto& code = alpha.code;
          if (code.find("$$") != std::string::npos) {
            auto jt = rule_type.find(r.first);
            if (jt == rule_type.end()) {
              throw std::runtime_error(r.first + std::string(" needs type, but it is not presented"));
            }
            code = std::regex_replace(code, std::regex("\\$\\$"), std::string("res.") + jt->second);
          }
          for (int i = 0; i < w.size(); ++i) {
            auto temp = std::string("$") + std::to_string(i + 1);
            if (code.find(temp) != std::string::npos) {
              std::string ty = "";
              if (is_token(w[i])) {
                auto jt = token_type.find(w[i]);
                if (jt == token_type.end()) {
                  throw std::runtime_error(w[i] + std::string(" needs type, but it is not presented"));
                }
                ty = jt->second;
              } else {
                auto jt = rule_type.find(w[i]);
                if (jt == rule_type.end()) {
                  throw std::runtime_error(w[i] + std::string(" needs type, but it is not presented"));
                }
                ty = jt->second;
              }
              code = std::regex_replace(code, std::regex(std::string("\\") + temp), std::string("val") + std::to_string(i + 1) + std::string(".") + ty);
            }
          }
          out << endl << tab << tab << tab << code << endl;
          out << tab << tab << "} break;" << endl;
        }
      } else {
        exists_me = true;
      }
    }

    if (exists_me) {
      auto ww = (FOLLOW.find(r.first))->second;
      for (auto it = ww.begin(); it != ww.end(); ++it) {
        out << tab << tab << "case " << *it << ":" << endl;
      }
      for (auto &alpha : r.second.vars) {
        auto& w = alpha.rules;
        if (w.empty()) {
          auto& code = alpha.code;
          if (code.find("$$") != std::string::npos) {
            auto jt = rule_type.find(r.first);
            if (jt == rule_type.end()) {
              throw std::runtime_error(r.first + std::string(" needs type, but it is not presented"));
            }
            code = std::regex_replace(code, std::regex("\\$\\$"), std::string("res.") + jt->second);
          }
          out << endl << tab << tab << tab << code << endl;
          break;
        }
      }
      out << tab << tab << "break;" << endl;
    } else if (exists_somebody) {
      auto ww = (FOLLOW.find(r.first))->second;
      for (auto it = ww.begin(); it != ww.end(); ++it) {
        out << tab << tab << "case " << *it << ":" << endl;
      }
      for (auto & ttt : somebody) {
        out << tab << tab << tab << ttt << "();";
      }
      out << tab << tab << "break;" << endl;
    }
    out << tab << tab << "default: {" << endl << tab << tab << tab << "throw ";
    out << "std::runtime_error(std::string(\"unexpected token (rule " << r.first << ")\") + \" \" + cur_string);" << endl;
    out << tab << tab << "} break;" << endl;
    out << tab << "}" << endl;
    out << tab << "return res;" << endl;
    out << "}" << endl << endl;
  }
}

void generateHeader(std::ofstream &out) {
  out << "#pragma once" << endl;
  out << "#include <string>" << endl;
  out << header << endl;
  tokens.push_back(empty);
  tokens.push_back(end);
  out << "enum token {" << endl << tab;
  for (const auto &t : tokens) {
    out << t << ", ";
  }
  out << endl << "};" << endl << endl;

  out << "struct unio {" << endl;
  out << union_code << endl;
  out << endl << "};" << endl << endl;

  out << "extern unio cur_unio;" << endl;
  out << "extern unio parse(std::string &s);" << endl;

  for (auto &r : rules) {
    out << "unio " << r.first << "();" << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [parser file]" << endl;
    return 1;
  }

  std::string filename(argv[1]);
  if (!std::regex_match(filename, std::regex(".*\\.y")) or filename.length() <= 2) {
    std::cerr << "Filename must have .y extension" << endl;
    return 1;
  }

  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Cannot open parser file" << endl;
    return 1;
  }

  std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  yy_scan_string(content.data());
  yyparse();

  if (check()) return 1;
  generateFirst();
  generateFollow();

  /*
  outputSets(FIRST);
  std::cout << std::endl;
  outputSets(FOLLOW);
  */

  std::string prefix = filename.substr(0, filename.length() - 2);

  std::ofstream outCpp(prefix + ".cpp");
  if (!outCpp.is_open()) {
    std::cerr << "Cannot open cpp file to generate parser" << endl;
    return 1;
  }
  generateCpp(outCpp);

  std::ofstream outHeader(prefix + ".h");
  if (!outHeader.is_open()) {
    std::cerr << "Cannot open header file to generate parser" << endl;
    return 1;
  }
  generateHeader(outHeader);

  return 0;
}
