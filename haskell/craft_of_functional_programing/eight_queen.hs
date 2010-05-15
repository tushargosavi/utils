type Position = (Int, Int)

isSafe :: Position -> [Position] -> Bool
isSafe _ [] = True
isSafe p (x:xs) 
  | collide p x = False
  | otherwise = isSafe p xs
                
collide :: Position -> Position -> Bool
collide (i1, j1) (i2,j2) 
  | i1 == i2 = True
  | j1 == j2 = True
  | (abs (i1 - i2) == abs (j1 - j2)) = True
  | otherwise = False
                

{- 
The size is (bord size -1), i.e to slove 8 queen problem you
need to specify size as '7'
-}
solution :: Int -> Position -> [Position] -> [Position]
solution size pos curr
  -- if column is greater than bord size then we have found an solution.
  | fst pos > size = curr
  -- no soluation, if we have come to first column and last row, we have checked all positions on bord.
  | fst pos == 0 && snd pos > size = []
  -- current column is exhausested without a solution, backtrack.
  | (snd pos > size) = solution size (fst (head curr), snd (head curr) + 1 ) (tail curr)
  -- this is not a safe position try next cell
  | not (isSafe pos curr) = solution size (fst pos, (snd pos) + 1) curr
  -- this is a safe position , add it to list and check for other columns.
  | otherwise = solution size (fst pos + 1 , 0) (pos : curr)
                

{-
Find all solutions
Input : size of bord and first solution
i.e, all_sol size (solution size (0,0) [])
-}
all_sol _ [] = [] 
all_sol size last_sol = all_sol size next_sol ++ [last_sol]
                      where 
                        next_sol = solution size (fst (head last_sol), snd (head last_sol) + 1) (tail last_sol)


{-
safehead [] = []
safehead (x:xs) = x
all_pairs = [(i,j) | i<- [0..7], j <- [0..7]]
prob_sol y = [x | x <- all_pairs , isSafe x y]
cur_sol y = [ x| x <- prob_sol y, x /= [] && 
-}
