module Folding.SplitJoin
  ( joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty (..), (<|))

splitOn :: (Eq a) => a -> [a] -> NonEmpty [a]
splitOn e = foldr f ([] :| [])
  where
    f x acc@(a :| as) | x == e    = [] <| acc
                      | otherwise = (x : a) :| as

joinWith :: a -> NonEmpty [a] -> [a]
joinWith _ (x :| []) = x
joinWith e (x :| xs) = foldl f x xs
  where
    f acc a = acc ++ (e : a)
