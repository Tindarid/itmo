#pragma once
#include <string>

/*
L -> E EEE
EEE -> = E | eps
E -> A EE
EE -> + A EE | - A EE | eps
A -> C AA
AA -> * C AA | / C AA | eps
C -> B | B >> C
B -> NUM | (E) | -B | VAR
*/
#include <map>
#include <iostream>
extern std::map<char, int> gl_map;
struct expr {
  int type;
  expr *a, *b;
  int num;
  char ch;
  expr(int t, expr* a1, expr* b1, int n) {
    type = t; a = a1; b = b1; num = n;
  }
  expr(char c) { ch = c; type = -1; }
  int count(int c) {
    switch (type) {
      case 0: //EE
        return b->count(c + a->count(0)); 
      case 1: //EE
        return b->count(c - a->count(0)); 
      case 2: //AA
        return b->count(c * a->count(0)); 
      case 3: //AA
        return b->count(c / a->count(0)); 
      case 4: //AA or EE
        return c; 
      case 5: // E
        return b->count(a->count(0));
      case 6: // A
        return b->count(a->count(0));
      case 7: // B
        return -a->count(0);
      case -100: // SHIFT
        //std::cout << b->count(0) << std::endl;
        //std::cout << a->count(0) << std::endl;
        return a->count(0) >> b->count(0);
      case -1: // VAR
        if (gl_map.find(ch) == gl_map.end()) {
          throw std::runtime_error("no such variable");
        }
        return gl_map.find(ch)->second;
      case -2:
        if (b == nullptr) {
          return a->count(0);
        } else {
          if (!(a->b != nullptr && a->b->b == nullptr && a->b->a == nullptr &&
              a->a != nullptr && a->a->b != nullptr && a->a->b->a == nullptr && a->a->b->b == nullptr &&
              a->a->a != nullptr && a->a->a->type == -1)) {
            throw std::runtime_error("on the left we have only variables");
          }
          int ans = b->count(0);
          char c = a->a->a->ch;
          std::cout << c << " = ";
          gl_map.insert({c, ans});
          return ans;
        }
      default:
        return num;
    }
  }
};

enum token {
  VAR, NUM, PLUS, MINUS, MUL, DIV, LBR, RBR, EQUAL, SHIFT, EMPTY, END, 
};

struct unio {

  expr* e;
  int num;
  char ch;


};

extern unio cur_unio;
extern unio parse(std::string &s);
unio A();
unio AA();
unio B();
unio C();
unio E();
unio EE();
unio EEE();
unio L();
unio P();
