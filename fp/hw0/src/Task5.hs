module Task5
  ( Nat
  , churchMult
  , churchPlus
  , churchToInt
  , succChurch
  , zero
  ) where

type Nat a = (a -> a) -> a -> a

zero :: Nat a
zero _ x = x

succChurch :: Nat a -> Nat a
succChurch a = \f x -> f (a f x)

churchPlus, churchMult :: Nat a -> Nat a -> Nat a
churchPlus a b = \f x -> a f (b f x)
churchMult a b = \f x -> a (b f) (zero f x)

churchToInt :: Nat Integer -> Integer
churchToInt a = a (+ 1) 0
