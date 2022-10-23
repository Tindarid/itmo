{
module Lexer where
}

%wrapper "basic"

$digit = 0-9
$alpha = [a-z]
$comma = [\']
$point = [\.]
$slash = [\\]

tokens :-

  $white+                           ;
  \(                                { \s -> TLeft }
  \)                                { \s -> TRight }
  $point                            { \s -> TPoint }
  $slash                            { \s -> TSlash }
  $alpha [$alpha $digit $comma]*    { \s -> TVar s }

{

data Token = TLeft | TRight | TPoint | TSlash | TVar String deriving (Show, Eq)

}
