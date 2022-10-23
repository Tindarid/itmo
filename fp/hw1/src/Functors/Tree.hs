module Functors.Tree
  ( Tree (..)
  ) where

data Tree a = Branch (Tree a) (Tree a) | Leaf a

instance Functor Tree where
  fmap f (Branch l r) = Branch (fmap f l) (fmap f r)
  fmap f (Leaf a)     = Leaf (f a)

instance Applicative Tree where
  pure = Leaf
  (Leaf f)       <*> a = fmap f a
  (Branch fl fr) <*> a = Branch (fl <*> a) (fr <*> a)

instance Foldable Tree where
  foldMap f (Leaf a)     = f a
  foldMap f (Branch l r) = (foldMap f l) <> (foldMap f r)

  foldr f acc (Leaf a)     = f a acc
  foldr f acc (Branch l r) = foldr f (foldr f acc r) l

instance Traversable Tree where
  traverse f (Leaf a)     = fmap Leaf (f a)
  traverse f (Branch l r) = (fmap Branch (traverse f l)) <*> (traverse f r)
