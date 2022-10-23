module Main where

import Grammar
import Lexer (alexScanTokens)
import Parser (parse)
import Generate

import System.IO (isEOF)
import Control.Exception

import Data.Map (Map)
import qualified Data.Map as Map
import Data.Set (Set)
import qualified Data.Set as Set

data Result = Axiom Int | MP Int Int | Dup | Hypo Int | Error

bad = Var "z"

main = do 
    firstLine <- getLine
    let temp1 = resolveFirst firstLine
    let temp2 = resolveHypo (take (length firstLine - length temp1 - 2) firstLine)
    let theorem = resolveSome temp1
    let hypos = Map.fromList $ numerateList $ map resolveSome temp2
    result <- try (readProof 1 Map.empty Map.empty Map.empty Map.empty bad hypos) 
                  :: IO (Either SomeException (Map Int Expr, Map Expr Int, Map Expr [Int], Map Int (Int, Int), Expr))
    case result of 
        Left ex  -> putStrLn $ "Proof is incorrect"
        Right (mapInt, mapExpr, mapMP, mapIntInt, last) -> do
            case (last == theorem) of
                False -> putStrLn $ "Proof is incorrect"
                True -> do
                    let lastNumber = Map.findWithDefault 0 last mapExpr
                    let used = Set.toList $ resolveUsed (Set.insert lastNumber Set.empty) lastNumber mapIntInt
                    let newMap = Map.fromList $ numerateList used
                    putStrLn $ (take (length firstLine - length temp1 - 2) firstLine) ++ " |- " ++ (show $ Not (Not theorem))
                    writeLine 1 mapIntInt mapExpr mapInt used

writeLine n mapIntInt mapExpr mapInt (a:as) = do
                               mapM_ (putStrLn . show) (r some)
                               writeLine (n + 1) mapIntInt mapExpr mapInt as
                               where reduceMP (Impl a2 b2) = b2
                                     reduce10 (Impl (Not (Not a3)) (a4)) = a3
                                     expr = Map.findWithDefault bad a mapInt
                                     some = Map.findWithDefault (0, 0) a mapIntInt
                                     r (b, c) | b == 0 && c < 10     = generateSimple expr
                                              | b == 0 && c == 10    = generate10 (reduce10 expr)
                                              | b == 0 && c > 10     = generateSimple expr
                                              | otherwise            = generateMP c1 (reduceMP b1) 
                                              where b1 = Map.findWithDefault bad b mapInt
                                                    c1 = Map.findWithDefault bad c mapInt

writeLine _ _ _ _ [] = putStr $ ""

numerateList list = helper 1 list
                    where helper n (a:as) = (a, n) : helper (n + 1) as
                          helper n [] = []

resolveUsed set n mapIntInt | a == 0 = set
                            | otherwise = resolveUsed (Set.insert b (resolveUsed (Set.insert a set) a mapIntInt)) b mapIntInt
                            where (a, b) = Map.findWithDefault (0, 0) n mapIntInt

resolveSome theorem = case parse (alexScanTokens theorem) of
                       Right expr -> expr
                       Left error -> bad

resolveFirst (a:b:as) | a == '|' && b == '-' = as
                      | otherwise = resolveFirst (b:as)

resolveHypo s =  case dropWhile (== ',') s of
                      "" -> []
                      s' -> w : resolveHypo s''
                            where (w, s'') = break (== ',') s'

readProof n mapInt mapExpr mapMP mapIntInt last hypos = do
    ineof <- isEOF
    if ineof
        then return (mapInt, mapExpr, mapMP, mapIntInt, last)
    else do 
        line <- getLine
        case parse (alexScanTokens line) of
            Right expr -> do
                        let newMapMP = resolve expr mapMP n
                        case check expr mapInt mapExpr mapMP hypos of
                            Dup      -> readProof (n + 1) mapInt mapExpr mapMP mapIntInt expr hypos
                            Axiom a  -> readNext newMapMP (ins (0, a)) expr hypos
                            MP m1 m2 -> readNext newMapMP (ins (m1, m2)) expr hypos
                            Hypo h   -> readNext newMapMP (ins (0, h + 10)) expr hypos
                            Error    -> error "incorrect"
                            where newMapInt = Map.insert n expr mapInt
                                  newMapExpr = Map.insert expr n mapExpr
                                  readNext = readProof (n + 1) newMapInt newMapExpr
                                  ins a = Map.insert n a mapIntInt
            Left error -> return (mapInt, mapExpr, mapMP, mapIntInt, last)

