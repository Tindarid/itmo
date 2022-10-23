%{
  #include <string>
  #include "parser.hpp"
  extern void yyerror(const char *);
  int balanc = 0;
%}

%option outfile="gen/lexer.cpp" header-file="gen/lexer.hpp"
%option noyywrap

white  [ \t\n]+
atom   [A-Za-z]+
type   \<{atom}\>
code   [^{}]*

%x INBRACKETS

%%

<INITIAL>{white}    {                   }
<INITIAL>"%union"   { return UNION;     }
<INITIAL>"%start"   { return START;     }
<INITIAL>"%token"   { return TOKENLIST; }
<INITIAL>"%type"    { return TYPELIST; }
<INITIAL>{atom}     { yylval.inner = new std::string(yytext);
                      return ATOM;      }
<INITIAL>{type}     { yylval.inner = new std::string(yytext + 1, strlen(yytext) - 2);
                      return TYPE;      }
<INITIAL>"%"        { return SEP;    }
<INITIAL>"%%"       { return SEPSEP;    }
<INITIAL>"|"        { return OR;       }
<INITIAL>":"        { return DOTS;       }
<INITIAL>"{"        { balanc++; BEGIN(INBRACKETS); return LBR; }
<INITIAL>.          { std::string error = std::string("unexpected character: ") + *yytext;
                      yyerror(error.data());
                      return *yytext;   }

<INBRACKETS>{code}  { yylval.inner = new std::string(yytext);
                       return CODE; }
<INBRACKETS>"}"     { balanc--; if (balanc == 0) { BEGIN(INITIAL); return RBR; } 
                      yylval.inner = new std::string("}"); return CODE; }
<INBRACKETS>"{"     { balanc++; yylval.inner = new std::string("{"); return CODE; }

%%
