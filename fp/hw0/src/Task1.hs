{-# LANGUAGE TypeOperators #-}

module Task1
  ( associator
  , distributivity
  , eitherAssoc
  ) where

distributivity :: Either a (b, c) -> (Either a b, Either a c)
distributivity (Left a)       = (Left a, Left a)
distributivity (Right (b, c)) = (Right b, Right c)

associator :: (a, (b, c)) -> ((a, b), c)
associator (a, (b, c)) = ((a, b), c)

infixr 1 -->
(-->) :: Either a (Either b c) -> Either (Either a b) c
(-->) (Left a)          = Left (Left a)
(-->) (Right (Left b))  = Left (Right b)
(-->) (Right (Right c)) = Right c

infixr 1 <--
(<--) :: Either (Either a b) c -> Either a (Either b c)
(<--) (Left (Left a))  = (Left a)
(<--) (Left (Right b)) = (Right (Left b))
(<--) (Right c)        = (Right (Right c))

type (<->) a b = (a -> b, b -> a)

eitherAssoc :: Either a (Either b c) <-> Either (Either a b) c
eitherAssoc = ((-->), (<--))
