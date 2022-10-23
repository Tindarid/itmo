%{
  #include "tree.h"
}%

%{
  #include "parser.h"
  #include "lexer.h"
}%

%union {
  tree *t;
}

%token<t> VAR XOR OR AND NOT LBR RBR
%type<t> EXPR EXPRR DIS DISS CON CONN NEG

%start EXPR

%%

EXPR: DIS EXPRR { if ($2 == nullptr) $$ = $1; else $$ = new tree("xor", {*$1, *$2}); }
EXPRR: XOR EXPR { $$ = $2; } | { $$ = nullptr; }
DIS:  CON DISS { if ($2 == nullptr) $$ = $1; else $$ = new tree("or", {*$1, *$2}); }
DISS: OR DIS { $$ = $2; } | { $$ = nullptr; }
CON:  NEG CONN { if ($2 == nullptr) $$ = $1; else $$ = new tree("and", {*$1, *$2}); }
CONN: AND CON { $$ = $2; } | { $$ = nullptr; }
NEG: VAR { $$ = $1; } 
     | NOT NEG { $$ = new tree("not", {*$2}); } 
     | LBR EXPR RBR { $$ = $2; }

%%
