module Main where

import Grammar
import Lexer (alexScanTokens)
import Parser (parse)

import System.IO (isEOF)

import Data.Map (Map)
import qualified Data.Map as Map

main = resolveNextLine Map.empty

resolveNextLine m = do
  eof <- isEOF
  if (eof) then return ()
  else do
    input <- getLine
    case parse (alexScanTokens input) of
      Left error   -> putStrLn error
      Right expr   -> case expr of
                        (Eq (Var v) e)  -> case eval e m of
                                          Left er   -> do
                                                      putStrLn er
                                                      resolveNextLine m
                                          Right res -> do
                                                      putStrLn (v ++ " = " ++ show res)
                                                      resolveNextLine (Map.insert v res m)
                        (Eq _ _)       -> do
                                          putStrLn "Left expr must be variable"
                                          resolveNextLine m
                        _              -> case eval expr m of
                                          Left e    -> do
                                                      putStrLn e
                                                      resolveNextLine m
                                          Right res -> do
                                                      putStrLn (show res)
                                                      resolveNextLine m

eval (Mod e1 e2) m  = case eval e1 m of
                         (Left er1) -> Left er1
                         Right a1   -> case eval e2 m of
                                       (Left er2) -> Left er2
                                       (Right a2) -> case a2 of 
                                                     0 -> Left "Division(mod) by zero"
                                                     _ -> Right (a1 `mod` a2)
eval (Minus e1 e2) m  = case eval e1 m of
                         (Left er1) -> Left er1
                         Right a1   -> case eval e2 m of
                                       (Left er2) -> Left er2
                                       (Right a2) -> Right (a1 - a2)
eval (Plus e1 e2) m  = case eval e1 m of
                         (Left er1) -> Left er1
                         Right a1   -> case eval e2 m of
                                       (Left er2) -> Left er2
                                       (Right a2) -> Right (a1 + a2)
eval (Mul e1 e2) m  = case eval e1 m of
                         (Left er1) -> Left er1
                         Right a1   -> case eval e2 m of
                                       (Left er2) -> Left er2
                                       (Right a2) -> Right (a1 * a2)
eval (Div e1 e2) m  = case eval e1 m of
                         (Left er1) -> Left er1
                         Right a1   -> case eval e2 m of
                                       (Left er2) -> Left er2
                                       (Right a2) -> case a2 of 
                                                     0 -> Left "Division by zero"
                                                     _ -> Right (a1 `div` a2)
eval (Neg e) m       = case eval e m of
                          Right a  -> Right (-a)
                          (Left a) -> Left a
eval (Number n) m    = Right ((read n) :: Int)
eval (Var a) m       = case Map.lookup a m of 
                       Nothing -> Left ("No \"" ++  a ++ "\" in expressions before")
                       Just b  -> Right b
eval (Eq _ _) m      = Left "Cannot use several \"=\" in one expr"
