module Task2
  ( Neg
  , doubleNeg
  , doubleNegElim
  , excludedNeg
  , pierce
  , thirdNegElim
  ) where

import Data.Void (Void)

type Neg a = a -> Void

doubleNeg :: a -> Neg (Neg a)
doubleNeg a f = f a
-- | doubleNeg :: a -> (a -> Void) -> Void
-- | Or: doubleNeg = flip id

excludedNeg :: Neg (Neg (Either a (Neg a)))
excludedNeg f = (f . Right) (f . Left)
-- | excludedNeg :: (((Either a (Neg a)) -> Void) -> Void)
-- | f :: ((Either a (Neg a)) -> Void)
-- | Left and Right in this context
-- | Left :: a -> Either a (Neg a)
-- | Right :: (a -> Void) -> Either a (Neg a)
-- | (f . Left) :: (a -> Void)
-- | (f . Right) :: (a -> Void) -> Void

pierce :: ((a -> b) -> a) -> a
pierce = undefined
-- | Если закон Пирса доказуем в ИИВ (т.е. мы можем построить терм,
-- | имеющий такой тип) - то из него доказуемо (!!a -> a), что
-- | не доказуемо в ИИВ (а лямбда-исчисление изоморфно импликационному
-- | фрагменту ИИВ)

doubleNegElim :: Neg (Neg a) -> a
doubleNegElim = undefined
-- | !!a -> a - не доказуемо в ИИВ (+ смотри pierce)

thirdNegElim :: Neg (Neg (Neg a)) -> Neg a
thirdNegElim f = f . doubleNeg
-- | thirdNegElim :: (((a -> Void) -> Void) -> Void) -> (a -> Void)
-- | doubleNeg :: (a -> func)
-- | f :: (func -> Void)
-- | thirdNegElim :: f -> (a -> Void)
