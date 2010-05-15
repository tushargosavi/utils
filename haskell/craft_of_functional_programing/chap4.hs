
import Prelude 
import Data.Char hiding (isDigit)

exOr :: Bool -> Bool -> Bool
-- exOr x y = (x || y) && (not (x && y))

exOr x y = (x == True && y == False) || (x == False && y == True)

nAnd :: Bool -> Bool -> Bool
nAnd x y = not (x && y )

threeEqual :: Int -> Int -> Int -> Bool
threeEqual a b c = (a ==b) && (b == c)

threeDifferent :: Int -> Int -> Int -> Bool
threeDifferent a b c = (a /= b) && (b /= c) && (c /= a)

fourEqual :: Int -> Int -> Int -> Int -> Bool
fourEqual a b c d = (a == b) && ( b == c) && (c ==d)

fourEqual1 :: Int -> Int -> Int -> Int -> Bool
fourEqual1 a b c d = threeEqual a b c && a == d

fourDifferent :: Int -> Int -> Int -> Int -> Bool
fourDifferent a b c d = (a /= b) && ( a /= c) && (a /= d) && (b /= c) && (b /= d) && (c /= d)

fourDifferent1 :: Int -> Int -> Int -> Int -> Bool
fourDifferent1 a b c d = (a /= b) && ( a /= c) && (a /= d) && (b /= c) && (b /= d) && (c /= d)

maxThree :: Int -> Int -> Int -> Int
maxThree a b c 
	| a >= b && a >= c = a
	| b >= c = b
	| otherwise = c

maxFour :: Int -> Int -> Int -> Int -> Int
maxFour a b c d 
	| a >= b && a >= c && a >= d	= a
	| b >= c && b >=d 		= b
	| c >= d 			= c
	| otherwise 			= d

maxFour1 :: Int -> Int -> Int -> Int -> Int
maxFour1 a b c d = max a (maxThree b c d)

isDigit :: Char -> Bool
isDigit x = ('0' <= x) && ( '9' >= x)

offset :: Int
offset = (ord 'A') - (ord 'a')

isSmall :: Char -> Bool
isSmall c = ('a' <= c) && ('z' >= c)

toUpper :: Char -> Char
-- toUpper c = if (isSmall c) then chr (ord c + offset) else c
  
toUpper c 
	| isSmall c = chr (ord c + offset)
	| otherwise = c

charToNum :: Char -> Int
charToNum a 
	| isDigit a = (ord a - ord '0')
	| otherwise = 0

averageThree :: Int -> Int -> Int -> Float
averageThree a b c = fromIntegral (a + b + c) / 3


aboveAverage :: Float -> Float -> Int
aboveAverage x y 
	| x >= y = 1
	| otherwise = 0

howManyAboveAverage :: Int -> Int -> Int -> Int
howManyAboveAverage a b c = aboveAverage (fromIntegral a) (averageThree a b c) + 
				aboveAverage (fromIntegral b) (averageThree a b c) +
				aboveAverage (fromIntegral c) (averageThree a b c) 

numberNDroots :: Float -> Float -> Float -> Int
numberNDroots a b c 
	| b^2 > 4.0 * a * c	= 2
	| b^2 ==  4.0 * a * c	= 1
	| b^2 < 4.0 * a * c	= 0

numberRoots :: Float -> Float -> Float -> Int
numberRoots a b c 
	| a /= 0.0		= numberNDroots a b c
	| b /= 0		= 1
	| b == 0 && c /= 0	= 0
	| b == 0 && c == 0	= 3

largerRoot :: Float -> Float -> Float -> Float
largerRoot a b c = ((-b) + sqrt (b^2 - 4*a*c)) / (2*a)

smallerRoot :: Float -> Float -> Float -> Float
smallerRoot a b c = ((-b) + sqrt (b^2 - 4*a*c)) / (2*a)


-- 
-- Chapter 4
--
boolToInt :: Bool -> Int
boolToInt x 
	| x == True 	= 1
	| otherwise 	= 0

howManyEqual :: Int -> Int -> Int -> Int
howManyEqual a b c 
	| (a == b) && (b == c) && (a == c)	= 3
	| (a == b) || (a == c) || (b ==c)	= 2
	| otherwise				= 0

rangeProduct :: Int -> Int -> Int
rangeProduct a b 
	| (a == b)	= a
	| otherwise  = b * rangeProduct a (b-1)

fac :: Int -> Int 
fac n = rangeProduct 1 n

-- 4.7
multiAB :: Int -> Int -> Int
multiAB a b 
	| (a == 0)	= 0
	| otherwise	= b + multiAB (a-1) b


testFunc :: Int -> Int
testFunc 0 = 0
testFunc 1 = 44
testFunc 2 = 17
testFunc 6 = 50
testFunc _ = 0 

-- f is function of type (Int -> Int)
-- n is current counter
-- b is max value till now.
maxFuncValue :: (Int -> Int) -> Int ->Int -> Int
maxFuncValue f n b
	| n == 0	= b
	| n > 0		= maxFuncValue f (n-1) (max (f n) b)

-- 4.13
--
gcd1 :: Int -> Int -> Int
gcd1 a b = if (b == 0) then a else gcd b (a `mod` b)

square :: Int -> Int
square a = a * a

power2 :: Int -> Int
power2 a
	| a == 0 		= 1
	| (a `mod` 2 == 0)	= square (power2 (a `div` 2))
	| (a `mod` 2 /= 0)	= square (power2 (a `div` 2)) * 2


