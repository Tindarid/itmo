module Main where

import Grammar
import Lexer (alexScanTokens)
import Parser (parse)

import qualified Data.Map as Map
import qualified Data.Set as Set
import qualified Data.Tuple as Tuple

main :: IO ()
main = do
  input <- getContents
  case parse (alexScanTokens input) of
    Left error -> putStrLn "Expression has no type"
    Right expr -> do
      let (system, root, _, _, mapFree) = resolveExpr expr 1 Map.empty Map.empty
      case solveSystem (Set.fromList system) of 
           Nothing -> putStrLn "Expression has no type"
           Just solved -> printTree root 0 (Map.toList mapFree) (Set.toList solved)

resolveExpr expr counter mapBound mapFree = case expr of
                   (Var x) -> do
                     let l = Map.toList mapBound
                     case Map.lookup x mapBound of 
                         Nothing -> do
                           case Map.lookup x mapFree of 
                               Nothing -> do
                                 let t = Single ("t" ++ show (counter))
                                 let newMapFree = Map.insert x t mapFree
                                 ([], Default (Term expr t) Empty Empty l, counter + 1, mapBound, newMapFree)
                               Just t -> do
                                 ([], Default (Term expr t) Empty Empty l, counter, mapBound, mapFree)
                         Just t -> do
                           ([], Default (Term expr t) Empty Empty l, counter, mapBound, mapFree)
                   (Lambda x p) -> do
                     let t = Single ("t" ++ show (counter))
                     let newMap = Map.insert x t mapBound
                     let l = Map.toList mapBound
                     let (system, node, counter2, mapBound2, mapFree2) = resolveExpr p (counter + 1) newMap mapFree
                     (system, Default (Term expr (Impl t (getType node))) Empty node l, counter2, (Map.delete x mapBound2), mapFree2)
                   (Appl p q) -> do
                     let newType = Single ("t" ++ show (counter))
                     let (system1, node1, counter2, mapBound2, mapFree2) = resolveExpr p (counter + 1) mapBound mapFree
                     let (system2, node2, counter3, mapBound3, mapFree3) = resolveExpr q counter2 mapBound2 mapFree2
                     let equation = (getType node1, Impl (getType node2) newType)
                     let l = Map.toList mapBound
                     (system1 ++ system2 ++ [equation], Default (Term expr newType) node1 node2 l, counter3, mapBound3, mapFree3)

containsType t (Impl a b) = (containsType t a) || (containsType t b)
containsType t (Single a) = (Single a) == t

substType t1 t2 (Impl a b) = Impl (substType t1 t2 a) (substType t1 t2 b)
substType t1 t2 (Single a) | t1 == (Single a) = t2
                           | otherwise        = (Single a)

substTypeFromList ((a, b):rest) t = substTypeFromList rest (substType a b t)
substTypeFromList [] t = t

solveSystem r0 = do
               let temp = Set.filter solveSystemHelper r0
               case Set.size temp of
                    0 -> do
                       let (reduced1, r1) = reduceSystem1 r0
                       let (reduced2, r2) = reduceSystem2 r1
                       let (reduced3, r3) = reduceSystem3 r2
                       let (reduced4, r4) = reduceSystem4 r3
                       let reduced = reduced1 || reduced2 || reduced3 || reduced4
                       case reduced of 
                            True  -> solveSystem r4
                            False -> Just r4
                    _ -> Nothing
solveSystemHelper (Single a, Impl c d) = containsType (Single a) (Impl c d)
solveSystemHelper _ = False

-- T = x -> x = T
reduceSystem1 system = do
                   let (need, rest) = Set.partition reduceSystem1Helper1 system
                   case (Set.size need) of 
                            0 -> (False, rest)
                            _ -> (True, Set.union (Set.map Tuple.swap need) rest)
reduceSystem1Helper1 (Impl _ _, Single _) = True
reduceSystem1Helper1 (_, _) = False
                   
-- Get rid of T=T
reduceSystem2 system = do
                   let result = Set.filter (\(k, v) -> k /= v) system
                   let reduced = (Set.size system) /= (Set.size result)
                   (reduced, result)

-- a -> b = c -> d => a = c, b = d
reduceSystem3 system = do
                   let (need, rest) = Set.partition reduceSystem3Helper1 system
                   case (Set.size need) of 
                            0 -> (False, rest)
                            _ -> (True, Set.union (reduceSystem3Helper2 need) rest)
reduceSystem3Helper1 (Impl _ _, Impl _ _) = True
reduceSystem3Helper1 (_, _) = False
reduceSystem3Helper2 system = do 
                   let (l, r) = unzip (map convertSystem3 (Set.toList system))
                   Set.fromList (l ++ r)
convertSystem3 (Impl a b, Impl c d) = ((a, c), (b, d))

-- x = T, R = S
reduceSystem4 system = reduceSystem4Helper4 (Set.toList (Set.filter reduceSystem4Helper1 system)) system
reduceSystem4Helper1 (Single _, _) = True
reduceSystem4Helper1 (_, _) = False
reduceSystem4Helper2 t (r, s) = (containsType t r) || (containsType t s)
reduceSystem4Helper3 t1 t2 (r, s) = (substType t1 t2 r, substType t1 t2 s)
reduceSystem4Helper4 (a:as) system = do
                    let (x, y) = a
                    let s = Set.delete a system
                    let need = Set.filter (reduceSystem4Helper2 x) s
                    case (Set.size need) of
                          0 -> reduceSystem4Helper4 as system
                          _ -> (True, Set.insert a (Set.map (reduceSystem4Helper3 x y) s))
reduceSystem4Helper4 [] system = (False, system)

resolveFreeVars ((v, t):[]) system = v ++ " : " ++ show (substTypeFromList system t) ++ " "
resolveFreeVars ((v, t):rest) system = v ++ " : " ++ show (substTypeFromList system t) ++ ", " ++ (resolveFreeVars rest system)
resolveFreeVars [] system = ""

printTree (Default (Term e t) l r list) deep vars system = do
                    printDelim deep
                    putStr (resolveFreeVars (vars ++ list) system)
                    putStr "|- "
                    putStr (show e)
                    putStr " : "
                    putStr (show (substTypeFromList system t))
                    printRule e
                    printTree l (deep + 1) vars system
                    printTree r (deep + 1) vars system
printTree Empty _ _ _ = putStr ""

printRule e = case e of 
               Var _      -> putStrLn " [rule #1]"
               Appl _ _   -> putStrLn " [rule #2]"
               Lambda _ _ -> putStrLn " [rule #3]"

printDelim 0 = putStr ""
printDelim deep = do
               putStr "*   "
               printDelim (deep - 1)
