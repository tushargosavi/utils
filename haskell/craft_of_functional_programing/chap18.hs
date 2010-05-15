helloWorld = putStr "Hello World"

sum2Num :: IO ()
sum2Num =
	do
	putStr "Enter Number 1 :"
	num1 <- getLine
	putStr "Enter Number 2 :"
	num2 <- getLine
	let sum = (read num1 :: Int) + (read num2 :: Int)
	putStr ("Sum of Entered Number is : " ++ show sum)


copyUntilEmpty :: IO ()
copyUntilEmpty =
	do
		line <- getLine
		if (line == []) then
			return ()
		else (do putStr line
			 copyUntilEmpty)

