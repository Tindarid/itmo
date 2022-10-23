module Algebraic.Tree
  ( Tree (..)
  , count
  , empty
  , erase
  , fromList
  , search
  , insert
  ) where

import Data.List.NonEmpty (NonEmpty (..), (<|))

data Tree a = Leaf | Branch (NonEmpty a) (Tree a) (Tree a)

empty :: Tree a -> Bool
empty Leaf = True
empty _    = False

count :: Tree a -> Int
count Leaf            = 0
count (Branch xs l r) = length xs + count l + count r

search :: Ord a => Tree a -> a -> Bool
search Leaf _ = False
search (Branch (x :| _) l r) e | e == x     = True
                               | e < x      = search l e
                               | otherwise  = search r e

insert :: Ord a => Tree a -> a -> Tree a
insert Leaf e = Branch (e :| []) Leaf Leaf
insert (Branch xs@(x :| _) l r) e | e == x     = Branch (e <| xs) l r
                                  | e < x      = Branch xs (insert l e) r
                                  | otherwise  = Branch xs l (insert r e)

fromList :: Ord a => [a] -> Tree a
fromList = foldl insert Leaf

erase :: Ord a => Tree a -> a -> Tree a
erase Leaf _ = Leaf
erase (Branch xs@(x :| _) l r) e | e == x     = Branch xs l r -- TODO If empty???
                                 | e < x      = Branch xs (erase l e) r
                                 | otherwise  = Branch xs l (erase r e)
