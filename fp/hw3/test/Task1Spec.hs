module Task1Spec (spec) where

import Task1
import Test.Hspec
import Test.QuickCheck

-- | Geometry tests
spec :: Spec
spec = do
  describe "Geometry (simple unit tests)" $ do
    geometryUnitSpec
  describe "Geometry (property tests)" $ do
    geometryPropertySpec

-- | Checks that two double-s are equal with precision
almostEqual :: Double -> Double -> Double -> Bool
almostEqual eps a b = (abs $ a - b) < eps

-- | Geometry unit tests
geometryUnitSpec :: Spec
geometryUnitSpec = do
  describe "plus" $ do
    it "(0, 0) + (0, 0)" $
      plus (Point 0 0) (Point 0 0) `shouldBe` (Point 0 0)
    it "(1, 10) + (10, 1)" $
      plus (Point 1 10) (Point 10 1) `shouldBe` (Point 11 11)
  describe "minus" $ do
    it "(0, 0) - (0, 0)" $
      minus (Point 0 0) (Point 0 0) `shouldBe` (Point 0 0)
    it "(1, 10) - (10, 1)" $
      minus (Point 1 10) (Point 10 1) `shouldBe` (Point (-9) 9)
  describe "scalar" $ do
    it "(1, 2) * (3, 4)" $
      scalarProduct (Point 1 2) (Point 3 4) `shouldBe` 11
    it "(3, 4) * (5, 6)" $
      scalarProduct (Point 3 4) (Point 5 6) `shouldBe` 39
    it "(7, 8) * (9, 10)" $
      scalarProduct (Point 7 8) (Point 9 10) `shouldBe` 143
    it "(11, 12) * (13, 14)" $
      scalarProduct (Point 11 12) (Point 13 14) `shouldBe` 311
  describe "cross" $ do
    it "(1, 2) x (3, 4)" $
      crossProduct (Point 1 2) (Point 3 4) `shouldBe` -2
    it "(3, 4) x (5, 6)" $
      crossProduct (Point 3 4) (Point 5 6) `shouldBe` -2
    it "(7, 8) x (9, 10)" $
      crossProduct (Point 7 8) (Point 9 10) `shouldBe` -2
    it "(11, 12) x (13, 14)" $
      crossProduct (Point 11 12) (Point 13 14) `shouldBe` -2
  describe "perimeter" $ do
    it "square with a = 1" $
      perimeter [Point 0 0, Point 0 1, Point 1 1, Point 1 0] `shouldSatisfy` (almostEqual 1e-30 4.0)
    it "rectangle with a = 2, b = 4" $
      perimeter [Point 0 0, Point 0 4, Point 2 4, Point 2 0] `shouldSatisfy` (almostEqual 1e-30 12.0)
    it "some pentagon" $
      perimeter [Point 0 2, Point 2 6, Point 5 6, Point 6 3, Point 0 6] `shouldSatisfy` (almostEqual 1e-3 21.3426)
  describe "doubleArea" $ do
    it "square with a = 1" $
      doubleArea [Point 0 0, Point 0 1, Point 1 1, Point 1 0] `shouldBe` 2
    it "rectangle with a = 2, b = 4" $
      doubleArea [Point 0 0, Point 0 4, Point 2 4, Point 2 0] `shouldBe` 16
    it "some hexagon" $
      doubleArea [Point 0 2, Point 2 6, Point 5 6, Point 6 3, Point 6 0, Point 2 0] `shouldBe` 57

-- | Checks that two polygon actions have same result using equality function
polygonActionChecker :: (Polygon -> a) -> (Polygon -> a) -> (a -> a -> Bool) -> [(Int, Int)] -> Bool
polygonActionChecker f1 f2 eq pairs = (f1 points) `eq` (f2 points)
 where
  points = map (\(x, y) -> Point x y) pairs

-- | Geometry property tests
-- Note: optimized versions have no unit tests, because they are compared to naive versions in this tests
geometryPropertySpec :: Spec
geometryPropertySpec = do
  describe "naive and optimized are equal" $ do
    it "perimeter" $
      property $ polygonActionChecker perimeter perimeterOptimized (almostEqual 1e-5)
    it "doubleArea" $
      property $ polygonActionChecker doubleArea doubleAreaOptimized (==)
