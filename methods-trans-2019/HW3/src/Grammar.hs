module Grammar where

data Expr = Eq Expr Expr | Plus Expr Expr | Var String | Minus Expr Expr | Mul Expr Expr | Div Expr Expr | Number String | Neg Expr | Mod Expr Expr

instance Show Expr where
  show (Eq a b)    = (show a) ++ " = " ++ (show b)
  show (Plus a b)  = "(" ++ (show a) ++ " + " ++ (show b) ++ ")"
  show (Mod a b)  = "(" ++ (show a) ++ " % " ++ (show b) ++ ")"
  show (Minus a b) = "(" ++ (show a) ++ " - " ++ (show b) ++ ")"
  show (Mul a b)   = "(" ++ (show a) ++ " * " ++ (show b) ++ ")"
  show (Div a b)   = "(" ++ (show a) ++ " / " ++ (show b) ++ ")"
  show (Var a)     = a
  show (Number a)  = a
  show (Neg a)     = "(-" ++ (show a) ++ ")"

