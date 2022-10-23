{-# LANGUAGE InstanceSigs #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}

module Folding.Tree
  ( toList
  ) where

import Algebraic.Tree (Tree (..))

instance Foldable Tree where
  foldMap :: (Monoid m) => (a -> m) -> Tree a -> m
  foldMap _ Leaf            = mempty
  foldMap f (Branch xs l r) = foldMap f l <> foldMap f xs <> foldMap f r

  foldr :: (a -> b -> b) -> b -> Tree a -> b
  foldr _ acc (Leaf)          = acc
  foldr f acc (Branch xs l r) = foldr f (foldr f (foldr f acc l) xs) r

toList :: Tree a -> [a]
toList = reverse . foldr (:) []
