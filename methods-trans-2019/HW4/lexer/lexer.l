%{
  #include <string>
  #include "parser.hpp"
  extern void yyerror(const char *);
  int balanc = 0;
%}

%option outfile="gen/lexer.cpp" header-file="gen/lexer.hpp"
%option noyywrap

white  [ \t\n]+
regexp \"(([^"])|(\\\"))+\"
code   [^{}]*

%x INBRACKETS

%%

<INITIAL>{white}    {                 }
<INITIAL>"%"        { return SEP;     }
<INITIAL>"%%"       { return SEPSEP;  }
<INITIAL>{regexp}   { yylval.inner = new std::string(yytext + 1, strlen(yytext) - 2);
                      return REGEXP;  }
<INITIAL>"{"        { balanc++; BEGIN(INBRACKETS); return LBR; }
<INITIAL>.          { std::string error = std::string("unexpected character: ") + *yytext;
                      yyerror(error.data());
                      return *yytext; }
<INBRACKETS>{code}  { yylval.inner = new std::string(yytext);
                       return CODE; }
<INBRACKETS>"}"     { balanc--; if (balanc == 0) { BEGIN(INITIAL); return RBR; } 
                      yylval.inner = new std::string("}"); return CODE; }
<INBRACKETS>"{"     { balanc++; yylval.inner = new std::string("{"); return CODE; }


%%
