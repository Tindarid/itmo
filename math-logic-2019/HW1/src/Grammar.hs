module Grammar where

data Op = And | Or | Impl | Not
data Expr = Binary Op Expr Expr | Unary Op Expr | Var String

instance Show Op where
        show And  = "&"
        show Or   = "|"
        show Impl = "->"
        show Not  = "!"

instance Show Expr where
        show (Binary op x y) = "(" ++ show op ++ "," ++ show x ++ "," ++ show y ++ ")"
        show (Unary op x)    = "(" ++ show op ++ show x ++ ")"
        show (Var var)       = var
