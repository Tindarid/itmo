#pragma once

#include <string>

enum token {
  VAR, END, AND, OR, XOR, NOT, LPAREN, RPAREN
};

class lexer {
private:
  std::string src;
  std::string word;
  char cur_char;
  int cur_pos;
  token cur_token;

  void next_char() {
    cur_char = ++cur_pos == src.length() ? -1 : src[cur_pos];
  }

public:
  lexer(const std::string &s) : src(s), cur_pos(-1), word("") {
    next_char();
  }

  void next() {
    while (isspace(cur_char)) {
      next_char();
    }

    word.clear();
    if (islower(cur_char)) {
      while (islower(cur_char)) {
        word += cur_char;
        next_char();
      }
      if (word.length() == 1) {
        cur_token = token::VAR;
      } else if (word == "and") {
        cur_token = token::AND;
      } else if (word == "xor") {
        cur_token = token::XOR;
      } else if (word == "or") {
        cur_token = token::OR;
      } else if (word == "not") {
        cur_token = token::NOT;
      } else {
        throw std::runtime_error((std::string("lexer error: illegal word ") + word).c_str());
      }
    } else {
      switch (cur_char) {
        case '(':
          cur_token = token::LPAREN;
          break;
        case ')':
          cur_token = token::RPAREN;
          break;
        case -1:
          cur_token = token::END;
          break;
        default:
          throw std::runtime_error((std::string("lexer error: illegal character ") + cur_char).c_str());
          break;
      }
      next_char();
    }
  }

  token cur() {
    return cur_token;
  }

  token get_next() {
    next();
    return cur();
  }

  std::string cur_word() {
    return word;
  }

  int get_pos() {
    return cur_pos;
  }
};
