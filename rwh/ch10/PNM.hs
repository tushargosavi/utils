import qualified Data.ByteString.Lazy.Char8 as L8
import qualified Data.ByteString.Lazy as L
import Data.Char (isSpace, chr, isDigit)
import Data.Int (Int64)
import Data.Word (Word8)

data Greymap = Greymap {
  greyWidth :: Int,
  greyHeigth :: Int,
  greyMax :: Int,
  greyData :: L.ByteString
  } deriving(Eq)

instance Show Greymap where
  show (Greymap w h m _) = "Greymap " ++ show w ++ "x" ++ show h ++ " " ++ show m


{-
- parse a image, return image and remaining string. as a PNM file
- can container multiple images.
-}


matchHeader :: L.ByteString -> L.ByteString -> Maybe L.ByteString
matchHeader prefix str
  | prefix `L8.isPrefixOf` str =
      Just (L8.dropWhile isSpace (L.drop (L.length prefix) str))
  | otherwise =
      Nothing

getNat :: L.ByteString -> Maybe (Int, L.ByteString)
getNat s = case L8.readInt s of
  Nothing -> Nothing
  Just (num, rest)
    | num <= 0 -> Nothing
    | otherwise -> Just (fromIntegral num, rest)

getBytes :: Int -> L.ByteString -> Maybe (L.ByteString, L.ByteString)
getBytes num str = let count = fromIntegral num
                       both@(prefix,_) = L.splitAt count str
                   in
                     if L.length prefix < count
                     then Nothing
                     else Just both

parseP5_ugly :: L.ByteString -> Maybe (Greymap, L.ByteString)
parseP5_ugly s =
  case matchHeader (L8.pack "P5") s of
    Nothing -> Nothing
    Just s1 ->
      case getNat s1 of
        Nothing -> Nothing
        Just (width, s2) ->
          case getNat (L8.dropWhile isSpace s2) of
            Nothing -> Nothing
            Just (height, s3) ->
              case getNat (L8.dropWhile isSpace s3) of
                Nothing -> Nothing
                Just (maxGrey, s4)
                  | maxGrey > 255 -> Nothing
                  | otherwise ->
                    case getBytes 1 s4 of
                      Nothing -> Nothing
                      Just (_, s5) ->
                        case getBytes (width * height) s5 of
                          Nothing -> Nothing
                          Just (bitmap, s6) ->
                            Just (Greymap width height maxGrey bitmap, s6)

(>>?) :: Maybe a -> (a -> Maybe b) -> Maybe b
Nothing >>? _ = Nothing
Just v >>? f = f v

skipSpaces1 :: (a, L.ByteString) -> Maybe (a, L.ByteString)
skipSpaces1 (a, s) = Just (a, L8.dropWhile isSpace s)

parseP5 :: L.ByteString -> Maybe (Greymap, L.ByteString)
parseP5 s =
  matchHeader (L8.pack "P5") s   >>?
  \s ->skipSpaces1 ((), s)        >>?
  \(_, s) -> getNat s            >>?
  skipSpaces1                     >>?
  \(width, s) -> getNat s        >>?
  skipSpaces1                     >>?
  \(height, s) -> getNat s       >>?
  \(maxGrey, s) -> getBytes 1 s  >>?
  (getBytes (width * height) . snd) >>?
  \(bitmap, s) -> Just (Greymap width height maxGrey bitmap, s)


data ParseState = ParseState {
  string :: L.ByteString,
  offset :: Int64
  } deriving (Show)

-- runParse is the extractor, which extract function from the
-- Parse.
newtype Parse a = Parse {
  runParse :: ParseState -> Either String (a, ParseState)
  }
{-- Parse a is a function taking parseState and returning an result and newParse state
or an error.

Parse Int = \s -> (fromInt (string s), newParseState)
  where newParseState = s { string = remainig, offset = newOffset }
        newOffset = numeber of chars consumes while reading int.
}
-}

-- helper function to wrap any value, as a function which
-- retuns that value, and parseState when applied on parseState.
identity :: a -> Parse a
identity a = Parse (\parseState -> Right (a, parseState))

