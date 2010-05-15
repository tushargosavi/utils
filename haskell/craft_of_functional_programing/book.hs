
fact :: Int -> Int
fact 0 = 1
fact n = n * fact (n - 1)

type Person = String
type Book = String

type Database = [(Person, Book)]

exampleDatabase :: Database
exampleDatabase = [ ("Tushar", "Algorithms"), ("Sagar", "Compilers"), ("Shital", "Mocrobiology"), ("Tushar", "C++"), ("Sagar", "C++")]

books :: Database -> Person -> [ Book ]
books dbase name = [ snd b | b <- dbase, name == fst b] 

borrowers :: Database -> Book -> [ Person ]
borrowers dbase book = [ fst b | b <- dbase , snd b == book ]

borrowed :: Database -> Book -> Bool
borrowed dbase book = borrowers dbase book /= []

numBorrowed :: Database -> Person -> Int
numBorrowed dbase name = length (books dbase name)

-- Final

fibTable :: Int -> (Int, String)
fibTable 0 = (0, "0\t\t" ++ show 0 ++ "\n")
fibTable 1 = (1, "1\t\t" ++ show 1 ++ "\n")
fibTable n = ((fst (fibTable (n-2)) + fst (fibTable (n -1))),


