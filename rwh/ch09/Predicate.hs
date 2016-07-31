{-# LANGUAGE ScopedTypeVariables #-}

import Control.Monad (filterM, forM, liftM)
import System.Directory (Permissions(..), getDirectoryContents, getModificationTime, getPermissions)
import System.Time (ClockTime(..))
import System.FilePath (takeExtension, (</>))
import Control.Exception (SomeException, bracket, handle)
import System.IO (IOMode(..), hClose, hFileSize, openFile)

import RecursiveContents (getRecursiveContents)

type Predicate = FilePath -> Permissions -> Maybe Integer -> ClockTime -> Bool

type InfoP p = FilePath -> Permissions -> Maybe Integer -> ClockTime -> p

pathP path _ _ _ = path
sizeP _ _ (Just size) _ = size
sizeP _ _ Nothing _ = -1
mtimeP _ _ _ time = time
permP _ perm _ _ = perm

liftP :: (a -> b -> c) -> InfoP a -> b -> InfoP c
liftP q f k = \w x y z -> (f w x y z) `q` k

equalP, (==?) :: (Eq a) => InfoP a -> a -> InfoP Bool
equalP = liftP (==)
(==?) = equalP

greaterP, lesserP, (<?), (>?) :: (Ord a) => InfoP a -> a -> InfoP Bool
greaterP = liftP (>)
lesserP = liftP (<)
(>?) = greaterP
(<?) = lesserP

simpleAndP :: InfoP Bool -> InfoP Bool -> InfoP Bool
simpleAndP f g w x y z = f w x y z && g w x y z

liftP2 :: (a -> b -> c) -> InfoP a -> InfoP b -> InfoP c
liftP2 q f g w x y z = f w x y z `q` g w x y z

andP = liftP2 (&&)
orP = liftP (||)

(&&?) = andP
(||?) = orP

infixr 3 &&?
infix 4 >?
infix 4 <?
infix 4 ||?
infix 4 ==?

getSize :: FilePath -> IO (Maybe Integer)
getSize path = do
  h <- openFile path ReadMode
  size <- hFileSize h
  hClose h
  return (Just size)

getSafeSize :: FilePath -> IO (Maybe Integer)
getSafeSize path = handle (\(_::SomeException) -> return Nothing) $
  bracket (openFile path ReadMode) hClose $ \h -> do
    size <- hFileSize h
    return (Just size)

find p path = getRecursiveContents path >>= filterM check
  where
    check name = do
      perms <- getPermissions name
      size <- getSize name
      modified <- getModificationTime name
      return (p name perms size modified)


data Info = Info {
  infoPath :: FilePath,
  infoPerms :: Permissions,
  infoSize :: Maybe Integer,
  infoTime :: Maybe ClockTime
  } deriving (Show, Eq, Ord)

getInfo :: FilePath -> IO Info
getInfo = undefined

traverseDir :: ([Info] -> [Info]) -> FilePath -> IO [Info]
traverseDir order path = do
  names <- getUsefulContent path
  contents <- mapM getInfo (path : map (path </>) names)
  liftM concat $ forM (order contents) $ \info -> do
    if isDirectory info && infoPath info /= path
      then traverseDir order (infoPath info)
      else return [info]

getUsefulContent :: FilePath -> IO [String]
getUsefulContent path = do
  files <- getDirectoryContents path
  return (filter (`notElem` [".", ".."]) files)

isDirectory :: FilePath -> Bool
isDirectory = maybe False searchable . infoPerms
