{
module Lexer where
}

%wrapper "basic"

tokens :-

  $white+                           ;
  \(                                { \s -> TLeft }
  \)                                { \s -> TRight }
  \*                                { \s -> TMul }
  \-                                { \s -> TMinus }
  \+                                { \s -> TPlus }
  \/                                { \s -> TDiv }
  \=                                { \s -> TEq }
  \;                                { \s -> TEnd }
  \%                                { \s -> TMod }
  [a-z]+                            { \s -> TVar s }
  [0-9]+                            { \s -> TNumber s }

{

data Token = TLeft | TRight | TMul | TMinus | TPlus | TDiv | TEq | TEnd | TNumber String | TVar String | TMod deriving (Show, Eq)

}
