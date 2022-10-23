#include <string>

  #include "parser.h"
  #include "lexer.h"
  #include <utility>
  #include <stdexcept>
  #include <map>
  std::map<char, int> gl_map;
  // 4 >> 1 >> 2 = 4 >> (1 >> 2)

struct unio;
unio cur_unio;
void next_token();
token cur_token();
unio parse(std::string &s) {
  scan_string(s);
  next_token();
  return L();
}

static unio consume(token t) {
  if (t != cur_token()) throw std::runtime_error("unexpected token in consume");
  unio temp = cur_unio;
  cur_unio = unio();
  next_token();
  return temp;
}

unio A() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = C();
      auto val2 = AA();

       res.e = new expr(6, val1.e, val2.e, 0); 
    } break;
    case MINUS: {
      auto val1 = C();
      auto val2 = AA();

       res.e = new expr(6, val1.e, val2.e, 0); 
    } break;
    case NUM: {
      auto val1 = C();
      auto val2 = AA();

       res.e = new expr(6, val1.e, val2.e, 0); 
    } break;
    case VAR: {
      auto val1 = C();
      auto val2 = AA();

       res.e = new expr(6, val1.e, val2.e, 0); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule A)") + " " + cur_string);
    } break;
  }
  return res;
}

unio AA() {
  unio res = unio();
  switch (cur_token()) {
    case MUL: {
      auto val1 = consume(MUL);
      auto val2 = C();
      auto val3 = AA();

       res.e = new expr(2, val2.e, val3.e, 0); 
    } break;
    case DIV: {
      auto val1 = consume(DIV);
      auto val2 = C();
      auto val3 = AA();

       res.e = new expr(3, val2.e, val3.e, 0); 
    } break;
    case END:
    case EQUAL:
    case MINUS:
    case PLUS:
    case RBR:

       res.e = new expr(4, nullptr, nullptr, 0); 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule AA)") + " " + cur_string);
    } break;
  }
  return res;
}

unio B() {
  unio res = unio();
  switch (cur_token()) {
    case NUM: {
      auto val1 = consume(NUM);

       res.e = new expr(8, nullptr, nullptr, val1.num); 
    } break;
    case LBR: {
      auto val1 = consume(LBR);
      auto val2 = E();
      auto val3 = consume(RBR);

       res.e = val2.e; 
    } break;
    case MINUS: {
      auto val1 = consume(MINUS);
      auto val2 = B();

       res.e = new expr(7, val2.e, nullptr, 0); 
    } break;
    case VAR: {
      auto val1 = consume(VAR);

       res.e = new expr(val1.ch); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule B)") + " " + cur_string);
    } break;
  }
  return res;
}

unio C() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = B();
      auto val2 = P();

       if (val2.e->a == nullptr && val2.e->b == nullptr) res.e = val1.e; else res.e = new expr(-100, val1.e, val2.e->a, 0); 
    } break;
    case MINUS: {
      auto val1 = B();
      auto val2 = P();

       if (val2.e->a == nullptr && val2.e->b == nullptr) res.e = val1.e; else res.e = new expr(-100, val1.e, val2.e->a, 0); 
    } break;
    case NUM: {
      auto val1 = B();
      auto val2 = P();

       if (val2.e->a == nullptr && val2.e->b == nullptr) res.e = val1.e; else res.e = new expr(-100, val1.e, val2.e->a, 0); 
    } break;
    case VAR: {
      auto val1 = B();
      auto val2 = P();

       if (val2.e->a == nullptr && val2.e->b == nullptr) res.e = val1.e; else res.e = new expr(-100, val1.e, val2.e->a, 0); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule C)") + " " + cur_string);
    } break;
  }
  return res;
}

unio E() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = A();
      auto val2 = EE();

       res.e = new expr(5, val1.e, val2.e, 0); 
    } break;
    case MINUS: {
      auto val1 = A();
      auto val2 = EE();

       res.e = new expr(5, val1.e, val2.e, 0); 
    } break;
    case NUM: {
      auto val1 = A();
      auto val2 = EE();

       res.e = new expr(5, val1.e, val2.e, 0); 
    } break;
    case VAR: {
      auto val1 = A();
      auto val2 = EE();

       res.e = new expr(5, val1.e, val2.e, 0); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule E)") + " " + cur_string);
    } break;
  }
  return res;
}

unio EE() {
  unio res = unio();
  switch (cur_token()) {
    case PLUS: {
      auto val1 = consume(PLUS);
      auto val2 = A();
      auto val3 = EE();

       res.e = new expr(0, val2.e, val3.e, 0); 
    } break;
    case MINUS: {
      auto val1 = consume(MINUS);
      auto val2 = A();
      auto val3 = EE();

       res.e = new expr(1, val2.e, val3.e, 0); 
    } break;
    case END:
    case EQUAL:
    case RBR:

       res.e = new expr(4, nullptr, nullptr, 0); 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule EE)") + " " + cur_string);
    } break;
  }
  return res;
}

unio EEE() {
  unio res = unio();
  switch (cur_token()) {
    case EQUAL: {
      auto val1 = consume(EQUAL);
      auto val2 = E();

       res.e = val2.e; 
    } break;
    case END:

       res.e = nullptr; 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule EEE)") + " " + cur_string);
    } break;
  }
  return res;
}

unio L() {
  unio res = unio();
  switch (cur_token()) {
    case LBR: {
      auto val1 = E();
      auto val2 = EEE();

       res.e = new expr(-2, val1.e, val2.e, 0); 
    } break;
    case MINUS: {
      auto val1 = E();
      auto val2 = EEE();

       res.e = new expr(-2, val1.e, val2.e, 0); 
    } break;
    case NUM: {
      auto val1 = E();
      auto val2 = EEE();

       res.e = new expr(-2, val1.e, val2.e, 0); 
    } break;
    case VAR: {
      auto val1 = E();
      auto val2 = EEE();

       res.e = new expr(-2, val1.e, val2.e, 0); 
    } break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule L)") + " " + cur_string);
    } break;
  }
  return res;
}

unio P() {
  unio res = unio();
  switch (cur_token()) {
    case SHIFT: {
      auto val1 = consume(SHIFT);
      auto val2 = C();

       res.e = new expr(8, val2.e, nullptr, 0); 
    } break;
    case DIV:
    case END:
    case EQUAL:
    case MINUS:
    case MUL:
    case PLUS:
    case RBR:

      res.e = new expr(4, nullptr, nullptr, 0); 
    break;
    default: {
      throw std::runtime_error(std::string("unexpected token (rule P)") + " " + cur_string);
    } break;
  }
  return res;
}