resolve expr mapMP n = case res expr of
                           Nothing -> mapMP
                           Just b  -> Map.insertWith (++) b [n] mapMP
                       where res (Impl a b) = Just b
                             res _          = Nothing

check expr mapInt mapExpr mapMP hypos | Map.member expr mapExpr = Dup
                                      | axiom /= 0              = Axiom axiom
                                      | h /= 0                  = Hypo h
                                      | m1 /= 0                 = MP m1 m2
                                      | otherwise               = Error
                                      where axiom    = checkAxioms expr
                                            (m1, m2) = checkMP expr mapInt mapExpr mapMP
                                            h        = checkHypo hypos expr

checkHypo hypos expr = Map.findWithDefault 0 expr hypos

checkMP expr mapInt mapExpr mapMP = case Map.lookup expr mapMP of
                                        Nothing   -> (0, 0)
                                        Just list -> findFirst mapInt mapExpr list

findFirst mapInt mapExpr (a:as) | res /= 0  = (a, res)
                                | otherwise = findFirst mapInt mapExpr as
                                where res = predi mapInt mapExpr a
findFirst _ _ [] = (0, 0)

predi mapInt mapExpr a = case Map.lookup (red $ Map.findWithDefault bad a mapInt) mapExpr of
                            Nothing  -> 0
                            Just ind -> ind
                         where red (Impl a b) = a

checkAxioms expr | check1 expr = 1
                 | check2 expr = 2
                 | check3 expr = 3
                 | check4 expr = 4
                 | check5 expr = 5
                 | check6 expr = 6
                 | check7 expr = 7
                 | check8 expr = 8
                 | check9 expr = 9
                 | check10 expr = 10
                 | otherwise = 0

check1 (Impl a1 (Impl a2 a3)) 
    | a1 == a3 = True
    | otherwise = False
check1 expr = False

check2 (Impl (Impl a1 a2) (Impl (Impl a3 (Impl a4 a5)) (Impl a6 a7))) 
    | (a1 == a3) && (a1 == a6) && (a5 == a7) && (a2 == a4) = True
    | otherwise = False
check2 expr = False

check3 (Impl a1 (Impl a2 (And a3 a4))) 
    | (a1 == a3) && (a2 == a4) = True
    | otherwise = False
check3 expr = False

check4 (Impl (And a1 a2) a3)
    | a1 == a3 = True
    | otherwise = False
check4 expr = False

check5 (Impl (And a1 a2) a3)
    | a2 == a3 = True
    | otherwise = False
check5 expr = False

check6 (Impl a1 (Or a2 a3))
    | a1 == a2 = True
    | otherwise = False
check6 expr = False

check7 (Impl a1 (Or a2 a3))
    | a1 == a3 = True
    | otherwise = False
check7 expr = False

check8 (Impl (Impl a1 a2) (Impl (Impl a3 a4) (Impl (Or a5 a6) a7)))
    | (a1 == a5) && (a2 == a4) && (a2 == a7) && (a3 == a6) = True
    | otherwise = False
check8 expr = False

check9 (Impl (Impl a1 a2) (Impl (Impl a3 (Not a4)) (Not a5)))
    | (a1 == a3) && (a1 == a5) && (a2 == a4) = True
    | otherwise = False
check9 expr = False

check10 (Impl (Not (Not a1)) a2)
    | a1 == a2 = True
    | otherwise = False
check10 expr = False
