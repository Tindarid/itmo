{
module Parser where

import Grammar
import Lexer
}

%name      parse
%tokentype { Token }
%error     { parseError }
%monad     { Either String }{ >>= }{ return }

%token LEFT  { TLeft }
%token RIGHT { TRight }
%token POINT { TPoint }
%token SLASH { TSlash }
%token VAR   { TVar $$ }

%%

Expr
    : Application                       { $1 }
    | SLASH VAR POINT Expr              { Lambda $2 $4 }
    | Application SLASH VAR POINT Expr  { Appl $1 (Lambda $3 $5) }
Application
    : Atom                              { $1 }
    | Application Atom                  { Appl $1 $2 }
Atom
    : VAR                               { Var $1 }
    | LEFT Expr RIGHT                   { $2 }
{
parseError = fail "Parse error"
}
