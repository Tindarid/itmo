{-# OPTIONS_GHC -fno-warn-orphans #-}

module Functors.NonEmpty
  ( NonEmpty (..)
  ) where

import Monoids.Semigroup (NonEmpty (..))

instance Functor NonEmpty where
  fmap f (a :| as) = (f a) :| (fmap f as)

instance Applicative NonEmpty where
  pure a = a :| []
  (<*>) (f :| fs) (a :| as) = (f a) :| ((fs <*> [a]) ++ ((f : fs) <*> as))

instance Foldable NonEmpty where
  foldMap f (a :| as) = (f a) <> (foldMap f as)

  foldr f acc (a :| as) = foldr f (f a acc) as

instance Monad NonEmpty where
  return a = a :| []
  (a :| as) >>= f = foldl (<>) (f a) (fmap f as)

instance Traversable NonEmpty where
  traverse f (a :| as) = (fmap (:|) (f a)) <*> (traverse f as)
