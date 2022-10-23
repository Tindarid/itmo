module Monoids.Concat
  ( maybeConcat
  ) where

import Data.Maybe (fromMaybe)

maybeConcat :: [Maybe [a]] -> [a]
maybeConcat = foldMap (fromMaybe [])
