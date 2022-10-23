module Parsers.Combinator
  ( Parser (..)
  , cbsParser
  , digit
  , element
  , eof
  , integer
  , ok
  , satisfy
  , stream
  ) where

import Control.Applicative (Alternative, empty, some, (<|>))
import Data.Char (isDigit)

-- | Parsers input (list of elements of type 's'),
-- returns 'Just' pair of
--   element with type 'a' (consumes it)
--   rest of input
-- or returns 'Nothing'
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

-- | Parser that never fails
ok :: Parser s ()
ok = Parser $ \s -> Just ((), s)

-- | Parser that fails if input is not empty
eof :: Parser s ()
eof = Parser $ \s -> case s of
  [] -> Just ((), [])
  _  -> Nothing

-- | Parser that fails if predicate on first
-- element of input is 'False'
--
-- otherwise consumes this element
satisfy :: (s -> Bool) -> Parser s s
satisfy p = Parser $ \s -> case s of
  []       -> Nothing
  (x : xs) -> if p x then Just (x, xs) else Nothing

-- | Parser that fails if first element of input
-- is not argument of this parser
--
-- otherwise consumes this element
element :: Eq s => s -> Parser s s
element c = satisfy (== c)

-- | Parser that fails if there is no prefix equal
-- to argument of this parser in input
--
-- otherwise consumes this prefix
stream :: Eq s => [s] -> Parser s [s]
stream s = traverse element s

-- | Parser that fails if the first `Char` of input
-- is not a digit (0..9)
--
-- otherwise consumes this char
digit :: Parser Char Char
digit = satisfy isDigit

-- | Parser that fails if there is no prefix that
-- can be valid integer
-- integer grammar: ('+' | '-' | "") ++ (('0'..'9')+)
--
-- otherwise consumes this prefix
integer :: Parser Char String
integer = Parser $ \s -> do
  (a, as) <- runParser (elementStr '-' <|> elementStr '+' <|> okStr) s
  (b, bs) <- runParser (some digit) as
  return (a ++ b, bs)
    where
      elementStr c = return   <$> element c
      okStr        = const "" <$> ok

-- | Parser that fails if input is not CBS
cbsParser :: Parser Char ()
cbsParser = let s = (element '(' >> s >> element ')' >> s) <|> ok in s >> eof
