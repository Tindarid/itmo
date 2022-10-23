{
module Lexer where
}

%wrapper "basic"

$digit = 0-9
$alpha = [A-Z]
$comma = [\']

tokens :-

  $white+                           ;
  \(                                { \s -> TLeft }
  \)                                { \s -> TRight }
  !                                 { \s -> TNot }
  &                                 { \s -> TAnd }
  \|                                { \s -> TOr }
  "->"                              { \s -> TImpl }
  $alpha [$alpha $digit $comma]*    { \s -> TVar s }

{

data Token = TLeft | TRight | TNot | TAnd | TOr | TImpl | TVar String deriving (Show, Eq)

}
