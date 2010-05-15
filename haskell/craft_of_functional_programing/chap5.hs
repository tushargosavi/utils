import Prelude hiding (elem)
import Data.Char hiding (isDigit, toUpper)

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



---
-- Chapter 5
-- 
fibStep :: (Int, Int) -> (Int, Int)
fibStep (u, v) = (v, (u+v))

fibPair :: Int -> (Int, Int)
fibPair 0 = (0, 1)
fibPair n = fibStep (fibPair ( n - 1))

fastFib :: Int -> Int
fastFib = fst . fibPair

-- 5.1
maxOccurs :: Int -> Int -> (Int, Int)
maxOccurs a b
	| a > b = (a, 1)
	| a == b = (a, 2)
	| otherwise = (b,1)

maxThreeOccurs :: Int -> Int -> Int -> (Int, Int)
maxThreeOccurs a b c
	| fst (maxOccurs a b) == c = (c, snd (maxOccurs a b) + 1)
	| fst (maxOccurs a b) > c  = maxOccurs a b
	| fst (maxOccurs a b) < c  = (c, 1)

minThree :: Int -> Int -> Int -> Int
minThree a b c 
	| a <= b && a <= c	= a
	| b <= c		= b
	| otherwise		= c

middle :: Int -> Int -> Int -> Int
middle a b c
	| (a <= b && b <= c) || (c <= b && b <= a)	= b
	| (b <= a && a <= c) || (c <= a && a <=b )	= a
	| otherwise					= c

orderTripple :: (Int, Int, Int) -> (Int, Int, Int)
orderTripple (a, b, c) = (minThree a b c, middle a b c, maxThree a b c)

-- 5.3
--
slope :: (Float, Float) -> (Float, Float) -> Float
slope (x1,y1) (x2,y2) =  (y2-y1) / (x2-x1)

xIntersect :: (Float, Float) -> (Float, Float) -> (Float, Float)
xIntersect (x1,y1) (x2,y2) = (x2 - y2 * (1.0 / slope (x1, y1) (x2, y2)), 0)

-- 5.4
--
doubleAll :: [Int] -> [Int]
doubleAll xs = [ 2*n | n <- xs ]

capitalize :: String -> String
capitalize str = [ toUpper c | c <- str ]

divisors :: Int -> [ Int ]
divisors n = [ no | no <-[1 .. n] , n `mod` no == 0]

-- Need to handle slepcial case for 1 because [ 1 .. 1 ] in divisor 
-- will get expand to [1] and not [ 1, 1]
isPrime :: Int -> Bool
isPrime n
	| n == 1		= True
	| divisors n == [1, n]	= True
	| otherwise		= False

matches :: Int -> [Int] -> [Int]
matches n list = [ no | no <- list , n == no]

elem :: Int -> [Int] -> Bool
elem n list
	| matches n list == []		= False
	| otherwise			= True 
