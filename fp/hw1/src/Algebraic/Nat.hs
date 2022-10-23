module Algebraic.Nat
 ( Nat (..)
 , natToInteger
 ) where

data Nat = Z | S Nat deriving (Show)

instance Eq Nat where
  (S a) == (S b) = a == b
  Z     ==  Z    = True
  _     ==  _    = False

instance Ord Nat where
  Z     <=  _    = True
  (S _) <= Z     = False
  (S a) <= (S b) = a <= b

instance Num Nat where
  (S a) + b = a + (S b)
  Z     + b = b

  (S a) * b = a * b + b
  Z     * _ = Z

  a     - Z     = a
  (S a) - (S b) = a - b
  Z     - (S _) = error "not supported"

  signum (S _) = S Z
  signum Z     = Z

  abs = id

  fromInteger n | n == 0    = Z
                | n > 0     = S (fromInteger (n - 1))
                | otherwise = error "not supported"

natToInteger :: Nat -> Integer
natToInteger Z     = 0
natToInteger (S n) = succ (natToInteger n)

-- | TODO hard version
