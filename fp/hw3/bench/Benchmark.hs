module Main where

import Control.DeepSeq (NFData)
import Criterion.Main
import System.Random (randomRIO)
import Task1 (Point (..), Polygon, doubleArea, doubleAreaOptimized, perimeter, perimeterOptimized)

-- | Random list (with specified size) of ints in range (-10000, 10000)
randomList :: Int -> IO [Int]
randomList n = sequence $ replicate n $ randomRIO (-10000, 10000)

-- | Random polygon (with specified number of angles)
randomPolygon :: Int -> IO Polygon
randomPolygon n = do
  xs <- randomList n
  ys <- randomList n
  return (zipWith Point xs ys)

-- | Benchmark action with polygon
benchPolygonAction :: NFData a => (Polygon -> a) -> [Benchmark]
benchPolygonAction action =
  [ helper 1000000
  , helper 5000000
  , helper 10000000
  ]
  where helper n = env (randomPolygon n) (\p -> bench (show n) $ nf action p)

-- | Benchmark all stuff
main :: IO ()
main = defaultMain
  [ bgroup "perimeter/slow" $ benchPolygonAction perimeter
  , bgroup "perimeterfast" $ benchPolygonAction perimeterOptimized
  , bgroup "doubleArea/slow" $ benchPolygonAction doubleArea
  , bgroup "doubleArea/fast" $ benchPolygonAction doubleAreaOptimized
  ]
