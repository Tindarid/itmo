module Monoids.Semigroup
  ( NonEmpty (..)
  , ThisOrThat (..)
  ) where

data NonEmpty a = a :| [a] deriving (Show, Eq)
data ThisOrThat a b = This a | That b | Both a b

instance Semigroup (NonEmpty a) where
  (a :| as) <> (b :| bs) = a :| (as ++ (b : bs))

instance (Semigroup a, Semigroup b) => Semigroup (ThisOrThat a b) where
  This a   <> This b   = This (a <> b)
  That a   <> That b   = That (a <> b)
  Both a b <> Both c d = Both (a <> c) (b <> d)
  This a   <> That b   = Both a b
  That a   <> This b   = Both b a
  This a   <> Both b c = Both (a <> b) c
  Both b c <> This a   = Both (b <> a) c
  That a   <> Both b c = Both b (a <> c)
  Both b c <> That a   = Both b (c <> a)
