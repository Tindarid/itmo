#pragma once
#include "lexer.h"
#include "tree.h"
#include <iostream>

class parser {
  lexer lex;

  tree temp() {
    tree ans("");
    switch (lex.cur()) {
      case token::VAR:
        ans = tree("Rule: Temp", {tree("Term: " + lex.cur_word())});
        lex.next();
        break;
      case token::LPAREN:
        lex.next();
        ans = tree("Rule: Temp", {tree("Term: ("), expr(), tree("Term: )")});
        if (lex.cur() != token::RPAREN) {
          throw std::runtime_error(std::string("parser error: expected \")\" at ") + std::to_string(lex.get_pos()));
        }
        lex.next();
        break;
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
    return ans;
  }

  tree nott() {
    tree ans;
    switch (lex.cur()) {
      case token::VAR:
      case token::LPAREN:
        ans = tree("Rule: Not", {temp()});
        break;
      case token::NOT:
        lex.next();
        ans = tree("Rule: Not", {tree("Term: not"), temp()});
        break;
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
    return ans;
  }

  tree con_() {
    switch (lex.cur()) {
      case token::AND:
        lex.next();
        return tree("Rule: Con'", {tree("Term: and"), con()});
      case token::RPAREN:
      case token::END:
      case token::XOR:
      case token::OR:
        return tree("Rule: Con'", {tree("eps")});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

  tree con() {
    tree n, c;
    switch (lex.cur()) {
      case token::VAR:
      case token::NOT:
      case token::LPAREN:
        n = nott();
        c = con_();
        return tree("Rule: Con", {n, c});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

  tree dis_() {
    switch (lex.cur()) {
      case token::OR:
        lex.next();
        return tree("Rule: Dis'", {tree("Term: or"), dis()});
      case token::RPAREN:
      case token::END:
      case token::XOR:
        return tree("Rule: Dis'", {tree("eps")});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

  tree dis() {
    tree c, d;
    switch (lex.cur()) {
      case token::VAR:
      case token::NOT:
      case token::LPAREN:
        c = con();
        d = dis_();
        return tree("Rule: Dis", {c, d});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

  tree expr_() {
    switch (lex.cur()) {
      case token::XOR:
        lex.next();
        return tree("Rule: Expr'", {tree("Term: xor"), expr()});
      case token::RPAREN:
      case token::END:
        return tree("Rule: Expr'", {tree("eps")});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

  tree expr() {
    tree d, e;
    switch (lex.cur()) {
      case token::VAR:
      case token::NOT:
      case token::LPAREN:
        d = dis();
        e = expr_();
        return tree("Rule: Expr", {d, e});
      default:
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
  }

public:
  parser() : lex("") { }
  tree parse(const std::string &s) {
    lex = lexer(s); lex.next();
    auto ans = expr();
    if (lex.cur() != token::END) {
        throw std::runtime_error(std::string("parser error: unexpected token at ") + std::to_string(lex.get_pos()));
    }
    return ans;
  }
};
