#include <string>

  #include "parser.h"
  #include "lexer.h"

struct unio;
unio cur_unio;
void next_token();
token cur_token();
unio parse(std::string &s) {
  scan_string(s);
  next_token();
  return EXPR();
}

static unio consume(token t) {
  if (t != cur_token()) throw std::runtime_error("unexpected token in consume");
  unio temp = cur_unio;
  cur_unio = unio();
  next_token();
  return temp;
}

unio CON() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = NEG();
      auto val2 = CONN();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("and", {*val1.t, *val2.t}); 
    } break;
    case NOT: {
      auto val1 = NEG();
      auto val2 = CONN();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("and", {*val1.t, *val2.t}); 
    } break;
    case VAR: {
      auto val1 = NEG();
      auto val2 = CONN();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("and", {*val1.t, *val2.t}); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule CON)") + " " + cur_string);
    } break;
  }
  return res;
}

unio CONN() {
  unio res = unio();
  switch (cur_token()) {
    case AND: {
      auto val1 = consume(AND);
      auto val2 = CON();

       res.t = val2.t; 
    } break;
    case END:
    case OR:
    case RBR:
    case XOR:

       res.t = nullptr; 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule CONN)") + " " + cur_string);
    } break;
  }
  return res;
}

unio DIS() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = CON();
      auto val2 = DISS();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("or", {*val1.t, *val2.t}); 
    } break;
    case NOT: {
      auto val1 = CON();
      auto val2 = DISS();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("or", {*val1.t, *val2.t}); 
    } break;
    case VAR: {
      auto val1 = CON();
      auto val2 = DISS();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("or", {*val1.t, *val2.t}); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule DIS)") + " " + cur_string);
    } break;
  }
  return res;
}

unio DISS() {
  unio res = unio();
  switch (cur_token()) {
    case OR: {
      auto val1 = consume(OR);
      auto val2 = DIS();

       res.t = val2.t; 
    } break;
    case END:
    case RBR:
    case XOR:

       res.t = nullptr; 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule DISS)") + " " + cur_string);
    } break;
  }
  return res;
}

unio EXPR() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = DIS();
      auto val2 = EXPRR();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("xor", {*val1.t, *val2.t}); 
    } break;
    case NOT: {
      auto val1 = DIS();
      auto val2 = EXPRR();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("xor", {*val1.t, *val2.t}); 
    } break;
    case VAR: {
      auto val1 = DIS();
      auto val2 = EXPRR();

       if (val2.t == nullptr) res.t = val1.t; else res.t = new tree("xor", {*val1.t, *val2.t}); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule EXPR)") + " " + cur_string);
    } break;
  }
  return res;
}

unio EXPRR() {
  unio res = unio();
  switch (cur_token()) {
    case XOR: {
      auto val1 = consume(XOR);
      auto val2 = EXPR();

       res.t = val2.t; 
    } break;
    case END:
    case RBR:

       res.t = nullptr; 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule EXPRR)") + " " + cur_string);
    } break;
  }
  return res;
}

unio NEG() {
  unio res = unio();
  switch (cur_token()) {
    case VAR: {
      auto val1 = consume(VAR);

       res.t = val1.t; 
    } break;
    case NOT: {
      auto val1 = consume(NOT);
      auto val2 = NEG();

       res.t = new tree("not", {*val2.t}); 
    } break;
    case LBR: {
      auto val1 = consume(LBR);
      auto val2 = EXPR();
      auto val3 = consume(RBR);

       res.t = val2.t; 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule NEG)") + " " + cur_string);
    } break;
  }
  return res;
}

