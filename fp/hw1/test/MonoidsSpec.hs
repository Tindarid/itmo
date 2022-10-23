module MonoidsSpec (spec) where

import Monoids.Concat
import Monoids.Semigroup
import Test.Hspec
import Test.QuickCheck

spec :: Spec
spec = do
  describe "Maybe" $ do
    maybeSpec
  describe "Semigroup" $ do
    semigroupSpec

maybeSpec :: Spec
maybeSpec = do
  describe "maybeConcat" $ do
    it "sample" $
      maybeConcat [Just [1,2,3], Nothing, Just [4,5]] `shouldBe` ([1,2,3,4,5] :: [Int])
    it "single Nothing" $
      maybeConcat [Nothing] `shouldBe` ([] :: [Int])
    it "single Just" $
      maybeConcat [Just [5, 2]] `shouldBe` ([5, 2] :: [Int])
    it "big numbers" $
      maybeConcat [Just [5000], Nothing, Nothing, Just [-10000]] `shouldBe` ([5000, -10000] :: [Int])
    it "another test" $
      maybeConcat [Just [1,2], Nothing, Just [4,5]] `shouldBe` ([1,2,4,5] :: [Int])
    it "one more test" $
      maybeConcat [Nothing, Just [1], Nothing, Just [4]] `shouldBe` ([1, 4] :: [Int])
    it "random" $ property propFunc
      where
        propFunc :: [[Int]] -> Bool
        propFunc rand = maybeConcat testCase == ansShouldBe
          where (testCase, ansShouldBe) = gen rand

        gen :: [[Int]] -> ([Maybe [Int]], [Int])
        gen = foldl f ([], [])
          where f (testCase, ans) l | (length l) `mod` 2 == 0 = (testCase ++ [Just l], ans ++ l)
                                    | otherwise               = (testCase ++ [Nothing], ans)

semigroupSpec :: Spec
semigroupSpec = do
  describe "NonEmpty" $ do
    it "simple" $
      ((1 :: Int) :| [1]) <> (2 :| [2]) `shouldBe` (1 :| [1, 2, 2])
    it "another simple" $
      ((2 :: Int) :| [2]) <> (2 :| [2]) `shouldBe` (2 :| [2, 2, 2])
    it "one more" $
      ((4 :: Int) :| []) <> (5 :| []) `shouldBe` (4 :| [5])
    it "random" $ property propFunc
      where
        propFunc :: (Int, [Int]) -> (Int, [Int]) -> (Int, [Int]) -> Bool
        propFunc (af, as) (bf, bs) (cf, cs) = (a <> (b <> c)) == ((a <> b) <> c)
          where a = af :| as
                b = bf :| bs
                c = cf :| cs
