module FileSystem
    ( FSCrumb
    , FSZipper
    , greeting
    , loadOnStart
    , lsDirectory
    , changeDirectory
    ) where

import Control.Exception
import Control.Monad.Trans.Class (lift)
import Control.Monad.Trans.Except (ExceptT (..), runExceptT, throwE)
import System.Directory (doesDirectoryExist, doesFileExist, listDirectory)
import System.FilePath

data FileInfo = FileInfo {filename :: FilePath} deriving (Show)
data FolderInfo = FolderInfo {foldername :: FilePath} deriving (Show)

data FSNode = File FileInfo | Folder FolderInfo [FSNode] deriving (Show)

data FSCrumb = FSCrumb FolderInfo [FSNode] deriving (Show)
type FSZipper = (FSNode, [FSCrumb])

data Direction = Up | Cur | Down FilePath

-- | Assumes that path is directory or file, reads it, on failure returns error
readPath :: FilePath -> ExceptT String IO FSNode
readPath path = do isDirectory <- lift $ doesDirectoryExist path
                   if isDirectory
                     then readEntireDirectory path
                     else do isFile <- lift $ doesFileExist path
                             if isFile
                               then readEntireFile path
                               else throwE (path ++ ": does not exist, somebody deleted it (existence checked before)")

-- | Assumes that path is file
readEntireFile :: FilePath -> ExceptT String IO FSNode
readEntireFile file = return (File (FileInfo file))

-- | Assumes that path is directory, reads it recursively, on failure returns error
readEntireDirectory :: FilePath -> ExceptT String IO FSNode
readEntireDirectory dir = do result <- lift (try (listDirectory dir) :: IO (Either IOException [FilePath]))
                             case result of
                               Left ex     -> throwE (dir ++ ": error while reading: " ++ show ex)
                               Right paths -> do nodes <- mapM readPath (map ((dir ++ "/") ++) paths)
                                                 return (Folder (FolderInfo dir) nodes)

-- | Checks that directory exists, it is valid path and loads it
loadOnStart :: FilePath -> IO (Either String (FSNode, [FSCrumb]))
loadOnStart path = if not (isValid path)
                     then return (Left (path ++ " is not valid"))
                     else do isDirectory <- doesDirectoryExist path
                             if not isDirectory
                               then return (Left (path ++ " directory does not exist or it is file"))
                               else do result <- runExceptT(readPath path)
                                       case result of
                                         Right dir -> return (Right (dir, []))
                                         Left err  -> return (Left err)

-- | Get directory contents (if it is directory)
lsDirectory :: FSNode -> String
lsDirectory (File info)         = (filename info) ++ " is a file"
lsDirectory (Folder info nodes) = "Directory " ++ (foldername info) ++ " contains\n" ++ concat (map ((++ "\n") . getMetaData) nodes)

-- | Get filesystem node metadata
getMetaData :: FSNode -> String
getMetaData (File info)         = "file: " ++ filename info
getMetaData (Folder info nodes) = "directory: " ++ foldername info ++ " with " ++ (show $ length nodes) ++ " items"

-- | Greeting in command line
greeting :: FSZipper -> String
greeting (Folder info _, _) = foldername info ++ "> "
greeting (File info, _)     = filename info ++ "> "

-- | Extract folder with specified name from list
extractFolder :: FilePath -> [FSNode] -> [FSNode] -> Either String (FSNode, [FSNode])
extractFolder _ [] _        = Left "No such directory"
extractFolder s (n:ns) rest = if (name n == s)
                                then case n of
                                  (File _) -> Left "Is a file"
                                  _        -> Right (n, ns ++ rest)
                                else extractFolder s ns (n:rest)
                              where name (File info)     = filename info
                                    name (Folder info _) = foldername info

-- | Changes directory and returns new zipper on success
changeDirectory :: FSZipper -> [Direction] -> Either String FSZipper
changeDirectory z []     = Right z
changeDirectory z (d:ds) = let (node, crumbs) = z in
                             case d of
                               Cur -> changeDirectory z ds
                               Up  -> case crumbs of
                                          []     -> Left "You cannot left root directory"
                                          (c:cs) -> changeDirectory ((goUp node c, cs)) ds
                                             where goUp folder (FSCrumb info l) = Folder info (folder:l)
                               Down dir -> case node of
                                             File _ -> Left "Something wrong has happened"
                                             Folder info nodes -> case extractFolder dir nodes [] of
                                                        Right (found, rest) -> changeDirectory (found, (FSCrumb info rest):crumbs) ds
                                                        Left err            -> Left err
