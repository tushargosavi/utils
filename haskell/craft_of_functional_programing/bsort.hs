-- This is recursive bubble sort in haskell

bsort :: (Ord a) => [a] -> [a]
bsort [] = []
bsort (x:[]) = [x]
bsort (x:y:[]) = if (x < y) then (x:y:[]) else (y:x:[])
bsort (x:xs) = if (x < head (bsort xs))
               then (x:bsort xs)
               else (head (bsort xs)) : bsort (x:tail (bsort xs))
                    
