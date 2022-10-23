module Main where

import Grammar
import Lexer (alexScanTokens)
import Parser (parse)
import Data.IORef
import Data.Map (Map)
import qualified Data.Map as Map
import Data.Set (Set)
import qualified Data.Set as Set

main :: IO ()
main = do
  nums <- getLine
  let (m:k:_) = map read (words nums)
  input <- getContents
  case parse (alexScanTokens input) of
    Left error -> putStrLn error
    Right expr -> betaReduction expr 0 k m 0

betaReduction e step k m counter = do
  printIf (mod step k == 0) e
  if (step /= m) then do
    (expr, reduced, counter1) <- reduce e counter
    if reduced then betaReduction expr (step + 1) k m counter1 
    else printIf (mod step k /= 0) e
  else printIf (mod step k /= 0) e

printIf condition e = if condition then toFlat e >>= (\n -> putStrLn $ show n) else return()

reduce e@(Var a) c = return (e, False, c)
reduce e@(Ref r) c = do
  expr <- readIORef r
  (exprR, reduced, c1) <- reduce expr c
  writeIORef r exprR
  return (e, reduced, c1)
reduce e@(Lambda a b) c = do
  (expr, reduced, c1) <- reduce b c
  return (Lambda a expr, reduced, c1)
reduce e@(Appl (Lambda x a) b) c = do
  ref <- newIORef b
  free <- findFree Set.empty b
  lol <- toFlat a
  (result, _, c1) <- subst lol x (Ref ref) free Map.empty c False
  return (result, True, c1)
reduce e@(Appl inner@(Ref r) b) c = do
  result <- isLambda inner
  case result of 
    Nothing   -> reduceHelper e c
    Just expr -> reduce (Appl expr b) c
reduce e@(Appl a b) c = reduceHelper e c

reduceHelper e@(Appl a b) c = do
  (exprA, reducedA, c1) <- reduce a c
  case reducedA of 
    True  -> return (Appl exprA b, True, c1)
    False -> do
      (exprB, reducedB, c2) <- reduce b c1
      return (Appl exprA exprB, reducedB, c2)

isLambda (Ref r) = do
  expr <- readIORef r
  case expr of 
    (Lambda _ _) -> return (Just expr)
    (Ref r)      -> isLambda expr
    _            -> return Nothing

toFlat (Ref r)      = readIORef r >>= toFlat
toFlat (Lambda x a) = toFlat a >>= (\y -> return (Lambda x y))
toFlat (Appl a b)   = toFlat a >>= (\x -> (toFlat b >>= \y -> return (Appl x y)))
toFlat (Var a)      = return (Var a)

contains p (Ref r)      = readIORef r >>= contains p
contains p (Lambda x a) = if x == p then return True else contains p a
contains p (Appl a b)   = do
  first <- contains p a
  if first then return True
  else contains p b
contains p (Var a)      = return (a == p)

findFree bound (Var a)      = if Set.member a bound then return (Set.empty) else return (Set.singleton a)
findFree bound (Ref r)      = readIORef r >>= findFree bound
findFree bound (Lambda x a) = findFree (Set.insert x bound) a
findFree bound (Appl a b)   = findFree bound a >>= (\x -> (findFree bound b >>= \y -> return (Set.union x y)))

subst expr@(Var a) from to free rename counter onlyRename = do
  if (a == from) then do
    if onlyRename then case Map.lookup a rename of
      Just found -> return ((Var found), rename, counter)
      Nothing    -> return (expr, rename, counter)
      --return (expr, rename, counter)
    else do
      return (to, rename, counter)
  else case Map.lookup a rename of
    Just found -> return ((Var found), rename, counter)
    Nothing    -> return (expr, rename, counter)
subst expr@(Ref r) from to free rename counter onlyRename = do
  inner <- readIORef r
  --cont <- contains from inner
  --if cont then do
  flat <- toFlat inner
  subst flat from to free rename counter onlyRename
  --else do
  --return (expr, rename, counter)
subst expr@(Lambda x a) from to free rename counter onlyRename = do
  if (x == from) then do
    (result, rename1, counter1) <- subst a from to free rename counter True
    return (Lambda x result, rename1, counter1)
  else do
    case Map.lookup x rename of
      Just found -> do
        let t = (x ++ (show (counter)))
        (result, rename1, counter1) <- subst a from to free (Map.insert x t rename) (counter + 1) onlyRename
        return (Lambda t result, (Map.insert x found (Map.delete x rename1)), counter1)
      Nothing    -> do
            if Set.member x free then do
              let t = (x ++ (show (counter)))
              (result, rename1, counter1) <- subst a from to free (Map.insert x t rename) (counter + 1) onlyRename
              return (Lambda t result, Map.delete x rename1, counter1)
            else do
              (result, _, counter1) <- subst a from to free rename counter onlyRename
              return (Lambda x result, rename, counter1)
subst expr@(Appl a b) from to free rename counter onlyRename = do
  (x, _, counter1) <- subst a from to free rename counter onlyRename 
  (y, _, counter2) <- subst b from to free rename counter1 onlyRename
  return (Appl x y, rename, counter2)
