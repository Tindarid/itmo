module ParsersSpec (spec) where

import Control.Applicative ((<|>))
import Data.Char (ord)
import Parsers.Combinator
import Test.Hspec
import Test.QuickCheck

spec :: Spec
spec = do
  describe "Copy-paste" $ do
    copyPasteSpec
  describe "Base combinators" $ do
    baseSpec
  describe "Simple parsers" $ do
    simpleParsersSpec

copyPasteSpec :: Spec
copyPasteSpec = do
  describe "<$>" $ do
    it "ord + char" $
      runParser (ord <$> element 'C') "C" `shouldBe` Just (67, "")
    it "ord + char + fail" $
      runParser (ord <$> element 'C') "c" `shouldBe` Nothing
  describe "<*>" $ do
    it "<$> + <*>" $
      runParser (const <$> element '1' <*> element '2') "123" `shouldBe` Just ('1', "3")
    it "<$> + <*> + fail" $
      runParser (const <$> element '2' <*> element '2') "123" `shouldBe` Nothing
  describe "<|>" $ do
    it "0 || 0" $ do
      runParser (element '1' <|> element '3') "2" `shouldBe` Nothing
    it "0 || 1" $ do
      runParser (element '1' <|> element '2') "2" `shouldBe` Just ('2', "")
    it "1 || 0" $ do
      runParser (element '2' <|> element '1') "2" `shouldBe` Just ('2', "")
    it "1 || 1" $ do
      runParser (element '2' <|> element '2') "2" `shouldBe` Just ('2', "")


baseSpec :: Spec
baseSpec = do
  describe "eof" $ do
    it "eof on EOF" $
      runParser eof "" `shouldBe` Just ((), "")
    it "eof on not EOF" $
      runParser eof "abacaba" `shouldBe` Nothing
  describe "satisfy" $ do
    it "satisfy simple" $
      runParser (satisfy (== 'c')) "cnotc" `shouldBe` Just ('c', "notc")
    it "satisfy isDigit" $
      runParser digit "1aaa" `shouldBe` Just ('1', "aaa")
    it "satisfy isNotDigit" $
      runParser digit "aaaa" `shouldBe` Nothing
  describe "element" $
    it "random" $
      property elementChecker
  describe "stream" $
    it "random" $
      property streamChecker
  describe "ok" $ do
    it "ok simple" $
      runParser ok "" `shouldBe` Just ((), "")
    it "ok simple 2" $
      runParser ok "aba" `shouldBe` Just ((), "aba")
    it "ok never fails" $
      property okChecker
        where
          okChecker :: String -> Bool
          okChecker s = runParser ok s == Just ((), s)

          elementChecker :: Char -> String -> Bool
          elementChecker c s = runParser (element c) (c : s) == Just (c, s)

          streamChecker :: String -> String -> Bool
          streamChecker p s = runParser (stream p) (p ++ s) == Just (p, s)

simpleParsersSpec :: Spec
simpleParsersSpec = do
  describe "integer" $ do
    it "`+` and many" $
      runParser integer "+123" `shouldBe` Just ("+123", "")
    it "`+` and single" $
      runParser integer "+1" `shouldBe` Just ("+1", "")
    it "`+` and nothing" $
      runParser integer "+" `shouldBe` Nothing
    it "`-` and many" $
      runParser integer "-23" `shouldBe` Just ("-23", "")
    it "`-` and single" $
      runParser integer "-3" `shouldBe` Just ("-3", "")
    it "`-` and nothing" $
      runParser integer "-" `shouldBe` Nothing
    it "one digit" $
      runParser integer "2" `shouldBe` Just ("2", "")
    it "several digits" $
      runParser integer "223213213 123" `shouldBe` Just ("223213213", " 123")
    it "random" $
      property integerChecker
        where
          integerChecker :: Integer -> String -> Bool
          integerChecker a s = case runParser integer ((show a) ++ " " ++ s) of
            Nothing        -> False
            Just (i, rest) -> (read i == a) && (rest == " " ++ s)
