
type Picture = [[Char]]

name :: Picture
name = 	[ "............" ,
	  "..######...." ,
	  "..######...." ,
	  "....##......" ,
	  "....##......" ,
	  "....##......" ,
	  "....##......" ,
	  "............" ]

picture2str :: Picture -> String
picture2str p = concat [ s ++ "\n" | s <- p ]

flipH :: Picture -> Picture
flipH = reverse

above :: Picture -> Picture -> Picture
above = (++)

flipV :: Picture -> Picture
flipV p = [ reverse line | line <- p ]

sideBySide :: Picture -> Picture -> Picture
sideBySide a b = [ line1 ++ line2 | (line1, line2) <- zip a b ]

invertChar :: Char -> Char
invertChar ch = if ch == '.' then '#' else '.'

invertColor :: Picture -> Picture
invertColor p = [ [invertChar c | c <- line ] | line <- p ]

superimposeChar :: Char -> Char -> Char
superimposeChar '.' '.'  = '.'
superimposeChar a b = '#'

superimposeLine :: String -> String -> String
superimposeLine l1 l2 = [ superimposeChar c1 c2 | (c1, c2) <- zip l1 l2 ]

superimposePicture :: Picture -> Picture -> Picture
superimposePicture p1 p2 = [ superimposeLine l1 l2 | (l1, l2) <- zip p1 p2 ]

supPic :: Picture -> Picture -> Picture 
supPic p1 p2 =
	[[ superimposeChar c1 c2 | (c1, c2) <- zip l1 l2] | (l1, l2) <- zip p1 p2]


type Position = (Int, Int)
type Image = (Picture, Position)

makeImage :: Picture -> Position -> Image
makeImage pict pos = (pict, pos)

changePosition :: Image -> Position -> Image
changePosition img pos = (fst img, pos)

moveImage :: Image -> Position -> Image
moveImage img pos = 
	(fst img, ((fst p + fst pos), (snd p + snd pos)))
	where p = snd img


type Name = String
type Price = Int
type BarCode = Int

lineLength :: Int
lineLength = 30

type Database = [(BarCode, Name, Price)]
codeIndex :: Database
codeIndex =
	[(123, "Fish Fingers", 121),
	 (100, "Chicken", 130),
	 (121, "Egges", 140),
	 (150, "Oil",	150)]

type Basket = [(BarCode)]
type BillType = [(Name, Price)]

isIn :: BarCode -> [(BarCode)] -> Bool
isIn code list 
	| [ a | a <- list, a == code] == []	= False
	| otherwise				= True

makeBill :: Basket -> BillType
makeBill list =
	[ (name, price) | (barcode, name, price) <- codeIndex, isIn barcode list]

formatPence :: Int -> String
formatPence no =
	show (no `div` 100) ++ "." ++ (if ((no `mod` 100) < 10) then "0" else "") ++ show (no `mod` 100)

formatLine :: (Name, Price) -> String
formatLine (name, price) =
	name ++ [ '.' | a <- [ 0 .. (lineLength - (length name + length (formatPence price)))]] ++ formatPence price ++ "\n"

formatLines :: BillType -> String
formatLines bill =
	concat [ formatLine line | line <- bill ]

makeTotal :: BillType -> Int
makeTotal bill =
	sum [ price | (name, price) <- bill ]

formatTotal :: Int -> String
formatTotal price = formatLine ("Total", price)

formatBill :: BillType -> String
formatBill bill = "      Haskell Store      \n" ++ formatLines bill ++ "\n" ++ formatTotal (makeTotal bill) 


look :: Database -> BarCode -> (Name, Price)
look database code
	| result == []		= ("Unknown Item" , 0)
	| otherwise		= head result
	where result = [ (name,price) | (barcode, name, price) <- database, barcode == code ]

lookup1 :: BarCode -> (Name, Price)
lookup1 code = look codeIndex code

makeBill1 :: Basket -> BillType
makeBill1 basket = [ lookup1 code | code <- basket]