-- wrap initial string in  a initialParseState and apply supplied
-- function on it to extract the result, discards final parseState.
parse:: Parse a -> L.ByteString -> Either String a
parse parser byteStr
  = case runParse parser (ParseState byteStr 0) of
      Left errorMsg -> Left errorMsg
      Right (result, _) -> Right result

modifyOffset :: ParseState -> Int64 -> ParseState
modifyOffset state newOffset = state { offset = newOffset }


{--
- This is most interesting function this chapter.
-
-}
parseByte ::Parse Word8
parseByte =
  getState ==> \initState ->
    case L.uncons(string initState) of
      Nothing -> bail "no more input"
      Just (byte, rest) ->
        putState newState ==> \_->
          identity byte
        where
          newState = initState { string = rest, offset = newOffset }
          newOffset = offset initState + 1

{--
 - make easier to access the initialState for functions which are
 - chained using (==>)
-}
getState :: Parse ParseState
getState = Parse (\s -> Right (s, s))

putState :: ParseState -> Parse ()
putState s = Parse(\_ -> Right((), s))

bail :: String -> Parse a
bail err = Parse (\state -> Left ("byte offset " ++ show (offset state) ++ ":" ++ err))

{- chaining of a parser, returns the function which applies first function on
   the parseState getting
   (result, newParseState). It then applies second function on result which
   returns new Parse b. after that the result Parse function is applied on
   newParseState.
-}
(==>) ::Parse a -> (a -> Parse b) -> Parse b
first ==> second = Parse chained
  where chained initState =
          case runParse first initState of
            Left errMsg -> Left errMsg
            Right (res, newState) ->
              runParse (second res) newState

instance Functor Parse where
  fmap f parser = parser ==> \result ->
                               identity (f result)

w2c :: Word8 -> Char
w2c = chr . fromIntegral

parseChar :: Parse Char
parseChar = w2c <$> parseByte

{-- fmap fst - this returns the first part of tuple, wrapped in Maybe.
    L.uncons . string = this part extract the string from parseState and then
    uncons return Maybe (Word8, Rest of String) if string has any char.
-}
peekByte :: Parse (Maybe Word8)
peekByte = (fmap fst . L.uncons . string) <$> getState

peekChar :: Parse (Maybe Char)
peekChar = fmap w2c <$> peekByte

parseWhile :: (Word8 -> Bool) -> Parse [Word8]
parseWhile p = (fmap p <$> peekByte) ==> \mp ->
  if mp == Just True
  then parseByte ==> \b ->
    (b:) <$> parseWhile p
  else identity []

parseRawPGN =
  parseWhileWith w2c notWhite ==> \header -> skipSpaces ==>&
  assert( header == "P5") "invalid raw header " ==>&
  parseNat ==> \width -> skipSpaces ==>&
  parseNat ==> \height -> skipSpaces ==>&
  parseNat ==> \maxGrey ->
  parseByte ==>&
  parseBytes (width * height) ==> \bitmap ->
  identity (Greymap width height maxGrey bitmap)
  where
    notWhite = (`notElem` " \r\t\n")

parseWhileWith :: (Word8 -> a) -> (a -> Bool) -> Parse [a]
parseWhileWith f p = fmap f <$> parseWhile (p . f)

parseNat :: Parse Int
parseNat = parseWhileWith w2c isDigit ==> \digits ->
  if null digits
  then bail "no more input"
  else let n = read digits
       in if n < 0
          then bail "interger overflow"
          else identity n

(==>&) :: Parse a -> Parse b -> Parse b
p ==>& f = p ==> \_ -> f

skipSpaces :: Parse ()
skipSpaces = parseWhileWith w2c isSpace ==>& identity ()

assert :: Bool -> String -> Parse ()
assert True _ = identity ()
assert False err = bail err

parseBytes :: Int -> Parse L.ByteString
parseBytes n =
  getState ==> \st ->
  let n' = fromIntegral n
      (h, t) = L.splitAt n' (string st)
      st' = st { offset = offset st + L.length h, string = t}
  in
    putState st' ==>&
    assert (L.length h == n') "end of input" ==>&
    identity h
