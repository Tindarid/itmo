%code requires {
  #include <string>
  #include <vector>
  #include <set>
}

%{
  #include <string>
  #include <vector>
  int yylex(void);
  void yyerror(const char*);

  std::vector<std::pair<std::string, std::string>> reg_to_action;
  std::string header, cpp;
%}

%union {
  std::string *inner;
}

%token <inner> REGEXP CODE
%token SEP LBR RBR SEPSEP
%type <inner> CODEE COD

%start INPUT

%%

INPUT: 
    SEP CODEE SEP SEP CODEE SEP SEPSEP RULES SEPSEP { header = *$2; cpp = *$5; }

RULES:
    RULE RULES {} | {}

RULE:
    REGEXP CODEE { reg_to_action.push_back({*$1, *$2}); }

CODEE:
    LBR COD RBR { $$ = $2; } 

COD:
  CODE COD { $$ = new std::string(*$1 + *$2); delete $1; delete $2;} 
  | { $$ = new std::string(""); }

%%
