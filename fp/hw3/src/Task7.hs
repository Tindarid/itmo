{-# LANGUAGE Rank2Types #-}

module Task7
    ( deleteIfEmpty
    , changeFilesExtTo
    , lsRecursively
    ) where

import Lens.Micro (traversed, (%~), (&), (^.), (^..), (^?), _tail)
import System.FilePath (replaceExtension)
import Task5

-- | Change extension of all files in directory (not recursively)
changeFilesExtTo :: String -> FS -> FS
changeFilesExtTo ext dir = dir & contents.traversed._file.name %~ (\old -> replaceExtension old ext)

-- | List directory contents recursively
lsRecursively :: FS -> [FilePath]
lsRecursively dir = (dir^..contentsRecursively.name)^._tail

-- | Deletes choosed directory, if it is empty (and is directory)
deleteIfEmpty :: FilePath -> FS -> FS
deleteIfEmpty path dir = dir & contents %~ (filter predicate)
  where
    predicate node = not (requested && empty)
      where
        requested = any (== path) (node^?_dir.name)
        empty     = any null (node^?_dir.contents)
