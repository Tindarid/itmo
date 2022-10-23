#pragma once
#include <string>

  #include "tree.h"

enum token {
  VAR, XOR, OR, AND, NOT, LBR, RBR, EMPTY, END, 
};

struct unio {

  tree *t;


};

extern unio cur_unio;
extern unio parse(std::string &s);
unio CON();
unio CONN();
unio DIS();
unio DISS();
unio EXPR();
unio EXPRR();
unio NEG();
