module AlgebraicSpec (spec) where

import Algebraic.Nat
import Algebraic.Week
import Test.Hspec
import Test.QuickCheck

spec :: Spec
spec = do
  describe "Week" $ do
    weekSpec
  describe "Nat" $ do
    natSpec

weekSpec :: Spec
weekSpec = do
  describe "nextDay" $ do
    it "for Monday" $
      nextDay Monday `shouldBe` Tuesday
    it "for Tuesday" $
      nextDay Tuesday `shouldBe` Wednesday
    it "for Wednesday" $
      nextDay Wednesday `shouldBe` Thursday
    it "for Thursday" $
      nextDay Thursday `shouldBe` Friday
    it "for Friday" $
      nextDay Friday `shouldBe` Saturday
    it "for Saturday" $
      nextDay Saturday `shouldBe` Sunday
    it "for Sunday" $
      nextDay Sunday `shouldBe` Monday

  describe "afterDays" $ do
    it "for Monday" $
      afterDays Monday 1 `shouldBe` Tuesday
    it "for Tuesday" $
      afterDays Tuesday 5 `shouldBe` Sunday
    it "for Wednesday" $
      afterDays Wednesday 10 `shouldBe` Saturday
    it "for Thursday" $
      afterDays Thursday 30 `shouldBe` Saturday
    it "for Friday" $
      afterDays Friday (-1) `shouldBe` Thursday
    it "for Saturday" $
      afterDays Saturday 5 `shouldBe` Thursday
    it "for Sunday" $
      afterDays Sunday 4 `shouldBe` Thursday

  describe "isWeekend" $ do
    let notWeekends = [Monday, Tuesday, Wednesday, Thursday, Friday]
    let weekends    = [Saturday, Sunday]

    it "for not weekends" $
      map isWeekend notWeekends `shouldSatisfy` all not
    it "for weekends" $
      map isWeekend weekends `shouldSatisfy` all id

  describe "daysToParty" $ do
    it "for Monday" $
      daysToParty Monday `shouldBe` 4
    it "for Tuesday" $
      daysToParty Tuesday `shouldBe` 3
    it "for Wednesday" $
      daysToParty Wednesday `shouldBe` 2
    it "for Thursday" $
      daysToParty Thursday `shouldBe` 1
    it "for Friday" $
      daysToParty Friday `shouldBe` 0
    it "for Saturday" $
      daysToParty Saturday `shouldBe` 6
    it "for Sunday" $
      daysToParty Sunday `shouldBe` 5

propFunc :: (Integer -> Integer -> Integer)
  -> (Nat -> Nat -> Nat) -> (Integer -> Integer -> Bool) -> Integer -> Integer -> Bool
propFunc op1 op2 cond a b = if (not (cond a b)) then True
                            else natToInteger (op2 (fromInteger a) (fromInteger b)) == op1 a b

natSpec :: Spec
natSpec = do
  describe "addition" $ do
    it "0 + 0 == 0" $
      (Z + Z) `shouldBe` Z
    it "1 + 1 == 2" $
      ((S Z) + (S Z)) `shouldBe` S (S Z)
    it "1 + 3 == 4" $
      ((S Z) + S (S (S Z))) `shouldBe` S (S (S (S Z)))
    it "3 + 1 == 4" $
      (S (S (S Z)) + S Z) `shouldBe` S (S (S (S Z)))

  describe "equality" $ do
    it "0 == 0" $
      (Z == Z) `shouldBe` True
    it "1 == 1" $
      (S Z == S Z) `shouldBe` True
    it "2 == 2" $
      (S (S Z) == S (S Z)) `shouldBe` True

  describe "addition (property)" $ do
    it "random" $ property (propFunc (+) (+) (\a b -> a >= 0 && b >= 0))

  describe "multiply (property)" $ do
    it "random" $ property (propFunc (*) (*) (\a b -> a >= 0 && b >= 0))

  describe "substraction (property)" $ do
    it "random" $ property (propFunc (-) (-) (\a b -> a >= 0 && b >= 0 && a >= b))

  describe "fromInteger toInteger (property)" $ do
    it "random" $ property func
      where
        func :: Integer -> Bool
        func a = if a < 0 then True
                 else natToInteger (fromInteger a) == a
