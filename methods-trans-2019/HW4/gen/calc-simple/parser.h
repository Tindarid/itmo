#pragma once
#include <string>

/*
E -> A EE
EE -> + A EE | - A EE | eps
A -> B AA
AA -> * B AA | / B AA | eps
B -> NUM | (E) | -B
*/
struct expr {
  int type;
  expr *a, *b;
  int num;
  expr(int t, expr* a1, expr* b1, int n) {
    type = t; a = a1; b = b1; num = n;
  }
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
      default:
        return num;
    }
  }
};

enum token {
  NUM, PLUS, MINUS, MUL, DIV, LBR, RBR, EMPTY, END, 
};

struct unio {

  expr* e;
  int num;


};

extern unio cur_unio;
extern unio parse(std::string &s);
unio A();
unio AA();
unio B();
unio E();
unio EE();
