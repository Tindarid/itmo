{-# LANGUAGE BangPatterns #-}

module Task1
    ( Point (..)
    , Polygon
    , crossProduct
    , doubleArea
    , doubleAreaOptimized
    , minus
    , perimeter
    , perimeterOptimized
    , plus
    , scalarProduct
    ) where

import Control.DeepSeq (NFData, rnf)
import Data.List (foldl')

-- | Point in R^2 (with integer coordinates).
-- Note: Show and Eq deriving is for tests
data Point = Point !Int !Int deriving (Show, Eq)

instance NFData Point where
  rnf (Point x y) = x `seq` (y `seq` ())

-- | Polygon (convex or non-convex) without self-intersections.
-- Points can be listed counter-clockwise and clockwise
type Polygon = [Point]

-- | Sum of points
-- (x1, y1) + (x2, y2) = (x1 + x2, y1 + y2)
plus :: Point -> Point -> Point
plus (Point x1 y1) (Point x2 y2) = Point (x1 + x2) (y1 + y2)

-- | Sub of points
-- (x1, y1) - (x2, y2) = (x1 - x2, y1 - y2)
minus :: Point -> Point -> Point
minus (Point x1 y1) (Point x2 y2) = Point (x1 - x2) (y1 - y2)

-- | Scalar product of points
-- (x1, y1) * (x2, y2) = x1 * x2 + y1 * y2
scalarProduct :: Point -> Point -> Int
scalarProduct (Point x1 y1) (Point x2 y2) = x1 * x2 + y1 * y2

-- | Cross product of points
-- (x1, y1) x (x2, y2) = x1 * x2 - y1 * y2
crossProduct :: Point -> Point -> Int
crossProduct (Point x1 y1) (Point x2 y2) = x1 * y2 - x2 * y1

-- | Distance from one point to another
-- distance (x1, y1) (x2, y2) = sqrt ((x1 - x2) ^ 2 + (y1 - y2) ^ 2)
distance :: Point -> Point -> Double
distance p1 p2 = sqrt $ fromIntegral $ (scalarProduct diff diff)
  where
    diff = minus p1 p2

-- | Process neighboring points of polygon with given function and sum results
processPolygon :: Num a => (Point -> Point -> a) -> Polygon -> a
processPolygon f points = foldl' (+) 0 (zipWith f points (shift 1 points))
  where
    shift = drop <> take

-- | Like `processPolygon`, but not so naive
processPolygonOptimized :: Num a => (Point -> Point -> a) -> Polygon -> a
processPolygonOptimized _ [] = 0
processPolygonOptimized f (first : other) = helper 0 (first : other)
  where
    helper !acc []             = acc
    helper !acc (p : [])       = acc + (f p first)
    helper !acc (p1 : p2 : ps) = helper (f p1 p2 + acc) (p2 : ps)

-- | Perimeter of polygon
perimeter :: Polygon -> Double
perimeter = processPolygon distance

-- | Doubled area of polygon
doubleArea :: Polygon -> Int
doubleArea = abs . (processPolygon crossProduct)

-- | Like `perimeter`, but not so naive
perimeterOptimized :: Polygon -> Double
perimeterOptimized = processPolygonOptimized distance

-- | Like `doubleArea`, but not so naive
doubleAreaOptimized :: Polygon -> Int
doubleAreaOptimized = abs . (processPolygonOptimized crossProduct)
