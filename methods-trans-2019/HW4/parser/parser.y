%code requires {
  #include <string>
  #include <vector>
  #include <map>

  struct subrule {
    std::vector<std::string> rules;
    std::string code;
  };

  struct rule {
     std::vector<subrule> vars;
  };
}

%{
  #include <string>
  #include <vector>
  #include <map>
  int yylex(void);
  void yyerror(const char*);

  std::string header, cpp, union_code, start_token;
  std::vector<std::string> tokens;
  std::map<std::string, std::string> token_type, rule_type;
  struct rule;
  std::map<std::string, rule> rules;
%}

%union {
  std::string *inner;
  subrule *var;
  std::vector<std::string> *tokens;
  rule *vars;
}

%type <tokens> TOKENS
%type <vars> RULE
%type <inner> CODEE COD
%type <var> SUBRULE
%token <inner> TYPE ATOM CODE
%token SEP UNION TOKENLIST START OR DOTS RBR LBR SEPSEP TYPELIST

%start INPUT

%%

INPUT: 
    SEP CODEE SEP SEP CODEE SEP UNIONDESCR TOKENDESCR STARTDESCR SEPSEP RULES SEPSEP { 
      header = *$2; delete $2; 
      cpp = *$5; delete $5; 
    }

UNIONDESCR:
    UNION CODEE { union_code = *$2; delete $2; } | {}

TOKENDESCR:
    TDESCR TOKENDESCR {} | TTDESCR TOKENDESCR {} | TYPEDESCR TOKENDESCR {} | {}

TDESCR:
    TOKENLIST TOKENS { 
       std::vector<std::string> &toks = *$2;
       for (const auto& t : toks) {
         tokens.push_back(t);
       }
       delete $2;
    }

TTDESCR:
    TOKENLIST TYPE TOKENS {
       std::vector<std::string> &toks = *$3;
       for (const auto& t : toks) {
         tokens.push_back(t);
         token_type.insert({t, *$2});
       }
       delete $3; delete $2;
    }

TYPEDESCR:
    TYPELIST TYPE TOKENS {
       std::vector<std::string> &toks = *$3;
       for (const auto& t : toks) {
         rule_type.insert({t, *$2});
       }
       delete $3; delete $2;
    }

TOKENS:
    TOKENS ATOM {
      $$ = $1;
      $$->push_back(*$2);
      delete $2;
    } | { $$ = new std::vector<std::string>(); }

STARTDESCR:
    START ATOM { start_token = *$2; delete $2; }

RULES:
    ATOM DOTS RULE RULES {
      rules.insert({*$1, *$3});
      delete $1; delete $3;
    } | {}

RULE:
    RULE OR SUBRULE {
      $$ = $1; $$->vars.push_back(*$3); delete $3; }
    | SUBRULE {
      $$ = new rule(); $$->vars.push_back(*$1); delete $1; }

SUBRULE:
    TOKENS CODEE {
      $$ = new subrule();
      $$->rules = *$1;
      $$->code = *$2;
      delete $1; delete $2;
    }

CODEE:
    LBR COD RBR { $$ = $2; } 

COD:
  CODE COD { $$ = new std::string(*$1 + *$2); delete $1; delete $2;} 
  | { $$ = new std::string(""); }
%%
