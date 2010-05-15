--
--
--
--

data GTree a = Leaf a | Gnode [GTree a]

countLeaves :: GTree a -> Int
countLeaves (Leaf a) = 1
countLeaves (Gnode l) = sum [ countLeaves a | a <- l ]

depthTree (Leaf a) = 0
depthTree (Gnode ls) = 1 + max [ depthTree a | a <- ls ] 

sumTree (Leaf a) = a
sumTree (Gnode xs) = sum [ sumTree a | a <- xs ]
 
