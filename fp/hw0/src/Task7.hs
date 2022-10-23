module Task7
 ( expr1
 ) where

expr1 :: Bool
expr1 =
  let term1 = ("Dorian " :: String) in
  let term2 = (" Grey" :: String) in
  let term3 = ((++) :: String -> String -> String) in
  let term4 = ((term3 term1) :: String -> String) in
  let term5 = ((term4, term2) :: (String -> String, String)) in
  let term6 = ([term5] :: [(String -> String, String)]) in
  let term7 = (id :: (String -> String) -> (String -> String)) in
  let term8 = (uncurry :: ((String -> String) -> (String -> String)) -> (String -> String, String) -> String) in
  let term9 = ((term8 term7) :: (String -> String, String) -> String) in
  let term10 = (map :: ((String -> String, String) -> String) -> [(String -> String, String)] -> [String]) in
  let term11 = ((term10 term9) :: ([(String -> String, String)] -> [String])) in
  let term12 = ((term11 term6) :: [String]) in
  let term13 = (head :: [String] -> String) in
  let term14 = (null :: String -> Bool) in
  let term15 = ((.) :: (String -> Bool) -> ([String] -> String) -> [String] -> Bool) in
  let term16 = ((term14 `term15` term13) :: [String] -> Bool) in
  term16 term12
