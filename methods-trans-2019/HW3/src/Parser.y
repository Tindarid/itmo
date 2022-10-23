{
module Parser where

import Grammar
import Lexer
}

%name      parse
%tokentype { Token }
%error     { parseError }
%monad     { Either String }{ >>= }{ return }

%token LEFT   { TLeft }
%token RIGHT  { TRight }
%token MUL    { TMul }
%token DIV    { TDiv }
%token PLUS   { TPlus }
%token MINUS  { TMinus }
%token VAR    { TVar $$ }
%token EQ     { TEq }
%token END    { TEnd }
%token NUMBER { TNumber $$ }
%token MOD    { TMod }

%%

L
    : E EQ E END   { Eq $1 $3}
    | E            { $1 }

E
    : A               { $1 }
    | E PLUS A        { Plus $1 $3 }
    | E MINUS A       { Minus $1 $3 }

A
    : K            { $1 }
    | A MUL K      { Mul $1 $3 }
    | A DIV K      { Div $1 $3 }

K
    : B            { $1 }
    | B MOD K      { Mod $1 $3 }

B
    : MINUS B           { Neg $2 }
    | VAR               { Var $1 }
    | NUMBER            { Number $1 }
    | LEFT E RIGHT      { $2 }

{
parseError tokens = fail "Parse error"
}
