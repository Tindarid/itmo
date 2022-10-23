module Parsers.Combinator
  ( Parser (..)
  , element
  , eof
  , ok
  , satisfy
  , stream
  ) where

import Control.Applicative (Alternative, empty, (<|>))

data Parser s a = Parser { runParser :: [s] -> Maybe (a, [s]) }

instance Functor (Parser s) where
  fmap f p = Parser $ \s -> do
    (a, as) <- runParser p s
    return (f a, as)

instance Applicative (Parser s) where
  pure a = Parser $ \s -> Just (a, s)

  pf <*> pa = Parser $ \s -> case (runParser pf s) of
    Nothing     -> Nothing
    Just (f, t) -> case (runParser pa t) of
      Nothing     -> Nothing
      Just (a, r) -> Just (f a, r)

instance Monad (Parser s) where
  return = pure

  p >>= f = Parser $ \s -> do
    (a, as) <- runParser p s
    runParser (f a) as

instance Alternative (Parser s) where
  empty = Parser (const Nothing)

  f <|> g = Parser $ \s -> do
    (runParser f s) <|> (runParser g s)

ok :: Parser s ()
ok = Parser $ \s -> Just ((), s)

eof :: Parser s ()
eof = Parser $ \s -> case s of
  [] -> Just ((), [])
  _  -> Nothing

satisfy :: (s -> Bool) -> Parser s s
satisfy p = Parser $ \s -> case s of
  []       -> Nothing
  (x : xs) -> if p x then Just (x, xs) else Nothing

element :: Eq s => s -> Parser s s
element c = satisfy (== c)

stream :: Eq s => [s] -> Parser s [s]
stream s = traverse element s
