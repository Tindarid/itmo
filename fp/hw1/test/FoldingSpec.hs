module FoldingSpec (spec) where

import Algebraic.Tree
import Data.List (sort)
import Data.List.NonEmpty (NonEmpty (..))
import Folding.SplitJoin
import Folding.Tree
import Test.Hspec
import Test.QuickCheck

spec :: Spec
spec = do
  describe "Foldable Tree" $ do
    treeSpec
  describe "Split and Join" $ do
    splitJoinSpec

treeSort :: Ord a => [a] -> [a]
treeSort = toList . fromList

treeSpec :: Spec
treeSpec = do
  describe "fromList . toList == sort (unit)" $ do
    let test0 = [] :: [Int]
    let test1 = [1] :: [Int]
    let test2 = [2, 4, 100, 8, 1, 4] :: [Int]
    let test3 = [31232, 1234, 1234, 81, 1, -4] :: [Int]

    it (show test0) $
      treeSort test0 `shouldBe` sort test0
    it (show test1) $
      treeSort test1 `shouldBe` sort test1
    it (show test2) $
      treeSort test2 `shouldBe` sort test2
    it (show test3) $
      treeSort test3 `shouldBe` sort test3

  describe "fromList . toList == sort (property)" $ do
    it "random" $ property ((\x -> treeSort x == sort x) :: [Integer] -> Bool)

splitJoinSpec :: Spec
splitJoinSpec = do
  describe "splitOn (unit)" $ do
    it "sample" $
      splitOn '/' "path/to/file" `shouldBe` "path" :| ["to", "file"]
    it "none" $
      splitOn (1 :: Int) [2] `shouldBe` [2] :| []
    it "single" $
      splitOn (1 :: Int) [1] `shouldBe` [] :| [[]]
    it "triple" $
      splitOn (1 :: Int) [2, 1, 2] `shouldBe` [2] :| [[2]]
    it "several" $
      splitOn (3 :: Int) [3, 3, 2, 1, 3, 2] `shouldBe` [] :| [[], [2, 1], [2]]

  describe "joinWith (unit)" $ do
    it "sample" $
      joinWith '/' ("path" :| ["to", "file"]) `shouldBe` "path/to/file"
    it "none" $
      joinWith (1 :: Int) ([2] :| []) `shouldBe` [2]
    it "single" $
      joinWith (1 :: Int) ([] :| [[]]) `shouldBe` [1]
    it "triple" $
      joinWith (1 :: Int) ([2] :| [[2]]) `shouldBe` [2, 1, 2]
    it "several" $
      joinWith (3 :: Int) ([] :| [[], [2, 1], [2]]) `shouldBe` [3, 3, 2, 1, 3, 2]

  describe "both (property)" $ do
    it "random" $ property propFunc
     where
       propFunc :: Integer -> [Integer] -> Bool
       propFunc x l = joinWith x (splitOn x l) == l
