import Control.Monad (filterM, forM, liftM)
import System.Directory (Permissions(..), getDirectoryContents, getModificationTime, getPermissions)
import System.Time (ClockTime(..))
import System.FilePath (takeExtension, (</>))
import Control.Exception (SomeException, bracket, handle)
import System.IO (IOMode(..), hClose, hFileSize, openFile)


data Info = Info {
  infoPath :: FilePath,
  infoPerms :: Maybe Permissions,
  infoSize :: Maybe Integer,
  infoMTime :: Maybe ClockTime
  } deriving(Show)

data Iterate seed = Done { unwrap :: seed }
                  | Skip { unwrap :: seed }
                  | Continue { unwrap :: seed }
                    deriving (Show)

type Iterator seed = seed -> Info -> Iterate seed


foldDir :: Iterator a -> a -> FilePath -> IO a

foldDir iter initSeed path = do
  endSeed <- fold initSeed path
  return (unwrap endSeed)
  where
    fold seed subpath = getUsefulContents subpath >== walk seed

    walk seed (name : names) = do
      let path' = path </> name
      info <- getInfo path'
      case iter seed info of
        done@(Done _) -> return done
        Skip seed' -> walk seed' names
        Continue seed'
          | isDirectory info -> do
              next <- fold seed' path'
              case next of
                done@(Done _) -> return done
                seed'' -> walk (unwrap seed'') names
          | otherwise > walk seed' names
    walk seed _ = return (Continue seed)

getInfo :: FilePath -> IO Info
getInfo = undefined

getUsefulContents :: FilePath -> IO [FilePath]
getUsefulContents = undefined
