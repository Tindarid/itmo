module Algebraic.Week
  ( Weekday (..)
  , afterDays
  , daysToParty
  , isWeekend
  , nextDay
  ) where

data Weekday = Monday | Tuesday | Wednesday | Thursday |
               Friday | Saturday | Sunday deriving (Show)

totalDays :: Int
totalDays = 7

instance Enum Weekday where
  toEnum 0 = Monday
  toEnum 1 = Tuesday
  toEnum 2 = Wednesday
  toEnum 3 = Thursday
  toEnum 4 = Friday
  toEnum 5 = Saturday
  toEnum 6 = Sunday
  toEnum n = toEnum (n `mod` totalDays)

  fromEnum Monday    = 0
  fromEnum Tuesday   = 1
  fromEnum Wednesday = 2
  fromEnum Thursday  = 3
  fromEnum Friday    = 4
  fromEnum Saturday  = 5
  fromEnum Sunday    = 6

instance Eq Weekday where
  Monday    == Monday    = True
  Tuesday   == Tuesday   = True
  Wednesday == Wednesday = True
  Thursday  == Thursday  = True
  Friday    == Friday    = True
  Saturday  == Saturday  = True
  Sunday    == Sunday    = True
  _         == _         = False

nextDay :: Weekday -> Weekday
nextDay = succ

afterDays :: Weekday -> Int -> Weekday
afterDays d n = toEnum (n + fromEnum d)

isWeekend :: Weekday -> Bool
isWeekend Saturday = True
isWeekend Sunday   = True
isWeekend _        = False

daysToParty :: Weekday -> Int
daysToParty d = (fromEnum Friday - fromEnum d + totalDays) `mod` totalDays
