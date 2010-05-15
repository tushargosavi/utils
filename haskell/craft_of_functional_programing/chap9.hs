length1 :: [a] -> Int
length1 xs = sum (map const_1 xs)

const_1 :: a -> Int
const_1 a = 1


min1 :: (Int -> Int) -> [Int] -> Int
min1 f xs = min2 (map f xs)

min2 :: [Int] -> Int
min2 (x:[]) = x
min2 (x:xs)
	| x  < min2 xs	= x
	| otherwise	= min2 xs

mapallsame :: (Int -> Int) -> [Int] -> Bool
mapallsame f xs = allsame (map f xs)

allsame []	= False
allsame (x:[])	= True
allsame (x:y:xs)
	| x == y	= allsame (y:xs)
	| otherwise	= False


greater [] = True
greater (x:xs) = if (x > 0) then greater xs else False

isSorted [] = True
isSorted (x:[]) = True
isSorted (x:y:xs) = if (x <= y) then isSorted (y:xs) else False

iter :: Int -> (a -> a) -> a -> a
iter 0 f x = x
iter n f x = iter (n - 1) f (f x)

naturalSquare :: Int -> Int
naturalSquare n = foldr (+) 0 (map sq [1 .. n]) where sq x = x * x

positiveSum xs = sum (map sq (filter positive xs))
		where 
			sq x = (x * x)
			positive x = (x > 0)


mystery xs = foldr (++) [] (map sing xs) where sing x = [x]

filterFirst :: (Int -> Bool) -> [Int] -> [Int]
filerFirst f [] = []
filterFirst f (x:xs)
	| f x	= xs
	| otherwise	= x : filterFirst f xs


