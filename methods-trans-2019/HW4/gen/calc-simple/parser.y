%{
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
}%

%{
  #include "parser.h"
  #include "lexer.h"
  #include <utility>
  #include <stdexcept>
}%

%union {
  expr* e;
  int num;
}

%token<num> NUM
%token PLUS MINUS MUL DIV LBR RBR
%type<e> E EE A AA B

%start E

%%

E: A EE { $$ = new expr(5, $1, $2,0 ); }
EE: PLUS A EE { $$ = new expr(0, $2, $3, 0); } | MINUS A EE { $$ = new expr(1, $2, $3, 0); } | { $$ = new expr(4, nullptr, nullptr, 0); }
A: B AA { $$ = new expr(6, $1, $2, 0); }
AA: MUL B AA { $$ = new expr(2, $2, $3, 0); } | DIV B AA { $$ = new expr(3, $2, $3, 0); } | { $$ = new expr(4, nullptr, nullptr, 0); }
B: NUM { $$ = new expr(8, nullptr, nullptr, $1); } | LBR E RBR { $$ = $2; } | MINUS B { $$ = new expr(7, $2, nullptr, 0); }

%%
