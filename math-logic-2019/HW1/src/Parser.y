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
%token NOT   { TNot }
%token AND   { TAnd }
%token OR    { TOr }
%token IMPL  { TImpl }
%token VAR   { TVar $$ }

%%

Expr
    : Dis               { $1 }
    | Dis IMPL Expr     { Binary Impl $1 $3 }

Dis
    : Con               { $1 }
    | Dis OR Con        { Binary Or $1 $3 }

Con
    : Term              { $1 }
    | Con AND Term      { Binary And $1 $3 }

Term
    : NOT Term          { Unary Not $2 }
    | VAR               { Var $1 }
    | LEFT Expr RIGHT   { $2 }
{
parseError = fail "Parse error"
}
