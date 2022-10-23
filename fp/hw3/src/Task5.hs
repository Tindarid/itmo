module Task5
    ( FS (..)
    , contents
    , contentsRecursively
    , getDirectory
    , name
    , _file
    , _dir
    ) where

import Control.Exception
import Control.Monad.Trans.Class (lift)
import Control.Monad.Trans.Except (ExceptT (..), runExceptT, throwE)
import Lens.Micro (Lens', Traversal', lens)
import System.Directory (doesDirectoryExist, doesFileExist, listDirectory)
import System.FilePath (isValid, splitDirectories)

-- | Type for filesystem tree (simple, only names)
data FS = Dir  { _name :: FilePath, _contents :: [FS] }
        | File { _name :: FilePath }
        deriving (Show)

-- | Get simple name of file path
getSimpleName :: FilePath -> FilePath
getSimpleName = last . splitDirectories

-- | Checks path, then reads path recursively, on failure returns error
readPath :: FilePath -> ExceptT String IO FS
readPath path = if not (isValid path)
                   then throwE ("error with path `" ++ path ++ "`: it is not valid")
                   else do isDirectory <- lift $ doesDirectoryExist path
                           if isDirectory
                             then readEntireDirectory path
                             else do isFile <- lift $ doesFileExist path
                                     if isFile
                                       then return (File { _name = getSimpleName path })
                                       else throwE ("error with path `" ++ path ++ "`: is not a file or directory (maybe does not exist)")

-- | Assumes that path is directory, reads it recursively, on failure returns error
readEntireDirectory :: FilePath -> ExceptT String IO FS
readEntireDirectory dir = do result <- lift (try (listDirectory dir) :: IO (Either IOException [FilePath]))
                             case result of
                               Left ex     -> throwE ("error while listing directory `" ++ dir ++ "`: " ++ show ex)
                               Right paths -> do nodes <- mapM readPath (map ((dir ++ "/") ++) paths)
                                                 return Dir { _name = getSimpleName dir, _contents = nodes}

-- | Read path recursively, check that it is directory
getDirectory :: FilePath -> IO (Either String FS)
getDirectory path = do result <- runExceptT (readPath path)
                       case result of
                         Right (File _) -> return (Left ("error with path `" ++ path ++ "`: it was read succesfull, but it is not directory"))
                         _              -> return result

name :: Lens' FS FilePath
name = lens (_name) (\node newName -> node { _name = newName })

contents :: Traversal' FS [FS]
contents f obj@(Dir { _contents = value }) = (\newValue -> obj { _contents = newValue }) <$> (f value)
contents _ obj                             = pure obj

_file :: Traversal' FS FS
_file f obj@(File {}) = f obj
_file _ obj           = pure obj

_dir :: Traversal' FS FS
_dir f obj@(Dir {}) = f obj
_dir _ obj          = pure obj

contentsRecursively :: Traversal' FS FS
contentsRecursively f obj@(Dir  { _contents = inner }) = pure <$> (f obj) <*> (traverse (contentsRecursively f) inner)
contentsRecursively f obj                              = f obj

-- | Practice block
-- 1. node^.contents
-- 2. node^?dir.name
-- 3. node^?_file.name^.non ""
-- 4. root & name .~ "/"
-- 5. root & name .% (++ "suffix")
-- 6. dir^..contents.traversed.(filtered (not isFile))^?each
-- 7. dir^..contents.traversed.(filtered isFile)
--    (isFile checks that FS == (File _))
