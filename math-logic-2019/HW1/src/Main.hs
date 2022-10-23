module Main where

import Grammar (Expr (..))
import Lexer (alexScanTokens)
import Parser (parse)

main :: IO ()
main = do
  input <- getLine
  case parse (alexScanTokens input) of
    Left error   -> putStrLn error
    Right expr   -> putStrLn (show expr)
