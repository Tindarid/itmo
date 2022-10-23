module Task6
  ( distrExpr
  , nullExpr
  ) where

import Data.Maybe (mapMaybe)
import Task1 (distributivity)

distrExpr :: (Either String b, Either String c)
distrExpr = distributivity (Left ("harold" ++ " hide " ++ "the " ++ "pain"))
-- | WHNF:
-- distrExpr =
--   ( Left ("harold" ++ " hide " ++ "the " ++ "pain")
--   , Left ("harold" ++ " hide " ++ "the " ++ "pain")
--   )

foo :: Char -> Maybe Double
foo char =
    case char == 'o' of
      True  -> Just $ exp pi
      False -> Nothing

nullExpr :: Bool
nullExpr = null $ mapMaybe foo "pole chudes ochen' chudesno"
-- | WHNF:
-- nullExpr = False
