%{
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
}%

%{
  #include "parser.h"
  #include "lexer.h"
  #include <utility>
  #include <stdexcept>
  #include <map>
  std::map<char, int> gl_map;
  // 4 >> 1 >> 2 = 4 >> (1 >> 2)
}%

%union {
  expr* e;
  int num;
  char ch;
}

%token<ch> VAR
%token<num> NUM
%token PLUS MINUS MUL DIV LBR RBR EQUAL SHIFT
%type<e> E EE A AA B EEE L C P

%start L

%%

L: E EEE { $$ = new expr(-2, $1, $2, 0); }
EEE: EQUAL E { $$ = $2; } | { $$ = nullptr; }
E: A EE { $$ = new expr(5, $1, $2, 0); }
EE: PLUS A EE { $$ = new expr(0, $2, $3, 0); } | MINUS A EE { $$ = new expr(1, $2, $3, 0); } | { $$ = new expr(4, nullptr, nullptr, 0); }
A: C AA { $$ = new expr(6, $1, $2, 0); }
AA: MUL C AA { $$ = new expr(2, $2, $3, 0); } | DIV C AA { $$ = new expr(3, $2, $3, 0); } | { $$ = new expr(4, nullptr, nullptr, 0); }
C: B P { if ($2->a == nullptr && $2->b == nullptr) $$ = $1; else $$ = new expr(-100, $1, $2->a, 0); }
P: SHIFT C { $$ = new expr(8, $2, nullptr, 0); } | {$$ = new expr(4, nullptr, nullptr, 0); }
B: NUM { $$ = new expr(8, nullptr, nullptr, $1); } | LBR E RBR { $$ = $2; } | MINUS B { $$ = new expr(7, $2, nullptr, 0); } | VAR { $$ = new expr($1); }

%%
