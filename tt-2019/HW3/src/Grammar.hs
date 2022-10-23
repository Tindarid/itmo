module Grammar where

data Expr = Var String | Lambda String Expr | Appl Expr Expr
data Type = Impl Type Type | Single String deriving (Eq, Ord)
data Term = Term Expr Type
data Node = Default Term Node Node [(String, Type)] | Empty

instance Show Expr where
        show (Lambda x y) = "(\\" ++ x ++ ". " ++ show y ++ ")"
        show (Appl x y)   = "(" ++ show x ++ " " ++ show y ++ ")"
        show (Var x)      = x

instance Show Type where
        show (Impl x y) = "(" ++ show x ++ " -> " ++ show y ++ ")"
        show (Single x) = x

getType (Default (Term _ t) _ _ _) = t
getType Empty = Single "Empty"

