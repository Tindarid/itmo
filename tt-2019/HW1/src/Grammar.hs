module Grammar where

data Expr = Var String | Lambda String Expr | Appl Expr Expr

instance Show Expr where
        show (Lambda x y) = "(\\" ++ x ++ "." ++ show y ++ ")"
        show (Appl x y)   = "(" ++ show x ++ " " ++ show y ++ ")"
        show (Var x)      = x
