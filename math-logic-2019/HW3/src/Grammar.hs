module Grammar where

data Expr = Impl Expr Expr | And Expr Expr | Or Expr Expr | Not Expr | Var String deriving (Eq, Ord)

instance Show Expr where
        show (And x y)  = "(" ++ show x ++ " & " ++ show y ++ ")"
        show (Or x y)   = "(" ++ show x ++ " | " ++ show y ++ ")"
        show (Impl x y) = "(" ++ show x ++ " -> " ++ show y ++ ")"
        show (Not x)    = "(!" ++ show x ++ ")"
        show (Var var)  = var
