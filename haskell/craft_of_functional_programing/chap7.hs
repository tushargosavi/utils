myhead :: [a] -> a
myhead (x:_) = x

mytail :: [a] -> [a]
mytail (_:x) = x

mynull :: [a] -> Bool
mynull []	= True
mynull (_:_)	= False 

-- 7.1
p1 :: [Int] -> Int
p1 []	= 0
p1 (a:xs) = a + 1

p1_1 :: [Int] -> Int
p1_1 a = if (a == []) then 0 else head a + 1

p2 :: [Int] -> Int
p2 [] = 0
p2 (a:[]) = a
p2 (a:b:_) = a + b

p2_1 a = if (a == []) then 0 else if (length a == 1) then head a else (head a + (head (tail a)))

-- 7.4
product1 :: [Int] -> Int
product1 [] = 1
product1 (x:xs) = x * product1 xs

myand :: [Bool] -> Bool
myand []= True
myand (a:as) = a && (myand as)

iSort :: [Int] -> [Int]
iSort [] = []
iSort (x:xs) = ins1 x (iSort xs)

ins1 :: Int -> [Int] -> [Int]
ins1 x [] = [x]
ins1 x (y : ys) 
	| x == y	=	ins1 x ys
	| x <= y	=	x:(y:ys)
	| otherwise	=	y:ins x ys


ins :: Int -> [Int] -> [Int]
ins x [] = x:[] 
ins x xs = [a | a <- xs, a < x || a == x] ++ [x] ++ [a | a <- xs, a > x]

elemNum :: Int -> [Int] -> Int
elemNum x [] = 0
elemNum x (y:ys) 
	| y == x	= 1 + elemNum x ys
	| otherwise	= elemNum x ys	

elemNum1 :: Int -> [Int] -> Int
elemNum1 x xs = length [1 | a <- xs, a == x]

unique :: [Int] -> [Int]
unique xs = uniq1 xs xs

uniq1 :: [Int] -> [Int] -> [Int]
uniq1 [] [] = []
uniq1 [] xs = []
uniq1 (x:xs) b 
	| (elemNum x b) == 1	= x : uniq1 xs b
	| otherwise		= uniq1 xs b

reverse1 :: [a] -> [a]
reverse1 [] = []
reverse1 (x:xs) = reverse1 xs ++ [x]

unzip1 :: [(a,b)] -> ([a], [b])
unzip1 [] = ([], [])
unzip1 (x:xs) = (fst x : fst b, snd x : snd b)
	where b = unzip1 xs

minarray :: [Int] -> Int
minarray (x:[]) = x
minarray (x:xs) 
	| minarray xs < x	=	minarray xs
	| otherwise		=	x

maxarray :: [Int] -> Int
maxarray (x:[])	=	x
maxarray (x:xs) 
	| maxarray xs > x	=	maxarray xs
	| otherwise		=	x

sortunique :: [Int] -> [Int]
sortunique [] = []
sortunique (x:[]) = [x]
sortunique (x:xs)
	| (x == head xs)	=	sortunique xs
	| otherwise		= 	x : sortunique xs

myzip3 :: [a] -> [b] -> [c] -> [(a,b,c)]
myzip3 (x:xs) (y:ys) (z:zs) = (x,y,z) : zip3 xs ys zs
myzip3 [] _ _  = []
myzip3 _ [] _  = []
myzip3 _ _ []  = []


--
-- 
sublist :: [Char] -> [Char] -> Bool
sublist (x:xs) (y:ys)
	| x == y	= sublist xs ys
	| otherwise	= sublist (x:xs) ys
sublist [] _		= True
sublist _ [] 		= False







--
-- Text processing system written in haskell
--   
whiteSpace = [ ' ' , '\t', '\n' ]
getWord :: String -> String
getWord [] = []
getWord (x:xs)
	| elem x whiteSpace	= []
	| otherwise		= x : getWord xs

dropWord :: String -> String
dropWord [] = []
dropWord (x:xs)
	| elem x whiteSpace	= x:xs
	| otherwise		= dropWord xs

dropSpace :: String -> String
dropSpace [] = []
dropSpace (x:xs)
	| elem x whiteSpace	= dropSpace xs
	| otherwise		= x:xs

type	Word =	String
type	Line = [Word]

splitWords :: String -> [Word]
splitWords st = split (dropSpace st)

split	:: String -> [Word]
split [] = []
split st = getWord st : split (dropSpace (dropWord st))

myGetLine	:: Int -> [Word] -> Line
myGetLine len [] = []
myGetLine len (w:ws)
	| length w <= len	= w : restOfLine
	| otherwise		= []
	where
	newLen = len - (length w + 1)
	restOfLine = myGetLine newLen ws

dropLine :: Int -> [Word] -> Line
dropLine len ws = drop (length (myGetLine len ws)) ws

splitLines :: Int -> [Word] -> [Line]
splitLines num [] = []
splitLines num ws = myGetLine num ws : splitLines num (dropLine num ws)

splitLines1 :: [Word] -> [Line]
splitLines1 ws = splitLines 80 ws

myFill :: String -> [Line]
myFill = splitLines1 . splitWords

joinLine :: Line -> String
joinLine [] = []
joinLine (w:ws) = w ++ " " ++ joinLine ws

joinLines :: [Line] -> String
joinLines [] = []
joinLines (l:ls) = joinLine l ++ "\n" ++ joinLines ls

countChar :: Char -> String -> Int
countChar ch [] = 0
countChar ch (c:cs)
	| ch == c	= 1 + countChar ch cs
	| otherwise	= countChar ch cs
wc :: String -> (Int, Int, Int)
wc str = (length str, length (split str), (countChar '\n' str) + 1)

--
-- Check palindrom of the list
--
isPalin :: String -> Bool
isPalin [] = True
isPalin	(x:[]) = True
isPalin (x:xs) = (x == last (x:xs)) && isPalin (init xs)

--
-- Check if the first string matches with
-- head of the second string or not.
--
isHead:: String -> String -> Bool
isHead [] _ = True
isHead _ [] = False
isHead (x:xs) (y:ys) = (x == y) && isHead xs ys

--
-- Checks if first argument is substring of second argument
-- or not
--
isSub :: String -> String -> Bool
isSub str [] = False
isSub str (x:xs)
	| isHead str (x:xs)	= True
	| otherwise		= isSub str xs

--
-- Replace first occuracne of str with dest in st
--
subst :: String -> String -> String -> String
subst src dest [] = []
subst src dest st
	| isHead src st	= dest ++ drop (length src) st
	| otherwise	= head st : subst src dest (tail st)

