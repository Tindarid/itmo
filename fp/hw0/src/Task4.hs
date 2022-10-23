module Task4
  ( factorial
  , fibonacci
  , iterateElement
  , mapFix
  ) where

import Data.Function (fix)

iterateElement :: a -> [a]
iterateElement x = fix (x:)

fibonacci :: Integer -> Integer
fibonacci = fix (\f n -> if (n <= 1) then 1 else f (n - 1) + f (n - 2))

factorial :: Integer -> Integer
factorial = fix (\f n -> if (n <= 1) then 1 else n * f (n - 1))

mapFix :: (a -> b) -> [a] -> [b]
mapFix mapper = fix mapFix'
  where
    mapFix' _ []     = []
    mapFix' f (x:xs) = (mapper x) : (f xs)
